#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class MessageObject;
} // namespace fw

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace gf {

class GfComAsm;
struct MsgDebugActivateComponentWindow;

class GfComBehaviorNpc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void validateBindedGmkInstInfo(bool param1);
  gmk::AGmkBase *getBindedGmkInst() const;
  void setGoalPos(const mm::Vec3 &position);

  u8 _10[0xc0 - 0x10];
  mm::Vec3 unknownc0; // Inferred role: goal position; original member name unknown.
  u8 _d0[0x100 - 0xd0];
  bool unknown100; // Role and original member name unknown.
  GfComAsm *getComAsm() const;
};

static_assert(offsetof(GfComBehaviorNpc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown100) == 0x100, "");

} // namespace gf
