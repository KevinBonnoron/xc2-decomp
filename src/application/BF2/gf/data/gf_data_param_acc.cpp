#include "gf/data/gf_data_param_acc.h"

#include <new>

#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_obj.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "ml/fixed_size_alloc.h"
#include "ml/rand.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  CREATE_CONFIG_UNKNOWN_1 = 1,   // Inferred role: create config sub ratio minus 3; original name unknown.
  CREATE_CONFIG_UNKNOWN_2 = 2,   // Inferred role: create config sub ratio minus 2; original name unknown.
  CREATE_CONFIG_UNKNOWN_3 = 3,   // Inferred role: create config sub ratio minus 1; original name unknown.
  CREATE_CONFIG_UNKNOWN_4 = 4,   // Inferred role: create config sub ratio 0; original name unknown.
  CREATE_CONFIG_UNKNOWN_5 = 5,   // Inferred role: create config sub ratio 1; original name unknown.
  CREATE_CONFIG_UNKNOWN_6 = 6,   // Inferred role: create config sub ratio 2; original name unknown.
  CREATE_CONFIG_UNKNOWN_7 = 7,   // Inferred role: create config sub ratio 3; original name unknown.
  CREATE_CONFIG_UNKNOWN_8 = 8,   // Inferred role: create config sub ratio 4; original name unknown.
  CREATE_CONFIG_UNKNOWN_9 = 9,   // Inferred role: create config sub ratio 5; original name unknown.
  CREATE_CONFIG_UNKNOWN_10 = 10, // Inferred role: create config ratio 0; original name unknown.
  CREATE_CONFIG_UNKNOWN_11 = 11, // Inferred role: create config ratio 1; original name unknown.
  CREATE_CONFIG_UNKNOWN_12 = 12, // Inferred role: create config ratio 2; original name unknown.
  CREATE_CONFIG_UNKNOWN_13 = 13, // Inferred role: create config ratio 3; original name unknown.
  CREATE_CONFIG_UNKNOWN_14 = 14, // Inferred role: create config ratio 4; original name unknown.
};

namespace _gfdac {

// Inferred role: storage of one data object of DataParamAcc; 128 of them fill the 0x4000 bytes of s_accbuf. Members unknown.
struct ACCMEM {
  u8 unknown00[0x80]; // Inferred role: object storage; original member name unknown.
};

ml::fixed_size_alloc_inside<ACCMEM, 128> s_accbuf;

static_assert(__builtin_offsetof(ml::fixed_size_alloc_inside<ACCMEM, 128>, unknown005) == 0x4008, "");
static_assert(__builtin_offsetof(ml::fixed_size_alloc_inside<ACCMEM, 128>, unknown006) == 0x4020, "");
static_assert(__builtin_offsetof(ml::fixed_size_alloc_inside<ACCMEM, 128>, unknown007) == 0x4028, "");
static_assert(__builtin_offsetof(ml::fixed_size_alloc_inside<ACCMEM, 128>, unknown008) == 0x4030, "");
static_assert(__builtin_offsetof(ml::fixed_size_alloc_inside<ACCMEM, 128>, unknown009) == 0x4034, "");
static_assert(sizeof(ml::fixed_size_alloc_inside<ACCMEM, 128>) == 0x4038, "");

} // namespace _gfdac

DataParamAcc::DataParamAcc(const ParamObj &paramObj) {
  if (paramObj.unknown00 != unknown020) {
    setupObjHandle(paramObj.unknown00);
  } else {
    setupObjId(paramObj.unknown08, paramObj.unknown0c, static_cast<GimmickType>(0));
  }
}

