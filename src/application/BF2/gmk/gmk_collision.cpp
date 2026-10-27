#include "gmk/gmk_collision.h"

#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"

namespace gmk {

void GmkCollision::dispose() {
  if (unknown58 != nullptr) {
    unknown58->setColiUserData(nullptr);
    unknown58->setListener(nullptr);
    mm::mtl::safeRelease(unknown58);
  }
  unknown50 = 0;
}

void GmkCollision::update(f32 deltaTime) {
  if (unknown58 != nullptr) {
    unknown60 = false;
    unknown61 = false;
  }
}

void GmkCollision::enter(const EnterInfo &info) {
  fw::ColiUserData *userData = info.other->unknown58;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&gf::GfComCollider::UserData::m_rtti)) {
    return;
  }
  if (static_cast<gf::GfObj *>(static_cast<gf::GfComCollider::UserData *>(userData)->unknown08->unknown08)->unknownf8 == gf::GfGameManager::getPartyLeader()) {
    unknown60 = true;
    unknown62 = true;
  }
}

void GmkCollision::leave(const LeaveInfo &info) {
  fw::ColiUserData *userData = info.other->unknown58;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&gf::GfComCollider::UserData::m_rtti)) {
    return;
  }
  if (static_cast<gf::GfObj *>(static_cast<gf::GfComCollider::UserData *>(userData)->unknown08->unknown08)->unknownf8 == gf::GfGameManager::getPartyLeader()) {
    unknown61 = true;
    unknown62 = false;
  }
}

const mm::mtl::RTTI *GmkCollision::getRTTI() const { return &m_rtti; }

} // namespace gmk
