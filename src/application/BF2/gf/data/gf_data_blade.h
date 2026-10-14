#pragma once
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum GfIdea {};

struct SDataBladeArts {
  u16 id;
  u16 artsH;
  u8 _04[0x06 - 0x04];
  u8 achievReleaseLevel;
  u8 level;
  u8 levelMax;
  u8 _09[0x0c - 0x09];
};

static_assert(offsetof(SDataBladeArts, artsH) == 0x02, "");
static_assert(offsetof(SDataBladeArts, achievReleaseLevel) == 0x06, "");
static_assert(offsetof(SDataBladeArts, level) == 0x07, "");
static_assert(offsetof(SDataBladeArts, levelMax) == 0x08, "");
static_assert(sizeof(SDataBladeArts) == 0x0c, "");

struct SDataBladeSkill {
  u16 id;
  u8 achievReleaseLevel;
  u8 level;
  u8 levelMax;
  u8 _05[0x06 - 0x05];
};

static_assert(offsetof(SDataBladeSkill, achievReleaseLevel) == 0x02, "");
static_assert(offsetof(SDataBladeSkill, level) == 0x03, "");
static_assert(offsetof(SDataBladeSkill, levelMax) == 0x04, "");
static_assert(sizeof(SDataBladeSkill) == 0x06, "");

struct SDataBladeAchievement {
  u16 achievement;
  u8 _002[0x004 - 0x002];
  AchievQuest quests[5];
};

static_assert(offsetof(SDataBladeAchievement, quests) == 0x004, "");

static_assert(sizeof(SDataBladeAchievement) == 0x090, "");

struct SDataBladeFavorite {
  u16 category;
  u16 item;
  u16 usedCategory;
  u16 usedItem;
};

static_assert(offsetof(SDataBladeFavorite, item) == 0x02, "");
static_assert(offsetof(SDataBladeFavorite, usedCategory) == 0x04, "");
static_assert(offsetof(SDataBladeFavorite, usedItem) == 0x06, "");
static_assert(sizeof(SDataBladeFavorite) == 0x08, "");

enum ActivateType {
  ACTIVATE_TYPE_UNUSE,
  ACTIVATE_TYPE_RESERVER,
  ACTIVATE_TYPE_PARTY,
  ACTIVATE_TYPE_MERCENARY_TEAM,
};

enum {
  BLADE_ACTIVATE_UNUSE = 0,
  BLADE_ACTIVATE_DRIVER = 1,
  BLADE_ACTIVATE_MERCENARY_TEAM = 2,
};

enum {
  GENDER_MALE = 1,
  GENDER_FEMALE = 2,
};

enum {
  QUEST_RACE_HUMAN = 1,
  QUEST_RACE_ANIMAL = 2,
};

