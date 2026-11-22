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

constexpr u32 BLADE_ID_UNKNOWN_1001 = 1001; // Inferred role: blade id first; original name unknown.
constexpr u32 BLADE_UNKNOWN_422 = 422;      // Inferred role: blade count; original name unknown.
constexpr int RANK_UNKNOWN_6 = 6;           // Inferred role: trust rank max; original name unknown.
constexpr int FLAG_UNKNOWN_35323 = 0x89fb;  // Inferred role: flag blade homuri name hikari; original name unknown.

enum GfIdea {};

struct SDataGame;

// Inferred role: save data blade arts; original type name unknown.
struct unknown108 {
  // Evidence: GfBladeCreateInfo::GfBladeCreateInfo (0x71003011a4) stores the six arts entries of its two arrays and its arts ex entry this way (strh 0, strh 100, strh 0, strh 0, strb 1, strh 0).
  unknown108() {
    unknown00 = 0;
    unknown02 = 100;
    unknown06 = 0;
    m_bladeArtsLevel = 0;
    unknown08 = 1;
    unknown04 = 0;
    unknown0a = 0;
  }

  u16 unknown00;       // Inferred role: id; original member name unknown.
  u16 unknown02;       // Inferred role: arts h; original member name unknown.
  u16 unknown04;       // Inferred role: zeroed by the constructor; original member name unknown.
  u8 unknown06;        // Inferred role: achiev release level; original member name unknown.
  u8 m_bladeArtsLevel; // Inferred role: level; named after the game accessor gf::DataObjBlade::getBladeArtsLevel.
  u8 unknown08;        // Inferred role: level max; original member name unknown.
  u8 _09[0x0a - 0x09];
  u16 unknown0a; // Inferred role: zeroed by the constructor; original member name unknown.
};

static_assert(offsetof(unknown108, unknown02) == 0x02, "");
static_assert(offsetof(unknown108, unknown06) == 0x06, "");
static_assert(offsetof(unknown108, m_bladeArtsLevel) == 0x07, "");
static_assert(offsetof(unknown108, unknown08) == 0x08, "");
static_assert(sizeof(unknown108) == 0x0c, "");

// Inferred role: save data blade skill; original type name unknown.
struct unknown109 {
  // Evidence: GfBladeCreateInfo::GfBladeCreateInfo (0x71003011a4) and SDataBlade::SDataBlade (0x7100145060) construct the first three of their six skill entries (SDataBlade 0x9c, GfBladeCreateInfo
  // 0x3dc) without storing the padding byte after the level max (no store at 0x3e1, 0x3e7, 0x3ed), unlike the last three (unknown110).
  unknown109() : unknown00(0), unknown02(0), unknown03(0), unknown04(1) {}

  u16 unknown00; // Inferred role: id; original member name unknown.
  u8 unknown02;  // Inferred role: achiev release level; original member name unknown.
  u8 unknown03;  // Inferred role: level; original member name unknown.
  u8 unknown04;  // Inferred role: level max; original member name unknown. The padding byte after it is no member (the 2-byte alignment gives the size 6): the game copies a skill entry as 5 bytes,
                 // `ldrb w10, [x8, #0x4]; strb w10, [x9, #0x3e0]; ldr w8, [x8]; str w8, [x9, #0x3dc]` at 0x7100305f84-0x7100305f94 (inside the common blade roll 0x7100304434),
                 // the data size of a class with a constructor. A hand-written padding member (`u8 _05[1]`) makes it `ldrh` + `strh` (6 bytes).
};

static_assert(offsetof(unknown109, unknown02) == 0x02, "");
static_assert(offsetof(unknown109, unknown03) == 0x03, "");
static_assert(offsetof(unknown109, unknown04) == 0x04, "");
static_assert(sizeof(unknown109) == 0x06, "");

// Inferred role: save data blade field skill; original type name unknown.
struct unknown110 {
  // Evidence: GfObjPropertyBlade::GfObjPropertyBlade builds three of them (0x71005aade8-0x71005aae10) and assigns them again (0x71005aae9c-0x71005aaebc); GfBladeCreateInfo::GfBladeCreateInfo
  // (0x71003011a4) stores the padding byte of its last three skill entries (0x3f3, 0x3f9, 0x3ff).
  unknown110() : m_fieldSkill(0), unknown02(0), m_fieldSkillLevel(0), unknown04(1), unknown05(0) {}