void DataParamAcc::setupObjHandle(GF_OBJ_HANDLE *handle) {
  unknown08 = nullptr;
  unknown10 = handle;
  _gfdac::ACCMEM *mem = _gfdac::s_accbuf.unknown003();
  IDataObj *obj;
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_MAP:
    obj = new (mem) DataObjMap(handle);
    break;
  case OBJECT_TYPE_PC:
    obj = new (mem) DataObjDriver(handle);
    break;
  case OBJECT_TYPE_BLADE:
    obj = new (mem) DataObjBlade(handle);
    break;
  case OBJECT_TYPE_ENEMY:
    if (GfObjUtil::isEnemyBlade(handle)) {
      GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
      obj = new (mem) DataObjEnemyBlade(handle);
    } else {
      obj = new (mem) DataObjEnemy(handle);
    }
    break;
  case OBJECT_TYPE_NPC:
    obj = new (mem) DataObjNpc(handle);
    break;
  case OBJECT_TYPE_MOB:
    obj = new (mem) DataObjMob(handle);
    break;
  case OBJECT_TYPE_GIMMICK:
    obj = new (mem) DataObjGmk(handle);
    break;
  case OBJECT_TYPE_PC_WEAPON:
    obj = new (mem) DataObjPcWpn(handle);
    break;
  case OBJECT_TYPE_OPTION:
    obj = new (mem) DataObjBelonging(handle);
    break;
  default:
    _gfdac::s_accbuf.unknown004(mem);
    return;
  }
  unknown08 = obj;
}

void DataParamAcc::setupObjId(u32 objectType, u32 id, GimmickType gimmickType) {
  unknown08 = nullptr;
  _gfdac::ACCMEM *mem = _gfdac::s_accbuf.unknown003();
  IDataObj *obj;
  switch (objectType) {
  case OBJECT_TYPE_MAP:
    obj = new (mem) DataObjMap(id);
    break;
  case OBJECT_TYPE_PC:
    obj = new (mem) DataObjDriver(id);
    break;
  case OBJECT_TYPE_BLADE:
    obj = new (mem) DataObjBlade(id);
    break;
  case OBJECT_TYPE_ENEMY:
    obj = new (mem) DataObjEnemy(id);
    break;
  case OBJECT_TYPE_NPC:
    obj = new (mem) DataObjNpc(id);
    break;
  case OBJECT_TYPE_MOB:
    obj = new (mem) DataObjMob(id);
    break;
  case OBJECT_TYPE_GIMMICK:
    obj = new (mem) DataObjGmk(id, gimmickType);
    break;
  case OBJECT_TYPE_PC_WEAPON:
    obj = new (mem) DataObjPcWpn(id);
    break;
  case OBJECT_TYPE_UI_OBJ:
    obj = new (mem) DataObjUiObj(id);
    break;
  default:
    _gfdac::s_accbuf.unknown004(mem);
    return;
  }
  unknown08 = obj;
}

DataParamAcc::DataParamAcc(GF_OBJ_HANDLE *handle) { setupObjHandle(handle); }

DataParamAcc::DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType) { setupObjId(objectType, id, gimmickType); }

DataParamAcc::~DataParamAcc() {
  if (unknown08 != nullptr) {
    unknown08->~IDataObj();
    _gfdac::s_accbuf.unknown004(unknown08);
    unknown08 = nullptr;
  }
}

bool DataParamAcc::isValid() const { return unknown08 != nullptr && unknown08->isValid(); }

u32 DataParamAcc::getObjType() const {
  if (isValid()) {
    return unknown08->getObjType();
  }

  return 0;
}

