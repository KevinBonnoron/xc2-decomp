#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/message/message_object.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;
struct CallBackCache;
class Plugin;

enum {
  MSG_PC_GET_LOOK_POINT = 0x1000008,
  MSG_OBJECT_GET_VELOCITY = 0x1000046,
};

struct MsgPcGetLookPoint : fw::Message {
  MsgPcGetLookPoint() : fw::Message(MSG_PC_GET_LOOK_POINT, 0x40), unknown10(mm::Vec3::zero), unknown20(false) {}

  mm::Vec3 unknown10; // Inferred role: look point; original member name unknown.
  bool unknown20;     // Inferred role: valid; original member name unknown.
};

static_assert(offsetof(MsgPcGetLookPoint, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcGetLookPoint, unknown20) == 0x20, "");

struct MsgObjectGetVelocity : fw::Message {
  mm::Vec3 unknown10; // Inferred role: velocity; original member name unknown.
};

static_assert(offsetof(MsgObjectGetVelocity, unknown10) == 0x10, "");

struct MsgPcFieldNotifyAction : fw::Message {
  MsgPcFieldNotifyAction(u32 action) : fw::Message(0x100000d, 0x40), unknown08(action) {}

  u32 unknown08; // Inferred role: action, 0 when the player accesses the object, 1 when the access ends; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyAction, unknown08) == 0x08, "");

struct MsgPcFieldGetAccessType : fw::Message {
  MsgPcFieldGetAccessType() : fw::Message(0x100000c, 0x40), unknown08(0), unknown0c(true), unknown0d(false) {}

  u32 unknown08;  // Inferred role: access type; original member name unknown.
  bool unknown0c; // Inferred role: access enabled; original member name unknown.
  bool unknown0d; // Inferred role: set for a salvage point; original member name unknown.
};

static_assert(offsetof(MsgPcFieldGetAccessType, unknown08) == 0x08, "");
static_assert(offsetof(MsgPcFieldGetAccessType, unknown0c) == 0x0c, "");
static_assert(offsetof(MsgPcFieldGetAccessType, unknown0d) == 0x0d, "");

class GfComBehavior : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 6;

  GfComBehavior() : unknown10(fw::Allocator::getProcAllocator()) {}

  void changeLayer(u32 oldLayer, u32 newLayer) override {}
  virtual void update(const fw::UpdateInfo &info) = 0;
  virtual void procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) {}

  void callbackAnim(GfComAsm *comAsm, const CallBackCache &cache);

  // Inferred helper: plugin at index when it has the type T; original name unknown.
  template <typename T> T *unknown001(u32 index) const {
    if (index < unknown10.unknown28.size()) {
      Plugin *plugin = unknown10.unknown28[index];
      if (plugin != nullptr) {
        return mm::mtl::dynamicCast<T>(plugin);
      }
    }
    return nullptr;
  }

  PluginManager unknown10; // Inferred role: plugin manager; original member name unknown.
};

static_assert(offsetof(GfComBehavior, unknown10) == 0x10, "");
static_assert(sizeof(GfComBehavior) == 0x98, "");

} // namespace gf