struct SDataBlade {
  u16 activate;
  u16 creator;
  u16 setDriver;
  u16 id;
  u32 bornTime;
  u8 _00c[0x034 - 0x00c];
  u32 trustPoint;
  GfIdea trustRank;
  mm::mtl::FixedArray<SDataBladeArts, 3> arts;
  mm::mtl::FixedArray<SDataBladeArts, 3> nArts;
  u16 artsEx;
  u16 artsExH;
  u8 _088[0x090 - 0x088];
  u16 artsEx2;
  u16 artsEx2H;
  u8 _094[0x09c - 0x094];
  mm::mtl::FixedArray<SDataBladeSkill, 3> skills;
  mm::mtl::FixedArray<SDataBladeSkill, 3> fieldSkills;
  mm::mtl::FixedArray<u8, 4> extraParts;
  mm::mtl::FixedArray<SDataBladeAchievement, 3> artsAchievements;
  mm::mtl::FixedArray<SDataBladeAchievement, 3> skillAchievements;
  mm::mtl::FixedArray<SDataBladeAchievement, 3> fieldSkillAchievements;
  SDataBladeAchievement keyAchievement;
  u16 keyReleaseLevel;
  mm::mtl::FixedArray<SDataBladeFavorite, 2> favorites;
  u8 _676[0x678 - 0x676];
  mm::mtl::FixedArray<u16, 3> equipOrbs;
  mm::mtl::FixedArray<u32, 3> equipOrbHandles;
  EquipHana equipHana;
  u16 equipPowerRank;
  u16 openCircuit;
  u8 race;
  u8 gender;
  u16 iconData;
  mm::mtl::FixStr<16> resourceNameModel;
  mm::mtl::FixStr<16> resourceNameModel2;
  mm::mtl::FixStr<16> resourceNameMotion;
  mm::mtl::FixStr<16> resourceNameMotion2;
  mm::mtl::FixStr<16> resourceNameAddMotion;
  char voiceStr[0x7ac - 0x770];
  char resourceNameEffect[0x28];
  char centerBone[0x14];
  char camBone[0x14];
  char sePack[0x820 - 0x7fc];
  u8 size;
  u8 weaponType;
  u8 equipOrbMax;
  u8 attribute;
  u8 personality;
  u8 _825[0x826 - 0x825];
  u8 eyeRotControl;
  u8 _827[0x828 - 0x827];
  u16 coolTime;
  u16 condition;
  u16 weapon;
  u16 chestHeight;
  u16 landingHeight;
  u16 name;
  u16 nameListCategory;
  u16 scale;
  u16 wpnScale;
  u16 offsetID;
  u16 collisionId;
  u8 pArmor;
  u8 eArmor;
  u8 hpMaxRev;
  u8 strengthRev;
  u8 powerEtherRev;
  u8 dexRev;
  u8 agilityRev;
  u8 luckRev;
  u8 questRace;
  u8 releaseLock;
  u8 footStep;
  u8 footStepEffect;
  u16 kizunaLinkSet;
  u16 normalTalk;
  u8 _84e[0x850 - 0x84e];
  u32 createEvent;
  u16 mountPoint;
  u16 mountObject;
  char customName[0x40];
  u32 customNameLength;
  u8 _89c[0x89e - 0x89c];
  u8 enableEngageRex;
  u8 attachedParty;
  u8 unselect;
  u8 kizunaringComplete;
  u8 _8a2[0x8a4 - 0x8a2];

  SDataBlade();
  SDataBlade &operator=(const SDataBlade &other);
};