  u16 m_fieldSkill;     // Inferred role: id; named after the game accessor gf::DataObjBlade::getFieldSkill.
  u8 unknown02;         // Inferred role: achiev release level; original member name unknown.
  u8 m_fieldSkillLevel; // Inferred role: level; named after the game accessor gf::DataObjBlade::getFieldSkillLevel.
  u8 unknown04;         // Inferred role: level max; original member name unknown.
  u8 unknown05;         // Inferred role: zeroed by the constructor; original member name unknown.
};

static_assert(offsetof(unknown110, unknown02) == 0x02, "");
static_assert(offsetof(unknown110, m_fieldSkillLevel) == 0x03, "");
static_assert(offsetof(unknown110, unknown04) == 0x04, "");
static_assert(sizeof(unknown110) == 0x06, "");

struct AchievInfo {
  // Evidence: GfBladeCreateInfo::GfBladeCreateInfo (0x71003011a4) zeroes the achievement of each of its ten entries (0x400, 0x490...) and not the padding after it.
  AchievInfo() : unknown00(0) {}

  u16 unknown00;                // Inferred role: achievement; original member name unknown. The two padding bytes after it are no member: the game copies and zeroes the entry without them
                                // (GfBladeCreate::setupSDataBlade, 0x7100301fd4).
  AchievQuest m_achievQuest[5]; // Inferred role: quests; original member name unknown.
};

static_assert(offsetof(AchievInfo, m_achievQuest) == 0x004, "");

static_assert(sizeof(AchievInfo) == 0x090, "");

typedef AchievInfo SDataBladeAchievement;

// Inferred role: save data blade favorite; original type name unknown.
struct unknown112 {
  // Evidence: GfBladeCreateInfo::GfBladeCreateInfo (0x71003011a4) zeroes the 16 bytes of its two favorites (0x9a0-0x9b0).
  unknown112() : unknown00(0), unknown02(0), unknown04(0), unknown06(0) {}

  u16 unknown00; // Inferred role: category; original member name unknown.
  u16 unknown02; // Inferred role: item; original member name unknown.
  u16 unknown04; // Inferred role: used category; original member name unknown.
  u16 unknown06; // Inferred role: used item; original member name unknown.
};

static_assert(offsetof(unknown112, unknown02) == 0x02, "");
static_assert(offsetof(unknown112, unknown04) == 0x04, "");
static_assert(offsetof(unknown112, unknown06) == 0x06, "");
static_assert(sizeof(unknown112) == 0x08, "");

enum {
  BLADE_ACTIVATE_UNKNOWN_0 = 0, // Inferred role: blade activate unuse; original name unknown.
  BLADE_ACTIVATE_UNKNOWN_1 = 1, // Inferred role: blade activate driver; original name unknown.
  BLADE_ACTIVATE_UNKNOWN_2 = 2, // Inferred role: blade activate mercenary team; original name unknown.
};

enum {
  GENDER_UNKNOWN_1 = 1, // Inferred role: gender male; original name unknown.
  GENDER_UNKNOWN_2 = 2, // Inferred role: gender female; original name unknown.
};

enum {
  QUEST_RACE_UNKNOWN_1 = 1, // Inferred role: quest race human; original name unknown.
  QUEST_RACE_UNKNOWN_2 = 2, // Inferred role: quest race animal; original name unknown.
};

constexpr u32 VOICE_UNKNOWN_61 = 61; // Inferred role: personality voice first; original name unknown.

