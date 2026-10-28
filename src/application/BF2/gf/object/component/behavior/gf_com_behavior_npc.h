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

struct CBdatWrapper;

namespace gf {

class GfComAsm;
struct MsgDebugActivateComponentWindow;

class GfComBehaviorNpc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  struct BdatInfo {
    void create(const CBdatWrapper &bdat, int id, const GfComBehaviorNpc &npc);
    int getTalkBonusFlagId() const;
    bool isIconTalkBonus() const;
    void setTalkBonusFlag() const;
    static f32 getDistYThreshold();

    u16 unknown00;  // Inferred role: shop id; original member name unknown.
    f32 unknown04;  // Inferred role: squared close range; original member name unknown.
    f32 unknown08;  // Inferred role: move speed; original member name unknown.
    f32 unknown0c;  // Inferred role: squared reaction range; original member name unknown.
    u16 unknown10;  // Inferred role: reaction percent; original member name unknown.
    u16 unknown12;  // Inferred role: reaction motion; original member name unknown.
    u16 unknown14;  // Inferred role: battle reaction; original member name unknown.
    u16 unknown16;  // Inferred role: battle motion; original member name unknown.
    u16 unknown18;  // Inferred role: event id used as talk bonus; original member name unknown.
    bool unknown1a; // Inferred role: talk bonus enabled; original member name unknown.
  };

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void validateBindedGmkInstInfo(bool param1);
  gmk::AGmkBase *getBindedGmkInst() const;
  void setGoalPos(const mm::Vec3 &position);

  u8 _98[0xc0 - 0x98];
  mm::Vec3 unknownc0; // Inferred role: goal position; original member name unknown.
  u8 _d0[0x100 - 0xd0];
  bool unknown100; // Role and original member name unknown.
  GfComAsm *getComAsm() const;
};

static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown18) == 0x18, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown1a) == 0x1a, "");
static_assert(sizeof(GfComBehaviorNpc::BdatInfo) == 0x1c, "");
static_assert(offsetof(GfComBehaviorNpc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown100) == 0x100, "");

} // namespace gf
