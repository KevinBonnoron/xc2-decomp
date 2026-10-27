#include "gf/object/component/pc/gf_com_property_pc.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

void GfComPropertyPc::resetInput() {
  unknown60.unknown00 = 0.0f;
  unknown60.unknown04 = 0.0f;
  unknown60.unknown08.clear();
  unknown6c.unknown00 = 0.0f;
  unknown6c.unknown04 = 0.0f;
  unknown6c.unknown08.clear();
}

void GfComPropertyPc::procMsgPcFieldWarpCancel(fw::MessageObject *object, MsgPcFieldWarpCancel &message) { unknown113_2 = false; }

} // namespace gf
