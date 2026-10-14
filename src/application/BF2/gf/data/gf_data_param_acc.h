#pragma once
#include "types.h"

namespace gf {

enum GimmickType {};

class DataParamAcc {
public:
  DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType);
  virtual ~DataParamAcc();

  bool isValid() const;
  const char *getModelResourceName() const;
  u32 getBlade(int slot, bool isVirtual) const;
  int getBladeSet(bool isVirtual) const;
  u32 getWeaponType(int slot, bool isVirtual) const;
  u32 getDriverArtsLevel(u32 arts) const;
  u32 getAttribute(int slot, bool isVirtual) const;
  u32 getQuestRace() const;
  u32 getGender() const;
  u32 getBladeArts(u32 index, bool isVirtual) const;
  u32 getBladeArtsLevel(u32 index, bool isVirtual) const;
  u32 getFieldSkill(u32 index, bool isVirtual) const;
  u32 getFieldSkillLevel(u32 index, bool isVirtual) const;

private:
  u8 _08[0x18 - 0x08];
};

} // namespace gf
