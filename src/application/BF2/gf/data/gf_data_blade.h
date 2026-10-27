#pragma once
#include <stddef.h>

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_item_handle.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

constexpr u32 BLADE_ID_FIRST = 1001;
constexpr u32 BLADE_COUNT = 422;
constexpr int TRUST_RANK_MAX = 6;
constexpr int FLAG_BLADE_HOMURI_NAME_HIKARI = 0x89fb;

enum GfIdea {};

struct SDataBladeArts {
  u16 unknown00; // Inferred role: id; original member name unknown.
  u16 unknown02; // Inferred role: arts h; original member name unknown.
  u8 _04[0x06 - 0x04];
  u8 unknown06; // Inferred role: achiev release level; original member name unknown.
  u8 unknown07; // Inferred role: level; original member name unknown.
  u8 unknown08; // Inferred role: level max; original member name unknown.
  u8 _09[0x0c - 0x09];
};

static_assert(offsetof(SDataBladeArts, unknown02) == 0x02, "");
static_assert(offsetof(SDataBladeArts, unknown06) == 0x06, "");
static_assert(offsetof(SDataBladeArts, unknown07) == 0x07, "");
static_assert(offsetof(SDataBladeArts, unknown08) == 0x08, "");
static_assert(sizeof(SDataBladeArts) == 0x0c, "");

struct SDataBladeSkill {
  u16 unknown00; // Inferred role: id; original member name unknown.
  u8 unknown02;  // Inferred role: achiev release level; original member name unknown.
  u8 unknown03;  // Inferred role: level; original member name unknown.
  u8 unknown04;  // Inferred role: level max; original member name unknown.
  u8 _05[0x06 - 0x05];
};

static_assert(offsetof(SDataBladeSkill, unknown02) == 0x02, "");
static_assert(offsetof(SDataBladeSkill, unknown03) == 0x03, "");
static_assert(offsetof(SDataBladeSkill, unknown04) == 0x04, "");
static_assert(sizeof(SDataBladeSkill) == 0x06, "");

struct AchievInfo {
  u16 unknown00; // Inferred role: achievement; original member name unknown.
  u8 _002[0x004 - 0x002];
  AchievQuest unknown04[5]; // Inferred role: quests; original member name unknown.
};

static_assert(offsetof(AchievInfo, unknown04) == 0x004, "");

static_assert(sizeof(AchievInfo) == 0x090, "");

typedef AchievInfo SDataBladeAchievement;

struct SDataBladeFavorite {
  u16 unknown00; // Inferred role: category; original member name unknown.
  u16 unknown02; // Inferred role: item; original member name unknown.
  u16 unknown04; // Inferred role: used category; original member name unknown.
  u16 unknown06; // Inferred role: used item; original member name unknown.
};

static_assert(offsetof(SDataBladeFavorite, unknown02) == 0x02, "");
static_assert(offsetof(SDataBladeFavorite, unknown04) == 0x04, "");
static_assert(offsetof(SDataBladeFavorite, unknown06) == 0x06, "");
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

constexpr u32 PERSONALITY_VOICE_FIRST = 61;

