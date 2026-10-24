#include "gf/object/gf_obj.h"

#include "framework/object/component_object.h"
#include "framework/pointer_map.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj_update.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/rtti.h"

namespace gf {

static const char *const TYPE_NAMES[] = {
    "NONE",
    "MAP",
    "MAP_LOD",
    "PC",
    "BLADE",
    "ENEMY",
    "NPC",
    "MOB",
    "GIMMICK",
    "FIELD_OBJ",
    "PC_WEAPON",
    "EVENT_OBJ",
    "EN_WEAPON",
    "OPTION",
    "EXTRA",
    "UI_OBJ",
};

GfObj::GfObj(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer)
    : fw::UpdatableObject(type, handle, layer), unknownf8(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown100(nullptr), _108(), unknown110(0), unknown118(false) {}

GfObj::~GfObj() {}

void GfObj::update(const fw::UpdateInfo &info) {
  unknown114.set(OBJ_STATE_UPDATING);
  GfObjUpdate::updateComponent(this, info);
  unknown114.set(OBJ_STATE_UPDATING, false);
}

void GfObj::onEvent(const fw::ObjectEvent &event) {
  if (event.type == fw::OBJECT_EVENT_UPDATE_END) {
    GfComProperty *property = getComponent<GfComProperty>();
    if (property != nullptr) {
      property->flush();
    }
  }
}

const char *GfObj::getTypeName(u32 type) { return TYPE_NAMES[type]; }

bool GfObj::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  for (u32 i = 0; i < COMPONENT_MAX; i++) {
    if ((message.unknown04 & (1 << i)) != 0 && unknown38[i] != nullptr) {
      GfComponent *component = mm::mtl::dynamicCast<GfComponent>(unknown38[i]);
      if (component != nullptr) {
        return component->recieveMessage(sender, message);
      }
    }
  }

  switch (message.unknown00) {
  case MSG_DEBUG_ACTIVATE_OBJECT_WINDOW:
    procMsgActivateObjectDebugWindow(sender, static_cast<MsgDebugActivateObjectWindow &>(message));
    return true;
  case MSG_DEBUG_DEACTIVATE_OBJECT_WINDOW:
    procMsgDeactivateObjectDebugWindow(sender, static_cast<MsgDebugDeactivateObjectWindow &>(message));
    return true;
  }

  return false;
}

void GfObj::procMsgActivateObjectDebugWindow(fw::MessageObject *sender, MsgDebugActivateObjectWindow &message) {}

void GfObj::procMsgDeactivateObjectDebugWindow(fw::MessageObject *sender, MsgDebugDeactivateObjectWindow &message) {}

void GfObj::setUpdateComponent(bool isUpdate) {
  unknown114.set(OBJ_STATE_UPDATE_ENABLE, isUpdate);
  GfObjUtil::applyExecUpdate(this);
}

GfObjLayerSpeed::Info GfObjLayerSpeed::s_info[fw::Framework::LAYER_MAX];

void GfObjLayerSpeed::initialize() {
  for (u32 layer = 0; layer < fw::Framework::LAYER_MAX; layer++) {
    s_info[layer] = Info();
  }
}

void GfObjLayerSpeed::finalize() {}

void GfObjLayerSpeed::reqApplyModelLayerSpeed(u32 layer, f32 speed) {
  s_info[layer].unknown00 = true;
  s_info[layer].unknown04 = speed;
}

bool GfObjLayerSpeed::isRequest(u32 layer) { return s_info[layer].unknown00; }

f32 GfObjLayerSpeed::getSpeed(u32 layer) { return s_info[layer].unknown04; }

void GfObjLayerSpeed::cleanup() {
  for (u32 layer = 0; layer < fw::Framework::LAYER_MAX; layer++) {
    s_info[layer] = Info();
  }
}

const mm::mtl::RTTI *GfObj::getRTTI() const { return &m_rtti; }

} // namespace gf
