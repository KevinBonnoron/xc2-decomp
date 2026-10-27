#include "grlib/cglib_depth_target.h"

#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_state.h"

namespace grlib {

void CGLibDepthTarget::clearDepth(bool isClear) { CGLibDepthCtl::clearDepthBuffer(*unknown120, isClear); }

void CGLibDepthTarget::clearValDepth(float value, bool isClear) { CGLibDepthCtl::clearValDepthBuffer(*unknown120, value, isClear); }

void CGLibDepthTarget::setRenderTarget() {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown00, unknown04, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterDepthTarget(*unknown120);
  CGLibState::endRegisterRenderTarget();
}

} // namespace grlib