struct SDataBlade {
  u16 m_dataType;         // Inferred role: activate; named after the game accessor gf::DataObjBlade::getDataType.
  u16 unknown02;          // Inferred role: creator; original member name unknown.
  u16 m_driverBySetBlade; // Inferred role: set driver; named after the game accessor gf::GfDataDriver::getDriverBySetBlade.
  u16 unknown06;          // Inferred role: id; original member name unknown.
  u32 unknown08;          // Inferred role: born time; original member name unknown.
  SDataIdea m_idea;       // Inferred role: idea; named after the game accessor gf::DataObjBlade::getIdea.
  u8 _02c[0x034 - 0x02c];
  u32 m_trustPoint;                             // Inferred role: trust point; named after the game accessor gf::GfDataBlade::getTrustPoint.
  GfIdea m_trustRank;                           // Inferred role: trust rank; named after the game accessor gf::GfDataBlade::getTrustRank.
  mm::mtl::FixedArray<unknown108, 3> unknown3c; // Inferred role: arts; original member name unknown.
  mm::mtl::FixedArray<unknown108, 3> unknown60; // Inferred role: n arts; original member name unknown.
  unknown108 unknown84; // Inferred role: arts ex (id in unknown00, h in unknown02); original member name unknown. Evidence: GfBladeCreate::setupSDataBlade copies 12 bytes at 0x84 from an unknown108
                        // of GfBladeCreateInfo.
  unknown108
      unknown90; // Inferred role: arts ex2 (id in unknown00, h in unknown02); original member name unknown. Evidence: SDataBlade::SDataBlade (0x7100145060) stores the unknown108 pattern at 0x90.
  mm::mtl::FixedArray<unknown109, 3> unknown9c;             // Inferred role: skills; original member name unknown.
  mm::mtl::FixedArray<unknown110, 3> unknownae;             // Inferred role: field skills; original member name unknown.
  mm::mtl::FixedArray<u8, 4> unknownc0;                     // Inferred role: extra parts; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknownc4;  // Inferred role: arts achievements; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown274; // Inferred role: skill achievements; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown424; // Inferred role: field skill achievements; original member name unknown.
  SDataBladeAchievement m_achievInfo;                       // Inferred role: key achievement; original member name unknown.
  u16 unknown664;                                           // Inferred role: key release level; original member name unknown.
  mm::mtl::FixedArray<unknown112, 2> unknown666;            // Inferred role: favorites; original member name unknown.
  u8 _676[0x678 - 0x676];
  mm::mtl::FixedArray<u16, 3> unknown678; // Inferred role: equip orbs; original member name unknown.
  mm::mtl::FixedArray<u32, 3> unknown680; // Inferred role: equip orb handles; original member name unknown.
  EquipHana m_equipParts;                 // Inferred role: equip hana; named after the game accessor gf::GfDataHana::getEquipParts.
  u16 m_equipPowerRank;                   // Inferred role: equip power rank; named after the game accessor gf::GfDataHana::getEquipPowerRank.
  u16 unknown706;                         // Inferred role: open circuit; original member name unknown.
  u8 m_race;                              // Inferred role: race; named after the game accessor gf::DataObjBlade::getRace.
  u8 m_gender;                            // Inferred role: gender; named after the game accessor gf::DataObjBlade::getGender.
  u16 m_iconData;                         // Inferred role: icon data; named after the game accessor gf::DataObjBlade::getIconData.
  mm::mtl::FixStr<16> unknown70c;         // Inferred role: resource name model; original member name unknown.
  mm::mtl::FixStr<16> unknown720;         // Inferred role: resource name model2; original member name unknown.
  mm::mtl::FixStr<16> unknown734;         // Inferred role: resource name motion; original member name unknown.
  mm::mtl::FixStr<16> unknown748;         // Inferred role: resource name motion2; original member name unknown.
  mm::mtl::FixStr<16> unknown75c;         // Inferred role: resource name add motion; original member name unknown.
  mm::mtl::FixStr<16> unknown770; // Inferred role: voice str; original member name unknown. Evidence: GfBladeCreate::setupSDataBlade (0x7100301fd4) assigns it from a FixStr<16> (length at 0x780,
                                  // assertion "m_nLen < LEN").
  u8 _784[0x7ac - 0x784];
  char m_effectResourceName[0x28]; // Inferred role: resource name effect; named after the game accessor gf::DataObjBlade::getEffectResourceName.
  char m_centerBone[0x14];         // Inferred role: center bone; named after the game accessor gf::DataObjBlade::getCenterBone.
  char m_camBone[0x14];            // Inferred role: cam bone; named after the game accessor gf::DataObjBlade::getCamBone.
  mm::mtl::FixStr<32> unknown7fc;  // Inferred role: se pack; original member name unknown. Evidence: GfBladeCreate::setupSDataBlade assigns it from a FixStr<32> (length at 0x81c).
  u8 unknown820;                   // Inferred role: size; original member name unknown.
  u8 m_weaponType;                 // Inferred role: weapon type; named after the game accessor gf::DataObjBlade::getWeaponType.
  u8 unknown822;                   // Inferred role: equip orb max; original member name unknown.
  u8 unknown823;                   // Inferred role: attribute; original member name unknown.
  u8 m_personality;                // Inferred role: personality; named after the game accessor gf::GfDataBlade::getPersonality.
  u8 _825[0x826 - 0x825];
  u8 m_eyeRotControl; // Inferred role: eye rot control; named after the game accessor gf::DataObjBlade::getEyeRotControl.
  u8 _827[0x828 - 0x827];
  u16 m_coolTime;      // Inferred role: cool time; named after the game accessor gf::DataObjBlade::getCoolTime.
  u16 unknown82a;      // Inferred role: condition; original member name unknown.
  u16 m_equipWeapon;   // Inferred role: weapon; named after the game accessor gf::DataObjBlade::getEquipWeapon.
  u16 m_chestHeight;   // Inferred role: chest height; named after the game accessor gf::DataObjBlade::getChestHeight.
  u16 m_landingHeight; // Inferred role: landing height; named after the game accessor gf::DataObjBlade::getLandingHeight.
  u16 unknown832;      // Inferred role: name; original member name unknown.
  u16 unknown834;      // Inferred role: name list category; original member name unknown.
  u16 unknown836;      // Inferred role: scale; original member name unknown.
  u16 unknown838;      // Inferred role: wpn scale; original member name unknown.
  u16 unknown83a;      // Inferred role: offset id; original member name unknown.
  u16 unknown83c;      // Inferred role: collision id; original member name unknown.
  u8 unknown83e;       // Inferred role: p armor; original member name unknown.
  u8 unknown83f;       // Inferred role: e armor; original member name unknown.
  u8 unknown840;       // Inferred role: hp max rev; original member name unknown.
  u8 unknown841;       // Inferred role: strength rev; original member name unknown.
  u8 unknown842;       // Inferred role: power ether rev; original member name unknown.
  u8 unknown843;       // Inferred role: dex rev; original member name unknown.
  u8 unknown844;       // Inferred role: agility rev; original member name unknown.
  u8 unknown845;       // Inferred role: luck rev; original member name unknown.
  u8 unknown846;       // Inferred role: quest race; original member name unknown.
  u8 unknown847;       // Inferred role: release lock; original member name unknown.
  u8 m_footStep;       // Inferred role: foot step; named after the game accessor gf::GfDataBlade::getFootStep.
  u8 m_footStepEffect; // Inferred role: foot step effect; named after the game accessor gf::GfDataBlade::getFootStepEffect.
  u16 unknown84a;      // Inferred role: kizuna link set; original member name unknown.
  u16 m_normalTalk;    // Inferred role: normal talk; named after the game accessor gf::GfDataBlade::getNormalTalk.
  u8 _84e[0x850 - 0x84e];
  u32 m_createEvent;              // Inferred role: create event; named after the game accessor gf::GfDataBlade::getCreateEvent.
  u16 unknown854;                 // Inferred role: mount point; original member name unknown.
  u16 unknown856;                 // Inferred role: mount object; original member name unknown.
  mm::mtl::FixStr<64> unknown858; // Inferred role: custom name; original member name unknown. Evidence: GfBladeCreate::setupSDataBlade assigns it from a C string (length at 0x898, assertions "pszName
                                  // != 0" and "m_nLen < LEN").
  u8 _89c[0x89e - 0x89c];
  u8 unknown89e;           // Inferred role: enable engage rex; original member name unknown.
  u8 unknown89f;           // Inferred role: attached party; original member name unknown.
  u8 unknown8a0;           // Inferred role: unselect; original member name unknown.
  u8 m_kizunaringComplete; // Inferred role: kizunaring complete; named after the game accessor gf::GfDataBlade::setKizunaringComplete.
  u8 _8a2[0x8a4 - 0x8a2];

