#include "gf/object/component/property/gf_com_property.h"

#include "gf/object/component/property/gf_env_property.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep

namespace gf {

GfComProperty::GfComProperty() {}

GfComProperty::~GfComProperty() {}

void GfComProperty::procMsgObjectInvincible(fw::MessageObject *object, MsgObjectInvincible &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown18 = message.invincible;
    unknown10->unknown19 = message.invincibleSub;
  }
}

void GfComProperty::procMsgObjectMaxHp(fw::MessageObject *object, MsgObjectMaxHp &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown0c = message.maxHp;
  }
}

void GfComProperty::procMsgObjectSetHp(fw::MessageObject *object, MsgObjectSetHp &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown10 = message.hp;
  }
}

void GfComProperty::procMsgObjectStopAutoHeal(fw::MessageObject *object, MsgObjectStopAutoHeal &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown1a = message.isStop;
  }
}

void GfComProperty::procMsgObjectLimitHP(fw::MessageObject *object, MsgObjectLimitHP &message) {
  if (unknown10.get() != nullptr) {
    unknown10->unknown14 = message.limitHp;
  }
}

} // namespace gf

template void mm::mtl::UniquePtr<gf::GfTargetProperty>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::UniquePtr<gf::GfAlphaProperty>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::UniquePtr<gf::GfDebugStatusProperty>::_safe_bool_helper::safe_bool_function() const;
