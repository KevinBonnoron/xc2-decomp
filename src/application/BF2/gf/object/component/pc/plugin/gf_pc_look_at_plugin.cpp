#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"

#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {

namespace pc {

LookAtPlugin::LookAtPlugin() : m_GF_SEARCH_OBJ(unknown012), unknown28(getAllocator(ALLOCATOR_UNKNOWN_0)), unknown40(nullptr), unknown68(0), unknown6c(0.0f), unknown70() {}

LookAtPlugin::~LookAtPlugin() {}

// 1.0.0: 0x7100578ca0, 254 instructions; the game keeps the null test of the IK component (cbz x21 at 0x7100578d3c, joining at the vector read), see GfComIK::unknown003 and
// UpdatableObject::getComponent.
bool LookAtPlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown408[5];
  const GfComIK *ik = behavior.unknown08->getComponent<GfComIK>();
  fw::LookIkSolver *look = ik->unknown003<fw::LookIkSolver>(unknown002_3);
  if (look == nullptr) {
    return false;
  }
  unknown10 = look;
  const unknown002 *param = getParam();
  GfBdatLookAt *bdat = GfBdatLookAt::get();
  GfSearchParam search(0x1f8);
  search.unknown3c = bdat->getMaxRadius();
  search.unknown00 |= 1;
  // As onReloadBdat: getMaxUpper (0x7100578ee8) and getMaxLower (0x7100578ef4), then the flag (0x7100578ef8), then both stores (stp s8, s0 at 0x7100578f00); the stores first give 252 instructions.
  f32 upper = bdat->getMaxUpper();
  f32 lower = bdat->getMaxLower();
  search.unknown00 |= 2;
  search.unknown30 = upper;
  search.unknown34 = lower;
  // The game loads the param (ldr w9, [x22] at 0x7100578f04) before the flag store (0x7100578f0c) and stores it after; reading it at the store gives 251 instructions.
  f32 height = param->unknown00;
  search.unknown00 |= 4;
  search.unknown40 = unknown020;
  search.unknown38 = height;
  search.unknown60 = static_cast<GfObj *>(behavior.unknown08)->unknownf8;
  // The game copies the frame twice (reference count + 2 at 0x7100578f70): into this local, then into the param; without the local the function has 234 instructions.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = behavior.unknown08->getComponent<GfComTransform>()->unknown001();
  search.unknown48 = frame;
  m_GF_SEARCH_OBJ = GfGameSearchObj::createObj(search);
  return true;
}

void LookAtPlugin::cleanup(GfComBehaviorPc &) {
  if (m_GF_SEARCH_OBJ != unknown012) {
    GfGameSearchObj::destroyObj(m_GF_SEARCH_OBJ);
    m_GF_SEARCH_OBJ = unknown012;
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
    GfObj *obj = GfObjUtil::getObj(unknown40->m_GF_OBJ_HANDLE);
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

bool LookAtPlugin::changeTarget() {
  TargetInfo *target = nullptr;
  for (mm::mtl::Map<GF_OBJ_HANDLE *, TargetInfo>::iterator it = unknown28.begin(); it != unknown28.end(); ++it) {
    TargetInfo &info = it->second;
    if (info.unknown1c) {
      continue;
    }
    if (unknown70[info.unknown18] > 0.0f) {
      continue;
    }
    u32 side = info.m_searchInfo->unknown24 >= 0.0f ? 1 : 2;
    if (unknown68 == side) {
      continue;
    }
    if (target != nullptr && (info.unknown10->unknown14 < target->unknown10->unknown14 || info.m_searchInfo->unknown20 >= target->m_searchInfo->unknown20)) {
      continue;
    }
    target = &info;
  }
  const unknown002 *param = getParam();
  if (target == nullptr) {
    if (unknown40 != nullptr) {
      unknown10->fadeOut(param->unknown10);
    }
    unknown40 = nullptr;
    return false;
  }
  if (unknown10->isEnable()) {
    unknown10->startTargetFade(param->unknown0c);
  }
  if (unknown40 == nullptr) {
    unknown10->fadeIn(param->unknown08);
  }
  target->unknown1c = true;
  if (target->unknown10 != nullptr) {
    unknown70[target->unknown18] = target->unknown10->unknown10;
  }
  unknown48 = *target;
  unknown40 = &unknown48;
  return true;
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
  GfObj *obj = GfObjUtil::getObj(info.m_GF_OBJ_HANDLE);
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
  GfGameSearchObj::GFSEARCH_INFO *info = GfGameSearchObj::getInfo(m_GF_SEARCH_OBJ);
  info->m_searchParam.unknown3c = bdat->getMaxRadius();
  info->m_searchParam.unknown00 |= 1;
  // The game calls getMaxUpper (1.0.0: 0x7100579c70) and getMaxLower (0x7100579c7c), then sets the flag (0x7100579c80), then stores both values (stp s8, s0 at 0x7100579c8c).
  f32 upper = bdat->getMaxUpper();
  f32 lower = bdat->getMaxLower();
  info->m_searchParam.unknown00 |= 2;
  info->m_searchParam.unknown30 = upper;
  info->m_searchParam.unknown34 = lower;
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
