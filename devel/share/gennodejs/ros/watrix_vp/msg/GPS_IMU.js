// Auto-generated. Do not edit!

// (in-package watrix_vp.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GPS_IMU {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.GPSWeek = null;
      this.GPSTime = null;
      this.yaw = null;
      this.pitch = null;
      this.roll = null;
      this.latitude = null;
      this.longitude = null;
      this.altitude = null;
      this.velocity_earth = null;
      this.velocity_north = null;
      this.velocity_up = null;
      this.baseline = null;
      this.NSV1 = null;
      this.NSV2 = null;
      this.Status = null;
      this.position_covariance = null;
      this.angular_covariance = null;
      this.position_covariance_type = null;
      this.angular_covariance_type = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('GPSWeek')) {
        this.GPSWeek = initObj.GPSWeek
      }
      else {
        this.GPSWeek = 0.0;
      }
      if (initObj.hasOwnProperty('GPSTime')) {
        this.GPSTime = initObj.GPSTime
      }
      else {
        this.GPSTime = 0.0;
      }
      if (initObj.hasOwnProperty('yaw')) {
        this.yaw = initObj.yaw
      }
      else {
        this.yaw = 0.0;
      }
      if (initObj.hasOwnProperty('pitch')) {
        this.pitch = initObj.pitch
      }
      else {
        this.pitch = 0.0;
      }
      if (initObj.hasOwnProperty('roll')) {
        this.roll = initObj.roll
      }
      else {
        this.roll = 0.0;
      }
      if (initObj.hasOwnProperty('latitude')) {
        this.latitude = initObj.latitude
      }
      else {
        this.latitude = 0.0;
      }
      if (initObj.hasOwnProperty('longitude')) {
        this.longitude = initObj.longitude
      }
      else {
        this.longitude = 0.0;
      }
      if (initObj.hasOwnProperty('altitude')) {
        this.altitude = initObj.altitude
      }
      else {
        this.altitude = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_earth')) {
        this.velocity_earth = initObj.velocity_earth
      }
      else {
        this.velocity_earth = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_north')) {
        this.velocity_north = initObj.velocity_north
      }
      else {
        this.velocity_north = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_up')) {
        this.velocity_up = initObj.velocity_up
      }
      else {
        this.velocity_up = 0.0;
      }
      if (initObj.hasOwnProperty('baseline')) {
        this.baseline = initObj.baseline
      }
      else {
        this.baseline = 0.0;
      }
      if (initObj.hasOwnProperty('NSV1')) {
        this.NSV1 = initObj.NSV1
      }
      else {
        this.NSV1 = 0.0;
      }
      if (initObj.hasOwnProperty('NSV2')) {
        this.NSV2 = initObj.NSV2
      }
      else {
        this.NSV2 = 0.0;
      }
      if (initObj.hasOwnProperty('Status')) {
        this.Status = initObj.Status
      }
      else {
        this.Status = 0.0;
      }
      if (initObj.hasOwnProperty('position_covariance')) {
        this.position_covariance = initObj.position_covariance
      }
      else {
        this.position_covariance = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('angular_covariance')) {
        this.angular_covariance = initObj.angular_covariance
      }
      else {
        this.angular_covariance = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('position_covariance_type')) {
        this.position_covariance_type = initObj.position_covariance_type
      }
      else {
        this.position_covariance_type = 0;
      }
      if (initObj.hasOwnProperty('angular_covariance_type')) {
        this.angular_covariance_type = initObj.angular_covariance_type
      }
      else {
        this.angular_covariance_type = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GPS_IMU
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [GPSWeek]
    bufferOffset = _serializer.float64(obj.GPSWeek, buffer, bufferOffset);
    // Serialize message field [GPSTime]
    bufferOffset = _serializer.float64(obj.GPSTime, buffer, bufferOffset);
    // Serialize message field [yaw]
    bufferOffset = _serializer.float64(obj.yaw, buffer, bufferOffset);
    // Serialize message field [pitch]
    bufferOffset = _serializer.float64(obj.pitch, buffer, bufferOffset);
    // Serialize message field [roll]
    bufferOffset = _serializer.float64(obj.roll, buffer, bufferOffset);
    // Serialize message field [latitude]
    bufferOffset = _serializer.float64(obj.latitude, buffer, bufferOffset);
    // Serialize message field [longitude]
    bufferOffset = _serializer.float64(obj.longitude, buffer, bufferOffset);
    // Serialize message field [altitude]
    bufferOffset = _serializer.float64(obj.altitude, buffer, bufferOffset);
    // Serialize message field [velocity_earth]
    bufferOffset = _serializer.float64(obj.velocity_earth, buffer, bufferOffset);
    // Serialize message field [velocity_north]
    bufferOffset = _serializer.float64(obj.velocity_north, buffer, bufferOffset);
    // Serialize message field [velocity_up]
    bufferOffset = _serializer.float64(obj.velocity_up, buffer, bufferOffset);
    // Serialize message field [baseline]
    bufferOffset = _serializer.float64(obj.baseline, buffer, bufferOffset);
    // Serialize message field [NSV1]
    bufferOffset = _serializer.float64(obj.NSV1, buffer, bufferOffset);
    // Serialize message field [NSV2]
    bufferOffset = _serializer.float64(obj.NSV2, buffer, bufferOffset);
    // Serialize message field [Status]
    bufferOffset = _serializer.float64(obj.Status, buffer, bufferOffset);
    // Check that the constant length array field [position_covariance] has the right length
    if (obj.position_covariance.length !== 9) {
      throw new Error('Unable to serialize array field position_covariance - length must be 9')
    }
    // Serialize message field [position_covariance]
    bufferOffset = _arraySerializer.float64(obj.position_covariance, buffer, bufferOffset, 9);
    // Check that the constant length array field [angular_covariance] has the right length
    if (obj.angular_covariance.length !== 9) {
      throw new Error('Unable to serialize array field angular_covariance - length must be 9')
    }
    // Serialize message field [angular_covariance]
    bufferOffset = _arraySerializer.float64(obj.angular_covariance, buffer, bufferOffset, 9);
    // Serialize message field [position_covariance_type]
    bufferOffset = _serializer.uint8(obj.position_covariance_type, buffer, bufferOffset);
    // Serialize message field [angular_covariance_type]
    bufferOffset = _serializer.uint8(obj.angular_covariance_type, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GPS_IMU
    let len;
    let data = new GPS_IMU(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [GPSWeek]
    data.GPSWeek = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [GPSTime]
    data.GPSTime = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [yaw]
    data.yaw = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pitch]
    data.pitch = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [roll]
    data.roll = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [latitude]
    data.latitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [longitude]
    data.longitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [altitude]
    data.altitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velocity_earth]
    data.velocity_earth = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velocity_north]
    data.velocity_north = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [velocity_up]
    data.velocity_up = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [baseline]
    data.baseline = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [NSV1]
    data.NSV1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [NSV2]
    data.NSV2 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [Status]
    data.Status = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [position_covariance]
    data.position_covariance = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [angular_covariance]
    data.angular_covariance = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [position_covariance_type]
    data.position_covariance_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [angular_covariance_type]
    data.angular_covariance_type = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 266;
  }

  static datatype() {
    // Returns string type for a message object
    return 'watrix_vp/GPS_IMU';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bd3be3d3b3e80f56ec81dcd5aa6195fd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GPS_IMU(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.GPSWeek !== undefined) {
      resolved.GPSWeek = msg.GPSWeek;
    }
    else {
      resolved.GPSWeek = 0.0
    }

    if (msg.GPSTime !== undefined) {
      resolved.GPSTime = msg.GPSTime;
    }
    else {
      resolved.GPSTime = 0.0
    }

    if (msg.yaw !== undefined) {
      resolved.yaw = msg.yaw;
    }
    else {
      resolved.yaw = 0.0
    }

    if (msg.pitch !== undefined) {
      resolved.pitch = msg.pitch;
    }
    else {
      resolved.pitch = 0.0
    }

    if (msg.roll !== undefined) {
      resolved.roll = msg.roll;
    }
    else {
      resolved.roll = 0.0
    }

    if (msg.latitude !== undefined) {
      resolved.latitude = msg.latitude;
    }
    else {
      resolved.latitude = 0.0
    }

    if (msg.longitude !== undefined) {
      resolved.longitude = msg.longitude;
    }
    else {
      resolved.longitude = 0.0
    }

    if (msg.altitude !== undefined) {
      resolved.altitude = msg.altitude;
    }
    else {
      resolved.altitude = 0.0
    }

    if (msg.velocity_earth !== undefined) {
      resolved.velocity_earth = msg.velocity_earth;
    }
    else {
      resolved.velocity_earth = 0.0
    }

    if (msg.velocity_north !== undefined) {
      resolved.velocity_north = msg.velocity_north;
    }
    else {
      resolved.velocity_north = 0.0
    }

    if (msg.velocity_up !== undefined) {
      resolved.velocity_up = msg.velocity_up;
    }
    else {
      resolved.velocity_up = 0.0
    }

    if (msg.baseline !== undefined) {
      resolved.baseline = msg.baseline;
    }
    else {
      resolved.baseline = 0.0
    }

    if (msg.NSV1 !== undefined) {
      resolved.NSV1 = msg.NSV1;
    }
    else {
      resolved.NSV1 = 0.0
    }

    if (msg.NSV2 !== undefined) {
      resolved.NSV2 = msg.NSV2;
    }
    else {
      resolved.NSV2 = 0.0
    }

    if (msg.Status !== undefined) {
      resolved.Status = msg.Status;
    }
    else {
      resolved.Status = 0.0
    }

    if (msg.position_covariance !== undefined) {
      resolved.position_covariance = msg.position_covariance;
    }
    else {
      resolved.position_covariance = new Array(9).fill(0)
    }

    if (msg.angular_covariance !== undefined) {
      resolved.angular_covariance = msg.angular_covariance;
    }
    else {
      resolved.angular_covariance = new Array(9).fill(0)
    }

    if (msg.position_covariance_type !== undefined) {
      resolved.position_covariance_type = msg.position_covariance_type;
    }
    else {
      resolved.position_covariance_type = 0
    }

    if (msg.angular_covariance_type !== undefined) {
      resolved.angular_covariance_type = msg.angular_covariance_type;
    }
    else {
      resolved.angular_covariance_type = 0
    }

    return resolved;
    }
};

module.exports = GPS_IMU;
