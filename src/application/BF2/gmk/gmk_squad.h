#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gmk {

class GmkSquadLeaderGobCustom;
class GmkSquadMemberGobCustom;

class GmkSquadLeader : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
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

class GmkSquad : public mm::mtl::ReferenceObject {
public:
  bool isValid() const;
  GmkSquadLeader *getBindedGmkSquadLeader() const;

  u8 _10[0x68 - 0x10];
  GmkSquadLeader *m_bindedGmkSquadLeader;
  int unknown70; // Inferred role: squad member count; original member name unknown.
  u8 _74[0x118 - 0x74];
};

static_assert(offsetof(GmkSquad, m_bindedGmkSquadLeader) == 0x68, "");
static_assert(offsetof(GmkSquad, unknown70) == 0x70, "");
static_assert(sizeof(GmkSquad) == 0x118, "");

} // namespace gmk
