#include "gf/object/component/behavior/gf_com_behavior.h"

#include <string.h>

#include "anm/anm_asm_listener.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/gf_obj.h"
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

void GfComBehavior::callbackAnimForEvent(GfComEvtAnim *evtAnim, const CallBackCache &cache) { procAsmCallbackCommon(cache); }

} // namespace gf