const char *DataParamAcc::getModelResourceName() const {
  if (isValid()) {
    return unknown08->getModelResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getMotionResourceName() const {
  if (isValid()) {
    return unknown08->getMotionResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getEffectResourceName() const {
  if (isValid()) {
    return unknown08->getEffectResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getSeResourceName() const {
  if (isValid()) {
    return unknown08->getSeResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getName() const {
  if (isValid()) {
    const char *name = unknown08->getName();
    return name == nullptr ? "" : name;
  }

  return "";
}

bool DataParamAcc::getName(u8 *&bdat, u32 &textId) const {
  if (isValid()) {
    return unknown08->getName(bdat, textId);
  }

  return false;
}

u32 DataParamAcc::getBdatId() const {
  if (isValid()) {
    return unknown08->getBdatId();
  }

  return 0;
}

u32 DataParamAcc::getHp() const {
  if (isValid()) {
    return unknown08->getHp();
  }

  return 0;
}

u32 DataParamAcc::getLevel(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getLevel(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getExp() const {
  if (isValid()) {
    return unknown08->getExp();
  }

  return 0;
}

u32 DataParamAcc::getBattleExp() const {
  if (isValid()) {
    return unknown08->getBattleExp();
  }

  return 0;
}

u32 DataParamAcc::getExpNext(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBattleExpNext(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBattleExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponPoint(u32 weaponType) const {
  if (isValid()) {
    return unknown08->getWeaponPoint(weaponType);
  }

  return 0;
}

void DataParamAcc::addWeaponPoint(u32 weaponType, int weaponPoint) {
  if (isValid()) {
    unknown08->addWeaponPoint(weaponType, weaponPoint);
  }
}

u32 DataParamAcc::getSkillPoint() const {
  if (isValid()) {
    return unknown08->getSkillPoint();
  }

  return 0;
}

void DataParamAcc::addSkillPoint(int skillPoint) {
  if (isValid()) {
    unknown08->addSkillPoint(skillPoint);
  }
}

u32 DataParamAcc::getDriverArts(u32 weaponType, u32 index) const {
  if (isValid()) {
    return unknown08->getDriverArts(weaponType, index);
  }

  return 0;
}

bool DataParamAcc::setDriverArts(u32 weaponType, int index, u32 arts) {
  if (isValid()) {
    return unknown08->setDriverArts(weaponType, index, arts);
  }

  return false;
}

u32 DataParamAcc::getDriverArtsLevel(u32 arts) const {
  if (isValid()) {
    return unknown08->getDriverArtsLevel(arts);
  }

  return 0;
}

void DataParamAcc::setDriverArtsLevel(u32 arts, u32 level) {
  if (isValid()) {
    unknown08->setDriverArtsLevel(arts, level);
  }
}

u32 DataParamAcc::getHpMax(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getHpMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getStrength(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getStrength(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPowerEther(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getPowerEther(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getDex(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getDex(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAgility(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getAgility(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getLuck(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getLuck(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPArmor(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getPArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEArmor(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getEArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getCriticalRate(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getCriticalRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getGuardRate(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getGuardRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAutoHate(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getAutoHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getArtsHate(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getArtsHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponDamage(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getWeaponDamage(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponStability(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getWeaponStability(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getChestHeight() const {
  if (isValid()) {
    return unknown08->getChestHeight();
  }

  return 0;
}

u32 DataParamAcc::getLandingHeight() const {
  if (isValid()) {
    return unknown08->getLandingHeight();
  }

  return 0;
}

u32 DataParamAcc::getIconData() const {
  if (isValid()) {
    return unknown08->getIconData();
  }

  return 0;
}

u32 DataParamAcc::getRace() const {
  if (isValid()) {
    return unknown08->getRace();
  }

  return 0;
}

u32 DataParamAcc::getQuestRace() const {
  if (isValid()) {
    return unknown08->getQuestRace();
  }

  return 1;
}

u32 DataParamAcc::getGender() const {
  if (isValid()) {
    return unknown08->getGender();
  }

  return 0;
}

u32 DataParamAcc::getAttribute(int slot, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getAttribute(isVirtual, slot);
  }

  return 0;
}

bool DataParamAcc::isDispInitExtraParts(u32 part) const {
  if (isValid()) {
    return unknown08->isDispInitExtraParts(part);
  }

  return true;
}

bool DataParamAcc::isScenarioMask() const {
  if (isValid()) {
    return unknown08->isScenarioMask();
  }

  return false;
}

u32 DataParamAcc::getRole(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getRole();
  }

  return 0;
}

const char *DataParamAcc::getVoiceStr() const {
  if (isValid()) {
    if (const char *voiceStr = unknown08->getVoiceStr()) {
      return voiceStr;
    }

    return "";
  }

  return "";
}

u32 DataParamAcc::getMenuOffset() const {
  if (isValid()) {
    return unknown08->getMenuOffset();
  }

  return 0;
}

u32 DataParamAcc::getFootStep() const {
  if (isValid()) {
    return unknown08->getFootStep();
  }

  return 0;
}

u32 DataParamAcc::getFootStepEffect() const {
  if (isValid()) {
    return unknown08->getFootStepEffect();
  }

  return 1;
}

u32 DataParamAcc::getEyeRotControl() const {
  if (isValid()) {
    return unknown08->getEyeRotControl();
  }

  return 0;
}

const char *DataParamAcc::getRotateBone() const {
  if (isValid()) {
    return unknown08->getRotateBone();
  }

  return nullptr;
}

u32 DataParamAcc::getPersonality() const {
  if (isValid()) {
    return unknown08->getPersonality();
  }

  return 0;
}

u32 DataParamAcc::getCoolTime() const {
  if (isValid()) {
    return unknown08->getCoolTime();
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMin(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getNorAtkDmgMin(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMax(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getNorAtkDmgMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipAcce(u32 slot, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getEquipAcce(slot, isVirtual);
  }

  return 0;
}

bool DataParamAcc::getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getEquipOrb(orbs, isVirtual);
  }

  return false;
}

int DataParamAcc::getBladeSet(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeSet(isVirtual);
  }

  return -1;
}

void DataParamAcc::setBladeSet(int slot) {
  if (isValid()) {
    unknown08->setBladeSet(slot);
  }
}

u32 DataParamAcc::getBlade(int slot, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBlade(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getClass(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getClass(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipWeapon(int slot, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getEquipWeapon(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getWeaponType(int slot, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getWeaponType(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getAsmWeaponType(int slot) const {
  u32 weaponType = 0;
  if (isValid()) {
    weaponType = unknown08->getWeaponType(false, slot);
  }

  return GfDataWeapon::getAsmWeaponType(weaponType);
}

u32 DataParamAcc::getBladePower(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladePower(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArts(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArts(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEnhance(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsEnhance(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsN(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsN(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsNH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsNH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getFieldSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getFieldSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getKeyLevel() const {
  if (isValid()) {
    return unknown08->getKeyLevel();
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsEx(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsExH(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsExH(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx2(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsEx2(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEx2H(bool isVirtual) const {
  if (isValid()) {
    return unknown08->getBladeArtsEx2H(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getFavoriteCategory(FAVORITE favorite) const {
  if (isValid()) {
    return unknown08->getFavoriteCategory(favorite);
  }

  return 0;
}

u32 DataParamAcc::getFavoriteItem(FAVORITE favorite) const {
  if (isValid()) {
    return unknown08->getFavoriteItem(favorite);
  }

  return 0;
}

u32 DataParamAcc::getArtsAchievement(u32 index) const {
  if (isValid()) {
    return unknown08->getArtsAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getSkillAchievement(u32 index) const {
  if (isValid()) {
    return unknown08->getSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillAchievement(u32 index) const {
  if (isValid()) {
    return unknown08->getFieldSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getKeyAchievement() const {
  if (isValid()) {
    return unknown08->getKeyAchievement();
  }

  return 0;
}

void DataParamAcc::setVirtualEquipWpn(u32 weapon, int slot) {
  if (isValid()) {
    unknown08->setVirtualEquipWpn(weapon, slot);
  }
}

void DataParamAcc::setVirtualEquipAcc(u32 slot, u32 accessory) {
  if (isValid()) {
    unknown08->setVirtualEquipAcc(slot, accessory);
  }
}

u32 DataParamAcc::getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) {
  if (isValid()) {
    return unknown08->getEquipAcceResult(slot, accessory, isVirtual);
  }

  return 5;
}

void DataParamAcc::setVirtualSetBlade(u32 blade, int slot) {
  if (isValid()) {
    unknown08->setVirtualSetBlade(blade, slot);
  }
}

void DataParamAcc::setVirtualEquipWpnChip(u32 chip) {
  if (isValid()) {
    unknown08->setVirtualEquipWpnChip(chip);
  }
}

void DataParamAcc::setVirtualEquipOrb(u32 orb, u32 slot) {
  if (isValid()) {
    unknown08->setVirtualEquipOrb(orb, slot);
  }
}

void DataParamAcc::setMenuParam() {
  if (isValid()) {
    unknown08->setMenuParam();
  }
}

u32 DataParamAcc::getLinkNum() const {
  if (isValid()) {
    return unknown08->getLinkNum();
  }

  return 500;
}

u32 DataParamAcc::getDeadNum() const {
  if (isValid()) {
    return unknown08->getDeadNum();
  }

  return 500;
}

u32 DataParamAcc::getAppStNum() const {
  if (isValid()) {
    return unknown08->getAppStNum();
  }

  return 500;
}

u32 DataParamAcc::getAppEndNum() const {
  if (isValid()) {
    return unknown08->getAppEndNum();
  }

  return 500;
}

u32 DataParamAcc::getBdatIdEnParam() const {
  if (isValid()) {
    return unknown08->getBdatIdEnParam();
  }

  return 0;
}

u32 DataParamAcc::getBdatIdEnRsc() const {
  if (isValid()) {
    return unknown08->getBdatIdEnRsc();
  }

  return 0;
}

bool DataParamAcc::isGuardFront() const {
  if (isValid()) {
    return unknown08->isGuardFront();
  }

  return false;
}

bool DataParamAcc::isGuardLeft() const {
  if (isValid()) {
    return unknown08->isGuardLeft();
  }

  return false;
}

bool DataParamAcc::isGuardRight() const {
  if (isValid()) {
    return unknown08->isGuardRight();
  }

  return false;
}

bool DataParamAcc::isGuardBack() const {
  if (isValid()) {
    return unknown08->isGuardBack();
  }

  return false;
}

bool DataParamAcc::isFieldDamage() const {
  if (isValid()) {
    return unknown08->isFieldDamage();
  }

  return false;
}

u32 DataParamAcc::getResistancePower() const {
  if (isValid()) {
    return unknown08->getResistancePower();
  }

  return 0;
}

u32 DataParamAcc::getResistanceEther() const {
  if (isValid()) {
    return unknown08->getResistanceEther();
  }

  return 0;
}

u32 DataParamAcc::getResistanceCombo() const {
  if (isValid()) {
    return unknown08->getResistanceCombo();
  }

  return 0;
}

u32 DataParamAcc::getInvincibleCombo() const {
  if (isValid()) {
    return unknown08->getInvincibleCombo();
  }

  return 0;
}

u32 DataParamAcc::getLevelGold() const {
  if (isValid()) {
    return unknown08->getLevelGold();
  }

  return 0;
}

u32 DataParamAcc::getLevelExp() const {
  if (isValid()) {
    return unknown08->getLevelExp();
  }

  return 0;
}

u32 DataParamAcc::getLevelWp() const {
  if (isValid()) {
    return unknown08->getLevelWp();
  }

  return 0;
}

u32 DataParamAcc::getLevelSp() const {
  if (isValid()) {
    return unknown08->getLevelSp();
  }

  return 0;
}

u32 DataParamAcc::getGenus() const {
  if (isValid()) {
    return unknown08->getGenus();
  }

  return 0;
}

bool DataParamAcc::isLinkGenus() const {
  if (isValid()) {
    return unknown08->isLinkGenus();
  }

  return false;
}

f32 DataParamAcc::getLinkRadius() const {
  if (isValid()) {
    return unknown08->getLinkRadius();
  }

  return 0.0f;
}

u32 DataParamAcc::getGoldDivide() const {
  if (isValid()) {
    return unknown08->getGoldDivide();
  }

  return 0;
}

u32 DataParamAcc::getGoldDivideRev() const {
  if (isValid()) {
    return unknown08->getGoldDivideRev();
  }

  return 0;
}

const SDataEnemy *DataParamAcc::getSDataEnemy() const {
  if (isValid()) {
    return unknown08->getSDataEnemy();
  }

  return nullptr;
}

void DataParamAcc::setVirtualLevel(u32 level) {
  if (isValid()) {
    unknown08->setVirtualLevel(level);
  }
}

bool DataParamAcc::isEnbaleTarget() const {
  if (isValid()) {
    return unknown08->isEnbaleTarget();
  }

  return true;
}

GimmickType DataParamAcc::getGimmickType() const {
  if (isValid()) {
    return unknown08->getGimmickType();
  }

  return GimmickType();
}

bool DataParamAcc::isNoCameraFade() const {
  if (isValid()) {
    return unknown08->isNoCameraFade();
  }

  return false;
}

bool DataParamAcc::isWeaponDrawDisp() const {
  if (isValid()) {
    return unknown08->isWeaponDrawDisp();
  }

  return false;
}

const char *DataParamAcc::getCenterBone() const {
  if (isValid()) {
    return unknown08->getCenterBone();
  }

  return nullptr;
}

const char *DataParamAcc::getCamBone() const {
  if (isValid()) {
    return unknown08->getCamBone();
  }

  return nullptr;
}

DataIdeaAcc::DataIdeaAcc(DataParamAcc &dataParamAcc) : unknown00(dataParamAcc.unknown08->getIdea()), unknown08(false) {
  if (unknown00 != nullptr) {
    unknown08 = dataParamAcc.getObjType() == OBJECT_TYPE_BLADE;
  }
}

DataIdeaAcc::DataIdeaAcc(SDataIdea &idea, bool isBlade) : unknown00(&idea), unknown08(isBlade) {}

bool DataIdeaAcc::isValid() const { return unknown00 != nullptr; }

int DataIdeaAcc::getLevel(u32 idea) const {
  if (this->unknown00 != nullptr) {
    return this->unknown00->unknown00[idea].unknown04;
  }

  return 0;
}

SDataIdea *DataIdeaAcc::get() const { return unknown00; }

void DataIdeaAcc::setLevel(u32 idea, u32 level) {
  if (this->unknown00 != nullptr) {
    this->unknown00->setLevel(idea, level);
  }
}

bool DataIdeaAcc::addPoint(u32 idea, u32 point) {
  if (this->unknown00 != nullptr) {
    this->unknown00->setPoint(idea, this->unknown00->unknown00[idea].unknown00 + point);
  }

  return false;
}

u32 DataIdeaAcc::getPoint(u32 idea) const {
  const SDataIdea::unknown004 *ideas = unknown00->unknown00;
  return ideas[idea].unknown00;
}

void DataIdeaAcc::setPointForDebug(u32 idea, u32 point) {
  if (this->unknown00 != nullptr) {
    this->unknown00->setPoint(idea, point);
  }
}

u32 DataIdeaAcc::getMaximumIdeaLevel() const {
  if (unknown00 == nullptr) {
    return 0;
  }
  mm::mtl::FixedVector<u32, 5> ideas;
  for (u32 idea = 0; idea < 4; idea++) {
    u32 level = getLevel(idea);
    if (ideas.empty()) {
      ideas.push_back(idea);
    } else {
      for (const u32 *it = ideas.begin(); it != ideas.end(); it++) {
        u32 other = getLevel(*it);
        if (other > level) {
          ideas.clear();
          ideas.push_back(idea);
          break;
        }
        if (other == level) {
          ideas.push_back(idea);
        }
      }
    }
  }
  if (ideas.size() > 1) {
    u32 random = ml::mtRand(ideas.size() * 100);
    return ideas[random / 100];
  }
  return ideas[0];
}

unknown079 DataIdeaAcc::getRatio(u32 level0, u32 level1, u32 level2, u32 level3, int offset0, int offset1, int offset2, int offset3) const {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  f32 total = getSubRatio(level0, offset0, 0) + getSubRatio(level1, offset1, 1) + getSubRatio(level2, offset2, 2) + getSubRatio(level3, offset3, 3);
  unknown079 result;
  result.unknown00 = static_cast<int>(total + (total > 0.0f ? 0.5f : -0.5f));
  if (result.unknown00 > 3) {
    result.unknown02 = bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_14);
  } else if (result.unknown00 > 2) {
    result.unknown02 = bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_13);
  } else if (result.unknown00 > 1) {
    result.unknown02 = bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_12);
  } else if (result.unknown00 > 0) {
    result.unknown02 = bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_11);
  } else {
    result.unknown02 = bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_10);
  }
  return result;
}

f32 DataIdeaAcc::getSubRatio(u32 level, int offset, u32 idea) const {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  int diff = level - mm::clamp(getLevel(idea) + offset, 0, static_cast<int>(IDEA_LEVEL_UNKNOWN_10));
  if (diff >= 5) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_9) * 0.1f;
  }
  if (diff >= 4) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_8) * 0.1f;
  }
  if (diff >= 3) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_7) * 0.1f;
  }
  if (diff >= 2) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_6) * 0.1f;
  }
  if (diff >= 1) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_5) * 0.1f;
  }
  if (diff >= 0) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_4) * 0.1f;
  }
  if (diff >= -1) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_3) * 0.1f;
  }
  if (diff >= -2) {
    return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_2) * 0.1f;
  }
  return bdatBlade->getCreateConfigValue(CREATE_CONFIG_UNKNOWN_1) * 0.1f;
}

} // namespace gf
