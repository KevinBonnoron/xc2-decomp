#include "gf/object/component/behavior/gf_com_behavior.h"

#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

bool GfComBehavior::procAsmCallbackCommon(const CallBackCache &cache) {
  const anm::AsmAnnotetion *annotation = cache.unknown08;
  if (strcmp(annotation->unknown00, "footStep") == 0) {
    FootStepPlugin *plugin = unknown001<FootStepPlugin>(0);
    if (plugin != nullptr) {
      plugin->notifyStep(*this, annotation->unknown10);
    }
  } else {
    if (strcmp(annotation->unknown00, "attachmentTrans") != 0) {
      return false;
    }
    MsgObjectNotifyAsmCallback message(nullptr, annotation);
    GfWeapon *weapon = GfObjUtil::getExtraMountObject(static_cast<GfObj *>(unknown08)->unknownf8);
    if (weapon != nullptr) {
      weapon->sendMessage(static_cast<GfObj *>(unknown08), message);
    }
  }

  return true;
}

void GfComBehavior::callbackAnim(GfComAsm *comAsm, const CallBackCache &cache) {
  if (procAsmCallbackCommon(cache)) {
    return;
  }

  const anm::AsmAnnotetion *annotation = cache.unknown08;
  const char *name = annotation->unknown00;
  if (strcmp(name, "weaponAttach") == 0) {
    GfMountManager::execMount(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_1);
    GfComEffectCaster *caster = unknown08->getComponent<GfComEffectCaster>();
    if (caster == nullptr) {
      return;
    }
    MsgFxWeapon message;
    message.unknown10 = GfMountManager::getOptionRight(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0);
    message.unknown18 = GfMountManager::getOptionLeft(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0);
    GfObj *sender = static_cast<GfObj *>(unknown08);
    caster->recieveMessage(sender, message);
  } else if (strcmp(name, "weaponDetach") == 0) {
    GfMountManager::execMount(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_2);
    GfComEffectCaster *caster = unknown08->getComponent<GfComEffectCaster>();
    if (caster == nullptr) {
      return;
    }
    MsgFxWeapon message;
    message.unknown08 = 1;
    message.unknown10 = GfMountManager::getOptionRight(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0);
    message.unknown18 = GfMountManager::getOptionLeft(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0);
    GfObj *sender = static_cast<GfObj *>(unknown08);
    caster->recieveMessage(sender, message);
  } else if (strcmp(name, "weaponChange") == 0) {
    GfComEffectCaster *effectCaster = unknown08->getComponent<GfComEffectCaster>();
    if (effectCaster != nullptr) {
      // The game reloads the annotation from the cache here (ldr x8, [x21, #0x8]); the local of the other branches gives 246 instructions.
      MsgObjectNotifyAsmCallback callback(comAsm, cache.unknown08);
      GfObj *sender = static_cast<GfObj *>(unknown08);
      effectCaster->recieveMessage(sender, callback);
    }
    procAnimCallback(comAsm, cache);
  } else if (strcmp(name, "weaponTrans") == 0 || strcmp(name, "battleStartEnd") == 0) {
    MsgObjectNotifyAsmCallback callback(comAsm, annotation);
    GfMountManager::sendMessage(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0, static_cast<GfObj *>(unknown08), callback);
  } else if (strcmp(name, "ikEvent") == 0) {
    const char *argument = annotation->unknown10;
    if (strcmp(argument, "syncDownOn") == 0) {
      FootIkControllerPlugin *plugin = unknown001<FootIkControllerPlugin>(3);
      if (plugin != nullptr) {
        plugin->unknown20 = true;
      }
    } else if (strcmp(argument, "syncDownOff") == 0) {
      FootIkControllerPlugin *plugin = unknown001<FootIkControllerPlugin>(3);
      if (plugin != nullptr) {
        plugin->unknown20 = false;
      }
    }
  } else {
    procAnimCallback(comAsm, cache);
  }
}

void GfComBehavior::callbackAnimForEvent(GfComEvtAnim *evtAnim, const CallBackCache &cache) { procAsmCallbackCommon(cache); }

} // namespace gf
