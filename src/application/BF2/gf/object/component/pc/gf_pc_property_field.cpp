#include "gf/object/component/pc/gf_pc_property_field.h"

#include <math.h>
#include <stdlib.h>

#include "anm/anm_qs_transform.h"
#include "framework/coli/coli_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

bool GfPropertyField::recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_OBJECT_UNKNOWN_16777275) {
    procMsgObjectFlushProperty(property, sender, static_cast<MsgObjectFlushProperty &>(message));
    return true;
  }

  return false;
}

void GfPropertyField::procMsgObjectFlushProperty(const GfComPropertyPc &property, fw::MessageObject *sender, MsgObjectFlushProperty &message) {
  flashWallInfo(property);
  GfObjProperty *objProperty = GfObjUtil::getProperty(static_cast<GfObj *>(property.unknown08)->unknownf8);
  if (objProperty->unknown18 != nullptr) {
    objProperty->unknown18->unknown7c = unknown11_0;
  }
}

GfPropertyField::GfPropertyField()
    : unknown08(nullptr), unknown10_0(false), unknown10_1(false), unknown10_2(false), unknown10_3(false), unknown10_4(false), unknown10_5(false), unknown10_6(false), unknown10_7(false),
      unknown11_0(false), unknown11_1(false), unknown11_2(false), unknown11_3(false), unknown11_4(false), unknown11_5(false), unknown11_6(false), unknown11_7(false), unknown12_0(false),
      unknown12_1(false), unknown12_2(0), unknown14(WALL_MOVE_MODE_UNKNOWN_FFFFFFFF), unknown18(0.25f), unknown1c(0.0f), unknown20(0.0f), unknown24(0.0f), unknown28(0.0f), unknown2c(0.0f),
      unknown30(0.0f), unknown34(0.0f), unknown38(0.0f), unknown3c(0.0f), unknown40(0.0f), unknown44(0.0f), unknown48(0.0f), unknown4c(0.25f), unknown50(5.0f), unknown54(0.0f),
      unknown60(mm::Vec3::zero), unknown70(0), unknown78(unknown020) {}

