#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"

#include "framework/ik/ik_look_at_solver.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {

namespace pc {

LookAtPlugin::LookAtPlugin() : unknown20(unknown012), unknown28(getAllocator(ALLOCATOR_UNKNOWN_0)), unknown40(nullptr), unknown68(0), unknown6c(0.0f), unknown70() {}

LookAtPlugin::~LookAtPlugin() {}

void LookAtPlugin::cleanup(GfComBehaviorPc &) {
  if (unknown20 != unknown012) {
    GfGameSearchObj::destroyObj(unknown20);
    unknown20 = unknown012;
  }
  unknown10 = nullptr;
}

void LookAtPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info) {
  updateHoldHandles(behavior);
  for (u32 i = 0; i < 5; i++) {
    if (unknown70[i] > 0.0f) {
      unknown70[i] -= info.unknown04;
    }
  }
  if (unknown6c > 0.0f) {
    unknown6c -= info.unknown04;
  }
  if (unknown6c <= 0.0f && changeTarget()) {
    unknown6c = unknown40->unknown10->unknown0c;
  }
  if (unknown40 == nullptr) {
    unknown68 = 0;
  } else {
    GfObj *obj = GfObjUtil::getObj(unknown40->unknown00);
    if (obj != nullptr) {
      MsgPcGetLookPoint message;
      if (static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message)) {
        unknown10->setTarget(message.unknown10);
      }
    }
  }
}

const unknown002 *LookAtPlugin::getParam() const {
  const fw::ParamList *list = unknown18.operator->();
  return list->unknown0c > 4 ? static_cast<const unknown002 *>(list->unknown10[4].param) : nullptr;
}

void LookAtPlugin::onActivate() {
  unknown40 = nullptr;
  unknown28.clear();
  unknown68 = 0;
  unknown6c = 0.0f;
  for (u32 i = 0; i < 5; i++) {
    unknown70[i] = 0.0f;
  }
}

void LookAtPlugin::onDeactivate() {
  const unknown002 *param = getParam();
  if (unknown40 != nullptr) {
    unknown10->fadeOut(param->unknown10);
  }
}

bool LookAtPlugin::getTargetTransform(const TargetInfo &info, fw::Transform *transform) const {
  GfObj *obj = GfObjUtil::getObj(info.unknown00);
  if (obj != nullptr) {
    GfObjAcc acc(obj);
    const fw::Transform &worldTransform = acc.getWorldTransform();
    transform->unknown00 = worldTransform.unknown00;
    transform->unknown10 = worldTransform.unknown10;
    return true;
  }
  return false;
}

void LookAtPlugin::onReloadBdat() {
  GfBdatLookAt *bdat = GfBdatLookAt::get();
  GfGameSearchObj::GFSEARCH_INFO *info = GfGameSearchObj::getInfo(unknown20);
  info->unknown00.unknown3c = bdat->getMaxRadius();
  info->unknown00.unknown00 |= 1;
  // The game calls getMaxUpper (1.0.0: 0x7100579c70) and getMaxLower (0x7100579c7c), then sets the flag (0x7100579c80), then stores both values (stp s8, s0 at 0x7100579c8c).
  f32 upper = bdat->getMaxUpper();
  f32 lower = bdat->getMaxLower();
  info->unknown00.unknown00 |= 2;
  info->unknown00.unknown30 = upper;
  info->unknown00.unknown34 = lower;
}

void LookAtPlugin::drawDebugTarget() {
  if (unknown40 != nullptr && unknown10.get() != nullptr) {
    fw::LookAtIkSolver *solver = unknown10->unknown28.get();
    if (solver != nullptr && solver->isEnable()) {
      solver->drawDebug();
    }
  }
}

} // namespace pc
} // namespace gf

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo>::MapTraits<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo> &);
template void unknown101::rebalance(unknown101::node *);
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
