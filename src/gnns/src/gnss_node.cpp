#include "ros/ros.h"
#include "std_msgs/String.h"
#include <visualization_msgs/Marker.h>
#include <sstream>
#include <iostream>
#include <watrix_vp/GPS_IMU.h>
#include <sensor_msgs/NavSatFix.h>
#include <queue>
#include <mutex>
#include <cmath>
#include <geometry_msgs/Pose.h>
#include <eigen3/Eigen/Dense>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geodesy/utm.h>
#include <geodesy/wgs84.h>
#include <geographic_msgs/GeoPointStamped.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <sensor_msgs/PointCloud2.h>

watrix_vp::GPS_IMU gpsReset0;

using namespace std;
class Vehicle_Localization{
private:
	ros::NodeHandle nh;

    ros::Subscriber subGps;
	ros::Subscriber subLidarXYZ;
	ros::Subscriber subLidarXYZ2;

	ros::Subscriber time_sub;
	ros::Publisher marker_pub;  //rviz可视化;

    ros::Publisher pubPosLLH;     
    ros::Publisher pubPosXYZ;
	ros::Publisher pose_rpy_publisher;//无遮挡的gps消息发布
	ros::Publisher sim_odom_pub;     //模拟里程计发布值
	ros::Publisher Pure_inertial_pub;    //纯惯导积分里程

	ros::Publisher use_lidar_pub;
	
	watrix_vp::GPS_IMU last_gps;
	watrix_vp::GPS_IMU new_gps_point0;
	watrix_vp::GPS_IMU new_gps_point1;

	watrix_vp::GPS_IMU finalPosOutput;

	std::mutex utmpose_queue_mutex;    //互斥锁
	std::queue<Eigen::Matrix<double, 3, 1> > utmpose_queue;

	geodesy::UTMPoint utm0;  
	geodesy::UTMPoint utm1;      //初始化的gps坐标值
	geodesy::UTMPoint gps_utm;      //无遮挡情况下gps的utm坐标值
	geometry_msgs::Pose gps_utm_coordinate;//刚进入遮挡区域记录的gps的信号

	ros::Time begin;
	ros::Time begin1;
	ros::Time begin2;
	ros::Time current_time, last_time;
	ros::Time time_cur1,time_pre1;
	ros::Time time_cur2,time_pre2;

	geometry_msgs::Point gps_or_lidar_msg;

	char band;
	int zone;
	char band1;
	int zone1;
	double dt_out;
	double dt_in;

	//里程计初始值:
    double x;
    double y;
    double th;   //先忽略角度

	int count_gps;   //防止gps和lidar之间跳变

	//记录时间参数
	bool time_flag;
	double dt;
	double t_init;
	double begin_1;

	bool time_flag1;
	bool time_flag2;

	bool use_lidar;
	bool init_gps;
	bool marker_flag;
	Eigen::Matrix<double, 3, 1> first_pose;
	Eigen::Vector3d  currentXYZ;   //当前接收到的
	Eigen::Vector3d  utmXYZ;       //东北天XYZ
	Eigen::Vector3d  utm_from_origin; 
	Eigen::Matrix3d  R0;
	Eigen::Matrix3d  R0_;
	Eigen::Vector3d  zero_utm;
	::Eigen::Matrix3d R;
	Eigen::Quaterniond q;

	Eigen::Isometry3d T_lidar;    //lidar    start     T 

	visualization_msgs::Marker points, line_strip, line_list;   //rviz marker


public:
	Vehicle_Localization():nh("~"){
		subGps = nh.subscribe<watrix_vp::GPS_IMU>("/fusion_pose/chatter", 1, &Vehicle_Localization::GpsHandler, this);

		subLidarXYZ = nh.subscribe<geometry_msgs::PoseStamped>("/lidar_XYZ", 1, &Vehicle_Localization::lidarXYZHandler, this);  ///aft_mapped_to_init
		//subLidarXYZ2 = nh.subscribe<nav_msgs::Odometry>("/vehicle/global_localization", 1, &Vehicle_Localization::lidarXYZHandler2, this); 
     
        pubPosLLH = nh.advertise<watrix_vp::GPS_IMU> ("/final_gps", 1);

		pose_rpy_publisher = nh.advertise<geometry_msgs::Pose> ("/lidar/first_pose", 1);

		marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 10);

