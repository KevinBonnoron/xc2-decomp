#include "gf/object/component/behavior/gf_com_behavior_map_lod_anim.h"

#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

void GfComBehaviorMapLodAnim::update(const fw::UpdateInfo &info) {
  GfFieldLodColiAnim::PosInfo *posInfo = getBindedPosInfo();
  if (posInfo != nullptr) {
    posInfo->update(info);
  }
}

GfFieldLodColiAnim::PosInfo *GfComBehaviorMapLodAnim::getBindedPosInfo() const {
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (!acc.isValid() || acc.isDestroy() || acc.testFlag(OBJ_FLAG_UNKNOWN_17) || acc.getObj() == nullptr) {
    return nullptr;
  }

  return reinterpret_cast<GfFieldLodColiAnim::PosInfo *>(acc.getUserData(OBJ_USER_DATA_UNKNOWN_1));
}

const mm::mtl::RTTI *GfComBehaviorMapLodAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
