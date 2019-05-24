
(cl:in-package :asdf)

(defsystem "hdl_graph_slam-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "DumpGraph" :depends-on ("_package_DumpGraph"))
    (:file "_package_DumpGraph" :depends-on ("_package"))
    (:file "SaveMap" :depends-on ("_package_SaveMap"))
    (:file "_package_SaveMap" :depends-on ("_package"))
  ))