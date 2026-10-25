#include "event/model_util.h"

#include "fw/fw_model_object.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "scn/scn_obj_acc.h"

namespace event {

void ModelUtil::setupRenderState(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  gf::GfComModel *model = obj->getComponent<gf::GfComModel>();
  if (model->unknown18 != nullptr) {
    gf::GfObjAcc acc(handle);
    ml::ScnObjAccResMdlInfo info(model->unknown18->getInterface());
    acc.setCameraFadeDisableForEvent(true);
    acc.setGpuClip(false);
    info.setDblBuffAlpha(false);
    info.setAlwaysMiddleTexStm(true);
    info.setAlwaysTexStm(false);
    gf::GfObjUtil::setVolumeFadeUserFlag(handle, true);
  }
}

} // namespace event