struct SDataBlade {
  u16 unknown00;       // Inferred role: activate; original member name unknown.
  u16 unknown02;       // Inferred role: creator; original member name unknown.
  u16 unknown04;       // Inferred role: set driver; original member name unknown.
  u16 unknown06;       // Inferred role: id; original member name unknown.
  u32 unknown08;       // Inferred role: born time; original member name unknown.
  SDataIdea unknown0c; // Inferred role: idea; original member name unknown.
  u8 _02c[0x034 - 0x02c];
  u32 unknown34;                                    // Inferred role: trust point; original member name unknown.
  GfIdea unknown38;                                 // Inferred role: trust rank; original member name unknown.
  mm::mtl::FixedArray<SDataBladeArts, 3> unknown3c; // Inferred role: arts; original member name unknown.
  mm::mtl::FixedArray<SDataBladeArts, 3> unknown60; // Inferred role: n arts; original member name unknown.
  u16 unknown84;                                    // Inferred role: arts ex; original member name unknown.
  u16 unknown86;                                    // Inferred role: arts ex h; original member name unknown.
  u8 _088[0x090 - 0x088];
  u16 unknown90; // Inferred role: arts ex2; original member name unknown.
  u16 unknown92; // Inferred role: arts ex2 h; original member name unknown.
  u8 _094[0x09c - 0x094];
  mm::mtl::FixedArray<SDataBladeSkill, 3> unknown9c;        // Inferred role: skills; original member name unknown.
  mm::mtl::FixedArray<SDataBladeSkill, 3> unknownae;        // Inferred role: field skills; original member name unknown.
  mm::mtl::FixedArray<u8, 4> unknownc0;                     // Inferred role: extra parts; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknownc4;  // Inferred role: arts achievements; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown274; // Inferred role: skill achievements; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown424; // Inferred role: field skill achievements; original member name unknown.
  SDataBladeAchievement unknown5d4;                         // Inferred role: key achievement; original member name unknown.
  u16 unknown664;                                           // Inferred role: key release level; original member name unknown.
  mm::mtl::FixedArray<SDataBladeFavorite, 2> unknown666;    // Inferred role: favorites; original member name unknown.
  u8 _676[0x678 - 0x676];
  mm::mtl::FixedArray<u16, 3> unknown678; // Inferred role: equip orbs; original member name unknown.
  mm::mtl::FixedArray<u32, 3> unknown680; // Inferred role: equip orb handles; original member name unknown.
  EquipHana unknown68c;                   // Inferred role: equip hana; original member name unknown.
  u16 unknown704;                         // Inferred role: equip power rank; original member name unknown.
  u16 unknown706;                         // Inferred role: open circuit; original member name unknown.
  u8 unknown708;                          // Inferred role: race; original member name unknown.
  u8 unknown709;                          // Inferred role: gender; original member name unknown.
  u16 unknown70a;                         // Inferred role: icon data; original member name unknown.
  mm::mtl::FixStr<16> unknown70c;         // Inferred role: resource name model; original member name unknown.
  mm::mtl::FixStr<16> unknown720;         // Inferred role: resource name model2; original member name unknown.
  mm::mtl::FixStr<16> unknown734;         // Inferred role: resource name motion; original member name unknown.
  mm::mtl::FixStr<16> unknown748;         // Inferred role: resource name motion2; original member name unknown.
  mm::mtl::FixStr<16> unknown75c;         // Inferred role: resource name add motion; original member name unknown.
  char unknown770[0x7ac - 0x770];         // Inferred role: voice str; original member name unknown.
  char unknown7ac[0x28];                  // Inferred role: resource name effect; original member name unknown.
  char unknown7d4[0x14];                  // Inferred role: center bone; original member name unknown.
  char unknown7e8[0x14];                  // Inferred role: cam bone; original member name unknown.
  char unknown7fc[0x820 - 0x7fc];         // Inferred role: se pack; original member name unknown.
  u8 unknown820;                          // Inferred role: size; original member name unknown.
  u8 unknown821;                          // Inferred role: weapon type; original member name unknown.
  u8 unknown822;                          // Inferred role: equip orb max; original member name unknown.
  u8 unknown823;                          // Inferred role: attribute; original member name unknown.
  u8 unknown824;                          // Inferred role: personality; original member name unknown.
  u8 _825[0x826 - 0x825];
  u8 unknown826; // Inferred role: eye rot control; original member name unknown.
  u8 _827[0x828 - 0x827];
  u16 unknown828; // Inferred role: cool time; original member name unknown.
  u16 unknown82a; // Inferred role: condition; original member name unknown.
  u16 unknown82c; // Inferred role: weapon; original member name unknown.
  u16 unknown82e; // Inferred role: chest height; original member name unknown.
  u16 unknown830; // Inferred role: landing height; original member name unknown.
  u16 unknown832; // Inferred role: name; original member name unknown.
  u16 unknown834; // Inferred role: name list category; original member name unknown.
  u16 unknown836; // Inferred role: scale; original member name unknown.
  u16 unknown838; // Inferred role: wpn scale; original member name unknown.
  u16 unknown83a; // Inferred role: offset id; original member name unknown.
  u16 unknown83c; // Inferred role: collision id; original member name unknown.
  u8 unknown83e;  // Inferred role: p armor; original member name unknown.
  u8 unknown83f;  // Inferred role: e armor; original member name unknown.
  u8 unknown840;  // Inferred role: hp max rev; original member name unknown.
  u8 unknown841;  // Inferred role: strength rev; original member name unknown.
  u8 unknown842;  // Inferred role: power ether rev; original member name unknown.
  u8 unknown843;  // Inferred role: dex rev; original member name unknown.
  u8 unknown844;  // Inferred role: agility rev; original member name unknown.
  u8 unknown845;  // Inferred role: luck rev; original member name unknown.
  u8 unknown846;  // Inferred role: quest race; original member name unknown.
  u8 unknown847;  // Inferred role: release lock; original member name unknown.
  u8 unknown848;  // Inferred role: foot step; original member name unknown.
  u8 unknown849;  // Inferred role: foot step effect; original member name unknown.
  u16 unknown84a; // Inferred role: kizuna link set; original member name unknown.
  u16 unknown84c; // Inferred role: normal talk; original member name unknown.
  u8 _84e[0x850 - 0x84e];
  u32 unknown850;        // Inferred role: create event; original member name unknown.
  u16 unknown854;        // Inferred role: mount point; original member name unknown.
  u16 unknown856;        // Inferred role: mount object; original member name unknown.
  char unknown858[0x40]; // Inferred role: custom name; original member name unknown.
  u32 unknown898;        // Inferred role: custom name length; original member name unknown.
  u8 _89c[0x89e - 0x89c];
  u8 unknown89e; // Inferred role: enable engage rex; original member name unknown.
  u8 unknown89f; // Inferred role: attached party; original member name unknown.
  u8 unknown8a0; // Inferred role: unselect; original member name unknown.
  u8 unknown8a1; // Inferred role: kizunaring complete; original member name unknown.
  u8 _8a2[0x8a4 - 0x8a2];

