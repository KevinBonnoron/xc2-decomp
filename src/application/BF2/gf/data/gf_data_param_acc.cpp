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
  if (paramObj.m_GF_OBJ_HANDLE != unknown020) {
    setupObjHandle(paramObj.m_GF_OBJ_HANDLE);
  } else {
    setupObjId(paramObj.unknown08, paramObj.unknown0c, static_cast<GimmickType>(0));
  }
}

void DataParamAcc::setupObjHandle(GF_OBJ_HANDLE *handle) {
  m_iDataObj = nullptr;
  m_GF_OBJ_HANDLE = handle;
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
  m_iDataObj = obj;
}

void DataParamAcc::setupObjId(u32 objectType, u32 id, GimmickType gimmickType) {
  m_iDataObj = nullptr;
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
  m_iDataObj = obj;
}

DataParamAcc::DataParamAcc(GF_OBJ_HANDLE *handle) { setupObjHandle(handle); }

DataParamAcc::DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType) { setupObjId(objectType, id, gimmickType); }

DataParamAcc::~DataParamAcc() {
  if (m_iDataObj != nullptr) {
    m_iDataObj->~IDataObj();
    _gfdac::s_accbuf.unknown004(m_iDataObj);
    m_iDataObj = nullptr;
  }
}

bool DataParamAcc::isValid() const { return m_iDataObj != nullptr && m_iDataObj->isValid(); }

u32 DataParamAcc::getObjType() const {
  if (isValid()) {
    return m_iDataObj->getObjType();
  }

  return 0;
}

