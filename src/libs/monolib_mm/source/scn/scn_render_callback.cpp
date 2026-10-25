#include "scn/scn_render_callback.h"

namespace ml {

void IScnRender::cbPreUpdate(Scn *scn, SCNPRIO_CB priority) {}

void IScnRender::cbManipuPickOn(Scn *scn, SCNPRIO_CB priority) {}

void IScnRender::cbManipuPickOff(Scn *scn, SCNPRIO_CB priority) {}

void IScnRender::cbManipuPickMove(Scn *scn, SCNPRIO_CB priority) {}

void IScnRender::cbRenderAfter(Scn *scn, SCNPRIO_CB priority) {}

} // namespace ml