  SDataBlade();
  SDataBlade &operator=(const SDataBlade &other);
};

static_assert(offsetof(SDataBlade, unknown00) == 0x000, "");
static_assert(offsetof(SDataBlade, unknown02) == 0x002, "");
static_assert(offsetof(SDataBlade, unknown04) == 0x004, "");
static_assert(offsetof(SDataBlade, unknown06) == 0x006, "");
static_assert(offsetof(SDataBlade, unknown08) == 0x008, "");
static_assert(offsetof(SDataBlade, unknown34) == 0x034, "");
static_assert(offsetof(SDataBlade, unknown38) == 0x038, "");
static_assert(offsetof(SDataBlade, unknown3c) == 0x03c, "");
static_assert(offsetof(SDataBlade, unknown60) == 0x060, "");
static_assert(offsetof(SDataBlade, unknown84) == 0x084, "");
static_assert(offsetof(SDataBlade, unknown90) == 0x090, "");
static_assert(offsetof(SDataBlade, unknown9c) == 0x09c, "");
static_assert(offsetof(SDataBlade, unknownae) == 0x0ae, "");
static_assert(offsetof(SDataBlade, unknownc0) == 0x0c0, "");
static_assert(offsetof(SDataBlade, unknownc4) == 0x0c4, "");
static_assert(offsetof(SDataBlade, unknown274) == 0x274, "");
static_assert(offsetof(SDataBlade, unknown424) == 0x424, "");
static_assert(offsetof(SDataBlade, unknown5d4) == 0x5d4, "");
static_assert(offsetof(SDataBlade, unknown664) == 0x664, "");
static_assert(offsetof(SDataBlade, unknown666) == 0x666, "");
static_assert(offsetof(SDataBlade, unknown678) == 0x678, "");
static_assert(offsetof(SDataBlade, unknown680) == 0x680, "");
static_assert(offsetof(SDataBlade, unknown68c) == 0x68c, "");
static_assert(offsetof(SDataBlade, unknown704) == 0x704, "");
static_assert(offsetof(SDataBlade, unknown706) == 0x706, "");
static_assert(offsetof(SDataBlade, unknown708) == 0x708, "");
static_assert(offsetof(SDataBlade, unknown709) == 0x709, "");
static_assert(offsetof(SDataBlade, unknown70a) == 0x70a, "");
static_assert(offsetof(SDataBlade, unknown70c) == 0x70c, "");
static_assert(offsetof(SDataBlade, unknown720) == 0x720, "");
static_assert(offsetof(SDataBlade, unknown734) == 0x734, "");
static_assert(offsetof(SDataBlade, unknown748) == 0x748, "");
static_assert(offsetof(SDataBlade, unknown75c) == 0x75c, "");
static_assert(offsetof(SDataBlade, unknown770) == 0x770, "");
static_assert(offsetof(SDataBlade, unknown7ac) == 0x7ac, "");
static_assert(offsetof(SDataBlade, unknown7d4) == 0x7d4, "");
static_assert(offsetof(SDataBlade, unknown7e8) == 0x7e8, "");
static_assert(offsetof(SDataBlade, unknown7fc) == 0x7fc, "");
static_assert(offsetof(SDataBlade, unknown820) == 0x820, "");
static_assert(offsetof(SDataBlade, unknown821) == 0x821, "");
static_assert(offsetof(SDataBlade, unknown822) == 0x822, "");
static_assert(offsetof(SDataBlade, unknown823) == 0x823, "");
static_assert(offsetof(SDataBlade, unknown824) == 0x824, "");
static_assert(offsetof(SDataBlade, unknown826) == 0x826, "");
static_assert(offsetof(SDataBlade, unknown828) == 0x828, "");
static_assert(offsetof(SDataBlade, unknown82a) == 0x82a, "");
static_assert(offsetof(SDataBlade, unknown82c) == 0x82c, "");
static_assert(offsetof(SDataBlade, unknown82e) == 0x82e, "");
static_assert(offsetof(SDataBlade, unknown830) == 0x830, "");
static_assert(offsetof(SDataBlade, unknown832) == 0x832, "");
static_assert(offsetof(SDataBlade, unknown834) == 0x834, "");
static_assert(offsetof(SDataBlade, unknown836) == 0x836, "");
static_assert(offsetof(SDataBlade, unknown838) == 0x838, "");
static_assert(offsetof(SDataBlade, unknown83a) == 0x83a, "");
static_assert(offsetof(SDataBlade, unknown83c) == 0x83c, "");
static_assert(offsetof(SDataBlade, unknown83e) == 0x83e, "");
static_assert(offsetof(SDataBlade, unknown845) == 0x845, "");
static_assert(offsetof(SDataBlade, unknown846) == 0x846, "");
static_assert(offsetof(SDataBlade, unknown847) == 0x847, "");
static_assert(offsetof(SDataBlade, unknown848) == 0x848, "");
static_assert(offsetof(SDataBlade, unknown849) == 0x849, "");
static_assert(offsetof(SDataBlade, unknown84a) == 0x84a, "");
static_assert(offsetof(SDataBlade, unknown84c) == 0x84c, "");
static_assert(offsetof(SDataBlade, unknown850) == 0x850, "");
static_assert(offsetof(SDataBlade, unknown854) == 0x854, "");
static_assert(offsetof(SDataBlade, unknown856) == 0x856, "");
static_assert(offsetof(SDataBlade, unknown858) == 0x858, "");
static_assert(offsetof(SDataBlade, unknown898) == 0x898, "");
static_assert(offsetof(SDataBlade, unknown89e) == 0x89e, "");
static_assert(offsetof(SDataBlade, unknown89f) == 0x89f, "");
static_assert(offsetof(SDataBlade, unknown8a0) == 0x8a0, "");
static_assert(offsetof(SDataBlade, unknown8a1) == 0x8a1, "");
static_assert(sizeof(SDataBlade) == 0x8a4, "");