		sim_odom_pub = nh.advertise<nav_msgs::Odometry>("/simulation/odom", 50);

		Pure_inertial_pub = nh.advertise<nav_msgs::Odometry>("/Pure_inertial/odom", 50);   //由惯导数据得出

		use_lidar_pub = nh.advertise<geometry_msgs::Point> ("/use_lidar/may_or_not", 1);

		//主要是为了使用点云时间戳,使图优化关键帧ndt与odom的时间戳对齐,然后进行图优化;
		time_sub = nh.subscribe("/filtered_points", 256, &Vehicle_Localization::pointcloud_callback, this);

	    resetParameters();
	}

	void resetParameters(){

		init_gps = false;
		use_lidar = false;
		time_flag = false;
		marker_flag = false;
		dt_out = 0;
		dt_in = 0;
		dt = 0;
		t_init = 0;
		begin_1 = 0;
		x = 0.0;
		y = 0.0;
		th = 0.0;
		begin = ros::Time::now();

		begin1 = ros::Time::now();
		current_time = ros::Time::now();
  		last_time = ros::Time::now();
		time_cur1 = ros::Time::now();
		time_pre1 = ros::Time::now();
		time_cur2 = ros::Time::now();
		time_pre2 = ros::Time::now();
		count_gps = 0;
		time_flag1 = false;
		time_flag2 = false;


			points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/map";
			points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
			points.ns = line_strip.ns = line_list.ns = "gnss_node";
			points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
			points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;		 

			//分配三个不同的id到三个markers
			points.id = 0;
			line_strip.id = 1;
			line_list.id = 2;

			//设置marker类型到 POINTS, LINE_STRIP 和 LINE_LIST
			points.type = visualization_msgs::Marker::POINTS;
			line_strip.type = visualization_msgs::Marker::LINE_STRIP;
			line_list.type = visualization_msgs::Marker::LINE_LIST;

			//设置点和线的大小和颜色;

			// scale成员对于这些marker类型是不同的,POINTS marker分别使用x和y作为宽和高，然而LINE_STRIP和LINE_LIST marker仅仅使用x，定义为线的宽度。单位是米。
			points.scale.x = 0.5;
			points.scale.y = 0.5;

			// LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
			line_strip.scale.x = 0.1;
			line_list.scale.x = 0.1;



			// 点为绿色
			points.color.g = 1.0f;
			points.color.a = 1.0;

			// Line strip 是蓝色
			line_strip.color.b = 1.0;
			line_strip.color.a = 1.0;

			// Line list 为红色
			line_list.color.r = 1.0;
			line_list.color.a = 1.0;
	}


	virtual ~Vehicle_Localization(){}

	//gps起始点坐标
	//geodesy::UTMPoint start_pose(const )

	void pointcloud_callback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg){
		//只需要使用时间戳
		begin = cloud_msg->header.stamp;
	}

	void sim_odom_calculate(double time_delta){

		double vx = 1.4175;
  		double vy = -0.3709;
  		double vth = 0.1;

		tf::TransformBroadcaster odom_broadcaster;


		double dt1 = 0.5;
		/*
		double delta_x = (vx * cos(th) - vy * sin(th)) * dt; 
		double delta_y = (vx * sin(th) + vy * cos(th)) * dt; 
		double delta_th = vth * dt; 
		*/
		double delta_x = vx *time_delta; 
		double delta_y = vy *time_delta; 
		double delta_z = 0; 
		double delta_th = vth * time_delta; 
		x += delta_x; 
		y += delta_y; 
		th += delta_th;

		Eigen::Vector3d ohyeah(x,y,1.0);
		Eigen::Vector3d p_odom = T_lidar.inverse() *(ohyeah + utm_from_origin);

		//std::cout << "里程计位置x : " << (ohyeah + utm_from_origin) << std::endl;

		//通过tf发布出去
		//since all odometry is 6DOF we'll need a quaternion created from yaw 
		geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

		 //first, we'll publish the transform over tf 
		 geometry_msgs::TransformStamped odom_trans; 
		 odom_trans.header.stamp = begin; 
		 odom_trans.header.frame_id = "sim_odom"; 
		 odom_trans.child_frame_id = "base_link"; 
		 odom_trans.transform.translation.x = p_odom.x(); 
		 odom_trans.transform.translation.y = p_odom.y(); 
		 odom_trans.transform.translation.z = p_odom.z(); 
		 odom_trans.transform.rotation = odom_quat;

    	//send the transform
    	odom_broadcaster.sendTransform(odom_trans);

		//next, we'll publish the odometry message over ROS 
		nav_msgs::Odometry odom; 
		odom.header.stamp = begin; 
		odom.header.frame_id = "sim_odom";

		 //set the position 
		 odom.pose.pose.position.x = x; 
		 odom.pose.pose.position.y = y; 
		 odom.pose.pose.position.z = 0.0; 
		 odom.pose.pose.orientation = odom_quat; 
		 //set the velocity 
		 odom.child_frame_id = "base_link"; 
		 odom.twist.twist.linear.x = vx; 
		 odom.twist.twist.linear.y = vy; 
		 odom.twist.twist.angular.z = vth; 
		 
		 //publish the message 
		 sim_odom_pub.publish(odom);

	}



	void GpsHandler(const watrix_vp::GPS_IMU gps){
		
		//判断if sat1>=4 &&sat2>=4
		if(gps.NSV1<10 || gps.NSV2<10)
		{
			dt_in = 0;
			time_flag2 = false;
			if (false == use_lidar)
			{
					//判断站外gps切换情况;
					//这里首先记录小于10的时间
					//double begin1;
					time_cur1 = ros::Time::now();
					//double begin_1;
					if(time_flag1 ==false){
						time_pre1 = time_cur1;
						time_flag1 = true;
					}
				
				
				

					dt_out += (time_cur1.toSec() - time_pre1.toSec());

					std::cout << "站外切换时间差" << dt_out << std::endl;
					//std::cout << "切换时间差-->" << gps.header.stamp.toSec() << std::endl;

					if(dt_out < 8){  //继续使用纯gps定位
						finalPosOutput = gps;
						geographic_msgs::GeoPoint gps_utm_pose1;
						gps_utm_pose1.latitude = gps.latitude; 
						gps_utm_pose1.longitude = gps.longitude;
						gps_utm_pose1.altitude = gps.altitude;
						geodesy::fromMsg(gps_utm_pose1, gps_utm);

						Eigen::Vector3d xyz_gps1(gps_utm.easting, gps_utm.northing, gps_utm.altitude);

						utm_from_origin = xyz_gps1 - first_pose;

						//std::lock_guard<std::mutex> lock(utmpose_queue_mutex);
						utmpose_queue.push(utm_from_origin);

						pubPosLLH.publish(finalPosOutput);
						std::cout << "gps还可以的情况下------>"<<utm_from_origin << std::endl;
					}
					if(dt_out >= 8){
						use_lidar = true;//开始用激光雷达定位
					}
					time_pre1 = time_cur1;
			}



				if(use_lidar == true){  //gps切换为激光雷达;

						//当使用激光雷达时候

						new_gps_point0 = gps;                                                  //---------->new_gps_point0
						
						//记录刚刚进站点的gps
						
						R0 = Eule2R_((90 - new_gps_point0.yaw)*M_PI/180,new_gps_point0.pitch*M_PI/180,new_gps_point0.roll*M_PI/180);   //---------->R
						//R0 = Eule2R_(M_PI/2,0,0);
						geographic_msgs::GeoPoint gps0_msg;

						gps0_msg.latitude = new_gps_point0.latitude; 
						gps0_msg.longitude = new_gps_point0.longitude;
						gps0_msg.altitude = new_gps_point0.altitude;
						
						// convert (latitude, longitude, altitude) -> (easting, northing, altitude) in UTM coordinate			
						geodesy::fromMsg(gps0_msg, utm0);

						Eigen::Vector3d xyz(utm0.easting, utm0.northing, utm0.altitude);

						zero_utm = xyz;
						band = utm0.band;
						zone = utm0.zone;

						//q.x() = gps0_msg.orientation.x;
						double z_yaw = atan2(utm_from_origin.y(),utm_from_origin.x());
						
						double angle_z = (z_yaw*180)/M_PI;
						//std::cout << "z_yaw" << angle_z << "imu角度"<< gps.yaw << std::endl;


						//记录刚进站的gps值;因为ndt匹配需要用到角度值;
						::Eigen::Vector3d ea0(z_yaw,0,0);
						
						R = ::Eigen::AngleAxisd(ea0[0], ::Eigen::Vector3d::UnitZ())  
						* ::Eigen::AngleAxisd(ea0[1], ::Eigen::Vector3d::UnitY())  
						* ::Eigen::AngleAxisd(ea0[2], ::Eigen::Vector3d::UnitX());  

						
						q = R0;
						Eigen::Isometry3d start_T(q);
						T_lidar = start_T;
						T_lidar.pretranslate(::Eigen::Vector3d(utm_from_origin.x(),utm_from_origin.y(),utm_from_origin.z()));
						//std::cout << T_lidar.matrix() << std::endl;

						

						

						gps_utm_coordinate.position.x = xyz.x();
						gps_utm_coordinate.position.y = xyz.y();
						gps_utm_coordinate.position.z = xyz.z();
						gps_utm_coordinate.orientation.x = q.x();
						gps_utm_coordinate.orientation.y = q.y();
						gps_utm_coordinate.orientation.z = q.z();	
						gps_utm_coordinate.orientation.w = q.w();
						pose_rpy_publisher.publish(gps_utm_coordinate);    //只发布刚进站的一次,主要是传递角度

						use_lidar = true;
						//count_gps = 0;
						//std::cout<<"we use lidar-->"<<std::endl;

					}



				}
				



				//std::cout<<"utm0-->X="<<utm0.easting<<" Y="<< utm0.northing<<" Z="<<utm0.altitude <<" band="<<utm0.band<<std::endl;
				//std::cout<<"gps0_msg-->lat="<<gps0_msg.latitude<<" lon="<< gps0_msg.longitude<<" alt="<<gps0_msg.altitude <<std::endl;
				//printf("gps0_msg-->lat=%lf ,lon=%lf ,alt=%lf",gps0_msg.latitude, gps0_msg.longitude,gps0_msg.altitude);

				//同时打开gps约束;
			/*
			else{
					//在遮挡区域(站内),由纯惯导推出来的gps值转换成utm坐标,在减去起始位置进行定位

					geographic_msgs::GeoPoint gps1_msg;   //由纯惯导推算的gps值

					gps1_msg.latitude = gps.latitude; 
					gps1_msg.longitude = gps.longitude;
					gps1_msg.altitude = gps.altitude;
					
					geodesy::UTMPoint utm2;
					// convert (latitude, longitude, altitude) -> (easting, northing, altitude) in UTM coordinate			
					geodesy::fromMsg(gps1_msg, utm2);

					Eigen::Vector3d xyz_state(utm2.easting, utm2.northing, utm2.altitude);

					Eigen::Vector3d interial_utm = xyz_state - first_pose;

					//ROS_INFO("纯惯导积分位置: [%f] [%f] [%f]", interial_utm.x(),interial_utm.y(), interial_utm.z());

					//将纯惯导的积分位置发布出去用于激光slam定位,用到x,y,z,还有四元数信息


				}
		}
		*/

				
			
		else{//纯gps定位


			time_flag1 = false;
			dt_out = 0;

			if (use_lidar == true)
				{
					//判断站外gps切换情况;
					//这里首先记录小于10的时间
					//double begin1;
					time_cur2 = ros::Time::now();
					//double begin_1;
					if(time_flag2 ==false){
						time_pre2 = time_cur2;
						time_flag2 = true;
					}
				
				
				

					dt_in += (time_cur2.toSec() - time_pre2.toSec());

					std::cout << "内部切换时间差" << dt_in << std::endl;




					if(dt_in >= 10){
						use_lidar = false;
					}

					time_pre2 = time_cur2;

				}


			

			//判断站内gps切换情况
			if(use_lidar == false){

			
			//if(dt_in>=10){

			
				if(init_gps == true){

					finalPosOutput = gps;
					geographic_msgs::GeoPoint gps_utm_pose;
					gps_utm_pose.latitude = gps.latitude; 
					gps_utm_pose.longitude = gps.longitude;
					gps_utm_pose.altitude = gps.altitude;
					geodesy::fromMsg(gps_utm_pose, gps_utm);

					Eigen::Vector3d xyz_gps(gps_utm.easting, gps_utm.northing, gps_utm.altitude);

					utm_from_origin = xyz_gps - first_pose;

					//std::lock_guard<std::mutex> lock(utmpose_queue_mutex);
					utmpose_queue.push(utm_from_origin);

					pubPosLLH.publish(finalPosOutput);
					std::cout << "gps良好的情况下"<<utm_from_origin << std::endl;


					//pose_rpy_publisher.publish(gps_utm_coordinate);

					std::cout<<"GpsHandler---publish"<<std::endl;
					use_lidar = false;
					x = 0;
					y = 0;
					//z = 0;
				}
				else{
					//记录gps的初始位置,以初始位置为坐标原点;
					new_gps_point1 = gps;
					geographic_msgs::GeoPoint gps1_msg;

					gps1_msg.latitude = new_gps_point1.latitude; 
					gps1_msg.longitude = new_gps_point1.longitude;
					gps1_msg.altitude = new_gps_point1.altitude;
					
					// convert (latitude, longitude, altitude) -> (easting, northing, altitude) in UTM coordinate			
					geodesy::fromMsg(gps1_msg, utm1);

					Eigen::Vector3d xyz(utm1.easting, utm1.northing, utm1.altitude);
					band1 = utm1.band;
					zone1 = utm1.zone;
					

					const Eigen::Matrix<double, 3, 1> temp_xyz = xyz;

					first_pose = temp_xyz;   //只是记录原点
				

					if(utmpose_queue.size() < 1){
						utmpose_queue.push(first_pose);
					}

					init_gps = 1;				
				}
			

		  }
		
		}

		gps_or_lidar_msg.x = double(use_lidar);
		gps_or_lidar_msg.y = dt_out;
		gps_or_lidar_msg.z = dt_in;
		use_lidar_pub.publish(gps_or_lidar_msg);

		flush_utmpose_queue();
		//creat_gps_lidar_marker(utmpose_queue);
			
	}

