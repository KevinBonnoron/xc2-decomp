#include "gf/object/component/behavior/gf_com_behavior_event.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/ik/ik_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/property/gf_com_property_event.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

GfComBehaviorEvent::GfComBehaviorEvent() : unknown98(0) {}

bool GfComBehaviorEvent::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 != MSG_OBJECT_GET_VELOCITY) {
    return false;
  }

  procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
  return true;
}

const mm::mtl::RTTI *GfComBehaviorEvent::getRTTI() const { return &m_rtti; }
void GfComBehaviorEvent::cleanup() { unknown10.cleanup(); }

void GfComBehaviorEvent::setFootIK(bool isEnable) {
  if (unknown08->getComponent<GfComIK>() == nullptr) {
    return;
  }

  GfComEvtAnim *evtAnim = unknown08->getComponent<GfComEvtAnim>();
  if (evtAnim != nullptr && evtAnim->unknown10.unknown10 != nullptr) {
    FootIkControllerPlugin *plugin = unknown001<FootIkControllerPlugin>(3);
    if (plugin != nullptr) {
      plugin->unknown1e = isEnable;
    }
  }
}

void GfComBehaviorEvent::setTarget(bool isEnable, f32 time, bool isLookOnly) {
  GfComIK *ik = unknown08->getComponent<GfComIK>();
  if (ik == nullptr) {
    return;
  }

  GfComEvtAnim *evtAnim = unknown08->getComponent<GfComEvtAnim>();
  if (evtAnim == nullptr || evtAnim->unknown10.unknown10 == nullptr) {
    return;
  }

  fw::IkSolver *solver = ik->unknown10.unknown10[unknown002_3].get();
  if (solver == nullptr) {
    return;
  }

  fw::LookIkSolver *look = mm::mtl::dynamicCast<fw::LookIkSolver>(solver);
  if (look == nullptr) {
    return;
  }

  fw::SpineIkSolver *spine = look->unknown20.get();
  fw::LookAtIkSolver *lookAt = look->unknown28.get();
  if (isEnable) {
    if ((unknown98 & 2) == 0) {
      if (lookAt != nullptr) {
        lookAt->fadeIn(time);
      }
      if (spine != nullptr && !isLookOnly) {
        spine->fadeIn(time);
      }
    } else {
      if (lookAt != nullptr) {
        lookAt->startTargetFade(time);
      }
      if (spine != nullptr && !isLookOnly) {
        spine->startTargetFade(time);
      }
    }
    unknown98 |= 2;
  } else {
    if (lookAt != nullptr) {
      lookAt->fadeOut(time);
    }
    if (spine != nullptr && !isLookOnly) {
      spine->fadeOut(time);
    }
    unknown98 &= ~2;
  }
}

void GfComBehaviorEvent::setTargetPos(const mm::Vec3 &position) {
  GfComIK *ik = unknown08->getComponent<GfComIK>();
  if (ik == nullptr) {
    return;
  }

  GfComEvtAnim *evtAnim = unknown08->getComponent<GfComEvtAnim>();
  if (evtAnim == nullptr || evtAnim->unknown10.unknown10 == nullptr) {
    return;
  }

  fw::IkSolver *solver = ik->unknown10.unknown10[unknown002_3].get();
  if (solver == nullptr) {
    return;
  }

  fw::LookIkSolver *look = mm::mtl::dynamicCast<fw::LookIkSolver>(solver);
  if (look == nullptr) {
    return;
  }

  fw::SpineIkSolver *spine = look->unknown20.get();
  fw::LookAtIkSolver *lookAt = look->unknown28.get();
  if (lookAt != nullptr) {
    lookAt->unknowna0 = position;
  }
  if (spine != nullptr) {
    spine->unknown50 = position;
  }
}

void GfComBehaviorEvent::execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4) {
  TFieldExecCmdTurn<GfComEvtAnim>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = angle;
  info.unknown0c = param3;
  info.unknown14 = param2;
  info.unknown18 = param4;
  unknowna0.create(info);
}

void GfComBehaviorEvent::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) {
  GfComPropertyEvent *property = unknown08->getComponent<GfComPropertyEvent>();
  if (property != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    property->recieveMessage(object, message);
  }
}

} // namespace gf
