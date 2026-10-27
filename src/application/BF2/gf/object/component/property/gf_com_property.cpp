#include "gf/object/component/property/gf_com_property.h"

namespace gf {

GfComProperty::GfComProperty() : unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr) {}

GfComProperty::~GfComProperty() {
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  if (unknown10 != nullptr) {
    unknown10->release();
  }
}

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
