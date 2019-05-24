; Auto-generated. Do not edit!


(cl:in-package hdl_graph_slam-srv)


;//! \htmlinclude DumpGraph-request.msg.html

(cl:defclass <DumpGraph-request> (roslisp-msg-protocol:ros-message)
  ((destination
    :reader destination
    :initarg :destination
    :type cl:string
    :initform ""))
)

(cl:defclass DumpGraph-request (<DumpGraph-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DumpGraph-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DumpGraph-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hdl_graph_slam-srv:<DumpGraph-request> is deprecated: use hdl_graph_slam-srv:DumpGraph-request instead.")))

(cl:ensure-generic-function 'destination-val :lambda-list '(m))
(cl:defmethod destination-val ((m <DumpGraph-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hdl_graph_slam-srv:destination-val is deprecated.  Use hdl_graph_slam-srv:destination instead.")
  (destination m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DumpGraph-request>) ostream)
  "Serializes a message object of type '<DumpGraph-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'destination))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'destination))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DumpGraph-request>) istream)
  "Deserializes a message object of type '<DumpGraph-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'destination) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'destination) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DumpGraph-request>)))
  "Returns string type for a service object of type '<DumpGraph-request>"
  "hdl_graph_slam/DumpGraphRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DumpGraph-request)))
  "Returns string type for a service object of type 'DumpGraph-request"
  "hdl_graph_slam/DumpGraphRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DumpGraph-request>)))
  "Returns md5sum for a message object of type '<DumpGraph-request>"
  "a8b810758ea760dd74984f070e767d53")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DumpGraph-request)))
  "Returns md5sum for a message object of type 'DumpGraph-request"
  "a8b810758ea760dd74984f070e767d53")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DumpGraph-request>)))
  "Returns full string definition for message of type '<DumpGraph-request>"
  (cl:format cl:nil "~%string destination~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DumpGraph-request)))
  "Returns full string definition for message of type 'DumpGraph-request"
  (cl:format cl:nil "~%string destination~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DumpGraph-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'destination))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DumpGraph-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DumpGraph-request
    (cl:cons ':destination (destination msg))
))
;//! \htmlinclude DumpGraph-response.msg.html

(cl:defclass <DumpGraph-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DumpGraph-response (<DumpGraph-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DumpGraph-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DumpGraph-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hdl_graph_slam-srv:<DumpGraph-response> is deprecated: use hdl_graph_slam-srv:DumpGraph-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <DumpGraph-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hdl_graph_slam-srv:success-val is deprecated.  Use hdl_graph_slam-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DumpGraph-response>) ostream)
  "Serializes a message object of type '<DumpGraph-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DumpGraph-response>) istream)
  "Deserializes a message object of type '<DumpGraph-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DumpGraph-response>)))
  "Returns string type for a service object of type '<DumpGraph-response>"
  "hdl_graph_slam/DumpGraphResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DumpGraph-response)))
  "Returns string type for a service object of type 'DumpGraph-response"
  "hdl_graph_slam/DumpGraphResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DumpGraph-response>)))
  "Returns md5sum for a message object of type '<DumpGraph-response>"
  "a8b810758ea760dd74984f070e767d53")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DumpGraph-response)))
  "Returns md5sum for a message object of type 'DumpGraph-response"
  "a8b810758ea760dd74984f070e767d53")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DumpGraph-response>)))
  "Returns full string definition for message of type '<DumpGraph-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DumpGraph-response)))
  "Returns full string definition for message of type 'DumpGraph-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DumpGraph-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DumpGraph-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DumpGraph-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DumpGraph)))
  'DumpGraph-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DumpGraph)))
  'DumpGraph-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DumpGraph)))
  "Returns string type for a service object of type '<DumpGraph>"
  "hdl_graph_slam/DumpGraph")