static_assert(offsetof(SDataBlade, activate) == 0x000, "");
static_assert(offsetof(SDataBlade, creator) == 0x002, "");
static_assert(offsetof(SDataBlade, setDriver) == 0x004, "");
static_assert(offsetof(SDataBlade, id) == 0x006, "");
static_assert(offsetof(SDataBlade, bornTime) == 0x008, "");
static_assert(offsetof(SDataBlade, trustPoint) == 0x034, "");
static_assert(offsetof(SDataBlade, trustRank) == 0x038, "");
static_assert(offsetof(SDataBlade, arts) == 0x03c, "");
static_assert(offsetof(SDataBlade, nArts) == 0x060, "");
static_assert(offsetof(SDataBlade, artsEx) == 0x084, "");
static_assert(offsetof(SDataBlade, artsEx2) == 0x090, "");
static_assert(offsetof(SDataBlade, skills) == 0x09c, "");
static_assert(offsetof(SDataBlade, fieldSkills) == 0x0ae, "");
static_assert(offsetof(SDataBlade, extraParts) == 0x0c0, "");
static_assert(offsetof(SDataBlade, artsAchievements) == 0x0c4, "");
static_assert(offsetof(SDataBlade, skillAchievements) == 0x274, "");
static_assert(offsetof(SDataBlade, fieldSkillAchievements) == 0x424, "");
static_assert(offsetof(SDataBlade, keyAchievement) == 0x5d4, "");
static_assert(offsetof(SDataBlade, keyReleaseLevel) == 0x664, "");
static_assert(offsetof(SDataBlade, favorites) == 0x666, "");
static_assert(offsetof(SDataBlade, equipOrbs) == 0x678, "");
static_assert(offsetof(SDataBlade, equipOrbHandles) == 0x680, "");
static_assert(offsetof(SDataBlade, equipHana) == 0x68c, "");
static_assert(offsetof(SDataBlade, equipPowerRank) == 0x704, "");
static_assert(offsetof(SDataBlade, openCircuit) == 0x706, "");
static_assert(offsetof(SDataBlade, race) == 0x708, "");
static_assert(offsetof(SDataBlade, gender) == 0x709, "");
static_assert(offsetof(SDataBlade, iconData) == 0x70a, "");
static_assert(offsetof(SDataBlade, resourceNameModel) == 0x70c, "");
static_assert(offsetof(SDataBlade, resourceNameModel2) == 0x720, "");
static_assert(offsetof(SDataBlade, resourceNameMotion) == 0x734, "");
static_assert(offsetof(SDataBlade, resourceNameMotion2) == 0x748, "");
static_assert(offsetof(SDataBlade, resourceNameAddMotion) == 0x75c, "");
static_assert(offsetof(SDataBlade, voiceStr) == 0x770, "");
static_assert(offsetof(SDataBlade, resourceNameEffect) == 0x7ac, "");
static_assert(offsetof(SDataBlade, centerBone) == 0x7d4, "");
static_assert(offsetof(SDataBlade, camBone) == 0x7e8, "");
static_assert(offsetof(SDataBlade, sePack) == 0x7fc, "");
static_assert(offsetof(SDataBlade, size) == 0x820, "");
static_assert(offsetof(SDataBlade, weaponType) == 0x821, "");
static_assert(offsetof(SDataBlade, equipOrbMax) == 0x822, "");
static_assert(offsetof(SDataBlade, attribute) == 0x823, "");
static_assert(offsetof(SDataBlade, personality) == 0x824, "");
static_assert(offsetof(SDataBlade, eyeRotControl) == 0x826, "");
static_assert(offsetof(SDataBlade, coolTime) == 0x828, "");
static_assert(offsetof(SDataBlade, condition) == 0x82a, "");
static_assert(offsetof(SDataBlade, weapon) == 0x82c, "");
static_assert(offsetof(SDataBlade, chestHeight) == 0x82e, "");
static_assert(offsetof(SDataBlade, landingHeight) == 0x830, "");
static_assert(offsetof(SDataBlade, name) == 0x832, "");
static_assert(offsetof(SDataBlade, nameListCategory) == 0x834, "");
static_assert(offsetof(SDataBlade, scale) == 0x836, "");
static_assert(offsetof(SDataBlade, wpnScale) == 0x838, "");
static_assert(offsetof(SDataBlade, offsetID) == 0x83a, "");
static_assert(offsetof(SDataBlade, collisionId) == 0x83c, "");
static_assert(offsetof(SDataBlade, pArmor) == 0x83e, "");
static_assert(offsetof(SDataBlade, luckRev) == 0x845, "");
static_assert(offsetof(SDataBlade, questRace) == 0x846, "");
static_assert(offsetof(SDataBlade, releaseLock) == 0x847, "");
static_assert(offsetof(SDataBlade, footStep) == 0x848, "");
static_assert(offsetof(SDataBlade, footStepEffect) == 0x849, "");
static_assert(offsetof(SDataBlade, kizunaLinkSet) == 0x84a, "");
static_assert(offsetof(SDataBlade, normalTalk) == 0x84c, "");
static_assert(offsetof(SDataBlade, createEvent) == 0x850, "");
static_assert(offsetof(SDataBlade, mountPoint) == 0x854, "");
static_assert(offsetof(SDataBlade, mountObject) == 0x856, "");
static_assert(offsetof(SDataBlade, customName) == 0x858, "");
static_assert(offsetof(SDataBlade, customNameLength) == 0x898, "");
static_assert(offsetof(SDataBlade, enableEngageRex) == 0x89e, "");
static_assert(offsetof(SDataBlade, attachedParty) == 0x89f, "");
static_assert(offsetof(SDataBlade, unselect) == 0x8a0, "");
static_assert(offsetof(SDataBlade, kizunaringComplete) == 0x8a1, "");
static_assert(sizeof(SDataBlade) == 0x8a4, "");

