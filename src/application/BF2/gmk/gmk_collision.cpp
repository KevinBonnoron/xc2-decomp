#include "gmk/gmk_collision.h"

#include "framework/reference_frame.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"

namespace gmk {

GmkCollision::GmkCollision(const CreateInfo *info) : unknown50(nullptr), unknown58(nullptr), unknown60(false), unknown61(false), unknown62(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GmkCollision::create(const CreateInfo &info) {
  dispose();
  unknown10 = info;
  if (unknown10.unknown30 && unknown10.unknown00 != GmkPhantom::SHAPE_TYPE_UNKNOWN_2 && unknown10.unknown00 != GmkPhantom::SHAPE_TYPE_UNKNOWN_3) {
    unknown10.unknown00 = GmkPhantom::SHAPE_TYPE_UNKNOWN_2;
    unknown10.unknown34[1] = unknown10.unknown34[0];
  }
  fw::ColiCharacterInfo coliInfo;
  coliInfo.unknown04 = fw::COLI_TYPE_UNKNOWN_0;
  coliInfo.unknown08 = 799;
  coliInfo.unknown14 = 0x200000;
  coliInfo.unknown0c = 2;
  coliInfo.unknown28.unknown08 = this;
  coliInfo.unknown20 = this;
  coliInfo.unknown28.unknown00 |= 1 << fw::ColiObject::EVENT_UNKNOWN_0;
  coliInfo.unknown28.unknown00 |= 1 << fw::ColiObject::EVENT_UNKNOWN_2;
  switch (info.unknown00) {
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_1: {
    fw::unknown131 shape(info.unknown34[0]);
    coliInfo.unknown80 = &shape;
    unknown58 = fw::ColiObject::createColiCharacter(coliInfo, mm::mtl::IntrusivePtr<fw::ReferenceFrame>());
    break;
  }
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_2: {
    fw::unknown132 shape(info.unknown34[0], info.unknown34[1]);
    shape.unknown0c = info.unknown30;
    coliInfo.unknown80 = &shape;
    unknown58 = fw::ColiObject::createColiCharacter(coliInfo, mm::mtl::IntrusivePtr<fw::ReferenceFrame>());
    break;
  }
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_3: {
    fw::unknown133 shape(mm::Vec3(info.unknown34[0], info.unknown34[1], info.unknown34[2]));
    shape.unknown10.unknown10 = info.unknown30;
    coliInfo.unknown80 = &shape;
    unknown58 = fw::ColiObject::createColiCharacter(coliInfo, mm::mtl::IntrusivePtr<fw::ReferenceFrame>());
    break;
  }
  default:
    break;
  }
  mm::Mat44 matrix;
  matrix.unknown011(info.unknown20);
  mm::Vec3 position = info.unknown10;
  matrix.rows[3][0] += position.x;
  matrix.rows[3][1] += position.y;
  matrix.rows[3][2] += position.z;
  unknown58->setMatrix(matrix);
}

void GmkCollision::create(const AGmkBase &gmk, bool flag) {
  CreateInfo info;
  info.unknown00 = unknown006[gmk.unknown08.unknown10->unknown0c];
  info.unknown10 = gmk.unknown08.unknown08->unknown00;
  info.unknown20 = gmk.unknown08.unknown08->unknown10;
  switch (info.unknown00) {
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_1:
    info.unknown34[0] = gmk.unknown08.unknown08->unknown20.x * 0.5f;
    break;
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_2:
    info.unknown34[0] = gmk.unknown08.unknown08->unknown20.y;
    info.unknown34[1] = gmk.unknown08.unknown08->unknown20.x * 0.5f;
    break;
  case GmkPhantom::SHAPE_TYPE_UNKNOWN_3:
    info.unknown34[0] = gmk.unknown08.unknown08->unknown20.x * 0.5f;
    info.unknown34[1] = gmk.unknown08.unknown08->unknown20.y * 0.5f;
    info.unknown34[2] = gmk.unknown08.unknown08->unknown20.z * 0.5f;
    break;
  default:
    break;
  }
  info.unknown30 = flag;
  create(info);
  unknown50 = gmk.unknown08.unknown10->unknown00;
}

void GmkCollision::dispose() {
  if (unknown58 != nullptr) {
    unknown58->setColiUserData(nullptr);
    unknown58->setListener(nullptr);
    mm::mtl::safeRelease(unknown58);
  }
  unknown50 = nullptr;
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
