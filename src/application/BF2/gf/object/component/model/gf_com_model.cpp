#include "gf/object/component/model/gf_com_model.h"

#include "fw/fw_model_object.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

bool GfComModel::isRender() const {
  if (unknown18 != nullptr) {
    return unknown18->isRender();
  }

  return false;
}

bool GfComModel::isVolumeFadeForUser() const { return GfObjUtil::isVolumeFadeForUser(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComModel::procMsgObjectNotifyDead(fw::MessageObject *, MsgObjectNotifyDead &) {}

void GfComModel::procMsgObjectNotifyDamage(fw::MessageObject *, MsgObjectNotifyDamage &) {}

void GfComModel::procMsgActivateComponentDebugWindow(fw::MessageObject *, MsgDebugActivateComponentWindow &) {}

} // namespace gf
