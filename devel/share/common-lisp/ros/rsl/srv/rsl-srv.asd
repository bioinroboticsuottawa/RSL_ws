
(cl:in-package :asdf)

(defsystem "rsl-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ResetCalibration" :depends-on ("_package_ResetCalibration"))
    (:file "_package_ResetCalibration" :depends-on ("_package"))
  ))