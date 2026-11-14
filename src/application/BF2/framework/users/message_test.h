#pragma once
#include <stddef.h>

#include "framework/applet.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace users {

// Inferred enumerator names from the message types MsgDamage and MsgGetLife; the values come from the receivers.
enum {
  MSG_UNKNOWN_0 = 0, // Inferred role: damage; original name unknown.
  MSG_UNKNOWN_1 = 1, // Inferred role: get life; original name unknown.
};

struct MsgDamage : fw::Message {
  explicit MsgDamage(int damage) : fw::Message(MSG_UNKNOWN_0, 0), unknown08(damage) {}

  int unknown08; // Inferred role: damage; original member name unknown.
};

struct MsgGetLife : fw::Message {
  MsgGetLife() : fw::Message(MSG_UNKNOWN_1, 0), unknown08(0) {}

  int unknown08; // Inferred role: life; original member name unknown.
};

class Component1 : public fw::ComponentObject {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  ~Component1() override { ; }

  u8 _10[0x1a0 - 0x10];
};

class Component2 : public Component1 {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  ~Component2() override { ; }

  u8 _1a0[0x330 - 0x1a0];
};

class Component3 : public fw::ComponentObject {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;
  ~Component3() override { ; }

  u8 _10[0x1a0 - 0x10];
};

static_assert(sizeof(Component1) == 0x1a0, "");
static_assert(sizeof(Component2) == 0x330, "");
static_assert(sizeof(Component3) == 0x1a0, "");

class Updatable1 : public fw::UpdatableObject, public fw::MessageObject {
public:
  static mm::mtl::RTTI m_rtti;

  Updatable1(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer);
  ~Updatable1() override;
  void update(const fw::UpdateInfo &info) override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void procMsgDamage(fw::MessageObject *sender, MsgDamage &message);
  void procMsgGetLife(fw::MessageObject *sender, MsgGetLife &message);

  fw::HandlePtr<fw::MessageObject> unknownf8; // Inferred role: message target; original member name unknown.
  u8 _108[0x298 - 0x108];
  int unknown298; // Inferred role: life; original member name unknown.
};

static_assert(offsetof(Updatable1, unknownf8) == 0xf8, "");
static_assert(offsetof(Updatable1, unknown298) == 0x298, "");
static_assert(sizeof(Updatable1) == 0x2a0, "");

class Updatable2 : public Updatable1 {
public:
  static mm::mtl::RTTI m_rtti;

  Updatable2(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer);
  ~Updatable2() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void update(const fw::UpdateInfo &info) override;

  u8 _2a0[0x3a0 - 0x2a0];
};

static_assert(sizeof(Updatable2) == 0x3a0, "");

class Updatable3 : public fw::UpdatableObject {
public:
  static mm::mtl::RTTI m_rtti;

  Updatable3(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer);
  ~Updatable3() override;
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u8 _e0[0x270 - 0xe0];
};

static_assert(sizeof(Updatable3) == 0x270, "");

class MessageTestApplet : public fw::Applet {
public:
  MessageTestApplet();
  ~MessageTestApplet() override;
  void finalize(const fw::Framework &framework) override;
  bool isInitialized() override;
  void enter() override;
  void update(const fw::UpdateInfo &info) override;
  void tail(const fw::UpdateInfo &info) override;
  void initialize(const fw::Framework &framework) override;
};

} // namespace users
