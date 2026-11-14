#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/scom/gf_scom_fade.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

constexpr u32 PC_UNKNOWN_18 = 18; // Inferred role: pc param fade; original name unknown.
constexpr u32 FADE_UNKNOWN_1 = 1; // Inferred role: fade channel; original name unknown.
constexpr f32 unknown016 = 30.0f; // Inferred role: frames per second; original name unknown.

FadePlugin::FadePlugin() : unknown0c(MODE_UNKNOWN_0), unknown18(nullptr) {}

FadePlugin::~FadePlugin() {}

bool FadePlugin::setup(GfComBehaviorPc &behavior) {
  GfComPropertyPc *property = mm::mtl::dynamicCast<GfComPropertyPc>(behavior.unknown08->unknown38[GfComProperty::COMPONENT_INDEX]);
  const fw::ParamList *paramList = property->unknown310.unknown08.operator->();
  unknown18 = paramList->unknown0c > PC_UNKNOWN_18 ? &paramList->unknown10[PC_UNKNOWN_18] : nullptr;
  return true;
}

void FadePlugin::cleanup(GfComBehaviorPc &) {}

void FadePlugin::onActivate() { changeMode(MODE_UNKNOWN_3); }

void FadePlugin::changeMode(Mode mode) {
  const FadeParam *param = getParam();
  if (this->unknown0c == mode) {
    return;
  }

  this->unknown0c = mode;
  unknown10 = 0.0f;
  if (mode == MODE_UNKNOWN_1) {
    SCOM_FADE::create(FADE_UNKNOWN_1, param->fadeOutTime * unknown016, mm::Col4::zero);
  } else if (mode == MODE_UNKNOWN_3) {
    SCOM_FADE::create(FADE_UNKNOWN_1, param->fadeOutTime * unknown016, mm::Col4::black);
  }
}

void FadePlugin::onDeactivate() { changeMode(MODE_UNKNOWN_0); }

void FadePlugin::update(GfComBehaviorPc &, const fw::UpdateInfo &info) {
  const FadeParam *param = getParam();
  unknown10 += info.unknown04;
  switch (unknown0c) {
  case MODE_UNKNOWN_3:
    if (unknown10 >= param->fadeInTime) {
      changeMode(MODE_UNKNOWN_2);
    }
    break;
  case MODE_UNKNOWN_2:
    if (unknown10 >= param->blackOutTime) {
      changeMode(MODE_UNKNOWN_1);
    }
    break;
  case MODE_UNKNOWN_1:
    if (unknown10 >= param->fadeOutTime) {
      setActivate(false);
    }
    break;
  default:
    break;
  }
}

} // namespace pc
} // namespace gf
