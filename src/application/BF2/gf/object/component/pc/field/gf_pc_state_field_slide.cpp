#include "gf/object/component/pc/field/gf_pc_state_field_slide.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"

namespace gf {
namespace pc {

void StateFieldSlide::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown310.unknown11_3 = true; }

void StateFieldSlide::leave(GfComBehaviorPc *behavior, ai::State *next) { behavior->getProperty()->unknown310.unknown11_3 = false; }

void StateFieldSlide::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
