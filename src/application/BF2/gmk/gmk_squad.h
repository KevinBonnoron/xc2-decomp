#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkSquadLeaderGobCustom;
class GmkSquadMemberGobCustom;
class GmkSquadNavi;

class GmkSquadLeader : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  struct Data {
    u32 unknown00; // Inferred role: member definition type; original member name unknown.
    f32 unknown04; // Inferred role: circle radius; original member name unknown. The size of this structure is unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SQUAD_LEADER;

  ~GmkSquadLeader() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;
  virtual const IGmkList *getBindedSquadMemberList() const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkSquadLeader) == 0x50, "");

typedef TGmkList<GmkSquadLeader, GmkSquadLeader::BdatInfo, 0x444c5153, 2, GmkSquadLeaderGobCustom> GmkSquadLeaderList;

class GmkSquadMember : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SQUAD_MEMBER;

  ~GmkSquadMember() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugUpdateMmf() override;

  u8 _48[0x50 - 0x48];
};

static_assert(sizeof(GmkSquadMember) == 0x50, "");

typedef TGmkList<GmkSquadMember, GmkSquadMember::BdatInfo, 0x424d5153, 1, GmkSquadMemberGobCustom> GmkSquadMemberList;

class GmkSquad : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<GmkSquad> {
public:
  bool isValid() const;
  GmkSquadLeader *getBindedGmkSquadLeader() const;
  void getPosRotY(mm::Vec3 &position, f32 &rotY, u32 index) const;
  void update(f32 deltaTime);
  void removeGmkSquadNavi(GmkSquadNavi *navi);

  u8 _20[0x68 - 0x20];
  GmkSquadLeader *m_bindedGmkSquadLeader;
  int unknown70; // Inferred role: squad member count; original member name unknown.
  u8 _74[0x78 - 0x74];
  void (GmkSquad::*unknown78)(f32);               // Inferred role: seq; original member name unknown.
  mm::mtl::IntrusiveList<GmkSquadNavi> unknown88; // Inferred role: navis sorted by member index; original member name unknown.
  mm::mtl::Vector<mm::Vec3> unknowna0;            // Inferred role: member positions; original member name unknown.
  mm::mtl::Vector<f32> unknownc8;                 // Inferred role: member rotation y; original member name unknown.
  mm::mtl::Vector<bool> unknownf0;                // Inferred role: member indices in use; original member name unknown.
};

static_assert(offsetof(GmkSquad, m_bindedGmkSquadLeader) == 0x68, "");
static_assert(offsetof(GmkSquad, unknown70) == 0x70, "");
static_assert(offsetof(GmkSquad, unknown78) == 0x78, "");
static_assert(offsetof(GmkSquad, unknown88) == 0x88, "");
static_assert(offsetof(GmkSquad, unknowna0) == 0xa0, "");
static_assert(offsetof(GmkSquad, unknownc8) == 0xc8, "");
static_assert(offsetof(GmkSquad, unknownf0) == 0xf0, "");
static_assert(sizeof(GmkSquad) == 0x118, "");

// Layout evidence: the functions of GmkSquadNavi (0x71005ea67c to 0x71005eae6c) read the squad at 0x10, the object handle
// at 0x18 (compared with -1), two floats at 0x20, the member index at 0x28 and a position offset at 0x30; the node of
// GmkSquad::unknown88 is the intrusive list node at 0. GfBehaviorEnemyField holds one at offset 0x50 (0x30 bytes of
// padding followed by the offset at 0x80).
class GmkSquadNavi : public mm::mtl::IntrusiveListNode<GmkSquadNavi> {
public:
  void dispose();
  u32 getMemberDefType() const;
  bool getPosRotY(mm::Vec3 &position, f32 &rotY) const;
  bool isArrived(const mm::Vec3 &position) const;

  // Inferred helper: whether the navi is bound to a member of its squad; original name unknown.
  bool unknown001() const { return unknown10 != nullptr && unknown18 != gf::INVALID_HANDLE && unknown28 >= 0 && static_cast<u32>(unknown28) < static_cast<u32>(unknown10->unknown70); }

  // Inferred helper: unbinds the navi from its squad; original name unknown.
  void unknown002() {
    unknown10 = nullptr;
    unknown18 = gf::INVALID_HANDLE;
    unknown20.x = 0.1f;
    unknown20.y = 1.0f;
  }

  GmkSquad *unknown10;          // Inferred role: squad; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown18; // Inferred role: object handle; original member name unknown.
  mm::Vec2 unknown20;           // Inferred role: arrival radius and height; original member name unknown.
  int unknown28;                // Inferred role: member index; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  mm::Vec3 unknown30; // Inferred role: position offset; original member name unknown.
};

static_assert(offsetof(GmkSquadNavi, unknown10) == 0x10, "");
static_assert(offsetof(GmkSquadNavi, unknown18) == 0x18, "");
static_assert(offsetof(GmkSquadNavi, unknown20) == 0x20, "");
static_assert(offsetof(GmkSquadNavi, unknown28) == 0x28, "");
static_assert(offsetof(GmkSquadNavi, unknown30) == 0x30, "");
static_assert(sizeof(GmkSquadNavi) == 0x40, "");

class GmkSquadManager : public mm::mtl::PtrSingleton<GmkSquadManager> {
public:
  void update(f32 deltaTime);

  mm::mtl::IntrusiveList<GmkSquad> unknown08; // Inferred role: squads; original member name unknown.
};

static_assert(offsetof(GmkSquadManager, unknown08) == 0x08, "");
static_assert(sizeof(GmkSquadManager) == 0x20, "");

} // namespace gmk
