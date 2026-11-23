#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

#include "framework/object/updatable_object.h"
#include "framework/sound/sound_variable_table.h"
#include "fw/fw_pad.h"
#include "fw/fw_transform.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

namespace {

// Inferred type: element of the splash sound table (SPLASH_SOUNDS of WaterInPlugin::onEvent); original name unknown. The game builds that table at run time under a
// guard (0x710057d06c to 0x710057d254: one stp per pair of names, then a memset of the unused rows), which a plain array of const char * never does:
// the same table written with const char * elements is constant-initialised and the guard disappears. An element with constructors reproduces it.
struct unknown001 {
  unknown001() : unknown00(nullptr) {}
  unknown001(const char *name) : unknown00(name) {}

  const char *unknown00; // Inferred role: sound effect name, null when the object has no sound; original member name unknown.
};

} // namespace

WaterInPlugin::WaterInPlugin() : m_comBehaviorPc(nullptr), unknown18(false) {}

WaterInPlugin::~WaterInPlugin() {}

bool WaterInPlugin::setup(GfComBehaviorPc &behavior) {
  this->m_comBehaviorPc = &behavior;
  return true;
}

void WaterInPlugin::cleanup(GfComBehaviorPc &) { m_comBehaviorPc = nullptr; }

void WaterInPlugin::onActivate() { unknown18 = false; }

void WaterInPlugin::onDeactivate() {
  if (!unknown18) {
    GfComEnvSensor *envSensor = m_comBehaviorPc->unknown08->getComponent<GfComEnvSensor>();
    GfComPropertyPc *property = m_comBehaviorPc->unknown08->getComponent<GfComPropertyPc>();
    if (envSensor != nullptr && property != nullptr && envSensor->m_envSensor.unknown24_1 && envSensor->m_envSensor.m_verticalData.unknown70.unknown00 >= property->unknown160.unknown00.y) {
      onEvent(*m_comBehaviorPc);
    }
  }
}

void WaterInPlugin::onEvent(GfComBehaviorPc &behavior) {
  unknown18 = true;
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  f32 depth = property->unknown11c;
  GfComSound *sound = behavior.unknown08->getComponent<GfComSound>();
  int threshold = 10;
  // Single-use local: places the load of the variable name before the store of the default value (0x710057cfa4 to 0x710057cfbc); without it the store comes first and the registers differ.
  const char *variableName = SND_VAR_WATER_THRESOULD_NAME;
  sound->m_soundVariableTable.getVariable(variableName, &threshold);
  f32 splashDepth = threshold * 0.01f;
  f32 bigDepth = property->unknown2f0;
  bool isBigFall = StateUtilField::isBigSplashFallSpeed(behavior);
  bool isBigSplash = isBigFall & (depth > splashDepth);
  GfComEffectCaster *plugin = behavior.unknown08->getComponent<GfComEffectCaster>();
  if (plugin != nullptr) {
    MsgFxSplashdown message(isBigSplash);
    // Same form as the other senders of a component message on main (GfComProperty::onDamage/onHeal, FootStepPlugin::emissionEffect): the direct call gives the vtable and object
    // pointers the registers x8/x9 the other way round (first difference 0x710057d038, 256/256 instructions either way); every one of those functions needs the local.
    GfObj *sender = static_cast<GfObj *>(behavior.unknown08);
    plugin->recieveMessage(sender, message);
  }
  if (isBigSplash) {
    StateUtil::playVibration(behavior, fw::VIBRATION_ID_UNKNOWN_18);
  }
  static const unknown001 SPLASH_SOUNDS[16][6] = {
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
      {"fld_splashwater_s_NORMAL", "fld_splashwater_m_NORMAL", "fld_splashwater_l_NORMAL", "fld_splashcloud_s_NORMAL", "fld_splashcloud_m_NORMAL", "fld_splashcloud_l_NORMAL"},
      {"fld_splashwater_s_NOPON", "fld_splashwater_m_NOPON", "fld_splashwater_l_NOPON", "fld_splashcloud_s_NOPON", "fld_splashcloud_m_NOPON", "fld_splashcloud_l_NOPON"},
      {"fld_splashwater_s_HUGE", "fld_splashwater_m_HUGE", "fld_splashwater_l_HUGE", "fld_splashcloud_s_HUGE", "fld_splashcloud_m_HUGE", "fld_splashcloud_l_HUGE"},
      {"fld_splashwater_s_HANA", "fld_splashwater_m_HANA", "fld_splashwater_l_HANA", "fld_splashcloud_s_HANA", "fld_splashcloud_m_HANA", "fld_splashcloud_l_HANA"},
      {"fld_splashwater_s_BENKEI", "fld_splashwater_m_BENKEI", "fld_splashwater_l_BENKEI", "fld_splashcloud_s_BENKEI", "fld_splashcloud_m_BENKEI", "fld_splashcloud_l_BENKEI"},
      {"fld_splashwater_s_ANIMAL", "fld_splashwater_m_ANIMAL", "fld_splashwater_l_ANIMAL", "fld_splashcloud_s_ANIMAL", "fld_splashcloud_m_ANIMAL", "fld_splashcloud_l_ANIMAL"},
      {"fld_splashwater_s_FLY", "fld_splashwater_m_FLY", "fld_splashwater_l_FLY", "fld_splashcloud_s_FLY", "fld_splashcloud_m_FLY", "fld_splashcloud_l_FLY"},
  };
  bool isCloud = StateUtilField::testCloud(*property);
  u32 index;
  if (depth <= splashDepth) {
    index = isCloud ? 3 : 0;
  } else if (depth <= bigDepth) {
    index = isCloud ? 4 : 1;
  } else if (isBigFall) {
    index = isCloud ? 5 : 2;
  } else {
    // Same index as the branch above: the game tests the flag with a plain tbz (0x710057d270), which the merged condition 'depth <= bigDepth || !isBigFall' turns into eor + tbnz.
    index = isCloud ? 4 : 1;
  }
  GfObjSetup *setup = GfObjUtil::getObjSetup(static_cast<GfObj *>(behavior.unknown08)->unknownf8);
  if (setup != nullptr) {
    const char *soundName = SPLASH_SOUNDS[setup->getFootStep()][index].unknown00;
    if (soundName != nullptr) {
      sound->playSe(soundName, 1.0f, mm::Vec3::zero, false);
    }
  }
}

void WaterInPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &) {
  if (!unknown18) {
    GfComEnvSensor *envSensor = behavior.unknown08->getComponent<GfComEnvSensor>();
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    if (envSensor != nullptr && property != nullptr && envSensor->m_envSensor.unknown24_1) {
      if (property->unknown160.unknown00.y < property->unknown180.unknown00.y && property->unknown180.unknown00.y > envSensor->m_envSensor.m_verticalData.unknown70.unknown00 &&
          envSensor->m_envSensor.m_verticalData.unknown70.unknown00 >= property->unknown160.unknown00.y) {
        onEvent(behavior);
      }
    }
  }
}

} // namespace pc
} // namespace gf
