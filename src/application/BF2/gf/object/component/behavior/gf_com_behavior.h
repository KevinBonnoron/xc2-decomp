#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/message/message_object.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComAsm;
struct CallBackCache;

enum {
  MSG_PC_GET_LOOK_POINT = 0x1000008,
  MSG_OBJECT_GET_VELOCITY = 0x1000046,
};

struct MsgPcGetLookPoint : fw::Message {
  mm::Vec3 unknown10; // Inferred role: look point; original member name unknown.
  bool unknown20;     // Inferred role: valid; original member name unknown.
};

static_assert(offsetof(MsgPcGetLookPoint, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcGetLookPoint, unknown20) == 0x20, "");

struct MsgObjectGetVelocity : fw::Message {
  mm::Vec3 unknown10; // Inferred role: velocity; original member name unknown.
};

static_assert(offsetof(MsgObjectGetVelocity, unknown10) == 0x10, "");

class GfComBehavior : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 6;

  GfComBehavior() : unknown10(fw::Allocator::getProcAllocator()) {}

  void changeLayer(u32 oldLayer, u32 newLayer) override {}
  virtual void update(const fw::UpdateInfo &info) = 0;
  virtual void procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) {}

  PluginManager unknown10; // Inferred role: plugin manager; original member name unknown.
};

static_assert(offsetof(GfComBehavior, unknown10) == 0x10, "");
static_assert(sizeof(GfComBehavior) == 0x98, "");

} // namespace gf
