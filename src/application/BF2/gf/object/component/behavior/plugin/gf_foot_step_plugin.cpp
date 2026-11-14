#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"

#include <math.h>
#include <string.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_param_manager.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

FootStepPlugin::FootStepPlugin() : unknown09(false) {}

bool FootStepPlugin::setup(GfComBehavior &behavior) {
  setAnkleHeight(behavior);
  return true;
}

void FootStepPlugin::cleanup(GfComBehavior &) {}

void FootStepPlugin::setAnkleHeight(GfComBehavior &behavior) {
  const FootStepParam *param = getParam();
  GfComEffectCaster *caster = behavior.unknown08->getComponent<GfComEffectCaster>();
  if (caster != nullptr) {
    caster->unknown24 = static_cast<f32>(param->ankleHeight) * 0.01f;
  }
  GfComSound *sound = behavior.unknown08->getComponent<GfComSound>();
  if (sound != nullptr) {
    sound->unknown001(SND_VAR_WATER_THRESOULD_NAME, param->ankleHeight);
  }
}

void FootStepPlugin::update(GfComBehavior &behavior, const fw::UpdateInfo &info) {
  const FootStepParam *param = getParam();
  f32 rapidSpeed = param->rapidSpeed / 3.6f;
  MsgObjectGetVelocity message;
  GfObj *obj = static_cast<GfObj *>(behavior.unknown08);
  obj->sendMessage(obj, message);
  message.unknown10.y = 0.0f;
  unknown09 = sqrtf(message.unknown10.x * message.unknown10.x + message.unknown10.y * message.unknown10.y + message.unknown10.z * message.unknown10.z) >= rapidSpeed;
  GfComSound *sound = behavior.unknown08->getComponent<GfComSound>();
  if (sound != nullptr) {
    sound->unknown001(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_4), unknown09);
  }
}

void FootStepPlugin::onActivate() { unknown09 = false; }

void FootStepPlugin::onDeactivate() {}

const FootStepParam *FootStepPlugin::getParam() {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->unknown408[24];
  const fw::ParamList::unknown005 *entry = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
  return entry != nullptr ? static_cast<const FootStepParam *>(entry->param) : nullptr;
}

GfEnvProperty::GROUND_INDEX getFootGroundIndex(const char *name) {
  if (strcmp("right", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_2;
  }
  if (strcmp("left", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_1;
  }
  if (strcmp("right00", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_2;
  }
  if (strcmp("left00", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_1;
  }
  if (strcmp("right01", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_4;
  }
  if (strcmp("left01", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_3;
  }
  if (strcmp("right02", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_6;
  }
  if (strcmp("left02", name) == 0) {
    return GfEnvProperty::GROUND_INDEX_UNKNOWN_5;
  }
  return GfEnvProperty::GROUND_INDEX_UNKNOWN_0;
}

void FootStepPlugin::emissionEffect(GfComBehavior &behavior, GfEnvProperty::GROUND_INDEX ground) {
  GfComEffectCaster *caster = behavior.unknown08->getComponent<GfComEffectCaster>();
  if (caster != nullptr) {
    MsgFxFootPrint message(ground);
    message.unknown0c = unknown09;
    GfObj *obj = static_cast<GfObj *>(behavior.unknown08);
    caster->recieveMessage(obj, message);
  }
}

bool isLeftFoot(GfEnvProperty::GROUND_INDEX ground) {
  switch (ground) {
  case GfEnvProperty::GROUND_INDEX_UNKNOWN_1:
  case GfEnvProperty::GROUND_INDEX_UNKNOWN_3:
  case GfEnvProperty::GROUND_INDEX_UNKNOWN_5:
    return true;
  default:
    return false;
  }
}

bool isBearFoot(GfEnvProperty::GROUND_INDEX ground) { return ground == GfEnvProperty::GROUND_INDEX_UNKNOWN_3 || ground == GfEnvProperty::GROUND_INDEX_UNKNOWN_4; }

const FootStepParam *getFootParam(fw::ParamAdapter &adapter) { return adapter.get<FootStepParam>(); }

} // namespace gf
