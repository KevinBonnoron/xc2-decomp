#include "gf/request/gf_req_command.h"

#include "mm_math/mm_vec3.h"

namespace gf {

void GfMapjumpInfo::setupForSaveData(u32 mapjumpId, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isStartChapterSave) {
  unknown00 = mapjumpId;
  unknown100 = true;
  f32 rotY = rotation.y;
  GfPartyPosInfo::Position &pos = unknown40.unknown00[0];
  pos.unknown00.x = position.x;
  pos.unknown00.y = position.y;
  pos.unknown00.z = position.z;
  pos.unknown10 = rotY;
  pos.unknown14 = true;
  unknown101 = isStartChapterSave;
  unknown108 = 1;
}

} // namespace gf
