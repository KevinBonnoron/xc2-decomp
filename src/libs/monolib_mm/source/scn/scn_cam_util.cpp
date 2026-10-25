#include "ml/scn_cam_util.h"

namespace ml {

bool ScnCamUtil::getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, const mm::Vec3 &position) { return getScreenPos(screen, cam, false, position); }

} // namespace ml
