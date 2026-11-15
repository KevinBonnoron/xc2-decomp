#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct MsgObjectNotifyAsmCallback;

enum {
  MSG_UNKNOWN_16777249 = 0x1000021, // Inferred role: msg pc field notify extra; original name unknown.
};

// Layout from StateUtilField::notifyJumpEnd (1.0.0: 0x7100550778): it builds the message on the stack as id 0x1000021, size 0x40 and a zero
// word at 0x08, which the receiver never reads.
struct MsgPcFieldNotifyExtra : fw::Message {
  MsgPcFieldNotifyExtra() : fw::Message(MSG_UNKNOWN_16777249, 0x40), unknown08(0) {}

  u32 unknown08; // Role and original member name unknown, zero in the jump end notification.
};

class GfComBehaviorExtra : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyAsmCallback(fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message);
  void procMsgPcFieldNotifyExtra(fw::MessageObject *sender, MsgPcFieldNotifyExtra &message);
  GfComBehaviorExtra();
  ~GfComBehaviorExtra() override;
  void setup();
  void cleanup();
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::Vector<const char *> unknown98; // Inferred role: pending asm commands; original member name unknown.
};

static_assert(offsetof(GfComBehaviorExtra, unknown98) == 0x98, "");
static_assert(sizeof(GfComBehaviorExtra) == 0xc0, "");

} // namespace gf
