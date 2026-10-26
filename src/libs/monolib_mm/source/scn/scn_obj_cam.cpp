#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_mtl/fixstr.h"

namespace ml {
class DebDraw;

const char *ScnObjCam::getName() const { return m_name.c_str(); }

void ScnObjCam::renderDebug(DebDraw *debDraw) {}

void ScnObjCam::setCopydataCam(bool isCopydata) {}

template class threadval<ScnObjCam::RENDER_INFO>;

} // namespace ml
