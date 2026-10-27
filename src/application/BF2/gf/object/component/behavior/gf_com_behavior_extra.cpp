#include "gf/object/component/behavior/gf_com_behavior_extra.h"

#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "types.h"

namespace gf {

constexpr s32 ANNOTATION_KIND_UNKNOWN_1 = 1;

bool GfComBehaviorExtra::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 != MSG_PC_FIELD_NOTIFY_EXTRA) {
    if (message.unknown00 != MSG_OBJECT_NOTIFY_ASM_CALLBACK) {
      return false;
    }

    procMsgObjectNotifyAsmCallback(sender, static_cast<MsgObjectNotifyAsmCallback &>(message));
    return true;
  }

  procMsgPcFieldNotifyExtra(sender, static_cast<MsgPcFieldNotifyExtra &>(message));
  return true;
}

void GfComBehaviorExtra::procMsgObjectNotifyAsmCallback(fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message) {
  if (unknown08->getComponent<GfComAsm>() != nullptr) {
    const anm::AsmAnnotetion *annotation = message.unknown10;
    if (strcmp(annotation->unknown00, "attachmentTrans") == 0 && annotation->unknown08 == ANNOTATION_KIND_UNKNOWN_1) {
      unknown98.push_back(annotation->unknown10);
    }
  }
}

void GfComBehaviorExtra::procMsgPcFieldNotifyExtra(fw::MessageObject *sender, MsgPcFieldNotifyExtra &message) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    comAsm->execCmd("C_schedule_00_00", ANIM_LAYER_BASE);
  }
}

GfComBehaviorExtra::GfComBehaviorExtra() : unknown98(getAllocator(ALLOCATOR_DEFAULT)) {}

GfComBehaviorExtra::~GfComBehaviorExtra() {}

void GfComBehaviorExtra::setup() {}

void GfComBehaviorExtra::cleanup() {}

void GfComBehaviorExtra::update(const fw::UpdateInfo &info) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    for (u32 i = 0; i < unknown98.size(); i++) {
      comAsm->execCmd(unknown98[i], ANIM_LAYER_BASE);
    }
    unknown98.clear();
  }
}

const mm::mtl::RTTI *GfComBehaviorExtra::getRTTI() const { return &m_rtti; }

} // namespace gf
