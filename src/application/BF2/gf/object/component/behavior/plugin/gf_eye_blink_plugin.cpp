#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "ml/rand.h"

namespace gf {

static const char *const EYE_CLOSE_STATE = "S_eye_close";

EyeBlinkPlugin::EyeBlinkPlugin() : unknown10(nullptr), unknown18(0.0f), unknown1c(MODE_UNKNOWN_0), unknown20(nullptr) {}

bool EyeBlinkPlugin::setup(GfComBehavior &behavior) {
  unknown10 = &behavior;
  unknown20 = fw::ParamManager::get()->unknown460;
  return true;
}

void EyeBlinkPlugin::cleanup(GfComBehavior &) {}

void EyeBlinkPlugin::onActivate() {
  setMode(MODE_UNKNOWN_0);
  resetTimer();
}

void EyeBlinkPlugin::setMode(Mode mode) {
  GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  const unknown001 *param = getParameter();
  if (param == nullptr) {
    return;
  }

  if (unknown1c == mode) {
    return;
  }

  switch (mode) {
  case MODE_UNKNOWN_0: {
    f32 rate = ml::mtRandf1();
    unknown18 = rate * param->unknown04 + (1.0f - rate) * param->unknown00;
    break;
  }
  case MODE_UNKNOWN_1:
  case MODE_UNKNOWN_3:
    comAsm->easeIn(EYE_CLOSE_STATE, param->unknown08, ANIM_LAYER_EYE);
    unknown18 = param->unknown08 + param->unknown10;
    break;
  case MODE_UNKNOWN_2:
  case MODE_UNKNOWN_4:
    comAsm->easeOut(EYE_CLOSE_STATE, param->unknown0c, ANIM_LAYER_EYE);
    unknown18 = param->unknown0c;
    break;
  default:
    break;
  }
  unknown1c = mode;
}

void EyeBlinkPlugin::resetTimer() {
  const unknown001 *param = getParameter();
  if (param != nullptr) {
    f32 rate = ml::mtRandf1();
    unknown18 = rate * param->unknown04 + (1.0f - rate) * param->unknown00;
  }
}

void EyeBlinkPlugin::onDeactivate() {
  if (unknown1c != MODE_UNKNOWN_0) {
    const unknown001 *param = getParameter();
    GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
    if (param != nullptr && comAsm != nullptr) {
      comAsm->easeOut(EYE_CLOSE_STATE, param->unknown0c, ANIM_LAYER_EYE);
    }
  }
}

const EyeBlinkPlugin::unknown001 *EyeBlinkPlugin::getParameter() const {
  if (unknown20 == nullptr) {
    return nullptr;
  }
  if (unknown20->unknown0c == 0 || unknown20->unknown10 == nullptr) {
    return nullptr;
  }
  return static_cast<const unknown001 *>(unknown20->unknown10->param);
}

void EyeBlinkPlugin::update(GfComBehavior &, const fw::UpdateInfo &info) {
  unknown18 -= info.unknown04;
  if (unknown18 <= 0.0f) {
    switch (unknown1c) {
    case MODE_UNKNOWN_0:
      setMode(MODE_UNKNOWN_1);
      break;
    case MODE_UNKNOWN_1:
      setMode(MODE_UNKNOWN_2);
      break;
    case MODE_UNKNOWN_2:
      if (testDouble()) {
        setMode(MODE_UNKNOWN_3);
        break;
      }
      setMode(MODE_UNKNOWN_0);
      break;
    case MODE_UNKNOWN_3:
      setMode(MODE_UNKNOWN_4);
      break;
    case MODE_UNKNOWN_4:
      setMode(MODE_UNKNOWN_0);
      break;
    }
  }
}

bool EyeBlinkPlugin::testDouble() {
  const unknown001 *param = getParameter();
  if (param == nullptr) {
    return false;
  }
  return ml::mtRandf1() < param->unknown14;
}

} // namespace gf
