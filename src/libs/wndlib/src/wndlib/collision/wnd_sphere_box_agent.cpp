// Original file name from the game string .../wndlib/src/wndlib/collision/wnd_sphere_box_agent.cpp.
#include "wnd/wnd_dispatcher.h" // IWYU pragma: keep
#include "wnd/wnd_shape.h"

namespace wnd {

void SphereBoxAgent::registerAgent(Dispatcher &dispatcher) { dispatcher.unknown10[SHAPE_TYPE_UNKNOWN_0][SHAPE_TYPE_UNKNOWN_1] = &SphereBoxAgent::processCollision; }

} // namespace wnd