  SDataBlade();
  SDataBlade &operator=(const SDataBlade &other);
};

static_assert(offsetof(SDataBlade, m_dataType) == 0x000, "");
static_assert(offsetof(SDataBlade, unknown02) == 0x002, "");
static_assert(offsetof(SDataBlade, m_driverBySetBlade) == 0x004, "");
static_assert(offsetof(SDataBlade, unknown06) == 0x006, "");
static_assert(offsetof(SDataBlade, unknown08) == 0x008, "");
static_assert(offsetof(SDataBlade, m_trustPoint) == 0x034, "");
static_assert(offsetof(SDataBlade, m_trustRank) == 0x038, "");
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
static_assert(offsetof(SDataBlade, m_achievInfo) == 0x5d4, "");
static_assert(offsetof(SDataBlade, unknown664) == 0x664, "");
static_assert(offsetof(SDataBlade, unknown666) == 0x666, "");
static_assert(offsetof(SDataBlade, unknown678) == 0x678, "");
static_assert(offsetof(SDataBlade, unknown680) == 0x680, "");
static_assert(offsetof(SDataBlade, m_equipParts) == 0x68c, "");
static_assert(offsetof(SDataBlade, m_equipPowerRank) == 0x704, "");
static_assert(offsetof(SDataBlade, unknown706) == 0x706, "");
static_assert(offsetof(SDataBlade, m_race) == 0x708, "");
static_assert(offsetof(SDataBlade, m_gender) == 0x709, "");
static_assert(offsetof(SDataBlade, m_iconData) == 0x70a, "");
static_assert(offsetof(SDataBlade, unknown70c) == 0x70c, "");
static_assert(offsetof(SDataBlade, unknown720) == 0x720, "");
static_assert(offsetof(SDataBlade, unknown734) == 0x734, "");
static_assert(offsetof(SDataBlade, unknown748) == 0x748, "");
static_assert(offsetof(SDataBlade, unknown75c) == 0x75c, "");
static_assert(offsetof(SDataBlade, unknown770) == 0x770, "");
static_assert(offsetof(SDataBlade, m_effectResourceName) == 0x7ac, "");
static_assert(offsetof(SDataBlade, m_centerBone) == 0x7d4, "");
static_assert(offsetof(SDataBlade, m_camBone) == 0x7e8, "");
static_assert(offsetof(SDataBlade, unknown7fc) == 0x7fc, "");
static_assert(offsetof(SDataBlade, unknown820) == 0x820, "");
static_assert(offsetof(SDataBlade, m_weaponType) == 0x821, "");
static_assert(offsetof(SDataBlade, unknown822) == 0x822, "");
static_assert(offsetof(SDataBlade, unknown823) == 0x823, "");
static_assert(offsetof(SDataBlade, m_personality) == 0x824, "");
static_assert(offsetof(SDataBlade, m_eyeRotControl) == 0x826, "");
static_assert(offsetof(SDataBlade, m_coolTime) == 0x828, "");
static_assert(offsetof(SDataBlade, unknown82a) == 0x82a, "");
static_assert(offsetof(SDataBlade, m_equipWeapon) == 0x82c, "");
static_assert(offsetof(SDataBlade, m_chestHeight) == 0x82e, "");
static_assert(offsetof(SDataBlade, m_landingHeight) == 0x830, "");
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
static_assert(offsetof(SDataBlade, m_footStep) == 0x848, "");
static_assert(offsetof(SDataBlade, m_footStepEffect) == 0x849, "");
static_assert(offsetof(SDataBlade, unknown84a) == 0x84a, "");
static_assert(offsetof(SDataBlade, m_normalTalk) == 0x84c, "");
static_assert(offsetof(SDataBlade, m_createEvent) == 0x850, "");
static_assert(offsetof(SDataBlade, unknown854) == 0x854, "");
static_assert(offsetof(SDataBlade, unknown856) == 0x856, "");
static_assert(offsetof(SDataBlade, unknown858) == 0x858, "");
static_assert(offsetof(SDataBlade, unknown89e) == 0x89e, "");
static_assert(offsetof(SDataBlade, unknown89f) == 0x89f, "");
static_assert(offsetof(SDataBlade, unknown8a0) == 0x8a0, "");
static_assert(offsetof(SDataBlade, m_kizunaringComplete) == 0x8a1, "");
static_assert(sizeof(SDataBlade) == 0x8a4, "");

