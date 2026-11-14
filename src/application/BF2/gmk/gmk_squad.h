#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
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
    f32 unknown04; // Inferred role: circle radius; original member name unknown.
    int unknown08; // Inferred role: first member index; original member name unknown.
    int unknown0c; // Inferred role: last member index; original member name unknown. The size of this structure is unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SQUAD_LEADER; // Inferred name; shared by every gimmick class for the TGmkList templates.

  GmkSquadLeader() : unknown48(nullptr) {}
  ~GmkSquadLeader() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;
  virtual const IGmkList *getBindedSquadMemberList() const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  void *unknown48; // Inferred role: cleared by the constructor; original member name unknown.
};

static_assert(sizeof(GmkSquadLeader) == 0x50, "");

typedef TGmkList<GmkSquadLeader, GmkSquadLeader::BdatInfo, 0x444c5153, 2, GmkSquadLeaderGobCustom> GmkSquadLeaderList;

class GmkSquadMember : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SQUAD_MEMBER; // Inferred name; shared by every gimmick class for the TGmkList templates.

  GmkSquadMember() : unknown48(nullptr) {}
  ~GmkSquadMember() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugUpdateMmf() override;

  void *unknown48; // Inferred role: cleared by the constructor; original member name unknown.
};

static_assert(sizeof(GmkSquadMember) == 0x50, "");

typedef TGmkList<GmkSquadMember, GmkSquadMember::BdatInfo, 0x424d5153, 1, GmkSquadMemberGobCustom> GmkSquadMemberList;

class GmkSquad : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<GmkSquad> {
public:
  // Layout evidence: create (0x7100614dd8) copies the 12 bytes, the constructor and dispose (0x71006151b8) store -1, -1 and 1.
  struct CreateInfo {
    CreateInfo() : unknown00(-1), unknown04(-1), unknown08(1) {}

    int unknown00; // Inferred role: gmk set id; original member name unknown.
    int unknown04; // Inferred role: index of the squad leader gimmick; original member name unknown.
    int unknown08; // Inferred role: circle member count; original member name unknown.
  };

  explicit GmkSquad(const CreateInfo *info);
  ~GmkSquad() override { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  bool isValid() const;
  const GmkSquadLeader *getBindedGmkSquadLeader() const;
  void getPosRotY(mm::Vec3 &position, f32 &rotY, u32 index) const;
  void update(f32 deltaTime);
  void addGmkSquadNavi(GmkSquadNavi *navi);
  void removeGmkSquadNavi(GmkSquadNavi *navi);
  void seqInit(f32 deltaTime);
  void updatePosRotY(bool isImmediate);
  void updateMemberPosRotY_MemberDef_Circle(u32 index);
  void seqUpdate(f32 deltaTime);
  void debugDraw() const;

  // Inferred helper: the gimmick of the accessor as the squad leader it was created for; original name unknown.
  const GmkSquadLeader *unknown003() const { return static_cast<const GmkSquadLeader *>(m_bindedGmkSquadLeader.unknown38); }

  CreateInfo unknown20; // Inferred role: create info; original member name unknown.
  f32 unknown2c;        // Inferred role: member distance scale; original member name unknown.
  // Named from getBindedGmkSquadLeader, which returns its gimmick. Layout evidence: the constructor (0x7100614d08) builds a GmkAcc
  // here, create calls GmkAcc::create on it and dispose inlines GmkAcc::dispose (GmkAccManager::removeGmkAcc at 0x710061518c).
  GmkAcc m_bindedGmkSquadLeader;
  u32 unknown70; // Inferred role: squad member count; original member name unknown.
  u8 _74[0x78 - 0x74];
  void (GmkSquad::*unknown78)(f32);               // Inferred role: seq; original member name unknown.
  mm::mtl::IntrusiveList<GmkSquadNavi> unknown88; // Inferred role: navis sorted by member index; original member name unknown.
  mm::mtl::Vector<mm::Vec3> unknowna0;            // Inferred role: member positions; original member name unknown.
  mm::mtl::Vector<f32> unknownc8;                 // Inferred role: member rotation y; original member name unknown.
  mm::mtl::Vector<bool> unknownf0;                // Inferred role: member indices in use; original member name unknown.
};

static_assert(sizeof(GmkSquad::CreateInfo) == 0xc, "");
static_assert(offsetof(GmkSquad, unknown20) == 0x20, "");
static_assert(offsetof(GmkSquad, unknown2c) == 0x2c, "");
static_assert(offsetof(GmkSquad, m_bindedGmkSquadLeader) == 0x30, "");
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
  struct CreateInfo {
    CreateInfo() : unknown00(nullptr), unknown08(gf::unknown020) {
      unknown10 = 0.1f;
      unknown14 = 1.0f;
    }

    GmkSquad *unknown00;          // Inferred role: squad; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown08; // Inferred role: object handle; original member name unknown.
    f32 unknown10;                // Inferred role: arrival radius; original member name unknown.
    f32 unknown14;                // Inferred role: arrival height; original member name unknown.
  };

  struct UpdateInfo {
    UpdateInfo() : position(mm::Vec3::zero) {}

    mm::Vec3 position; // Inferred role: position of the member; original member name unknown.
  };

  GmkSquadNavi() {
    unknown28 = -1;
    unknown30 = mm::Vec3::zero;
  }

  ~GmkSquadNavi() { dispose(); }
  void create(const CreateInfo &info);
  void update(const UpdateInfo &info);
  void dispose();
  u32 getMemberDefType() const;
  bool getPosRotY(mm::Vec3 &position, f32 &rotY) const;
  bool isArrived(const mm::Vec3 &position) const;

  // Inferred helper: whether the navi is bound to a member of its squad; original name unknown.
  bool unknown001() const {
    if (unknown10.unknown00 != nullptr && unknown10.unknown08 != gf::unknown020 && unknown28 >= 0) {
      if (static_cast<u32>(unknown28) < unknown10.unknown00->unknown70) {
        return true;
      }
    }

    return false;
  }

  // Inferred helper: unbinds the navi from its squad; original name unknown.
  void unknown002() {
    unknown10.unknown00 = nullptr;
    unknown10.unknown08 = gf::unknown020;
    unknown10.unknown10 = 0.1f;
    unknown10.unknown14 = 1.0f;
  }

  CreateInfo unknown10; // Inferred role: create info; original member name unknown.
  int unknown28;        // Inferred role: member index; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  mm::Vec3 unknown30; // Inferred role: position offset; original member name unknown.
};

static_assert(offsetof(GmkSquadNavi::CreateInfo, unknown08) == 0x08, "");
static_assert(offsetof(GmkSquadNavi::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(GmkSquadNavi::CreateInfo, unknown14) == 0x14, "");
static_assert(sizeof(GmkSquadNavi::CreateInfo) == 0x18, "");
static_assert(offsetof(GmkSquadNavi, unknown10) == 0x10, "");
static_assert(offsetof(GmkSquadNavi, unknown28) == 0x28, "");
static_assert(offsetof(GmkSquadNavi, unknown30) == 0x30, "");
static_assert(sizeof(GmkSquadNavi) == 0x40, "");

} // namespace gmk