void GfPropertyField::setup(const GfComPropertyPc &property) {
  resetStatus(property);
  GfComAsm *comAsm = property.unknown08->getComponent<GfComAsm>();
  f32 time;
  anm::QsTransform transform;
  if (comAsm->getPlaybackTime("S_uplanding_00", &time) && comAsm->getLocomotionReference("S_uplanding_00", time, &transform)) {
    mm::Vec3 move(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
    unknown20 = move.y;
    move.y = 0.0f;
    unknown1c = sqrtf(move.x * move.x + move.y * move.y + move.z * move.z);
  }

  if (comAsm->getPlaybackTime("S_uplanding_01", &time) && comAsm->getLocomotionReference("S_uplanding_01", time, &transform)) {
    mm::Vec3 move(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
    unknown28 = move.y;
    move.y = 0.0f;
    unknown24 = sqrtf(move.x * move.x + move.y * move.y + move.z * move.z);
  }

  if (comAsm->getPlaybackTime("S_downlanding_00", &time) && comAsm->getLocomotionReference("S_downlanding_00", time, &transform)) {
    mm::Vec3 move(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
    unknown30 = move.y;
    move.y = 0.0f;
    unknown2c = sqrtf(move.x * move.x + move.y * move.y + move.z * move.z);
  }

  if (comAsm->getPlaybackTime("S_downlanding_01", &time) && comAsm->getLocomotionReference("S_downlanding_01", time, &transform)) {
    mm::Vec3 move(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
    unknown38 = move.y + 0.01f;
    move.y = 0.0f;
    unknown34 = sqrtf(move.x * move.x + move.y * move.y + move.z * move.z);
  }

  const fw::ParamList *paramList = unknown08.operator->();
  const WallMoveParam *wallMove = paramList->unknown0c > 16 ? static_cast<const WallMoveParam *>(paramList->unknown10[16].param) : nullptr;
  if (comAsm->getPlaybackTime("S_climbup_base", &time)) {
    unknown3c = time * wallMove->upSpeed;
  }

  if (comAsm->getPlaybackTime("S_climedown_base", &time)) {
    unknown40 = time * wallMove->downSpeed;
  }

  if (comAsm->getPlaybackTime("S_climbright_base", &time)) {
    unknown44 = time * wallMove->sideSpeed;
  }

  if (comAsm->getPlaybackTime("S_climbjump_base_02", &time) && comAsm->getLocomotionReference("S_climbjump_base_02", time, &transform)) {
    unknown48 = transform.unknown00.y;
  }

  if (comAsm->getPlaybackTime("S_waterhole_01", &time) && comAsm->getLocomotionReference("S_waterhole_01", time, &transform)) {
    unknown50 = transform.unknown00.y;
  }

  const void *appendix = comAsm->getAppendix("wallOffset");
  if (appendix != nullptr) {
    unknown4c = atof(static_cast<const char *>(appendix));
  }

  appendix = comAsm->getAppendix("uniqueIdleSpace");
  if (appendix != nullptr) {
    unknown54 = atof(static_cast<const char *>(appendix));
  }
}

void GfPropertyField::flashWallInfo(const GfComPropertyPc &property) {
  unknown070 *move = GfObjUtil::getProperty(static_cast<GfObj *>(property.unknown08)->unknownf8)->unknown18;
  if (move != nullptr) {
    if (unknown10_6) {
      move->unknown90 = unknown130.unknown00;
      move->unknown7e = true;
    } else {
      move->unknown90.unknown002(mm::Vec3(0.0f, 1.0f, 0.0f), 0.0f);
      move->unknown7e = false;
    }
  }
}

void GfPropertyField::resetStatus(const GfComPropertyPc &property) {
  if (property.unknown111_2) {
    unknown10_3 = true;
  }
  unknown12_1 = true;
}

void GfPropertyField::flushOwner(GfComPropertyPc &property) {
  if (unknown11_3) {
    property.unknown110_4 = true;
    property.unknown110_7 = true;
  }
}

void GfPropertyField::cleanup(const GfComPropertyPc &property) {}

void GfPropertyField::flush(const GfComPropertyPc &property) {
  fw::ComponentObject *component = property.unknown08->unknown38[GfComCollider::COMPONENT_INDEX];
  if (component != nullptr && !component->getRTTI()->isKindOf(&GfComCollider::m_rtti)) {
    component = nullptr;
  }
  const GfComCollider *collider = static_cast<GfComCollider *>(component);
  fw::ColiObject *coli = collider->unknown18[0];
  if (coli != nullptr) {
    bool isAttribute = coli->testAttribute(fw::COLI_ATRR_UNKNOWN_3);
    if (isAttribute) {
      unknown12_1 = true;
    } else {
      unknown12_1 = false;
    }
  }
}

void GfPropertyField::setBigJumpInfo(const MsgPcFieldNotifyBigJump *message) {
  if (message != nullptr) {
    unknown11_4 = true;
    unknown80 = *message;
  } else {
    unknown11_4 = false;
  }
}

const MsgPcFieldNotifyBigJump *GfPropertyField::getBigJumpInfo() const { return unknown11_4 ? &unknown80 : nullptr; }

void GfPropertyField::setWarpInfo(const MsgPcFieldNotifyWarp *message) {
  if (message != nullptr) {
    unknown11_5 = true;
    unknownc0 = *message;
  } else {
    unknown11_5 = false;
  }
}

const MsgPcFieldNotifyWarp *GfPropertyField::getWarpInfo() const { return unknown11_5 ? &unknownc0 : nullptr; }

void GfPropertyField::setWallJump(const MsgPcFieldNotifyWallJump *message) {
  if (message != nullptr) {
    unknown11_6 = true;
    unknown100 = *message;
  } else {
    unknown11_6 = false;
  }
}

const MsgPcFieldNotifyWallJump *GfPropertyField::getWallJumpInfo() const { return unknown11_6 ? &unknown100 : nullptr; }

f32 GfPropertyField::getWallHeightOffset() const { return static_cast<const WallCommonParam *>(unknown08->unknown10[15].param)->wallHeightRatio * unknown28; }

} // namespace pc
} // namespace gf