/*
	void lidarXYZHandler2(const nav_msgs::Odometry odom){
		
		currentXYZ.x() = odom.pose.pose.position.x;
		currentXYZ.y() = odom.pose.pose.position.x;
		currentXYZ.y() = odom.pose.pose.position.x;

		std::cout<<" lidarXYZHandler2!!!"<<std::endl;

		if (true == use_lidar)    //subLidarXYZ 到位
	    {	

			//utmXYZ = R0.transpose()  * currentXYZ;
			utmXYZ = R0.transpose()* currentXYZ;
			std::cout<<" R0:"<< R0 <<std::endl;
			std::cout<<" input-->X="<<currentXYZ.x()<<"  Y="<< currentXYZ.y()<<"  Z="<<currentXYZ.z() <<std::endl;
			std::cout<<" utmXYZ-->X="<<utmXYZ.x()<<"  Y="<< utmXYZ.y()<<"  Z="<<utmXYZ.z() <<std::endl;
			
			utmXYZ = zero_utm + utmXYZ;
			//utmXYZ -= zero_utm;
			geodesy::UTMPoint temp_xyz;
			temp_xyz.easting  = utmXYZ.x();
			temp_xyz.northing = utmXYZ.y();
			temp_xyz.altitude = utmXYZ.z();
			temp_xyz.band = band;
			temp_xyz.zone = zone;

			std::cout<<"temp_xyz-->X="<<temp_xyz.easting<<" Y="<< temp_xyz.northing<<" Z="<<temp_xyz.altitude<<  temp_xyz.band <<std::endl;

			geographic_msgs::GeoPoint gps_msg_out;

			gps_msg_out = 	geodesy::toMsg (temp_xyz);  //test utm0  
			//gps_msg_out = 	geodesy::toMsg (utm0);
			
			finalPosOutput.latitude = gps_msg_out.latitude;
			finalPosOutput.longitude = gps_msg_out.longitude;
			finalPosOutput.altitude = gps_msg_out.altitude;
			
			pubPosLLH.publish(finalPosOutput);
			//std::cout<<"finalPosOutput-->lat="<<finalPosOutput.latitude<<" lon="<< finalPosOutput.longitude<<" alt="<<finalPosOutput.altitude <<std::endl;
			printf("finalPosOutput-->lat=%lf ,lon=%lf ,alt=%lf",finalPosOutput.latitude, finalPosOutput.longitude,finalPosOutput.altitude);

			std::cout<<"lidarXYZHandler---publish"<<std::endl;

			
		}

	}
	*/

	void lidarXYZHandler(const geometry_msgs::PoseStamped msg){

		if(time_flag == false){
			t_init = msg.header.stamp.toSec();
			time_flag = true;
		}

		if(time_flag ==true){
			//ros::Time const begin = msg.header.stamp;
			dt = msg.header.stamp.toSec() - t_init;
			//secs = -10000 *secs;
			//std::cout << "时间" << dt << std::endl;

		}

		
		current_time = ros::Time::now();

 	//compute odometry in a typical way given the velocities of the robot 
		double dt_ = (current_time - last_time).toSec(); 

		if(dt_>17){
			dt_ = 1.546;
		}

		//std::cout << "两次时间差值" << dt_ << std::endl;

		//使用里程计定位;
		sim_odom_calculate(dt_);
		
		//Eigen::Isometry3d pose_gps(q);
		
		currentXYZ.x() = msg.pose.position.x;    
		currentXYZ.y() = msg.pose.position.y;
		currentXYZ.z() = msg.pose.position.z;
		

		//Eigen::Vector3d init1(gps_utm_coordinate.position.x,gps_utm_coordinate.position.y,gps_utm_coordinate.position.z);
		//pose_gps.pretranslate(Eigen::Vector3d(gps_utm_coordinate.position.x,gps_utm_coordinate.position.y,gps_utm_coordinate.position.z));

		Eigen::Vector3d lidar_first_from_gps = Eigen::Vector3d(gps_utm_coordinate.position.x,gps_utm_coordinate.position.y,gps_utm_coordinate.position.z);

/********************************************
		Eigen::Quaterniond q_lidar;
		q_lidar.x() = msg.orientation.x;
		q_lidar.y() = msg.orientation.y;
		q_lidar.z() = msg.orientation.z;
		q_lidar.w() = msg.orientation.w;


		Eigen::AngleAxisd rotation_vector(q_lidar);
		Eigen::Matrix3d rotation_matrix;
        rotation_matrix=q_lidar.matrix();


		Eigen::Isometry3d pose_lidar(q_lidar);
		pose_lidar.pretranslate(Eigen::Vector3d(msg.position.x,msg.position.y,msg.position.z));

		std::cout << pose_lidar.matrix() << std::endl;
***********************************************************/
//y方向误差建模:

		double error_y = 0.1448 *dt;





		if (true == use_lidar)    //subLidarXYZ 到位
	    {	

			//utmXYZ = R0.transpose()  * currentXYZ;
			//utmXYZ = R* currentXYZ;
			//std::cout<<" R0:"<< R0 <<std::endl;
			//currentXYZ = gg - first_pose;
			currentXYZ = Eigen::Vector3d(msg.pose.position.x,msg.pose.position.y,msg.pose.position.z);
			//std::cout<<" gg-->X="<<gg.x()<<"  Y="<< gg.y()<<"  Z="<<gg.z() <<std::endl;
			//std::cout<<" 初始匹配值-->X="<<init1.x()<<"  Y="<< init1.y()<<"  Z="<<init1.z() <<std::endl;
			//std::cout<<" 初始位置-->X="<<first_pose.x()<<"  Y="<< first_pose.y()<<"  Z="<<first_pose.z() <<std::endl;




			//Eigen::Vector3d pose_lidar_in_utm = (R.transpose()) *currentXYZ;
			Eigen::Vector3d pose_lidar_in_utm = T_lidar *currentXYZ;

			Eigen::Vector3d ppp = T_lidar.translation() + currentXYZ;

			std::cout << currentXYZ << std::endl;

			//std::cout<<"激光slam-->X="<<pose_lidar_in_utm.x()<<" Y="<< pose_lidar_in_utm.y() <<" Z="<<pose_lidar_in_utm.z()<< std::endl;

			std::cout<<"进站-->X="<<ppp.x()<<" Y="<< ppp.y() <<" Z="<<ppp.z()<< std::endl;

			//utmXYZ = init1 - utmXYZ;
			//utmXYZ = Eigen::Vector3d(pose1(0,3),pose1(1,3),pose1(2,3));

			//先不考虑这种方式;
			//utm_from_origin = pose_lidar_in_utm + lidar_first_from_gps - first_pose;

			//utm_from_origin = Eigen::Vector3d(utm_from_origin.x,utm_from_origin.y() + error_y,utm_from_origin.z());

			//std::cout<<"utm_from_origin-->X="<<utm_from_origin.x()<<" Y="<< utm_from_origin.y() <<" Z="<<utm_from_origin.z()<< std::endl;

			std::lock_guard<std::mutex> lock(utmpose_queue_mutex);
			utmpose_queue.push(ppp);			



			//utmXYZ -= zero_utm;
			geodesy::UTMPoint temp_xyz;
			temp_xyz.easting  = (pose_lidar_in_utm + lidar_first_from_gps).x();
			temp_xyz.northing = (pose_lidar_in_utm + lidar_first_from_gps).y();
			temp_xyz.altitude = (pose_lidar_in_utm + lidar_first_from_gps).z();
			temp_xyz.band = band;
			temp_xyz.zone = zone;

			

			geographic_msgs::GeoPoint gps_msg_out;

			gps_msg_out = 	geodesy::toMsg (temp_xyz);  //test utm0  
			//gps_msg_out = 	geodesy::toMsg (utm0);
			
			finalPosOutput.latitude = gps_msg_out.latitude;
			finalPosOutput.longitude = gps_msg_out.longitude;
			finalPosOutput.altitude = gps_msg_out.altitude;
			
			pubPosLLH.publish(finalPosOutput);
			//std::cout<<"finalPosOutput-->lat="<<finalPosOutput.latitude<<" lon="<< finalPosOutput.longitude<<" alt="<<finalPosOutput.altitude <<std::endl;
			//printf("finalPosOutput-->lat=%lf ,lon=%lf ,alt=%lf",finalPosOutput.latitude, finalPosOutput.longitude,finalPosOutput.altitude);

			std::cout<<"lidarXYZHandler---publish"<<std::endl;

			last_time = current_time;

			//flush_utmpose_queue()
		}
		
	}


	//utm 队列
  void flush_utmpose_queue() {

		std::lock_guard<std::mutex> lock(utmpose_queue_mutex);

		if(utmpose_queue.empty()) {
			return;
		}

		for(int i=0;i<utmpose_queue.size();i++){
			creat_gps_lidar_marker(utmpose_queue.front());
			utmpose_queue.pop();
		}
		return;
	}


	Eigen::Matrix3d Eule2R_(const double &yaw,const double &pitch ,const double &roll){
		Eigen::AngleAxisd rollAngle(Eigen::AngleAxisd(roll,Eigen::Vector3d::UnitX()));
		Eigen::AngleAxisd pitchAngle(Eigen::AngleAxisd(pitch,Eigen::Vector3d::UnitY()));
		Eigen::AngleAxisd yawAngle(Eigen::AngleAxisd(yaw,Eigen::Vector3d::UnitZ()));
		
		
		Eigen::Matrix3d  R;
		return R = yawAngle*pitchAngle*rollAngle; 
	}
	void publishPos(){
		pubPosLLH.publish(finalPosOutput);
 	}


	 void creat_gps_lidar_marker(Eigen::Matrix<double, 3, 1>  &car_pose){  //对副本进行操作
    	/*创建一个 visualization_msgs/Marker消息，并且初始化所有共享的数据。消息成员默认为0，仅仅设置位姿成员w。
		POINTS类型在每个点添加的位置放置一个点。LINE_STRIP类型将每个点用作一个连接的线中的定点，
		其中点0和点1连接，1和2连接，等等。LINE_LIST类型在每对点外创建一个不相连的线，也就是0连接1,2连接3，等等。

		*/

		//if(marker_flag == false){

		//std::cout <<"women" << car_pose << std::endl;

		//}


		//for(int i=0;i<1;i++){

			geometry_msgs::Point p;
			p.x = car_pose.x();
			p.y = car_pose.y();
			p.z = 1.8;
			//car_pose_queue.pop();
			//p.position.x = car_pose.x();

			points.points.push_back(p);
			line_strip.points.push_back(p);

		// The line list needs two points for each line
			line_list.points.push_back(p);
			p.z += 1.0;
			line_list.points.push_back(p);

		//}
		


        //p.z = 0.0;
        //line_list.points.push_back(p);

		//发布各个markers
		marker_pub.publish(points);
		marker_pub.publish(line_strip);
		marker_pub.publish(line_list);

	}

};

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char *argv[])
{
	
	ros::init(argc, argv, "gnss_node");

	Vehicle_Localization VL;

	ROS_INFO("------>gnss node Started.");

    ros::spin();
	return 0;
}