class GfDataBlade {
public:
  static void setCreator(u32 blade, u32 creator);
  static u32 getCreator(u32 blade);
  static void setActivateDriver(u32 bladeId, int slot, u32 driverId, u32 option);
  static SDataBlade *getSDataBlade(u32 blade);
  static u32 getBladeID(u32 index);
  static u32 getBladeWpnType(u32 blade);
  static bool isDisableHomuraHikari(u32 blade);
  static bool isHikariCurrent();
  static bool isEnableEngageRex(u32 blade);
  static void setEnableEngageRex(u32 blade, bool enableEngageRex);
  static u32 getBLD_NameList(u32 blade);
  static bool isCommonBlade(u32 blade);
  static u32 getCrownPoint(u32 blade);
  static bool isRegularBlade(u32 blade);
  static bool isRareBlade(u32 blade);
  static u32 getKizunaringMax(u32 blade);
  static u32 getBornTime(u32 blade);
  static u8 getEyeRotControl(u32 blade);
  static void setHikariCurrent(bool hikariCurrent);
  static bool isActivateParty(u32 blade);
  static bool isHomuriNameHikari();
  static void setHomuriNameHikari(bool homuriNameHikari);
  static u16 makeNormalTalkByPersonality(u32 personality);
  static u32 getBladeRelativeID(u32 blade);
  static const char *getName(u32 blade, u32 textId);
  static bool getNameWithMsgID(u8 *&bdat, u32 &textId, u32 blade);
  static const char *getName(const SDataBlade &dataBlade, u32 textId);
  static bool getNameWithMsgID(u8 *&bdat, u32 &textId, const SDataBlade &dataBlade);
  static bool getName(u8 *&bdat, u32 &textId, u32 blade);
  static const char *getCommonBladeName(u32 nameList);
  static bool getCommonBladeName(u8 *&bdat, u32 &textId, u32 nameList);
  static u32 getFavorite(u32 blade, FAVORITE favorite);
  static u32 getAchievementQuestPrefix(u32 blade, u32 line, u32 level);
  static SDataBladeAchievement *getAchievInfo(u32 blade, u32 line);
  static bool isValid(u32 blade);
  static bool isActivateDriver(u32 blade);
  static u32 getSetDriver(u32 blade);
  static bool isDummyBlade(u32 blade);
  static bool isUnselect(u32 blade);
  static void getListParty(mm::mtl::FixedVector<u16, 422> &blades);
  static void getListReserver(mm::mtl::FixedVector<u16, 422> &reservers);
  static bool isActivateUnuse(u32 blade);
  static bool isActivateMercenaryTeam(u32 blade);
  static bool isAttachedParty(u32 blade);
  static void getListForFieldSkill(mm::mtl::FixedVector<u16, 422> &blades);
  static u32 getStartBlade();
  static u32 getEndBlade();
  static u32 getStartRareBlade();
  static u32 getStartCommonBlade();
  static u32 getEndCommonBlade();
  static ActivateType getBladeActivateType(u32 blade);
  static ActivateType getBladeActivateType(const SDataBlade &dataBlade);
  static bool isBattleMember(u32 blade);
  static void setKizunaringComplete(u32 blade);
  static bool isKizunaringComplete(u32 blade);
  static bool getExtraParts(u32 blade, u32 index);
  static bool getExtraParts(const SDataBlade &dataBlade, u32 index);
  static u32 getLinkChNum(u32 blade);
  static void setUnselect(u32 blade, bool unselect);
  static bool isReleasedRareBlade(u32 blade);
  static void resetAttachedParty(u32 blade);
  static bool setActivateReserver(u32 blade);
  static bool isActivateReserver(u32 blade);
  static void setActivateMercenaryTeam(u32 blade);
  static u32 getEndRareBlade();
  static u32 addRareBlade(const SDataBlade &dataBlade);
  static u32 addCommonBlade(const SDataBlade &dataBlade);
  static u32 getStartUiCommonBlade();
  static u32 getEndUiCommonBlade();
  static u32 getStartActCommonBlade();
  static u32 getEndActCommonBlade();
  static bool isSetBlade(u32 blade);
  static u32 getBladeWeaponWithChip(u32 blade, u32 chip);
  static u16 getBladeWeapon(u32 blade);
  static u32 getBladeWeaponByRank(u32 blade, u32 chip);
  static const char *getResourceNameModel(u32 blade);
  static const char *getResourceNameMotion(u32 blade);
  static const char *getResourceNameAddMotion(u32 blade);
  static const char *getDebugName(u32 blade);
  static u8 getRace(u32 blade);
  static u8 getGender(u32 blade);
  static u32 getQuestRace(u32 blade);
  static bool isOperable(u32 blade);
  static bool isAnimal(u32 blade);
  static bool isMale(u32 blade);
  static bool isFemale(u32 blade);
  static bool getNameWithFieldSkillForDebug(mm::mtl::FixStr<128> &name, u32 blade);
  static u16 getKeyReleaseLevel(u32 blade);
  static void setAchievReleaseLevel(u32 blade, u32 line, u32 level);
  static u8 getAttribute(u32 blade);
  static const char *getDeathBlowWeaponName(u32 blade);
  static u32 getRealBladeId(u32 blade);
  static u32 getBladePower(SDataBlade &dataBlade);
  static u32 getBladePower(u32 blade);
  static f32 getWpnScale(u32 blade);
  static f32 getScale(u32 blade);
  static u32 getOffsetID(u32 blade);
  static u16 getMountPoint(u32 blade);
  static u16 getMountObject(u32 blade);
  static u8 getSize(u32 blade);
  static u16 getCollisionId(u32 blade);
  static u32 getRoleByWpnType(u32 weaponType);
  static u32 getRole(u32 blade);
  static u32 getEquipOrbMax(u32 blade);
  static u16 getEquipOrb(u32 blade, u32 slot);
  static GfItemHandle getEquipOrbHandle(u32 blade, u32 slot);
  static bool getEquipOrb(mm::mtl::FixedArray<u16, 3> &equipOrbs, u32 blade);
  static bool getEquipOrbHandle(mm::mtl::FixedArray<u32, 3> &equipOrbHandles, u32 blade);
  static void setEquipOrb(u32 blade, u16 orb, u32 slot);
  static void setEquipOrbHandle(u32 blade, GfItemHandle handle, u32 slot);
  static bool isEquipOrbFull(u32 blade);
  static bool getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, u32 blade);
  static bool getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, SDataBlade &dataBlade);
  static u32 getBladeWeaponRank(u32 blade);
  static void setBladeWeapon(u32 blade, u32 weapon);
  static void setAttributeForDebug(u32 blade, u8 attribute);
  static SDataBladeArts *getArts(u32 blade, u32 slot);
  static SDataBladeArts *getNArts(u32 blade, u32 slot);
  static u32 getArtsEnhance(u32 blade, u32 slot);
  static SDataBladeSkill *getSkill(u32 blade, u32 slot);
  static u32 getCreateEvent(u32 blade);
  static u16 getNormalTalk(u32 blade);
  static u32 getActBlade2CommonBlade(u32 blade);
  static bool isNeedAttributeResource(u32 blade);
  static u32 getTrustPoint(u32 blade);
  static GfIdea getTrustRank(u32 blade);
  static void setTrustPoint(u32 blade, u32 trustPoint);
  static void setTrustRank(u32 blade, GfIdea trustRank);
  static u32 getParmor(u32 blade);
  static u32 getEarmor(u32 blade);
  static u32 getHpMaxRev(u32 blade);
  static u32 getStrengthRev(u32 blade);
  static u32 getPowerEtherRev(u32 blade);
  static u32 getDexRev(u32 blade);
  static u32 getAgilityRev(u32 blade);
  static u32 getLuckRev(u32 blade);
  static void getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, SDataBlade &dataBlade, bool isVirtual);
  static u32 getBookedItemInfo(u32 blade);
  static bool isUsedFavorite(u32 blade, FAVORITE favorite);
  static u32 getFootStep(u32 blade);
  static u32 getFootStepEffect(u32 blade);
  static bool isBladeID(u32 blade);
  static bool isReleaseLock(u32 blade);
  static bool getMercenaryName(u8 *&bdat, u32 &textId, u32 blade);
  static u8 getPersonality(u32 blade);
  static u32 getVoiceID(u32 blade);
  static const char *getVoiceStr(u32 blade);
  static const char *getSePack(u32 blade);
  static u32 getBladeNum();
  static u32 getBladeNumForMale();
  static u32 getBladeNumForFemale();
  static u32 getBladeNumForAnimal();
  static u32 getBladeNumForWeapon(u32 weaponType);
  static bool isNeedChangeWeapon(u32 blade);
};

} // namespace gf
