#include "gf/object/component/pc/field/gf_pc_state_field_ride_on.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/fixed_queue.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"      // IWYU pragma: keep

namespace gf {
namespace pc {

void StateFieldRideOn::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown110_0 = true; }

void StateFieldRideOn::leave(GfComBehaviorPc *behavior, ai::State *next) { behavior->getProperty()->unknown110_0 = false; }

} // namespace pc
} // namespace gf

template mm::mtl::FixStr<32> mm::mtl::FixedQueue<mm::mtl::FixStr<32>, 8>::pop_front();
