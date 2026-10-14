#pragma once
#include "gf/data/gf_data_driver.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
struct SDataEnemy;
class IDataObj;

enum GimmickType {
  GIMMICK_TYPE_NONE = 0,
  GIMMICK_TYPE_TREASURE_BOX = 1,
};

struct ParamObj {
  GF_OBJ_HANDLE *handle;
  u32 objectType;
  u32 id;
};

static_assert(offsetof(ParamObj, objectType) == 0x08, "");
static_assert(offsetof(ParamObj, id) == 0x0c, "");

class DataParamAcc {
public:
  DataParamAcc(const ParamObj &paramObj);
  void setupObjHandle(GF_OBJ_HANDLE *handle);
  void setupObjId(u32 objectType, u32 id, GimmickType gimmickType);
  DataParamAcc(GF_OBJ_HANDLE *handle);
  DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType);
  virtual ~DataParamAcc();

  bool isValid() const;
  u32 getObjType() const;
  const char *getModelResourceName() const;
  const char *getMotionResourceName() const;
  const char *getEffectResourceName() const;
  const char *getSeResourceName() const;
  const char *getName() const;
  bool getName(u8 *&bdat, u32 &textId) const;
  u32 getBdatId() const;
  u32 getHp() const;
  u32 getLevel(bool isVirtual) const;
  u32 getExp() const;
  u32 getBattleExp() const;
  u32 getExpNext(bool isVirtual) const;
  u32 getBattleExpNext(bool isVirtual) const;
  u32 getWeaponPoint(u32 weaponType) const;
  void addWeaponPoint(u32 weaponType, int weaponPoint);
  u32 getSkillPoint() const;
  void addSkillPoint(int skillPoint);
  u32 getDriverArts(u32 weaponType, u32 index) const;
  bool setDriverArts(u32 weaponType, int index, u32 arts);
  u32 getDriverArtsLevel(u32 arts) const;
  void setDriverArtsLevel(u32 arts, u32 level);
  u32 getHpMax(bool isVirtual) const;
  u32 getStrength(bool isVirtual) const;
  u32 getPowerEther(bool isVirtual) const;
  u32 getDex(bool isVirtual) const;
  u32 getAgility(bool isVirtual) const;
  u32 getLuck(bool isVirtual) const;
  u32 getPArmor(bool isVirtual) const;
  u32 getEArmor(bool isVirtual) const;
  u32 getCriticalRate(bool isVirtual) const;
  u32 getGuardRate(bool isVirtual) const;
  u32 getAutoHate(bool isVirtual) const;
  u32 getArtsHate(bool isVirtual) const;
  u32 getWeaponDamage(bool isVirtual) const;
  u32 getWeaponStability(bool isVirtual) const;
  u32 getChestHeight() const;
  u32 getLandingHeight() const;
  u32 getIconData() const;
  u32 getRace() const;
  u32 getQuestRace() const;
  u32 getGender() const;
  u32 getAttribute(int slot, bool isVirtual) const;
  bool isDispInitExtraParts(u32 part) const;
  bool isScenarioMask() const;
  u32 getRole(bool isVirtual) const;
  const char *getVoiceStr() const;
  u32 getMenuOffset() const;
  u32 getFootStep() const;
  u32 getFootStepEffect() const;
  u32 getEyeRotControl() const;
  const char *getRotateBone() const;
  u32 getPersonality() const;
  u32 getCoolTime() const;
  u32 getNorAtkDmgMin(bool isVirtual) const;
  u32 getNorAtkDmgMax(bool isVirtual) const;
  u16 getEquipAcce(u32 slot, bool isVirtual) const;
  bool getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const;
  int getBladeSet(bool isVirtual) const;
  void setBladeSet(int slot);
  u32 getBlade(int slot, bool isVirtual) const;
  u32 getClass(bool isVirtual) const;
  u32 getEquipWeapon(int slot, bool isVirtual) const;
  u32 getWeaponType(int slot, bool isVirtual) const;
  u32 getAsmWeaponType(int slot) const;
  u32 getBladePower(bool isVirtual) const;
  u32 getBladeArts(u32 index, bool isVirtual) const;
  u32 getBladeArtsEnhance(u32 index, bool isVirtual) const;
  u32 getBladeArtsLevel(u32 index, bool isVirtual) const;
  u32 getBladeArtsN(u32 index, bool isVirtual) const;
  u32 getBladeArtsNH(u32 index, bool isVirtual) const;
  u32 getBladeSkill(u32 index, bool isVirtual) const;
  u32 getBladeSkillLevel(u32 index, bool isVirtual) const;
  u32 getFieldSkill(u32 index, bool isVirtual) const;
  u32 getFieldSkillLevel(u32 index, bool isVirtual) const;
  u32 getKeyLevel() const;
  u32 getBladeArtsH(u32 index, bool isVirtual) const;
  u32 getBladeArtsEx(bool isVirtual) const;
  u32 getBladeArtsExH(bool isVirtual) const;
  u32 getBladeArtsEx2(bool isVirtual) const;
  u32 getBladeArtsEx2H(bool isVirtual) const;
  u32 getFavoriteCategory(FAVORITE favorite) const;
  u32 getFavoriteItem(FAVORITE favorite) const;
  u32 getArtsAchievement(u32 index) const;
  u32 getSkillAchievement(u32 index) const;
  u32 getFieldSkillAchievement(u32 index) const;
  u32 getKeyAchievement() const;
  void setVirtualEquipWpn(u32 weapon, int slot);
  void setVirtualEquipAcc(u32 slot, u32 accessory);
  u32 getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual);
  void setVirtualSetBlade(u32 blade, int slot);
  void setVirtualEquipWpnChip(u32 chip);
  void setVirtualEquipOrb(u32 orb, u32 slot);
  void setMenuParam();
  u32 getLinkNum() const;
  u32 getDeadNum() const;
  u32 getAppStNum() const;
  u32 getAppEndNum() const;
  u32 getBdatIdEnParam() const;
  u32 getBdatIdEnRsc() const;
  bool isGuardFront() const;
  bool isGuardLeft() const;
  bool isGuardRight() const;
  bool isGuardBack() const;
  bool isFieldDamage() const;
  u32 getResistancePower() const;
  u32 getResistanceEther() const;
  u32 getResistanceCombo() const;
  u32 getInvincibleCombo() const;
  u32 getLevelGold() const;
  u32 getLevelExp() const;
  u32 getLevelWp() const;
  u32 getLevelSp() const;
  u32 getGenus() const;
  bool isLinkGenus() const;
  f32 getLinkRadius() const;
  u32 getGoldDivide() const;
  u32 getGoldDivideRev() const;
  const SDataEnemy *getSDataEnemy() const;
  void setVirtualLevel(u32 level);
  bool isEnbaleTarget() const;
  GimmickType getGimmickType() const;
  bool isNoCameraFade() const;
  bool isWeaponDrawDisp() const;
  const char *getCenterBone() const;
  const char *getCamBone() const;

  IDataObj *obj;
  GF_OBJ_HANDLE *handle;
};

static_assert(offsetof(DataParamAcc, obj) == 0x08, "");
static_assert(offsetof(DataParamAcc, handle) == 0x10, "");
static_assert(sizeof(DataParamAcc) == 0x18, "");

} // namespace gf
