#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatRsc : public mm::mtl::PtrSingleton<GfBdatRsc> {
public:
  const char *getRscMobListModel(u32 mob) const;
  u8 getRscMobListRace(u32 mob) const;
  const char *getRscMobListMotion(u32 mob) const;
  const char *getRscMobListAddMotion(u32 mob) const;
  const char *getRscMobListComp_Eff(u32 mob) const;
  u16 getRscMobListFootStep(u32 mob) const;
  u8 getRscMobListFootStepEffect(u32 mob) const;

  u32 getRscNpcListStart() const;
  u32 getRscNpcListName(u32 npc) const;
  u32 getRscNpcListRace(u32 npc) const;
  u32 getRscNpcListGender(u32 npc) const;
  const char *getRscNpcListModel(u32 npc) const;
  const char *getRscNpcListMotion(u32 npc) const;
  const char *getRscNpcListAddMotion(u32 npc) const;
  const char *getRscNpcListComp_Eff(u32 npc) const;
  u32 getRscNpcListScale(u32 npc) const;
  u32 getRscNpcListCollisionId(u32 npc) const;
  u32 getRscNpcListOffsetID(u32 npc) const;
  u32 getRscNpcListExtraParts(u32 npc, u32 part) const;
  u32 getRscNpcListFootStep(u32 npc) const;
  u32 getRscNpcListFootStepEffect(u32 npc) const;
  u32 getRscNpcListEyeRot(u32 npc) const;

  const char *getRSC_PcWpnModel(u32 weapon) const;
  const char *getRSC_PcWpnMotion(u32 weapon) const;

  const char *getRscEnVoice(u32 resource) const;
  const char *getRscEnRefMotion(u32 resource) const;
  const char *getRscEnModel(u32 resource) const;
  const char *getRscEnMotion(u32 resource) const;
  const char *getRscEnSePack(u32 resource) const;
  const char *getRscEnLoopEffect(u32 resource) const;
  u32 getRscEnExtraParts(u32 resource, u32 part) const;
  u32 getRscEnDrType(u32 resource) const;

  u32 getDriverParamExtMountNpc(u32 driver) const;
  const char *getDriverParamExtMountBone(u32 driver) const;
  u32 getDriverParamExtMountCond(u32 driver) const;
};

} // namespace gf
