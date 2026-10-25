#include "gf/object/component/model/gf_com_model.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

void GfComModel::procMsgObjectNotifyDead(fw::MessageObject *, MsgObjectNotifyDead &) {}

void GfComModel::procMsgObjectNotifyDamage(fw::MessageObject *, MsgObjectNotifyDamage &) {}

void GfComModel::procMsgActivateComponentDebugWindow(fw::MessageObject *, MsgDebugActivateComponentWindow &) {}

} // namespace gf
