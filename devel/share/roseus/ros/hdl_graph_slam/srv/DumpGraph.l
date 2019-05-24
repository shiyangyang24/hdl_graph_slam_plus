;; Auto-generated. Do not edit!


(when (boundp 'hdl_graph_slam::DumpGraph)
  (if (not (find-package "HDL_GRAPH_SLAM"))
    (make-package "HDL_GRAPH_SLAM"))
  (shadow 'DumpGraph (find-package "HDL_GRAPH_SLAM")))
(unless (find-package "HDL_GRAPH_SLAM::DUMPGRAPH")
  (make-package "HDL_GRAPH_SLAM::DUMPGRAPH"))
(unless (find-package "HDL_GRAPH_SLAM::DUMPGRAPHREQUEST")
  (make-package "HDL_GRAPH_SLAM::DUMPGRAPHREQUEST"))
(unless (find-package "HDL_GRAPH_SLAM::DUMPGRAPHRESPONSE")
  (make-package "HDL_GRAPH_SLAM::DUMPGRAPHRESPONSE"))

(in-package "ROS")





(defclass hdl_graph_slam::DumpGraphRequest
  :super ros::object
  :slots (_destination ))

(defmethod hdl_graph_slam::DumpGraphRequest
  (:init
   (&key
    ((:destination __destination) "")
    )
   (send-super :init)
   (setq _destination (string __destination))
   self)
  (:destination
   (&optional __destination)
   (if __destination (setq _destination __destination)) _destination)
  (:serialization-length
   ()
   (+
    ;; string _destination
    4 (length _destination)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _destination
       (write-long (length _destination) s) (princ _destination s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _destination
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _destination (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass hdl_graph_slam::DumpGraphResponse
  :super ros::object
  :slots (_success ))

(defmethod hdl_graph_slam::DumpGraphResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass hdl_graph_slam::DumpGraph
  :super ros::object
  :slots ())

(setf (get hdl_graph_slam::DumpGraph :md5sum-) "a8b810758ea760dd74984f070e767d53")
(setf (get hdl_graph_slam::DumpGraph :datatype-) "hdl_graph_slam/DumpGraph")
(setf (get hdl_graph_slam::DumpGraph :request) hdl_graph_slam::DumpGraphRequest)
(setf (get hdl_graph_slam::DumpGraph :response) hdl_graph_slam::DumpGraphResponse)

(defmethod hdl_graph_slam::DumpGraphRequest
  (:response () (instance hdl_graph_slam::DumpGraphResponse :init)))

(setf (get hdl_graph_slam::DumpGraphRequest :md5sum-) "a8b810758ea760dd74984f070e767d53")
(setf (get hdl_graph_slam::DumpGraphRequest :datatype-) "hdl_graph_slam/DumpGraphRequest")
(setf (get hdl_graph_slam::DumpGraphRequest :definition-)
      "
string destination
---
bool success

")

(setf (get hdl_graph_slam::DumpGraphResponse :md5sum-) "a8b810758ea760dd74984f070e767d53")
(setf (get hdl_graph_slam::DumpGraphResponse :datatype-) "hdl_graph_slam/DumpGraphResponse")
(setf (get hdl_graph_slam::DumpGraphResponse :definition-)
      "
string destination
---
bool success

")



(provide :hdl_graph_slam/DumpGraph "a8b810758ea760dd74984f070e767d53")


