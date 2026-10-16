#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/scom/gf_scom_fade.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

constexpr u32 PC_PARAM_FADE = 18;
constexpr u32 FADE_CHANNEL = 1;
constexpr f32 FRAMES_PER_SECOND = 30.0f;

FadePlugin::FadePlugin() : mode(MODE_NONE), paramEntry(nullptr) {}

FadePlugin::~FadePlugin() {}

bool FadePlugin::setup(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = mm::mtl::dynamicCast<GfComPropertyPc>(behavior.owner->components[GfComProperty::COMPONENT_INDEX]);
  const fw::ParamList *paramList = property->paramList.operator->();
  paramEntry = paramList->count > PC_PARAM_FADE ? &paramList->entries[PC_PARAM_FADE] : nullptr;
  return true;
}

void FadePlugin::cleanup(GfComBehaviorPc &) {}

void FadePlugin::onActivate() { changeMode(MODE_FADE_OUT); }

void FadePlugin::changeMode(Mode mode) {
  const FadeParam *param = getParam();
  if (this->mode == mode) {
    return;
  }

  this->mode = mode;
  timer = 0.0f;
  if (mode == MODE_FADE_IN) {
    SCOM_FADE::create(FADE_CHANNEL, param->fadeTime * FRAMES_PER_SECOND, mm::Col4::zero);
  } else if (mode == MODE_FADE_OUT) {
    SCOM_FADE::create(FADE_CHANNEL, param->fadeTime * FRAMES_PER_SECOND, mm::Col4::black);
  }
}

void FadePlugin::onDeactivate() { changeMode(MODE_NONE); }

void FadePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  const FadeParam *param = getParam();
  timer += info.deltaTime;
  switch (mode) {
  case MODE_FADE_OUT:
    if (timer >= param->fadeOutTime) {
      changeMode(MODE_BLACK);
    }
    break;
  case MODE_BLACK:
    if (timer >= param->blackTime) {
      changeMode(MODE_FADE_IN);
    }
    break;
  case MODE_FADE_IN:
    if (timer >= param->fadeTime) {
      setActivate(false);
    }
    break;
  default:
    break;
  }
}

} // namespace pc
} // namespace gf
