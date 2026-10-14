#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_obj.h"
#include "gf/data/gf_data_weapon.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

DataParamAcc::DataParamAcc(const ParamObj &paramObj) {
  if (paramObj.handle != INVALID_HANDLE) {
    setupObjHandle(paramObj.handle);
  } else {
    setupObjId(paramObj.objectType, paramObj.id, static_cast<GimmickType>(0));
  }
}

DataParamAcc::DataParamAcc(GF_OBJ_HANDLE *handle) { setupObjHandle(handle); }

DataParamAcc::DataParamAcc(u32 objectType, u32 id, GimmickType gimmickType) { setupObjId(objectType, id, gimmickType); }

bool DataParamAcc::isValid() const { return obj != nullptr && obj->isValid(); }

u32 DataParamAcc::getObjType() const {
  if (isValid()) {
    return obj->getObjType();
  }

  return 0;
}

const char *DataParamAcc::getModelResourceName() const {
  if (isValid()) {
    return obj->getModelResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getMotionResourceName() const {
  if (isValid()) {
    return obj->getMotionResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getEffectResourceName() const {
  if (isValid()) {
    return obj->getEffectResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getSeResourceName() const {
  if (isValid()) {
    return obj->getSeResourceName();
  }

  return nullptr;
}

const char *DataParamAcc::getName() const {
  if (isValid()) {
    const char *name = obj->getName();
    return name == nullptr ? "" : name;
  }

  return "";
}

bool DataParamAcc::getName(u8 *&bdat, u32 &textId) const {
  if (isValid()) {
    return obj->getName(bdat, textId);
  }

  return false;
}

u32 DataParamAcc::getBdatId() const {
  if (isValid()) {
    return obj->getBdatId();
  }

  return 0;
}

u32 DataParamAcc::getHp() const {
  if (isValid()) {
    return obj->getHp();
  }

  return 0;
}

u32 DataParamAcc::getLevel(bool isVirtual) const {
  if (isValid()) {
    return obj->getLevel(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getExp() const {
  if (isValid()) {
    return obj->getExp();
  }

  return 0;
}

u32 DataParamAcc::getBattleExp() const {
  if (isValid()) {
    return obj->getBattleExp();
  }

  return 0;
}

u32 DataParamAcc::getExpNext(bool isVirtual) const {
  if (isValid()) {
    return obj->getExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBattleExpNext(bool isVirtual) const {
  if (isValid()) {
    return obj->getBattleExpNext(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponPoint(u32 weaponType) const {
  if (isValid()) {
    return obj->getWeaponPoint(weaponType);
  }

  return 0;
}

void DataParamAcc::addWeaponPoint(u32 weaponType, int weaponPoint) {
  if (isValid()) {
    obj->addWeaponPoint(weaponType, weaponPoint);
  }
}

u32 DataParamAcc::getSkillPoint() const {
  if (isValid()) {
    return obj->getSkillPoint();
  }

  return 0;
}

void DataParamAcc::addSkillPoint(int skillPoint) {
  if (isValid()) {
    obj->addSkillPoint(skillPoint);
  }
}

u32 DataParamAcc::getDriverArts(u32 weaponType, u32 index) const {
  if (isValid()) {
    return obj->getDriverArts(weaponType, index);
  }

  return 0;
}

bool DataParamAcc::setDriverArts(u32 weaponType, int index, u32 arts) {
  if (isValid()) {
    return obj->setDriverArts(weaponType, index, arts);
  }

  return false;
}

u32 DataParamAcc::getDriverArtsLevel(u32 arts) const {
  if (isValid()) {
    return obj->getDriverArtsLevel(arts);
  }

  return 0;
}

void DataParamAcc::setDriverArtsLevel(u32 arts, u32 level) {
  if (isValid()) {
    obj->setDriverArtsLevel(arts, level);
  }
}

u32 DataParamAcc::getHpMax(bool isVirtual) const {
  if (isValid()) {
    return obj->getHpMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getStrength(bool isVirtual) const {
  if (isValid()) {
    return obj->getStrength(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPowerEther(bool isVirtual) const {
  if (isValid()) {
    return obj->getPowerEther(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getDex(bool isVirtual) const {
  if (isValid()) {
    return obj->getDex(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAgility(bool isVirtual) const {
  if (isValid()) {
    return obj->getAgility(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getLuck(bool isVirtual) const {
  if (isValid()) {
    return obj->getLuck(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getPArmor(bool isVirtual) const {
  if (isValid()) {
    return obj->getPArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEArmor(bool isVirtual) const {
  if (isValid()) {
    return obj->getEArmor(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getCriticalRate(bool isVirtual) const {
  if (isValid()) {
    return obj->getCriticalRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getGuardRate(bool isVirtual) const {
  if (isValid()) {
    return obj->getGuardRate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getAutoHate(bool isVirtual) const {
  if (isValid()) {
    return obj->getAutoHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getArtsHate(bool isVirtual) const {
  if (isValid()) {
    return obj->getArtsHate(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponDamage(bool isVirtual) const {
  if (isValid()) {
    return obj->getWeaponDamage(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getWeaponStability(bool isVirtual) const {
  if (isValid()) {
    return obj->getWeaponStability(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getChestHeight() const {
  if (isValid()) {
    return obj->getChestHeight();
  }

  return 0;
}

u32 DataParamAcc::getLandingHeight() const {
  if (isValid()) {
    return obj->getLandingHeight();
  }

  return 0;
}

u32 DataParamAcc::getIconData() const {
  if (isValid()) {
    return obj->getIconData();
  }

  return 0;
}

u32 DataParamAcc::getRace() const {
  if (isValid()) {
    return obj->getRace();
  }

  return 0;
}

u32 DataParamAcc::getQuestRace() const {
  if (isValid()) {
    return obj->getQuestRace();
  }

  return 1;
}

u32 DataParamAcc::getGender() const {
  if (isValid()) {
    return obj->getGender();
  }

  return 0;
}

u32 DataParamAcc::getAttribute(int slot, bool isVirtual) const {
  if (isValid()) {
    return obj->getAttribute(isVirtual, slot);
  }

  return 0;
}

bool DataParamAcc::isDispInitExtraParts(u32 part) const {
  if (isValid()) {
    return obj->isDispInitExtraParts(part);
  }

  return true;
}

bool DataParamAcc::isScenarioMask() const {
  if (isValid()) {
    return obj->isScenarioMask();
  }

  return false;
}

u32 DataParamAcc::getRole(bool isVirtual) const {
  if (isValid()) {
    return obj->getRole();
  }

  return 0;
}

const char *DataParamAcc::getVoiceStr() const {
  if (isValid()) {
    if (const char *voiceStr = obj->getVoiceStr()) {
      return voiceStr;
    }

    return "";
  }

  return "";
}

u32 DataParamAcc::getMenuOffset() const {
  if (isValid()) {
    return obj->getMenuOffset();
  }

  return 0;
}

u32 DataParamAcc::getFootStep() const {
  if (isValid()) {
    return obj->getFootStep();
  }

  return 0;
}

u32 DataParamAcc::getFootStepEffect() const {
  if (isValid()) {
    return obj->getFootStepEffect();
  }

  return 1;
}

u32 DataParamAcc::getEyeRotControl() const {
  if (isValid()) {
    return obj->getEyeRotControl();
  }

  return 0;
}

const char *DataParamAcc::getRotateBone() const {
  if (isValid()) {
    return obj->getRotateBone();
  }

  return nullptr;
}

u32 DataParamAcc::getPersonality() const {
  if (isValid()) {
    return obj->getPersonality();
  }

  return 0;
}

u32 DataParamAcc::getCoolTime() const {
  if (isValid()) {
    return obj->getCoolTime();
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMin(bool isVirtual) const {
  if (isValid()) {
    return obj->getNorAtkDmgMin(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getNorAtkDmgMax(bool isVirtual) const {
  if (isValid()) {
    return obj->getNorAtkDmgMax(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipAcce(u32 slot, bool isVirtual) const {
  if (isValid()) {
    return obj->getEquipAcce(slot, isVirtual);
  }

  return 0;
}

bool DataParamAcc::getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool isVirtual) const {
  if (isValid()) {
    return obj->getEquipOrb(orbs, isVirtual);
  }

  return false;
}

int DataParamAcc::getBladeSet(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeSet(isVirtual);
  }

  return -1;
}

void DataParamAcc::setBladeSet(int slot) {
  if (isValid()) {
    obj->setBladeSet(slot);
  }
}

u32 DataParamAcc::getBlade(int slot, bool isVirtual) const {
  if (isValid()) {
    return obj->getBlade(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getClass(bool isVirtual) const {
  if (isValid()) {
    return obj->getClass(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getEquipWeapon(int slot, bool isVirtual) const {
  if (isValid()) {
    return obj->getEquipWeapon(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getWeaponType(int slot, bool isVirtual) const {
  if (isValid()) {
    return obj->getWeaponType(isVirtual, slot);
  }

  return 0;
}

u32 DataParamAcc::getAsmWeaponType(int slot) const {
  u32 weaponType = 0;
  if (isValid()) {
    weaponType = obj->getWeaponType(false, slot);
  }

  return GfDataWeapon::getAsmWeaponType(weaponType);
}

u32 DataParamAcc::getBladePower(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladePower(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArts(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArts(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEnhance(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsEnhance(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsN(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsN(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsNH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsNH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getBladeSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkill(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getFieldSkill(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillLevel(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getFieldSkillLevel(isVirtual, index);
  }

  return 0;
}

u32 DataParamAcc::getKeyLevel() const {
  if (isValid()) {
    return obj->getKeyLevel();
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsH(u32 index, bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsH(isVirtual, index);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsEx(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsExH(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsExH(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getBladeArtsEx2(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsEx2(isVirtual);
  }

  return 0;
}

u32 DataParamAcc::getBladeArtsEx2H(bool isVirtual) const {
  if (isValid()) {
    return obj->getBladeArtsEx2H(isVirtual);
  }

  return 100;
}

u32 DataParamAcc::getFavoriteCategory(FAVORITE favorite) const {
  if (isValid()) {
    return obj->getFavoriteCategory(favorite);
  }

  return 0;
}

u32 DataParamAcc::getFavoriteItem(FAVORITE favorite) const {
  if (isValid()) {
    return obj->getFavoriteItem(favorite);
  }

  return 0;
}

u32 DataParamAcc::getArtsAchievement(u32 index) const {
  if (isValid()) {
    return obj->getArtsAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getSkillAchievement(u32 index) const {
  if (isValid()) {
    return obj->getSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getFieldSkillAchievement(u32 index) const {
  if (isValid()) {
    return obj->getFieldSkillAchievement(index);
  }

  return 0;
}

u32 DataParamAcc::getKeyAchievement() const {
  if (isValid()) {
    return obj->getKeyAchievement();
  }

  return 0;
}

void DataParamAcc::setVirtualEquipWpn(u32 weapon, int slot) {
  if (isValid()) {
    obj->setVirtualEquipWpn(weapon, slot);
  }
}

void DataParamAcc::setVirtualEquipAcc(u32 slot, u32 accessory) {
  if (isValid()) {
    obj->setVirtualEquipAcc(slot, accessory);
  }
}

u32 DataParamAcc::getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) {
  if (isValid()) {
    return obj->getEquipAcceResult(slot, accessory, isVirtual);
  }

  return 5;
}

void DataParamAcc::setVirtualSetBlade(u32 blade, int slot) {
  if (isValid()) {
    obj->setVirtualSetBlade(blade, slot);
  }
}

void DataParamAcc::setVirtualEquipWpnChip(u32 chip) {
  if (isValid()) {
    obj->setVirtualEquipWpnChip(chip);
  }
}

void DataParamAcc::setVirtualEquipOrb(u32 orb, u32 slot) {
  if (isValid()) {
    obj->setVirtualEquipOrb(orb, slot);
  }
}

void DataParamAcc::setMenuParam() {
  if (isValid()) {
    obj->setMenuParam();
  }
}

u32 DataParamAcc::getLinkNum() const {
  if (isValid()) {
    return obj->getLinkNum();
  }

  return 500;
}

u32 DataParamAcc::getDeadNum() const {
  if (isValid()) {
    return obj->getDeadNum();
  }

  return 500;
}

u32 DataParamAcc::getAppStNum() const {
  if (isValid()) {
    return obj->getAppStNum();
  }

  return 500;
}

u32 DataParamAcc::getAppEndNum() const {
  if (isValid()) {
    return obj->getAppEndNum();
  }

  return 500;
}

u32 DataParamAcc::getBdatIdEnParam() const {
  if (isValid()) {
    return obj->getBdatIdEnParam();
  }

  return 0;
}

u32 DataParamAcc::getBdatIdEnRsc() const {
  if (isValid()) {
    return obj->getBdatIdEnRsc();
  }

  return 0;
}

bool DataParamAcc::isGuardFront() const {
  if (isValid()) {
    return obj->isGuardFront();
  }

  return false;
}

bool DataParamAcc::isGuardLeft() const {
  if (isValid()) {
    return obj->isGuardLeft();
  }

  return false;
}

bool DataParamAcc::isGuardRight() const {
  if (isValid()) {
    return obj->isGuardRight();
  }

  return false;
}

bool DataParamAcc::isGuardBack() const {
  if (isValid()) {
    return obj->isGuardBack();
  }

  return false;
}

bool DataParamAcc::isFieldDamage() const {
  if (isValid()) {
    return obj->isFieldDamage();
  }

  return false;
}

u32 DataParamAcc::getResistancePower() const {
  if (isValid()) {
    return obj->getResistancePower();
  }

  return 0;
}

u32 DataParamAcc::getResistanceEther() const {
  if (isValid()) {
    return obj->getResistanceEther();
  }

  return 0;
}

u32 DataParamAcc::getResistanceCombo() const {
  if (isValid()) {
    return obj->getResistanceCombo();
  }

  return 0;
}

u32 DataParamAcc::getInvincibleCombo() const {
  if (isValid()) {
    return obj->getInvincibleCombo();
  }

  return 0;
}

u32 DataParamAcc::getLevelGold() const {
  if (isValid()) {
    return obj->getLevelGold();
  }

  return 0;
}

u32 DataParamAcc::getLevelExp() const {
  if (isValid()) {
    return obj->getLevelExp();
  }

  return 0;
}

u32 DataParamAcc::getLevelWp() const {
  if (isValid()) {
    return obj->getLevelWp();
  }

  return 0;
}

u32 DataParamAcc::getLevelSp() const {
  if (isValid()) {
    return obj->getLevelSp();
  }

  return 0;
}

u32 DataParamAcc::getGenus() const {
  if (isValid()) {
    return obj->getGenus();
  }

  return 0;
}

bool DataParamAcc::isLinkGenus() const {
  if (isValid()) {
    return obj->isLinkGenus();
  }

  return false;
}

f32 DataParamAcc::getLinkRadius() const {
  if (isValid()) {
    return obj->getLinkRadius();
  }

  return 0.0f;
}

u32 DataParamAcc::getGoldDivide() const {
  if (isValid()) {
    return obj->getGoldDivide();
  }

  return 0;
}

u32 DataParamAcc::getGoldDivideRev() const {
  if (isValid()) {
    return obj->getGoldDivideRev();
  }

  return 0;
}

const SDataEnemy *DataParamAcc::getSDataEnemy() const {
  if (isValid()) {
    return obj->getSDataEnemy();
  }

  return nullptr;
}

void DataParamAcc::setVirtualLevel(u32 level) {
  if (isValid()) {
    obj->setVirtualLevel(level);
  }
}

bool DataParamAcc::isEnbaleTarget() const {
  if (isValid()) {
    return obj->isEnbaleTarget();
  }

  return true;
}

GimmickType DataParamAcc::getGimmickType() const {
  if (isValid()) {
    return obj->getGimmickType();
  }

  return GimmickType();
}

bool DataParamAcc::isNoCameraFade() const {
  if (isValid()) {
    return obj->isNoCameraFade();
  }

  return false;
}

bool DataParamAcc::isWeaponDrawDisp() const {
  if (isValid()) {
    return obj->isWeaponDrawDisp();
  }

  return false;
}

const char *DataParamAcc::getCenterBone() const {
  if (isValid()) {
    return obj->getCenterBone();
  }

  return nullptr;
}

const char *DataParamAcc::getCamBone() const {
  if (isValid()) {
    return obj->getCamBone();
  }

  return nullptr;
}

} // namespace gf
