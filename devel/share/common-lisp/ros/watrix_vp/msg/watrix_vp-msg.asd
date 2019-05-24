
(cl:in-package :asdf)

(defsystem "watrix_vp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "GPS_IMU" :depends-on ("_package_GPS_IMU"))
    (:file "_package_GPS_IMU" :depends-on ("_package"))
  ))