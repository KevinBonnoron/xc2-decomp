#include "framework/users/message_test.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "framework/message/message_manager.h"
#include "fw/fw_pad.h"

namespace users {

const mm::mtl::RTTI *Component1::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *Component2::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *Component3::getRTTI() const { return &m_rtti; }

Updatable1::Updatable1(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer) : fw::UpdatableObject(type, handle, layer), unknown298(100) {}

Updatable1::~Updatable1() { ; }

void Updatable1::update(const fw::UpdateInfo &info) {}

bool Updatable1::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_DAMAGE:
    procMsgDamage(sender, static_cast<MsgDamage &>(message));
    return true;
  case MSG_GET_LIFE:
    procMsgGetLife(sender, static_cast<MsgGetLife &>(message));
    return true;
  }

  return false;
}

void Updatable1::procMsgDamage(fw::MessageObject *sender, MsgDamage &message) { unknown298 -= message.unknown08; }

void Updatable1::procMsgGetLife(fw::MessageObject *sender, MsgGetLife &message) { message.unknown08 = unknown298; }

const mm::mtl::RTTI *Updatable1::getRTTI() const { return &m_rtti; }

Updatable2::Updatable2(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer) : Updatable1(type, handle, layer) {}

Updatable2::~Updatable2() { ; }

const mm::mtl::RTTI *Updatable2::getRTTI() const { return &m_rtti; }

// Inferred role: queues a message of type T for the receiver after a delay; the game keeps it in message_object.h; original name unknown.
template <typename T> static void unknown001(fw::MessageObject *sender, fw::MessageObject *receiver, f32 delay, int value) {
  if (fw::MessageManager::get() != nullptr) {
// The game compiles this allocation from line 61 of framework/message/message_object.h (its file string and line are
// arguments of operator new); the helper's original definition there is not reconstructed yet.
#line 61 "framework/message/message_object.h"
    T *message = new (fw::Framework::getAllocator(), 4, __FILE__, __LINE__) T(value);
    fw::MessageManager::get()->push(sender, receiver, message, delay);
  }
}

void Updatable2::update(const fw::UpdateInfo &info) {
  u32 trigger = fw::PadManager::getControlPadData(0)->unknown04;
  fw::MessageObject *target = unknownf8.get();
  if ((trigger & 0x4) != 0) {
    MsgDamage message(2);
    sendMessage(target, message);
  } else if ((trigger & 0x2) != 0) {
    unknown001<MsgDamage>(this, target, 5.0f, 2);
  } else if ((trigger & 0x1) != 0) {
    unknown001<MsgDamage>(this, target, 5.0f, 2);
    unknown001<MsgDamage>(this, target, 6.0f, 3);
  } else if ((trigger & 0x8) != 0) {
    MsgGetLife message;
    sendMessage(target, message);
  }
}

Updatable3::Updatable3(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer) : fw::UpdatableObject(type, handle, layer) {}

Updatable3::~Updatable3() { ; }

void Updatable3::update(const fw::UpdateInfo &info) {}

const mm::mtl::RTTI *Updatable3::getRTTI() const { return &m_rtti; }

MessageTestApplet::MessageTestApplet() {}

MessageTestApplet::~MessageTestApplet() {}

void MessageTestApplet::finalize(const fw::Framework &framework) {}

bool MessageTestApplet::isInitialized() { return true; }

void MessageTestApplet::enter() {}

void MessageTestApplet::update(const fw::UpdateInfo &info) {}

void MessageTestApplet::tail(const fw::UpdateInfo &info) {}

} // namespace users
