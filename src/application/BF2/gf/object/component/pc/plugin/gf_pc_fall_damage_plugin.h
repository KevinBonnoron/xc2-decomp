#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
class GfComPropertyPc;

enum {
  MSG_PC_FIELD_UNKNOWN_16777257 = 0x1000029, // Inferred role: msg pc field get fall max height; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777258 = 0x100002a, // Inferred role: msg pc field set fall max height; original name unknown.
};

struct MsgPcFieldGetFallMaxHeight : fw::Message {
  MsgPcFieldGetFallMaxHeight() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777257, 0x40), unknown08(0.0f), unknown0c(false) {}

  f32 unknown08;  // Inferred role: max height; original member name unknown.
  bool unknown0c; // Inferred role: valid; original member name unknown.
};

static_assert(offsetof(MsgPcFieldGetFallMaxHeight, unknown08) == 0x08, "");
static_assert(offsetof(MsgPcFieldGetFallMaxHeight, unknown0c) == 0x0c, "");

struct MsgPcFieldSetFallMaxHeight : fw::Message {
  explicit MsgPcFieldSetFallMaxHeight(f32 height) : fw::Message(MSG_PC_FIELD_UNKNOWN_16777258, 0x40), unknown08(height) {}

  f32 unknown08; // Inferred role: max height; original member name unknown.
};

static_assert(offsetof(MsgPcFieldSetFallMaxHeight, unknown08) == 0x08, "");

namespace pc {

class FallDamagePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  static const u32 PLUGIN_INDEX = 7;

  FallDamagePlugin();
  static FallDamagePlugin *create();
  ~FallDamagePlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void cacheMaxHeight(bool isReset);
  void onDeactivate() override;
  GF_OBJ_HANDLE *getAttachObj() const;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  void procMsgPcFieldGetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldGetFallMaxHeight &message);
  void procMsgPcFieldSetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldSetFallMaxHeight &message);

  GfComPropertyPc *unknown10; // Inferred role: property; original member name unknown.
  f32 unknown18;              // Inferred role: max height; original member name unknown.
  bool unknown1c;             // Inferred role: damage disabled; original member name unknown.
  GF_OBJ_HANDLE *unknown20;   // Inferred role: attach object; original member name unknown.
};

static_assert(offsetof(FallDamagePlugin, unknown10) == 0x10, "");
static_assert(offsetof(FallDamagePlugin, unknown18) == 0x18, "");
static_assert(offsetof(FallDamagePlugin, unknown20) == 0x20, "");
static_assert(sizeof(FallDamagePlugin) == 0x28, "");

} // namespace pc
} // namespace gf
