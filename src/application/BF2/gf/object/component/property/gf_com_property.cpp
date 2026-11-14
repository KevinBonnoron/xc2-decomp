#include "gf/object/component/property/gf_com_property.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep

namespace gf {

GfComProperty::GfComProperty() {}

GfComProperty::~GfComProperty() {}

void GfComProperty::changeLayer(u32 oldLayer, u32 newLayer) {}

void GfComProperty::flush() {
  GfObjPropertyCharacter *character = GfObjUtil::getProperty(static_cast<GfObj *>(unknown08)->unknownf8)->unknown10;
  if (character != nullptr) {
    GfStatusProperty *status = unknown10.get();
    if (status != nullptr) {
      character->unknown00 = status->unknown0c;
      character->unknown04 = status->unknown10;
    }
    if (unknown18) {
      character->unknown28 = unknown18->handle;
    }
  }

  MsgObjectFlushProperty message;
  recieveMessage(static_cast<GfObj *>(unknown08), message);
}

void GfComProperty::procMsgGameChangeTarget(fw::MessageObject *object, MsgGameChangeTarget &message) {
  if (unknown18) {
    unknown18->handle = message.unknown08;
    GfComBehavior *behavior = unknown08->getComponent<GfComBehavior>();
    if (behavior != nullptr) {
      behavior->recieveMessage(object, message);
    }
  }
}

void GfComProperty::procMsgObjectDead(fw::MessageObject *object, MsgObjectDead &message) {
  if (unknown10.get() != nullptr && unknown10->unknown10 != 0) {
    unknown10->unknown10 = 0;
    MsgObjectNotifyDead notify(0, static_cast<const MsgObjectDamage *>(static_cast<const fw::Message *>(&message)));
    notify.unknown08 = message.deadType;
    onDead(notify);
  }
}

void GfComProperty::onDead(MsgObjectNotifyDead &message) {
  GfComModel *model = unknown08->getComponent<GfComModel>();
  if (model != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    model->recieveMessage(object, message);
  }
  GfComBehavior *behavior = unknown08->getComponent<GfComBehavior>();
  if (behavior != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    behavior->recieveMessage(object, message);
  }

  SCOM_CHAR_DEAD::create(static_cast<GfObj *>(unknown08)->unknownf8, message);
}

void GfComProperty::onDamage(MsgObjectNotifyDamage &message) {
  GfComBehavior *behavior = unknown08->getComponent<GfComBehavior>();
  if (behavior != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    behavior->recieveMessage(object, message);
  }

  SCOM_CHAR_DMG::create(static_cast<GfObj *>(unknown08)->unknownf8, message);
}

void GfComProperty::procMsgObjectAlpha(fw::MessageObject *object, MsgObjectAlpha &message) { setAlpha(message.type, message.alpha); }

void GfComProperty::procMsgObjectNotifyChangeAttribute(fw::MessageObject *object, MsgObjectNotifyChangeAttribute &message) {
  GfComSound *sound = unknown08->getComponent<GfComSound>();
  if (sound != nullptr) {
    sound->unknown001(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_1), message.unknown08);
  }
}

void GfComProperty::onHeal(MsgObjectNotifyHealHp &message) {
  GfComBehavior *behavior = unknown08->getComponent<GfComBehavior>();
  if (behavior != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    behavior->recieveMessage(object, message);
  }
}

const mm::mtl::RTTI *GfComProperty::getRTTI() const { return &m_rtti; }

void GfComProperty::procMsgObjectInvincible(fw::MessageObject *object, MsgObjectInvincible &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown18 = message.invincible;
    unknown10->unknown19 = message.invincibleSub;
  }
}

void GfComProperty::procMsgObjectMaxHp(fw::MessageObject *object, MsgObjectMaxHp &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown0c = message.maxHp;
  }
}

void GfComProperty::procMsgObjectSetHp(fw::MessageObject *object, MsgObjectSetHp &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown10 = message.hp;
  }
}

void GfComProperty::procMsgObjectStopAutoHeal(fw::MessageObject *object, MsgObjectStopAutoHeal &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown1a = message.isStop;
  }
}

void GfComProperty::procMsgObjectLimitHP(fw::MessageObject *object, MsgObjectLimitHP &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown14 = message.limitHp;
  }
}

} // namespace gf

template void mm::mtl::UniquePtr<gf::GfTargetProperty>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::UniquePtr<gf::GfAlphaProperty>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::UniquePtr<gf::GfDebugStatusProperty>::_safe_bool_helper::safe_bool_function() const;