class GfDataBlade {
public:
  static void setCreator(u32 blade, u32 creator);
  static u32 getCreator(u32 blade);
  static void setUsedFavoriteItemForPouch(u32 blade, u32 item);
  static u32 getMenuCastName(u32 blade);
  static u32 getMenuIlustName(u32 blade);
  static const char *getMenuVoiceName(u32 blade, u32 index);
  static bool setActivateDriver(u32 bladeId, int slot, u32 driverId, u32 option);
  static SDataBlade &getSDataBlade(u32 blade);
  static void initSaveData(SDataGame &dataGame);
  static void setupSDataBlade(SDataBlade &dataBlade, u32 blade, bool unknown001);
  static void setupSDataBladeAchievement(SDataBlade &dataBlade, bool unknown001);
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
  static int getDriverSetID(u32 blade);
  static const char *getCommonBladeName(u32 nameList);
  static bool getCommonBladeName(u8 *&bdat, u32 &textId, u32 nameList);
  static u32 getFavorite(u32 blade, FAVORITE favorite);
  static bool isFavoriteItem(u32 blade, u32 item);
  static bool isFavoriteCategory(u32 blade, u32 item);
  static bool getPouchEnhanceFavorite(mm::mtl::FixedVector<EnhanceFavorite, 64> &favorites, u32 blade);
  static const char *getFieldSkillVoice(u32 blade, u32 skill);
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
  static void removeSameBlade(mm::mtl::FixedVector<u16, 422> &blades);
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
  static bool getListForFieldSkill(mm::mtl::FixedVector<u16, 422> &blades);
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
  static u32 addCommonBladeWithPos(const SDataBlade &dataBlade, u32 pos);
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
  static bool getBladeAddAnim(mm::mtl::FixStr<128> &animName, u32 blade, u32 weaponType);
  static const char *getDebugName(u32 blade);
  static u32 getRace(u32 blade);
  static u32 getGender(u32 blade);
  static u32 getQuestRace(u32 blade);
  static bool getCommonBladeName(const char *model);
  static bool isOperable(u32 blade);
  static bool isAnimal(u32 blade);
  static bool isMale(u32 blade);
  static bool isFemale(u32 blade);
  static bool getNameWithFieldSkillForDebug(mm::mtl::FixStr<128> &name, u32 blade);
  static u32 getKeyReleaseLevel(u32 blade);
  static u32 getSkillLineId(u32 blade, u32 line);
  static const char *getSkillLineName(u32 blade, u32 line);
  static u32 getSkillLineLevel(u32 blade, u32 line);
  static u32 getSkillLineLevelMax(u32 blade, u32 line);
  static void setSkillLineLevel(u32 blade, u32 line, u32 level);
  static void setSkillLevel(u32 blade, u32 line, u32 level);
  static bool setAchievReleaseLevel(u32 blade, u32 line, u32 level);
  // Return type inferred: GfKizunaringBlade::releaseAchievement compares the result with the level unsigned (cmp w0, w20; b.hs at 0x7100363c48).
  static u32 getAchievReleaseLevel(u32 blade, u32 line);
  // Return type inferred: GfBladeCreate::isEnableAddBlade (0x7100301f64) only tests w0 against zero.
  static u32 getEnableCountForCreateBlade();
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
  static bool setEquipOrb(u32 blade, u16 orb, u32 slot);
  static bool setEquipOrbHandle(u32 blade, GfItemHandle handle, u32 slot);
  static bool isEquipOrbFull(u32 blade);
  static bool getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, u32 blade);
  static bool getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, SDataBlade &dataBlade);
  static u32 getBladeWeaponRank(u32 blade);
  static void setBladeWeapon(u32 blade, u32 weapon);
  static void setAttributeForDebug(u32 blade, u8 attribute);
  static unknown108 *getArts(u32 blade, u32 slot);
  static unknown108 *getNArts(u32 blade, u32 slot);
  static u32 getArtsEnhance(u32 blade, u32 slot);
  static unknown109 *getSkill(u32 blade, u32 slot);
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
