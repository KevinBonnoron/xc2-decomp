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

struct MsgPcFieldGetFallMaxHeight : fw::Message {
  f32 maxHeight;
  bool isValid;
};

static_assert(offsetof(MsgPcFieldGetFallMaxHeight, maxHeight) == 0x08, "");
static_assert(offsetof(MsgPcFieldGetFallMaxHeight, isValid) == 0x0c, "");

struct MsgPcFieldSetFallMaxHeight : fw::Message {
  f32 maxHeight;
};

static_assert(offsetof(MsgPcFieldSetFallMaxHeight, maxHeight) == 0x08, "");

namespace pc {

class FallDamagePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  FallDamagePlugin();
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

  GfComPropertyPc *property;
  f32 maxHeight;
  bool isDamageDisabled;
  GF_OBJ_HANDLE *attachObj;
};

static_assert(offsetof(FallDamagePlugin, property) == 0x10, "");
static_assert(offsetof(FallDamagePlugin, maxHeight) == 0x18, "");
static_assert(offsetof(FallDamagePlugin, attachObj) == 0x20, "");
static_assert(sizeof(FallDamagePlugin) == 0x28, "");

} // namespace pc
} // namespace gf