class GfDataBlade {
public:
  static void setCreator(u32 blade, u32 creator);
  static u32 getCreator(u32 blade);
  static void setActivateDriver(u32 bladeId, int slot, u32 driverId, u32 option);
  static SDataBlade *getSDataBlade(u32 blade);
  static SDataIdea *getSDataIdea(u32 blade);
  static void setUiCommonBlade(const SDataBlade &dataBlade, u32 blade);
  static void setActCommonBlade(const SDataBlade &dataBlade, u32 blade);
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
  static void setupAchievQuest(AchievQuest &achievQuest);
  static u32 getKizunaringCompleteNum(u32 blade);
  static SDataBladeAchievement *getAchievInfo(u32 blade, u32 line);
  static bool isValid(u32 blade);
  static bool isActivateDriver(u32 blade);
  static u32 getSetDriver(u32 blade);
  static bool isDummyBlade(u32 blade);
  static bool isUnselect(u32 blade);
  static bool getListParty(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListRegular(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListRare(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListPartyAll(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListReserverAndUnuse(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListReserver(mm::mtl::FixedVector<u16, 422> &reservers);
  static bool getListUnuse(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListLeave(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getlistCommon(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListReserverWithSolo(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListUse(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListForAchievement(mm::mtl::FixedVector<u16, 422> &blades);
  static bool getListParty(mm::mtl::FixedVector<u16, 422> &blades, bool unknown001, bool unknown002);
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
  static bool setActivateUnuse(u32 blade);
  static bool setActivateReserver(u32 blade);
  static bool isActivateReserver(u32 blade);
  static bool setActivateMercenaryTeam(u32 blade);
  static u32 getEndRareBlade();
  static u32 addRareBlade(const SDataBlade &dataBlade);
  static u32 addCommonBlade(const SDataBlade &dataBlade);
  static u32 getStartUiCommonBlade();
  static u32 getEndUiCommonBlade();
  static u32 getStartActCommonBlade();
  static u32 getEndActCommonBlade();
  static bool isSetBlade(u32 blade);
  static u32 getBladeWeaponWithChip(u32 blade, u32 chip);
  static u32 getBladeWeapon(u32 blade);
  static u32 getBladeWeaponByRank(u32 blade, u32 chip);
  static const char *getResourceNameModel(u32 blade);
  static const char *getResourceNameMotion(u32 blade);
  static const char *getResourceNameAddMotion(u32 blade);
  static const char *getDebugName(u32 blade);
  static u8 getRace(u32 blade);
  static u8 getGender(u32 blade);
  static u32 getQuestRace(u32 blade);
  static bool getCommonBladeName(const char *model);
  static bool isOperable(u32 blade);
  static bool isAnimal(u32 blade);
  static bool isMale(u32 blade);
  static bool isFemale(u32 blade);
  static bool getNameWithFieldSkillForDebug(mm::mtl::FixStr<128> &name, u32 blade);
  static u16 getKeyReleaseLevel(u32 blade);
  static u32 getSkillLineId(u32 blade, u32 line);
  static bool setAchievReleaseLevel(u32 blade, u32 line, u32 level);
  static bool getTaskSkillMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line);
  static bool getTaskTitleMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level);
  static bool getTaskResultMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level);
  static bool isCompleteAchievement(u32 blade);
  static u32 getAchievementID(u32 blade, u32 line, u32 level);
  static const char *getBaseEabWeaponName(u32 blade);
  static const char *getBaseEfbWeaponName(u32 blade);
  static const char *getBaseEfbAttributeName(u32 blade, u32 attribute);
  static u8 getAttribute(u32 blade);
  static bool isMatchIdeaAttribute(u32 blade, u32 idea);
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
