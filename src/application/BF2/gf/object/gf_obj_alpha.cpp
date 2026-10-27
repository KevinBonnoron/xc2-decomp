#include "gf/object/gf_obj_alpha.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"

namespace gf {

void GfObjAlpha::updateCamera(GF_OBJ_HANDLE *handle, f32 deltaTime, bool isForce) {
  GfObjAcc acc(handle);
  {
    DataParamAcc paramAcc(handle);
    if (paramAcc.isNoCameraFade()) {
      acc.setAlphaCamera(1.0f);
      return;
    }
  }

  if (GfObjUtil::getParentObj(acc.getObj()) != nullptr) {
    acc.setAlphaCamera(1.0f);
    return;
  }

  f32 alpha = acc.getAlphaCamera();
  if (!acc.isCameraFadeAllOK()) {
    if (alpha <= 1e-06f) {
      alpha = 1.0f;
    }
  } else {
    f32 fadeStep = deltaTime * 0.125f;
    bool isCollide = acc.isCollideModelClip();
    if (isForce || !isCollide || acc.isCameraFadeDisableForEvent() || acc.isCameraFadeDisableForBattle()) {
      if (alpha < 1.0f) {
        alpha = mm::min(fadeStep + alpha, 1.0f);
      }
    } else if (alpha > 0.0f) {
      alpha -= fadeStep;
      alpha = alpha > 0.0f ? alpha : 0.0f;
    }
  }

  acc.setAlphaCamera(alpha);
}

f32 GfObjAlpha::getTotalAlpha(const GfComProperty *property) {
  if (property != nullptr && property->unknown20 != nullptr) {
    return property->unknown20->unknown18;
  }

  return 1.0f;
}

} // namespace gf
