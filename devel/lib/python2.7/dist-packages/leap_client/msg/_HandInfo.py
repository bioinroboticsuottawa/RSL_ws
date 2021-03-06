# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from leap_client/HandInfo.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import leap_client.msg
import std_msgs.msg

class HandInfo(genpy.Message):
  _md5sum = "937a409678ad32096fdeeb182c37c6da"
  _type = "leap_client/HandInfo"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """std_msgs/Header header
int32 id
float32 time_visible
geometry_msgs/Pose pose
geometry_msgs/Vector3 velocity
float32 sphere_radius
geometry_msgs/Point sphere_center
geometry_msgs/Pose stabilized_pose
FingerInfo[] fingers

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

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
================================================================================
MSG: leap_client/FingerInfo
std_msgs/Header header
int32 hand_id
int32 id
float32 time_visible
geometry_msgs/Point tip_position
geometry_msgs/Vector3 tip_velocity
geometry_msgs/Vector3 pointing_direction
geometry_msgs/Point stabilized_tip_position
"""
  __slots__ = ['header','id','time_visible','pose','velocity','sphere_radius','sphere_center','stabilized_pose','fingers']
  _slot_types = ['std_msgs/Header','int32','float32','geometry_msgs/Pose','geometry_msgs/Vector3','float32','geometry_msgs/Point','geometry_msgs/Pose','leap_client/FingerInfo[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,id,time_visible,pose,velocity,sphere_radius,sphere_center,stabilized_pose,fingers

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(HandInfo, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.id is None:
        self.id = 0
      if self.time_visible is None:
        self.time_visible = 0.
      if self.pose is None:
        self.pose = geometry_msgs.msg.Pose()
      if self.velocity is None:
        self.velocity = geometry_msgs.msg.Vector3()
      if self.sphere_radius is None:
        self.sphere_radius = 0.
      if self.sphere_center is None:
        self.sphere_center = geometry_msgs.msg.Point()
      if self.stabilized_pose is None:
        self.stabilized_pose = geometry_msgs.msg.Pose()
      if self.fingers is None:
        self.fingers = []
    else:
      self.header = std_msgs.msg.Header()
      self.id = 0
      self.time_visible = 0.
      self.pose = geometry_msgs.msg.Pose()
      self.velocity = geometry_msgs.msg.Vector3()
      self.sphere_radius = 0.
      self.sphere_center = geometry_msgs.msg.Point()
      self.stabilized_pose = geometry_msgs.msg.Pose()
      self.fingers = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_if10df10d.pack(_x.id, _x.time_visible, _x.pose.position.x, _x.pose.position.y, _x.pose.position.z, _x.pose.orientation.x, _x.pose.orientation.y, _x.pose.orientation.z, _x.pose.orientation.w, _x.velocity.x, _x.velocity.y, _x.velocity.z, _x.sphere_radius, _x.sphere_center.x, _x.sphere_center.y, _x.sphere_center.z, _x.stabilized_pose.position.x, _x.stabilized_pose.position.y, _x.stabilized_pose.position.z, _x.stabilized_pose.orientation.x, _x.stabilized_pose.orientation.y, _x.stabilized_pose.orientation.z, _x.stabilized_pose.orientation.w))
      length = len(self.fingers)
      buff.write(_struct_I.pack(length))
      for val1 in self.fingers:
        _v1 = val1.header
        buff.write(_struct_I.pack(_v1.seq))
        _v2 = _v1.stamp
        _x = _v2
        buff.write(_struct_2I.pack(_x.secs, _x.nsecs))
        _x = _v1.frame_id
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        if python3:
          buff.write(struct.pack('<I%sB'%length, length, *_x))
        else:
          buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1
        buff.write(_struct_2if.pack(_x.hand_id, _x.id, _x.time_visible))
        _v3 = val1.tip_position
        _x = _v3
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v4 = val1.tip_velocity
        _x = _v4
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v5 = val1.pointing_direction
        _x = _v5
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v6 = val1.stabilized_tip_position
        _x = _v6
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.pose is None:
        self.pose = geometry_msgs.msg.Pose()
      if self.velocity is None:
        self.velocity = geometry_msgs.msg.Vector3()
      if self.sphere_center is None:
        self.sphere_center = geometry_msgs.msg.Point()
      if self.stabilized_pose is None:
        self.stabilized_pose = geometry_msgs.msg.Pose()
      if self.fingers is None:
        self.fingers = None
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 172
      (_x.id, _x.time_visible, _x.pose.position.x, _x.pose.position.y, _x.pose.position.z, _x.pose.orientation.x, _x.pose.orientation.y, _x.pose.orientation.z, _x.pose.orientation.w, _x.velocity.x, _x.velocity.y, _x.velocity.z, _x.sphere_radius, _x.sphere_center.x, _x.sphere_center.y, _x.sphere_center.z, _x.stabilized_pose.position.x, _x.stabilized_pose.position.y, _x.stabilized_pose.position.z, _x.stabilized_pose.orientation.x, _x.stabilized_pose.orientation.y, _x.stabilized_pose.orientation.z, _x.stabilized_pose.orientation.w,) = _struct_if10df10d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.fingers = []
      for i in range(0, length):
        val1 = leap_client.msg.FingerInfo()
        _v7 = val1.header
        start = end
        end += 4
        (_v7.seq,) = _struct_I.unpack(str[start:end])
        _v8 = _v7.stamp
        _x = _v8
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2I.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v7.frame_id = str[start:end].decode('utf-8')
        else:
          _v7.frame_id = str[start:end]
        _x = val1
        start = end
        end += 12
        (_x.hand_id, _x.id, _x.time_visible,) = _struct_2if.unpack(str[start:end])
        _v9 = val1.tip_position
        _x = _v9
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v10 = val1.tip_velocity
        _x = _v10
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v11 = val1.pointing_direction
        _x = _v11
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v12 = val1.stabilized_tip_position
        _x = _v12
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.fingers.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_if10df10d.pack(_x.id, _x.time_visible, _x.pose.position.x, _x.pose.position.y, _x.pose.position.z, _x.pose.orientation.x, _x.pose.orientation.y, _x.pose.orientation.z, _x.pose.orientation.w, _x.velocity.x, _x.velocity.y, _x.velocity.z, _x.sphere_radius, _x.sphere_center.x, _x.sphere_center.y, _x.sphere_center.z, _x.stabilized_pose.position.x, _x.stabilized_pose.position.y, _x.stabilized_pose.position.z, _x.stabilized_pose.orientation.x, _x.stabilized_pose.orientation.y, _x.stabilized_pose.orientation.z, _x.stabilized_pose.orientation.w))
      length = len(self.fingers)
      buff.write(_struct_I.pack(length))
      for val1 in self.fingers:
        _v13 = val1.header
        buff.write(_struct_I.pack(_v13.seq))
        _v14 = _v13.stamp
        _x = _v14
        buff.write(_struct_2I.pack(_x.secs, _x.nsecs))
        _x = _v13.frame_id
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        if python3:
          buff.write(struct.pack('<I%sB'%length, length, *_x))
        else:
          buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1
        buff.write(_struct_2if.pack(_x.hand_id, _x.id, _x.time_visible))
        _v15 = val1.tip_position
        _x = _v15
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v16 = val1.tip_velocity
        _x = _v16
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v17 = val1.pointing_direction
        _x = _v17
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v18 = val1.stabilized_tip_position
        _x = _v18
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.pose is None:
        self.pose = geometry_msgs.msg.Pose()
      if self.velocity is None:
        self.velocity = geometry_msgs.msg.Vector3()
      if self.sphere_center is None:
        self.sphere_center = geometry_msgs.msg.Point()
      if self.stabilized_pose is None:
        self.stabilized_pose = geometry_msgs.msg.Pose()
      if self.fingers is None:
        self.fingers = None
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 172
      (_x.id, _x.time_visible, _x.pose.position.x, _x.pose.position.y, _x.pose.position.z, _x.pose.orientation.x, _x.pose.orientation.y, _x.pose.orientation.z, _x.pose.orientation.w, _x.velocity.x, _x.velocity.y, _x.velocity.z, _x.sphere_radius, _x.sphere_center.x, _x.sphere_center.y, _x.sphere_center.z, _x.stabilized_pose.position.x, _x.stabilized_pose.position.y, _x.stabilized_pose.position.z, _x.stabilized_pose.orientation.x, _x.stabilized_pose.orientation.y, _x.stabilized_pose.orientation.z, _x.stabilized_pose.orientation.w,) = _struct_if10df10d.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.fingers = []
      for i in range(0, length):
        val1 = leap_client.msg.FingerInfo()
        _v19 = val1.header
        start = end
        end += 4
        (_v19.seq,) = _struct_I.unpack(str[start:end])
        _v20 = _v19.stamp
        _x = _v20
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2I.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v19.frame_id = str[start:end].decode('utf-8')
        else:
          _v19.frame_id = str[start:end]
        _x = val1
        start = end
        end += 12
        (_x.hand_id, _x.id, _x.time_visible,) = _struct_2if.unpack(str[start:end])
        _v21 = val1.tip_position
        _x = _v21
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v22 = val1.tip_velocity
        _x = _v22
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v23 = val1.pointing_direction
        _x = _v23
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v24 = val1.stabilized_tip_position
        _x = _v24
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.fingers.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_if10df10d = struct.Struct("<if10df10d")
_struct_3I = struct.Struct("<3I")
_struct_2if = struct.Struct("<2if")
_struct_2I = struct.Struct("<2I")
_struct_3d = struct.Struct("<3d")
