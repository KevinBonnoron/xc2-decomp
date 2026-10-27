#include "gf/object/component/property/gf_com_property.h"

namespace gf {

void GfComProperty::procMsgObjectMaxHp(fw::MessageObject *object, MsgObjectMaxHp &message) {
  if (unknown10 != nullptr) {
    unknown10->unknown0c = message.maxHp;
  }
}

void GfComProperty::procMsgObjectSetHp(fw::MessageObject *object, MsgObjectSetHp &message) {
  if (unknown10 != nullptr) {
    unknown10->unknown10 = message.hp;
  }
}

void GfComProperty::procMsgObjectStopAutoHeal(fw::MessageObject *object, MsgObjectStopAutoHeal &message) {
  if (unknown10 != nullptr) {
    unknown10->unknown1a = message.isStop;
  }
}

void GfComProperty::procMsgObjectLimitHP(fw::MessageObject *object, MsgObjectLimitHP &message) {
  if (unknown10 != nullptr) {
    unknown10->unknown14 = message.limitHp;
  }
}

} // namespace gf
