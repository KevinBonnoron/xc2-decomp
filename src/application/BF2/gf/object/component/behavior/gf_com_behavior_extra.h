#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_mtl/vector.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct MsgObjectNotifyAsmCallback;

enum {
  MSG_PC_FIELD_NOTIFY_EXTRA = 0x1000021,
};

struct MsgPcFieldNotifyExtra : fw::Message {};

class GfComBehaviorExtra : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyAsmCallback(fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message);
  void procMsgPcFieldNotifyExtra(fw::MessageObject *sender, MsgPcFieldNotifyExtra &message);
  GfComBehaviorExtra();
  ~GfComBehaviorExtra() override;
  virtual void setup();
  virtual void cleanup();
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::Vector<const char *> unknown98; // Inferred role: pending asm commands; original member name unknown.
};

static_assert(offsetof(GfComBehaviorExtra, unknown98) == 0x98, "");
static_assert(sizeof(GfComBehaviorExtra) == 0xc0, "");

} // namespace gf