const char *DataParamAcc::getModelResourceName() const {
  if (isValid()) {
    return m_iDataObj->getModelResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getMotionResourceName() const {
  if (isValid()) {
    return m_iDataObj->getMotionResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getEffectResourceName() const {
  if (isValid()) {
    return m_iDataObj->getEffectResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getSeResourceName() const {
  if (isValid()) {
    return m_iDataObj->getSeResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getName() const {
  if (isValid()) {
    const char *name = m_iDataObj->getName();
    return name == nullptr ? "" : name;
  }

  return "";
}

bool DataParamAcc::getName(u8 *&bdat, u32 &textId) const {
  if (isValid()) {
    return m_iDataObj->getName(bdat, textId);
  }

  return false;
}

u32 DataParamAcc::getBdatId() const {
  if (isValid()) {
    return m_iDataObj->getBdatId();
  }

  return 0;
}

u32 DataParamAcc::getHp() const {
  if (isValid()) {
    return m_iDataObj->getHp();
  }

  return 0;
}

u32 DataParamAcc::getLevel(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getLevel(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getExp() const {
  if (isValid()) {
    return m_iDataObj->getExp();
  }

  return 0;
}

u32 DataParamAcc::getBattleExp() const {
  if (isValid()) {
    return m_iDataObj->getBattleExp();
  }

  return 0;
}

u32 DataParamAcc::getExpNext(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBattleExpNext(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBattleExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponPoint(u32 weaponType) const {
  if (isValid()) {
    return m_iDataObj->getWeaponPoint(weaponType);
  }

  return 0;
}

void DataParamAcc::addWeaponPoint(u32 weaponType, int weaponPoint) {
  if (isValid()) {
    m_iDataObj->addWeaponPoint(weaponType, weaponPoint);
  }
}

u32 DataParamAcc::getSkillPoint() const {
  if (isValid()) {
    return m_iDataObj->getSkillPoint();
  }

  return 0;
}

void DataParamAcc::addSkillPoint(int skillPoint) {
  if (isValid()) {
    m_iDataObj->addSkillPoint(skillPoint);
  }
}

u32 DataParamAcc::getDriverArts(u32 weaponType, u32 index) const {
  if (isValid()) {
    return m_iDataObj->getDriverArts(weaponType, index);
  }

  return 0;
}

bool DataParamAcc::setDriverArts(u32 weaponType, int index, u32 arts) {
  if (isValid()) {
    return m_iDataObj->setDriverArts(weaponType, index, arts);
  }

  return false;
}

u32 DataParamAcc::getDriverArtsLevel(u32 arts) const {
  if (isValid()) {
    return m_iDataObj->getDriverArtsLevel(arts);
  }

  return 0;
}

void DataParamAcc::setDriverArtsLevel(u32 arts, u32 level) {
  if (isValid()) {
    m_iDataObj->setDriverArtsLevel(arts, level);
  }
}

u32 DataParamAcc::getHpMax(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getHpMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getStrength(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getStrength(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPowerEther(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getPowerEther(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getDex(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getDex(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAgility(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getAgility(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getLuck(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getLuck(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPArmor(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getPArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEArmor(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getEArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getCriticalRate(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getCriticalRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getGuardRate(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getGuardRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAutoHate(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getAutoHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getArtsHate(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getArtsHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponDamage(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getWeaponDamage(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponStability(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getWeaponStability(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getChestHeight() const {
  if (isValid()) {
    return m_iDataObj->getChestHeight();
  }

  return 0;
}

u32 DataParamAcc::getLandingHeight() const {
  if (isValid()) {
    return m_iDataObj->getLandingHeight();
  }

  return 0;
}

u32 DataParamAcc::getIconData() const {
  if (isValid()) {
    return m_iDataObj->getIconData();
  }

  return 0;
}

u32 DataParamAcc::getRace() const {
  if (isValid()) {
    return m_iDataObj->getRace();
  }

  return 0;
}

u32 DataParamAcc::getQuestRace() const {
  if (isValid()) {
    return m_iDataObj->getQuestRace();
  }

  return 1;
}

u32 DataParamAcc::getGender() const {
  if (isValid()) {
    return m_iDataObj->getGender();
  }

  return 0;
}

u32 DataParamAcc::getAttribute(int slot, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getAttribute(isVirtual, slot);
  }

  return 0;
}

bool DataParamAcc::isDispInitExtraParts(u32 part) const {
  if (isValid()) {
    return m_iDataObj->isDispInitExtraParts(part);
  }

  return true;
}

bool DataParamAcc::isScenarioMask() const {
  if (isValid()) {
    return m_iDataObj->isScenarioMask();
  }

  return false;
}

u32 DataParamAcc::getRole(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getRole();
  }

  return 0;
}

const char *DataParamAcc::getVoiceStr() const {
  if (isValid()) {
    if (const char *voiceStr = m_iDataObj->getVoiceStr()) {
      return voiceStr;
    }

    return "";
  }

  return "";
}

u32 DataParamAcc::getMenuOffset() const {
  if (isValid()) {
    return m_iDataObj->getMenuOffset();
  }

  return 0;
}

u32 DataParamAcc::getFootStep() const {
  if (isValid()) {
    return m_iDataObj->getFootStep();
  }

  return 0;
}

u32 DataParamAcc::getFootStepEffect() const {
  if (isValid()) {
    return m_iDataObj->getFootStepEffect();
  }

  return 1;
}

u32 DataParamAcc::getEyeRotControl() const {
  if (isValid()) {
    return m_iDataObj->getEyeRotControl();
  }

  return 0;
}

const char *DataParamAcc::getRotateBone() const {
  if (isValid()) {
    return m_iDataObj->getRotateBone();
  }

  return nullptr;
}

u32 DataParamAcc::getPersonality() const {
  if (isValid()) {
    return m_iDataObj->getPersonality();
  }

  return 0;
}

u32 DataParamAcc::getCoolTime() const {
  if (isValid()) {
    return m_iDataObj->getCoolTime();
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMin(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getNorAtkDmgMin(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMax(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getNorAtkDmgMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipAcce(u32 slot, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getEquipAcce(slot, isVirtual);
  }

  return 0;
}

bool DataParamAcc::getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getEquipOrb(orbs, isVirtual);
  }

  return false;
}

int DataParamAcc::getBladeSet(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeSet(isVirtual);
  }

  return -1;
}

void DataParamAcc::setBladeSet(int slot) {
  if (isValid()) {
    m_iDataObj->setBladeSet(slot);
  }
}

u32 DataParamAcc::getBlade(int slot, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBlade(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getClass(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getClass(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipWeapon(int slot, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getEquipWeapon(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getWeaponType(int slot, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getWeaponType(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getAsmWeaponType(int slot) const {
  u32 weaponType = 0;
  if (isValid()) {
    weaponType = m_iDataObj->getWeaponType(false, slot);
  }

  return GfDataWeapon::getAsmWeaponType(weaponType);
}

u32 DataParamAcc::getBladePower(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladePower(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArts(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArts(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEnhance(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsEnhance(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsN(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsN(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsNH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsNH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getFieldSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getFieldSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getKeyLevel() const {
  if (isValid()) {
    return m_iDataObj->getKeyLevel();
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsEx(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsExH(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsExH(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx2(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsEx2(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEx2H(bool isVirtual) const {
  if (isValid()) {
    return m_iDataObj->getBladeArtsEx2H(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getFavoriteCategory(FAVORITE favorite) const {
  if (isValid()) {
    return m_iDataObj->getFavoriteCategory(favorite);
  }

  return 0;
}

u32 DataParamAcc::getFavoriteItem(FAVORITE favorite) const {
  if (isValid()) {
    return m_iDataObj->getFavoriteItem(favorite);
  }

  return 0;
}

u32 DataParamAcc::getArtsAchievement(u32 index) const {
  if (isValid()) {
    return m_iDataObj->getArtsAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getSkillAchievement(u32 index) const {
  if (isValid()) {
    return m_iDataObj->getSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillAchievement(u32 index) const {
  if (isValid()) {
    return m_iDataObj->getFieldSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getKeyAchievement() const {
  if (isValid()) {
    return m_iDataObj->getKeyAchievement();
  }

  return 0;
}

void DataParamAcc::setVirtualEquipWpn(u32 weapon, int slot) {
  if (isValid()) {
    m_iDataObj->setVirtualEquipWpn(weapon, slot);
  }
}

void DataParamAcc::setVirtualEquipAcc(u32 slot, u32 accessory) {
  if (isValid()) {
    m_iDataObj->setVirtualEquipAcc(slot, accessory);
  }
}

u32 DataParamAcc::getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) {
  if (isValid()) {
    return m_iDataObj->getEquipAcceResult(slot, accessory, isVirtual);
  }

  return 5;
}

void DataParamAcc::setVirtualSetBlade(u32 blade, int slot) {
  if (isValid()) {
    m_iDataObj->setVirtualSetBlade(blade, slot);
  }
}

void DataParamAcc::setVirtualEquipWpnChip(u32 chip) {
  if (isValid()) {
    m_iDataObj->setVirtualEquipWpnChip(chip);
  }
}

void DataParamAcc::setVirtualEquipOrb(u32 orb, u32 slot) {
  if (isValid()) {
    m_iDataObj->setVirtualEquipOrb(orb, slot);
  }
}

void DataParamAcc::setMenuParam() {
  if (isValid()) {
    m_iDataObj->setMenuParam();
  }
}

u32 DataParamAcc::getLinkNum() const {
  if (isValid()) {
    return m_iDataObj->getLinkNum();
  }

  return 500;
}

u32 DataParamAcc::getDeadNum() const {
  if (isValid()) {
    return m_iDataObj->getDeadNum();
  }

  return 500;
}

u32 DataParamAcc::getAppStNum() const {
  if (isValid()) {
    return m_iDataObj->getAppStNum();
  }

  return 500;
}

u32 DataParamAcc::getAppEndNum() const {
  if (isValid()) {
    return m_iDataObj->getAppEndNum();
  }

  return 500;
}

u32 DataParamAcc::getBdatIdEnParam() const {
  if (isValid()) {
    return m_iDataObj->getBdatIdEnParam();
  }

  return 0;
}

u32 DataParamAcc::getBdatIdEnRsc() const {
  if (isValid()) {
    return m_iDataObj->getBdatIdEnRsc();
  }

  return 0;
}

bool DataParamAcc::isGuardFront() const {
  if (isValid()) {
    return m_iDataObj->isGuardFront();
  }

  return false;
}

bool DataParamAcc::isGuardLeft() const {
  if (isValid()) {
    return m_iDataObj->isGuardLeft();
  }

  return false;
}

bool DataParamAcc::isGuardRight() const {
  if (isValid()) {
    return m_iDataObj->isGuardRight();
  }

  return false;
}

bool DataParamAcc::isGuardBack() const {
  if (isValid()) {
    return m_iDataObj->isGuardBack();
  }

  return false;
}

bool DataParamAcc::isFieldDamage() const {
  if (isValid()) {
    return m_iDataObj->isFieldDamage();
  }

  return false;
}

u32 DataParamAcc::getResistancePower() const {
  if (isValid()) {
    return m_iDataObj->getResistancePower();
  }

  return 0;
}

u32 DataParamAcc::getResistanceEther() const {
  if (isValid()) {
    return m_iDataObj->getResistanceEther();
  }

  return 0;
}

u32 DataParamAcc::getResistanceCombo() const {
  if (isValid()) {
    return m_iDataObj->getResistanceCombo();
  }

  return 0;
}

u32 DataParamAcc::getInvincibleCombo() const {
  if (isValid()) {
    return m_iDataObj->getInvincibleCombo();
  }

  return 0;
}

u32 DataParamAcc::getLevelGold() const {
  if (isValid()) {
    return m_iDataObj->getLevelGold();
  }

  return 0;
}

u32 DataParamAcc::getLevelExp() const {
  if (isValid()) {
    return m_iDataObj->getLevelExp();
  }

  return 0;
}

u32 DataParamAcc::getLevelWp() const {
  if (isValid()) {
    return m_iDataObj->getLevelWp();
  }

  return 0;
}

u32 DataParamAcc::getLevelSp() const {
  if (isValid()) {
    return m_iDataObj->getLevelSp();
  }

  return 0;
}

u32 DataParamAcc::getGenus() const {
  if (isValid()) {
    return m_iDataObj->getGenus();
  }

  return 0;
}

bool DataParamAcc::isLinkGenus() const {
  if (isValid()) {
    return m_iDataObj->isLinkGenus();
  }

  return false;
}

f32 DataParamAcc::getLinkRadius() const {
  if (isValid()) {
    return m_iDataObj->getLinkRadius();
  }

  return 0.0f;
}

u32 DataParamAcc::getGoldDivide() const {
  if (isValid()) {
    return m_iDataObj->getGoldDivide();
  }

  return 0;
}

u32 DataParamAcc::getGoldDivideRev() const {
  if (isValid()) {
    return m_iDataObj->getGoldDivideRev();
  }

  return 0;
}

const SDataEnemy *DataParamAcc::getSDataEnemy() const {
  if (isValid()) {
    return m_iDataObj->getSDataEnemy();
  }

  return nullptr;
}

void DataParamAcc::setVirtualLevel(u32 level) {
  if (isValid()) {
    m_iDataObj->setVirtualLevel(level);
  }
}

bool DataParamAcc::isEnbaleTarget() const {
  if (isValid()) {
    return m_iDataObj->isEnbaleTarget();
  }

  return true;
}

GimmickType DataParamAcc::getGimmickType() const {
  if (isValid()) {
    return m_iDataObj->getGimmickType();
  }

  return GimmickType();
}

bool DataParamAcc::isNoCameraFade() const {
  if (isValid()) {
    return m_iDataObj->isNoCameraFade();
  }

  return false;
}

bool DataParamAcc::isWeaponDrawDisp() const {
  if (isValid()) {
    return m_iDataObj->isWeaponDrawDisp();
  }

  return false;
}

const char *DataParamAcc::getCenterBone() const {
  if (isValid()) {
    return m_iDataObj->getCenterBone();
  }

  return nullptr;
}

const char *DataParamAcc::getCamBone() const {
  if (isValid()) {
    return m_iDataObj->getCamBone();
  }

  return nullptr;
}

DataIdeaAcc::DataIdeaAcc(DataParamAcc &dataParamAcc) : m_idea(dataParamAcc.m_iDataObj->getIdea()), unknown08(false) {
  if (m_idea != nullptr) {
    unknown08 = dataParamAcc.getObjType() == OBJECT_TYPE_BLADE;
  }
}

DataIdeaAcc::DataIdeaAcc(SDataIdea &idea, bool isBlade) : m_idea(&idea), unknown08(isBlade) {}

bool DataIdeaAcc::isValid() const { return m_idea != nullptr; }

int DataIdeaAcc::getLevel(u32 idea) const {
  if (this->m_idea != nullptr) {
    return this->m_idea->unknown00[idea].unknown04;
  }

  return 0;
}

SDataIdea *DataIdeaAcc::get() const { return m_idea; }

void DataIdeaAcc::setLevel(u32 idea, u32 level) {
  if (this->m_idea != nullptr) {
    this->m_idea->setLevel(idea, level);
  }
}

bool DataIdeaAcc::addPoint(u32 idea, u32 point) {
  if (this->m_idea != nullptr) {
    this->m_idea->setPoint(idea, this->m_idea->unknown00[idea].unknown00 + point);
  }

  return false;
}

u32 DataIdeaAcc::getPoint(u32 idea) const {
  const SDataIdea::unknown004 *ideas = m_idea->unknown00;
  return ideas[idea].unknown00;
}

void DataIdeaAcc::setPointForDebug(u32 idea, u32 point) {
  if (this->m_idea != nullptr) {
    this->m_idea->setPoint(idea, point);
  }
}

u32 DataIdeaAcc::getMaximumIdeaLevel() const {
  if (m_idea == nullptr) {
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
