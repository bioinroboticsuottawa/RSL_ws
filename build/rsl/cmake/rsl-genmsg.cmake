# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "rsl: 4 messages, 1 services")

set(MSG_I_FLAGS "-Irsl:/home/dzhi/catkin_ws/src/rsl/msg;-Isensor_msgs:/opt/ros/indigo/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(rsl_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg" NAME_WE)
add_custom_target(_rsl_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rsl" "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg" "geometry_msgs/Vector3:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg" NAME_WE)
add_custom_target(_rsl_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rsl" "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg" "geometry_msgs/Vector3:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg" NAME_WE)
add_custom_target(_rsl_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rsl" "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg" "rsl/LeapGesture:geometry_msgs/Point:rsl/LeapHand:geometry_msgs/Vector3:std_msgs/Header:rsl/LeapPointable"
)

get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg" NAME_WE)
add_custom_target(_rsl_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rsl" "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg" "geometry_msgs/Vector3:geometry_msgs/Point"
)

get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv" NAME_WE)
add_custom_target(_rsl_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rsl" "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
)
_generate_msg_cpp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
)
_generate_msg_cpp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg"
  "${MSG_I_FLAGS}"
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
)
_generate_msg_cpp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
)

### Generating Services
_generate_srv_cpp(rsl
  "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
)

### Generating Module File
_generate_module_cpp(rsl
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(rsl_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(rsl_generate_messages rsl_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg" NAME_WE)
add_dependencies(rsl_generate_messages_cpp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg" NAME_WE)
add_dependencies(rsl_generate_messages_cpp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg" NAME_WE)
add_dependencies(rsl_generate_messages_cpp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg" NAME_WE)
add_dependencies(rsl_generate_messages_cpp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv" NAME_WE)
add_dependencies(rsl_generate_messages_cpp _rsl_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rsl_gencpp)
add_dependencies(rsl_gencpp rsl_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rsl_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
)
_generate_msg_lisp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
)
_generate_msg_lisp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg"
  "${MSG_I_FLAGS}"
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
)
_generate_msg_lisp(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
)

### Generating Services
_generate_srv_lisp(rsl
  "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
)

### Generating Module File
_generate_module_lisp(rsl
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(rsl_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(rsl_generate_messages rsl_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg" NAME_WE)
add_dependencies(rsl_generate_messages_lisp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg" NAME_WE)
add_dependencies(rsl_generate_messages_lisp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg" NAME_WE)
add_dependencies(rsl_generate_messages_lisp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg" NAME_WE)
add_dependencies(rsl_generate_messages_lisp _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv" NAME_WE)
add_dependencies(rsl_generate_messages_lisp _rsl_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rsl_genlisp)
add_dependencies(rsl_genlisp rsl_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rsl_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
)
_generate_msg_py(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
)
_generate_msg_py(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg"
  "${MSG_I_FLAGS}"
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
)
_generate_msg_py(rsl
  "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
)

### Generating Services
_generate_srv_py(rsl
  "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
)

### Generating Module File
_generate_module_py(rsl
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(rsl_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(rsl_generate_messages rsl_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapGesture.msg" NAME_WE)
add_dependencies(rsl_generate_messages_py _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapHand.msg" NAME_WE)
add_dependencies(rsl_generate_messages_py _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapFrame.msg" NAME_WE)
add_dependencies(rsl_generate_messages_py _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/msg/LeapPointable.msg" NAME_WE)
add_dependencies(rsl_generate_messages_py _rsl_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dzhi/catkin_ws/src/rsl/srv/ResetCalibration.srv" NAME_WE)
add_dependencies(rsl_generate_messages_py _rsl_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rsl_genpy)
add_dependencies(rsl_genpy rsl_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rsl_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rsl
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(rsl_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(rsl_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rsl
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(rsl_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(rsl_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rsl
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(rsl_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(rsl_generate_messages_py std_msgs_generate_messages_py)
endif()
