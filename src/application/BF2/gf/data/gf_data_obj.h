#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct SDataIdea;
class GfObjSetupEnemy;

class IDataObj {
public:
  virtual ~IDataObj() {}
  virtual void setMenuParam() {}
  virtual bool isValid() const = 0;
  virtual const char *getModelResourceName() const { return nullptr; }
  virtual const char *getMotionResourceName() const { return nullptr; }
  virtual const char *getEffectResourceName() const { return nullptr; }
  virtual const char *getSeResourceName() const { return nullptr; }
  virtual const char *getName() const = 0;
  virtual const char *getRotateBone() const { return nullptr; }
  virtual bool getName(u8 *&bdat, u32 &textId) const { return false; }
  virtual u32 getBdatId() const = 0;
  virtual u32 getObjType() const = 0;
  virtual SDataIdea *getIdea() const { return nullptr; }
  virtual u32 getDataType() const { return 0; }
  virtual u32 getHp() const { return 0; }
  virtual u32 getLevel(bool isVirtual) const { return 0; }
  virtual u32 getHpMax(bool isVirtual) const { return 0; }
  virtual u32 getStrength(bool isVirtual) const { return 0; }
  virtual u32 getPowerEther(bool isVirtual) const { return 0; }
  virtual u32 getDex(bool isVirtual) const { return 0; }
  virtual u32 getAgility(bool isVirtual) const { return 0; }
  virtual u32 getLuck(bool isVirtual) const { return 0; }
  virtual u32 getPArmor(bool isVirtual) const { return 0; }
  virtual u32 getEArmor(bool isVirtual) const { return 0; }
  virtual u32 getCriticalRate(bool isVirtual) const { return 0; }
  virtual u32 getGuardRate(bool isVirtual) const { return 0; }
  virtual u32 getAutoHate(bool isVirtual) const { return 0; }
  virtual u32 getArtsHate(bool isVirtual) const { return 0; }
  virtual u32 getWeaponDamage(bool isVirtual) const { return 0; }
  virtual u32 getWeaponStability(bool isVirtual) const { return 0; }
  virtual u32 getWeaponType(bool isVirtual, int slot) const { return 0; }
  virtual u32 getChestHeight() const { return 0; }
  virtual u32 getLandingHeight() const { return 0; }
  virtual u32 getFootStep() const { return 0; }
  virtual u32 getFootStepEffect() const { return 1; }
  virtual u32 getIconData() const { return 0; }
  virtual u32 getRace() const { return 0; }
  virtual u32 getQuestRace() const { return 1; }
  virtual u32 getGender() const { return 0; }
  virtual u32 getAttribute(bool isVirtual, int slot) const { return 0; }
  virtual bool isDispInitExtraParts(u32 part) const { return false; }
  virtual bool isScenarioMask() const { return false; }
  virtual u32 getRole() const { return 1; }
  virtual const char *getVoiceStr() const { return nullptr; }
  virtual void setVirtualLevel(u32 level) {}
  virtual void setVirtualEquipWpn(u32 weapon, int slot) {}
  virtual void setVirtualEquipAcc(u32 slot, u32 accessory) {}
  virtual void setVirtualSetBlade(u32 blade, int slot) {}
  virtual void setVirtualEquipWpnChip(u32 chip) {}
  virtual void setVirtualEquipOrb(u32 orb, u32 slot) {}
  virtual bool isVirtualSetting() const { return false; }
  virtual bool isEnbaleTarget() const { return true; }
  virtual u32 getMenuOffset() const { return 0; }
  virtual bool isNoCameraFade() const { return false; }
  virtual const char *getCamBone() const { return nullptr; }
  virtual const char *getCenterBone() const { return nullptr; }
  virtual u32 getEyeRotControl() const { return 0; }
  virtual u32 getNorAtkDmgMin(bool isVirtual) const { return 0; }
  virtual u32 getNorAtkDmgMax(bool isVirtual) const { return 0; }
  virtual u32 getEquipAcce(u32 slot, bool isVirtual) const { return 0; }
  virtual u32 getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) const { return 5; }
  virtual bool getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const { return false; }
  virtual int getBladeSet(bool isVirtual) const { return -1; }
  virtual u32 getBlade(bool isVirtual, int slot) const { return 0; }
  virtual void setBladeSet(int slot) {}
  virtual u32 getExp() const { return 0; }
  virtual u32 getBattleExp() const { return 0; }
  virtual u32 getExpNext(bool isVirtual) const { return 0; }
  virtual u32 getBattleExpNext(bool isVirtual) const { return 0; }
  virtual u32 getWeaponPoint(u32 weaponType) const { return 0; }
  virtual void addWeaponPoint(u32 weaponType, int weaponPoint) {}
  virtual u32 getSkillPoint() const { return 0; }
  virtual void addSkillPoint(int skillPoint) {}
  virtual u32 getDriverArts(u32 weaponType, u32 index) const { return 0; }
  virtual bool setDriverArts(u32 weaponType, int index, u32 arts) { return false; }
  virtual u32 getDriverArtsLevel(u32 arts) const { return 0; }
  virtual void setDriverArtsLevel(u32 arts, u32 level) {}
  virtual u32 getClass(bool isVirtual) const { return 0; }
  virtual u32 getBladePower(bool isVirtual) const { return 0; }
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const { return 0; }
  virtual u32 getBladeArts(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getBladeArtsEnhance(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getBladeArtsLevel(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getBladeArtsH(bool isVirtual, u32 index) const { return 100; }
  virtual u32 getBladeArtsN(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getBladeArtsNH(bool isVirtual, u32 index) const { return 100; }
  virtual u32 getBladeArtsEx(bool isVirtual) const { return 0; }
  virtual u32 getBladeArtsExH(bool isVirtual) const { return 100; }
  virtual u32 getBladeArtsEx2(bool isVirtual) const { return 0; }
  virtual u32 getBladeArtsEx2H(bool isVirtual) const { return 100; }
  virtual u32 getBladeSkill(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getBladeSkillLevel(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getFieldSkill(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getFieldSkillLevel(bool isVirtual, u32 index) const { return 0; }
  virtual u32 getKeyLevel() const { return 0; }
  virtual u32 getPersonality() const { return 0; }
  virtual u32 getCoolTime() const { return 0; }
  virtual u32 getFavoriteCategory(FAVORITE favorite) const { return 0; }
  virtual u32 getFavoriteItem(FAVORITE favorite) const { return 0; }
  virtual u32 getArtsAchievement(u32 index) const { return 0; }
  virtual u32 getSkillAchievement(u32 index) const { return 0; }
  virtual u32 getFieldSkillAchievement(u32 index) const { return 0; }
  virtual u32 getKeyAchievement() const { return 0; }
  virtual u32 getLinkNum() const { return 500; }
  virtual u32 getDeadNum() const { return 500; }
  virtual u32 getAppStNum() const { return 500; }
  virtual u32 getAppEndNum() const { return 500; }
  virtual bool isWeaponDrawDisp() const { return false; }
  virtual u32 getBdatIdEnRsc() const { return 0; }
  virtual u32 getBdatIdEnParam() const { return 0; }
  virtual u32 getBdatIdEnArrange() const { return 0; }
  virtual bool isGuardFront() const { return false; }
  virtual bool isGuardLeft() const { return false; }
  virtual bool isGuardRight() const { return false; }
  virtual bool isGuardBack() const { return false; }
  virtual bool isFieldDamage() const { return true; }
  virtual u32 getResistancePower() const { return 0; }
  virtual u32 getResistanceEther() const { return 0; }
  virtual u32 getResistanceCombo() const { return 0; }
  virtual u32 getInvincibleCombo() const { return 0; }
  virtual u32 getLevelGold() const { return 0; }
  virtual u32 getLevelExp() const { return 0; }
  virtual u32 getLevelWp() const { return 0; }
  virtual u32 getLevelSp() const { return 0; }
  virtual u32 getGenus() const { return 0; }
  virtual bool isLinkGenus() const { return false; }
  virtual f32 getLinkRadius() const { return 0.0f; }
  virtual u32 getGoldDivide() const { return 0; }
  virtual u32 getGoldDivideRev() const { return 0; }
  virtual const SDataEnemy *getSDataEnemy() const { return nullptr; }
  virtual GimmickType getGimmickType() const { return GimmickType(); }
};

class DataObjDriver : public IDataObj {
public:
  DataObjDriver(u32 id);
  void setup(u32 id);
  DataObjDriver(GF_OBJ_HANDLE *handle);
  virtual ~DataObjDriver();
  SDataDriver *get(bool isVirtual) const { return isVirtual ? unknown10 : GfDataDriver::getSDataDriver(getBdatId()); }
  void setupVirtualParam();
  virtual void setVirtualLevel(u32 level);
  virtual void setVirtualEquipWpn(u32 weapon, int slot);
  virtual void setVirtualEquipAcc(u32 slot, u32 accessory);
  virtual void setVirtualSetBlade(u32 blade, int slot);
  virtual bool isVirtualSetting() const;
  virtual u32 getMenuOffset() const;
  virtual const char *getCenterBone() const;
  virtual const char *getCamBone() const;
  virtual u32 getEyeRotControl() const;
  virtual void setMenuParam() { unknown3c = true; }
  virtual bool isValid() const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual const char *getEffectResourceName() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_DRIVER; }
  virtual SDataIdea *getIdea() const;
  virtual u32 getDataType() const;
  virtual u32 getHp() const;
  virtual u32 getHpMax(bool isVirtual) const;
  virtual u32 getLevel(bool isVirtual) const;
  virtual u32 getExp() const;
  virtual u32 getBattleExp() const;
  virtual u32 getExpNext(bool isVirtual) const;
  virtual u32 getBattleExpNext(bool isVirtual) const;
  virtual u32 getWeaponPoint(u32 weaponType) const;
  virtual void addWeaponPoint(u32 weaponType, int weaponPoint);
  virtual u32 getSkillPoint() const;
  virtual void addSkillPoint(int skillPoint);
  virtual u32 getBladeArts(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsEnhance(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsLevel(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsN(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsNH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsEx(bool isVirtual) const;
  virtual u32 getBladeArtsExH(bool isVirtual) const;
  virtual u32 getBladeArtsEx2(bool isVirtual) const;
  virtual u32 getBladeArtsEx2H(bool isVirtual) const;
  virtual u32 getBladeSkill(bool isVirtual, u32 index) const;
  virtual u32 getBladeSkillLevel(bool isVirtual, u32 index) const;
  virtual u32 getDriverArts(u32 weaponType, u32 index) const;
  virtual bool setDriverArts(u32 weaponType, int index, u32 arts);
  virtual u32 getDriverArtsLevel(u32 arts) const;
  virtual void setDriverArtsLevel(u32 arts, u32 level);
  virtual u32 getClass(bool isVirtual) const;
  virtual u32 getStrength(bool isVirtual) const;
  virtual u32 getPowerEther(bool isVirtual) const;
  virtual u32 getDex(bool isVirtual) const;
  virtual u32 getAgility(bool isVirtual) const;
  virtual u32 getLuck(bool isVirtual) const;
  virtual u32 getPArmor(bool isVirtual) const;
  virtual u32 getEArmor(bool isVirtual) const;
  virtual u32 getCriticalRate(bool isVirtual) const;
  virtual u32 getGuardRate(bool isVirtual) const;
  virtual u32 getAutoHate(bool isVirtual) const;
  virtual u32 getArtsHate(bool isVirtual) const;
  virtual u32 getWeaponDamage(bool isVirtual) const;
  virtual u32 getWeaponStability(bool isVirtual) const;
  virtual u32 getNorAtkDmgMin(bool isVirtual) const;
  virtual u32 getNorAtkDmgMax(bool isVirtual) const;
  virtual u32 getEquipAcce(u32 slot, bool isVirtual) const;
  virtual u32 getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) const;
  virtual int getBladeSet(bool isVirtual) const;
  virtual void setBladeSet(int slot);
  virtual u32 getBlade(bool isVirtual, int slot) const;
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const;
  virtual u32 getWeaponType(bool isVirtual, int slot) const;
  virtual u32 getChestHeight() const;
  virtual u32 getLandingHeight() const;
  virtual u32 getIconData() const;
  virtual u32 getRace() const;
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getGender() const;
  virtual u32 getAttribute(bool isVirtual, int slot) const;
  virtual bool isScenarioMask() const;
  virtual u32 getRole() const;
  virtual const char *getVoiceStr() const;
  virtual u32 getFieldSkill(bool isVirtual, u32 index) const;
  virtual u32 getFieldSkillLevel(bool isVirtual, u32 index) const;
  virtual u32 getKeyLevel() const;
  virtual u32 getFavoriteCategory(FAVORITE favorite) const;
  virtual u32 getFavoriteItem(FAVORITE favorite) const;

  u32 m_bdatId;
  SDataDriver *unknown10;   // Inferred role: data; original member name unknown.
  GF_OBJ_HANDLE *unknown18; // Inferred role: handle; original member name unknown.
  SDataDriver *unknown20;   // Inferred role: virtual data; original member name unknown.
  u32 unknown28[5];         // Inferred role: virtual equip weapons; original member name unknown.
  bool unknown3c;           // Inferred role: menu param; original member name unknown.
};

static_assert(offsetof(DataObjDriver, m_bdatId) == 0x08, "");
static_assert(offsetof(DataObjDriver, unknown10) == 0x10, "");
static_assert(offsetof(DataObjDriver, unknown18) == 0x18, "");
static_assert(offsetof(DataObjDriver, unknown20) == 0x20, "");
static_assert(offsetof(DataObjDriver, unknown28) == 0x28, "");
static_assert(offsetof(DataObjDriver, unknown3c) == 0x3c, "");
static_assert(sizeof(DataObjDriver) == 0x40, "");

class DataObjBlade : public IDataObj {
public:
  DataObjBlade(u32 id);
  void setup(u32 id);
  DataObjBlade(GF_OBJ_HANDLE *handle);
  virtual ~DataObjBlade();
  SDataBlade *get(bool isVirtual) const { return isVirtual ? unknown08 : GfDataBlade::getSDataBlade(getBdatId()); }
  void setupVirtualParam();
  virtual bool isValid() const;
  virtual void setVirtualEquipWpn(u32 weapon, int slot);
  virtual u32 getPArmor(bool isVirtual) const;
  virtual u32 getEArmor(bool isVirtual) const;
  virtual u32 getCriticalRate(bool isVirtual) const;
  virtual u32 getGuardRate(bool isVirtual) const;
  virtual u32 getAutoHate(bool isVirtual) const;
  virtual u32 getArtsHate(bool isVirtual) const;
  virtual u32 getWeaponDamage(bool isVirtual) const;
  virtual u32 getWeaponStability(bool isVirtual) const;
  virtual u32 getNorAtkDmgMin(bool isVirtual) const;
  virtual u32 getNorAtkDmgMax(bool isVirtual) const;
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const;
  virtual u32 getWeaponType(bool isVirtual, int slot) const;
  virtual u32 getAttribute(bool isVirtual, int slot) const;
  virtual u32 getFieldSkill(bool isVirtual, u32 index) const;
  virtual u32 getFieldSkillLevel(bool isVirtual, u32 index) const;
  virtual u32 getKeyLevel() const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual const char *getEffectResourceName() const;
  virtual const char *getSeResourceName() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_BLADE; }
  virtual void setMenuParam() { unknown24 = true; }
  virtual u32 getDataType() const;
  virtual SDataIdea *getIdea() const;
  virtual u32 getHpMax(bool isVirtual) const;
  virtual u32 getStrength(bool isVirtual) const;
  virtual u32 getPowerEther(bool isVirtual) const;
  virtual u32 getDex(bool isVirtual) const;
  virtual u32 getAgility(bool isVirtual) const;
  virtual u32 getLuck(bool isVirtual) const;
  virtual bool getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const;
  virtual u32 getChestHeight() const;
  virtual u32 getLandingHeight() const;
  virtual u32 getIconData() const;
  virtual u32 getRace() const;
  virtual u32 getQuestRace() const;
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getGender() const;
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual u32 getRole() const;
  virtual const char *getVoiceStr() const;
  virtual int getBladeSet(bool isVirtual) const;
  virtual u32 getBlade(bool isVirtual, int slot) const;
  virtual u32 getBladePower(bool isVirtual) const;
  virtual u32 getBladeArts(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsEnhance(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsLevel(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsN(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsNH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsEx(bool isVirtual) const;
  virtual u32 getBladeArtsExH(bool isVirtual) const;
  virtual u32 getBladeArtsEx2(bool isVirtual) const;
  virtual u32 getBladeArtsEx2H(bool isVirtual) const;
  virtual u32 getBladeSkill(bool isVirtual, u32 index) const;
  virtual u32 getBladeSkillLevel(bool isVirtual, u32 index) const;
  virtual u32 getPersonality() const;
  virtual u32 getCoolTime() const;
  virtual u32 getFavoriteCategory(FAVORITE favorite) const;
  virtual u32 getFavoriteItem(FAVORITE favorite) const;
  virtual u32 getArtsAchievement(u32 index) const;
  virtual u32 getSkillAchievement(u32 index) const;
  virtual u32 getFieldSkillAchievement(u32 index) const;
  virtual u32 getKeyAchievement() const;
  virtual u32 getLinkNum() const;
  virtual u32 getDeadNum() const;
  virtual u32 getAppStNum() const;
  virtual u32 getAppEndNum() const;
  virtual void setVirtualEquipWpnChip(u32 chip);
  virtual void setVirtualEquipOrb(u32 orb, u32 slot);
  virtual bool isVirtualSetting() const;
  virtual bool isEnbaleTarget() const;
  virtual u32 getMenuOffset() const;
  virtual const char *getCenterBone() const;
  virtual const char *getCamBone() const;
  virtual u32 getEyeRotControl() const;

  SDataBlade *unknown08;    // Inferred role: data; original member name unknown.
  GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  SDataBlade *unknown18;    // Inferred role: virtual data; original member name unknown.
  u32 m_bdatId;
  bool unknown24; // Inferred role: menu param; original member name unknown.
};

static_assert(offsetof(DataObjBlade, unknown08) == 0x08, "");
static_assert(offsetof(DataObjBlade, unknown10) == 0x10, "");
static_assert(offsetof(DataObjBlade, unknown18) == 0x18, "");
static_assert(offsetof(DataObjBlade, m_bdatId) == 0x20, "");
static_assert(offsetof(DataObjBlade, unknown24) == 0x24, "");
static_assert(sizeof(DataObjBlade) == 0x28, "");

class DataObjPcWpn : public IDataObj {
public:
  DataObjPcWpn(u32 id);
  DataObjPcWpn(GF_OBJ_HANDLE *handle);
  virtual ~DataObjPcWpn();
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_PC_WEAPON; }
  virtual u32 getAttribute(bool isVirtual, int slot) const;
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const;
  virtual u32 getWeaponType(bool isVirtual, int slot) const;
  virtual int getBladeSet(bool isVirtual) const;
  virtual u32 getWeaponDamage(bool isVirtual) const;
  virtual u32 getWeaponStability(bool isVirtual) const;
  virtual bool isEnbaleTarget() const { return false; }

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
};

static_assert(offsetof(DataObjPcWpn, unknown08) == 0x08, "");
static_assert(offsetof(DataObjPcWpn, m_bdatId) == 0x10, "");
static_assert(sizeof(DataObjPcWpn) == 0x18, "");

class DataObjEnemy : public IDataObj {
public:
  DataObjEnemy(GF_OBJ_HANDLE *handle);
  DataObjEnemy(u32 id);
  virtual ~DataObjEnemy();
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual const char *getEffectResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_ENEMY; }
  virtual u32 getLevel(bool isVirtual) const;
  virtual u32 getHpMax(bool isVirtual) const;
  virtual u32 getHp() const;
  virtual u32 getStrength(bool isVirtual) const;
  virtual u32 getPowerEther(bool isVirtual) const;
  virtual u32 getDex(bool isVirtual) const;
  virtual u32 getAgility(bool isVirtual) const;
  virtual u32 getLuck(bool isVirtual) const;
  virtual u32 getPArmor(bool isVirtual) const;
  virtual u32 getEArmor(bool isVirtual) const;
  virtual u32 getCriticalRate(bool isVirtual) const;
  virtual u32 getGuardRate(bool isVirtual) const;
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getBlade(bool isVirtual, int slot) const;
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const;
  virtual u32 getWeaponType(bool isVirtual, int slot) const;
  virtual u32 getAttribute(bool isVirtual, int slot) const;
  virtual bool isEnbaleTarget() const;
  virtual u32 getChestHeight() const;
  virtual const char *getVoiceStr() const;
  virtual u32 getMenuOffset() const;
  virtual u32 getBdatIdEnRsc() const;
  virtual u32 getBdatIdEnParam() const;
  virtual u32 getBdatIdEnArrange() const { return getBdatId(); }
  virtual bool isGuardFront() const;
  virtual bool isGuardLeft() const;
  virtual bool isGuardRight() const;
  virtual bool isGuardBack() const;
  virtual bool isFieldDamage() const;
  virtual u32 getResistancePower() const;
  virtual u32 getResistanceEther() const;
  virtual u32 getResistanceCombo() const;
  virtual u32 getInvincibleCombo() const;
  virtual u32 getLevelGold() const;
  virtual u32 getLevelExp() const;
  virtual u32 getLevelWp() const;
  virtual u32 getLevelSp() const;
  virtual u32 getGenus() const;
  virtual bool isLinkGenus() const;
  virtual f32 getLinkRadius() const;
  virtual u32 getGoldDivide() const;
  virtual u32 getGoldDivideRev() const;
  virtual const SDataEnemy *getSDataEnemy() const;
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual bool isNoCameraFade() const;
  virtual bool isWeaponDrawDisp() const;
  virtual const char *getCenterBone() const;
  virtual const char *getCamBone() const;
  virtual u32 getEyeRotControl() const;
  virtual const char *getRotateBone() const;

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  SDataEnemy *m_SDataEnemy;
  SDataEnemy unknown18; // Inferred role: enemy; original member name unknown.
};

static_assert(offsetof(DataObjEnemy, unknown08) == 0x08, "");
static_assert(offsetof(DataObjEnemy, m_SDataEnemy) == 0x10, "");
static_assert(offsetof(DataObjEnemy, unknown18) == 0x18, "");
static_assert(sizeof(DataObjEnemy) == 0xd8, "");

class DataObjEnemyBlade : public DataObjEnemy {
public:
  DataObjEnemyBlade(GF_OBJ_HANDLE *handle);
  DataObjEnemyBlade(u32 id);
  virtual ~DataObjEnemyBlade();
  SDataBlade *get(bool isVirtual) const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual const char *getEffectResourceName() const;
  virtual u32 getWeaponType(bool isVirtual, int slot) const;
  virtual u32 getPArmor(bool isVirtual) const;
  virtual u32 getEArmor(bool isVirtual) const;
  virtual u32 getCriticalRate(bool isVirtual) const;
  virtual u32 getGuardRate(bool isVirtual) const;
  virtual u32 getWeaponDamage(bool isVirtual) const;
  virtual u32 getWeaponStability(bool isVirtual) const;
  virtual u32 getEquipWeapon(bool isVirtual, int slot) const;
  virtual u32 getChestHeight() const;
  virtual u32 getLandingHeight() const;
  virtual u32 getIconData() const;
  virtual u32 getRace() const;
  virtual u32 getQuestRace() const;
  virtual u32 getGender() const;
  virtual u32 getAttribute(bool isVirtual, int slot) const;
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual u32 getEyeRotControl() const;
  virtual u32 getBladeArts(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsLevel(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsN(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsNH(bool isVirtual, u32 index) const;
  virtual u32 getBladeArtsEx(bool isVirtual) const;
  virtual u32 getBladeArtsExH(bool isVirtual) const;
  virtual u32 getBladeArtsEx2(bool isVirtual) const;
  virtual u32 getBladeArtsEx2H(bool isVirtual) const;
  virtual u32 getPersonality() const;
  virtual u32 getCoolTime() const;
  virtual bool isEnbaleTarget() const { return false; }

  GfObjSetupEnemy *unknownd8; // Inferred role: setup enemy; original member name unknown.
  SDataBlade *unknowne0;      // Inferred role: data blade; original member name unknown.
};

static_assert(offsetof(DataObjEnemyBlade, unknownd8) == 0xd8, "");
static_assert(offsetof(DataObjEnemyBlade, unknowne0) == 0xe0, "");
static_assert(sizeof(DataObjEnemyBlade) == 0xe8, "");

class DataObjNpc : public IDataObj {
public:
  DataObjNpc(GF_OBJ_HANDLE *handle);
  DataObjNpc(u32 id);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_NPC; }
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual u32 getMenuOffset() const;
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;
  virtual u32 getEyeRotControl() const;

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
};

static_assert(offsetof(DataObjNpc, unknown08) == 0x08, "");
static_assert(offsetof(DataObjNpc, m_bdatId) == 0x10, "");
static_assert(sizeof(DataObjNpc) == 0x18, "");

class DataObjMap : public IDataObj {
public:
  DataObjMap(GF_OBJ_HANDLE *handle);
  DataObjMap(u32 id);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_MAP; }

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
};

static_assert(offsetof(DataObjMap, unknown08) == 0x08, "");
static_assert(offsetof(DataObjMap, m_bdatId) == 0x10, "");
static_assert(sizeof(DataObjMap) == 0x18, "");

class DataObjMob : public IDataObj {
public:
  DataObjMob(GF_OBJ_HANDLE *handle);
  DataObjMob(u32 id);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_MOB; }
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual u32 getMenuOffset() const;
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
};

static_assert(offsetof(DataObjMob, unknown08) == 0x08, "");
static_assert(offsetof(DataObjMob, m_bdatId) == 0x10, "");
static_assert(sizeof(DataObjMob) == 0x18, "");

class DataObjUiObj : public IDataObj {
public:
  DataObjUiObj(GF_OBJ_HANDLE *handle);
  DataObjUiObj(u32 id);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_MOB; }
  virtual bool isDispInitExtraParts(u32 part) const;

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
};

static_assert(offsetof(DataObjUiObj, unknown08) == 0x08, "");
static_assert(offsetof(DataObjUiObj, m_bdatId) == 0x10, "");
static_assert(sizeof(DataObjUiObj) == 0x18, "");

class DataObjGmk : public IDataObj {
public:
  DataObjGmk(GF_OBJ_HANDLE *handle);
  DataObjGmk(u32 id, GimmickType gimmickType);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_GIMMICK; }
  virtual bool isDispInitExtraParts(u32 part) const;
  virtual GimmickType getGimmickType() const { return m_gimmickType; }

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 m_bdatId;
  GimmickType m_gimmickType;
};

static_assert(offsetof(DataObjGmk, unknown08) == 0x08, "");
static_assert(offsetof(DataObjGmk, m_bdatId) == 0x10, "");
static_assert(offsetof(DataObjGmk, m_gimmickType) == 0x14, "");
static_assert(sizeof(DataObjGmk) == 0x18, "");

class DataObjBelonging : public IDataObj {
public:
  DataObjBelonging(GF_OBJ_HANDLE *handle);
  virtual bool isValid() const;
  virtual const char *getName() const;
  virtual bool getName(u8 *&bdat, u32 &textId) const;
  virtual const char *getModelResourceName() const;
  virtual const char *getMotionResourceName() const;
  virtual u32 getBdatId() const;
  virtual u32 getObjType() const { return OBJECT_TYPE_BELONGING; }

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(DataObjBelonging, unknown08) == 0x08, "");
static_assert(sizeof(DataObjBelonging) == 0x10, "");

} // namespace gf
