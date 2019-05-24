;; Auto-generated. Do not edit!


(when (boundp 'watrix_vp::GPS_IMU)
  (if (not (find-package "WATRIX_VP"))
    (make-package "WATRIX_VP"))
  (shadow 'GPS_IMU (find-package "WATRIX_VP")))
(unless (find-package "WATRIX_VP::GPS_IMU")
  (make-package "WATRIX_VP::GPS_IMU"))

(in-package "ROS")
;;//! \htmlinclude GPS_IMU.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass watrix_vp::GPS_IMU
  :super ros::object
  :slots (_header _GPSWeek _GPSTime _yaw _pitch _roll _latitude _longitude _altitude _velocity_earth _velocity_north _velocity_up _baseline _NSV1 _NSV2 _Status _position_covariance _angular_covariance _position_covariance_type _angular_covariance_type ))

(defmethod watrix_vp::GPS_IMU
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:GPSWeek __GPSWeek) 0.0)
    ((:GPSTime __GPSTime) 0.0)
    ((:yaw __yaw) 0.0)
    ((:pitch __pitch) 0.0)
    ((:roll __roll) 0.0)
    ((:latitude __latitude) 0.0)
    ((:longitude __longitude) 0.0)
    ((:altitude __altitude) 0.0)
    ((:velocity_earth __velocity_earth) 0.0)
    ((:velocity_north __velocity_north) 0.0)
    ((:velocity_up __velocity_up) 0.0)
    ((:baseline __baseline) 0.0)
    ((:NSV1 __NSV1) 0.0)
    ((:NSV2 __NSV2) 0.0)
    ((:Status __Status) 0.0)
    ((:position_covariance __position_covariance) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:angular_covariance __angular_covariance) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:position_covariance_type __position_covariance_type) 0)
    ((:angular_covariance_type __angular_covariance_type) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _GPSWeek (float __GPSWeek))
   (setq _GPSTime (float __GPSTime))
   (setq _yaw (float __yaw))
   (setq _pitch (float __pitch))
   (setq _roll (float __roll))
   (setq _latitude (float __latitude))
   (setq _longitude (float __longitude))
   (setq _altitude (float __altitude))
   (setq _velocity_earth (float __velocity_earth))
   (setq _velocity_north (float __velocity_north))
   (setq _velocity_up (float __velocity_up))
   (setq _baseline (float __baseline))
   (setq _NSV1 (float __NSV1))
   (setq _NSV2 (float __NSV2))
   (setq _Status (float __Status))
   (setq _position_covariance __position_covariance)
   (setq _angular_covariance __angular_covariance)
   (setq _position_covariance_type (round __position_covariance_type))
   (setq _angular_covariance_type (round __angular_covariance_type))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:GPSWeek
   (&optional __GPSWeek)
   (if __GPSWeek (setq _GPSWeek __GPSWeek)) _GPSWeek)
  (:GPSTime
   (&optional __GPSTime)
   (if __GPSTime (setq _GPSTime __GPSTime)) _GPSTime)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:altitude
   (&optional __altitude)
   (if __altitude (setq _altitude __altitude)) _altitude)
  (:velocity_earth
   (&optional __velocity_earth)
   (if __velocity_earth (setq _velocity_earth __velocity_earth)) _velocity_earth)
  (:velocity_north
   (&optional __velocity_north)
   (if __velocity_north (setq _velocity_north __velocity_north)) _velocity_north)
  (:velocity_up
   (&optional __velocity_up)
   (if __velocity_up (setq _velocity_up __velocity_up)) _velocity_up)
  (:baseline
   (&optional __baseline)
   (if __baseline (setq _baseline __baseline)) _baseline)
  (:NSV1
   (&optional __NSV1)
   (if __NSV1 (setq _NSV1 __NSV1)) _NSV1)
  (:NSV2
   (&optional __NSV2)
   (if __NSV2 (setq _NSV2 __NSV2)) _NSV2)
  (:Status
   (&optional __Status)
   (if __Status (setq _Status __Status)) _Status)
  (:position_covariance
   (&optional __position_covariance)
   (if __position_covariance (setq _position_covariance __position_covariance)) _position_covariance)
  (:angular_covariance
   (&optional __angular_covariance)
   (if __angular_covariance (setq _angular_covariance __angular_covariance)) _angular_covariance)
  (:position_covariance_type
   (&optional __position_covariance_type)
   (if __position_covariance_type (setq _position_covariance_type __position_covariance_type)) _position_covariance_type)
  (:angular_covariance_type
   (&optional __angular_covariance_type)
   (if __angular_covariance_type (setq _angular_covariance_type __angular_covariance_type)) _angular_covariance_type)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _GPSWeek
    8
    ;; float64 _GPSTime
    8
    ;; float64 _yaw
    8
    ;; float64 _pitch
    8
    ;; float64 _roll
    8
    ;; float64 _latitude
    8
    ;; float64 _longitude
    8
    ;; float64 _altitude
    8
    ;; float64 _velocity_earth
    8
    ;; float64 _velocity_north
    8
    ;; float64 _velocity_up
    8
    ;; float64 _baseline
    8
    ;; float64 _NSV1
    8
    ;; float64 _NSV2
    8
    ;; float64 _Status
    8
    ;; float64[9] _position_covariance
    (* 8    9)
    ;; float64[9] _angular_covariance
    (* 8    9)
    ;; uint8 _position_covariance_type
    1
    ;; uint8 _angular_covariance_type
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _GPSWeek
       (sys::poke _GPSWeek (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _GPSTime
       (sys::poke _GPSTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _altitude
       (sys::poke _altitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity_earth
       (sys::poke _velocity_earth (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity_north
       (sys::poke _velocity_north (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity_up
       (sys::poke _velocity_up (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _baseline
       (sys::poke _baseline (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _NSV1
       (sys::poke _NSV1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _NSV2
       (sys::poke _NSV2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _Status
       (sys::poke _Status (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[9] _position_covariance
     (dotimes (i 9)
       (sys::poke (elt _position_covariance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _angular_covariance
     (dotimes (i 9)
       (sys::poke (elt _angular_covariance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; uint8 _position_covariance_type
       (write-byte _position_covariance_type s)
     ;; uint8 _angular_covariance_type
       (write-byte _angular_covariance_type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _GPSWeek
     (setq _GPSWeek (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _GPSTime
     (setq _GPSTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw
     (setq _yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _pitch
     (setq _pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _roll
     (setq _roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _altitude
     (setq _altitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity_earth
     (setq _velocity_earth (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity_north
     (setq _velocity_north (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity_up
     (setq _velocity_up (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _baseline
     (setq _baseline (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _NSV1
     (setq _NSV1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _NSV2
     (setq _NSV2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _Status
     (setq _Status (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[9] _position_covariance
   (dotimes (i (length _position_covariance))
     (setf (elt _position_covariance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _angular_covariance
   (dotimes (i (length _angular_covariance))
     (setf (elt _angular_covariance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; uint8 _position_covariance_type
     (setq _position_covariance_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _angular_covariance_type
     (setq _angular_covariance_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get watrix_vp::GPS_IMU :md5sum-) "bd3be3d3b3e80f56ec81dcd5aa6195fd")
(setf (get watrix_vp::GPS_IMU :datatype-) "watrix_vp/GPS_IMU")
(setf (get watrix_vp::GPS_IMU :definition-)
      "Header header


float64 GPSWeek

float64 GPSTime


#angular status

float64 yaw

float64 pitch

float64 roll






# Latitude [degrees]. Positive is north of equator; negative is south.
float64 latitude

# Longitude [degrees]. Positive is east of prime meridian; negative is west.
float64 longitude

# Altitude [m]. Positive is above the WGS 84 ellipsoid
# (quiet NaN if no altitude is available).
float64 altitude



float64 velocity_earth

float64 velocity_north


float64 velocity_up





float64 baseline




float64 NSV1

float64 NSV2



float64 Status


float64[9] position_covariance

float64[9] angular_covariance



uint8 position_covariance_type

uint8 angular_covariance_type
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :watrix_vp/GPS_IMU "bd3be3d3b3e80f56ec81dcd5aa6195fd")


