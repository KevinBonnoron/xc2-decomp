#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_idea.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

// Layout from the constructor (0x71003011a4), clear (0x71003017c0), setupSDataBlade (0x7100301fd4) and the accessors (0x7100301e80-0x7100301fd4). The object is a blade being created: its
// sub-objects mirror those of SDataBlade (setupSDataBlade copies them one by one, the unnamed helper 0x7100303c54 fills them from an existing SDataBlade). Size 0xa54, aligned to 8: 0xa58.
// setupAddBooster (0x7100301ec4) shows a FixedVector<u32, 128> of boosters at 0x08 and an SDataIdea at 0x210.
class GfBladeCreateInfo {
public:
  // Defined inline: the game has only the base-object symbol _ZN2gf17GfBladeCreateInfoC2Ev, emitted right after the GfBladeCreate constructor that calls it (0x71003011a4), as an inline function is.
  GfBladeCreateInfo() : unknown210(), unknown338() { clear(); }
  void clear();
  bool getBladeName(u8 *&bdat, u32 &textId) const;

  static const u32 BOOSTER_UNKNOWN_128 = 128; // Inferred role: booster max; original name unknown.

  u32 unknown00;                                            // Inferred role: driver; original member name unknown.
  u32 unknown04;                                            // Inferred role: core crystal; original member name unknown.
  mm::mtl::FixedVector<u32, BOOSTER_UNKNOWN_128> unknown08; // Inferred role: boosters; original member name unknown.
  SDataIdea unknown210;                                     // Inferred role: idea levels added by the boosters; original member name unknown.
  u32 unknown230;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown234;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown238;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown23c;                                           // Inferred role: rare list entry passed to GfBdatBlade::getBladeListStatusID by the helper 0x7100303c54; original member name unknown.
  int unknown240;                                           // Inferred role: unknown; original member name unknown.
  bool unknown244;                                          // Inferred role: rare result; original member name unknown.
  mm::mtl::FixedVector<u32, 2> unknown248;                  // Inferred role: unknown, cleared by clear (count at 0x250); original member name unknown.
  mm::mtl::FixedVector<u32, 2> unknown258;                  // Inferred role: picked ids, pushed by createBladeNewVersion (capacity 2, count at 0x260); original member name unknown.
  u32 unknown268;                                           // Inferred role: quest race, from SDataBlade 0x846; original member name unknown.
  u32 unknown26c;                                           // Inferred role: gender, from SDataBlade 0x709; original member name unknown.
  u32 unknown270;                                           // Inferred role: weapon type, to SDataBlade 0x821; original member name unknown.
  u32 unknown274;                                           // Inferred role: weapon, to SDataBlade 0x82c; original member name unknown.
  u32 unknown278;                                           // Inferred role: attribute, to SDataBlade 0x823; original member name unknown.
  u32 unknown27c;                                           // Inferred role: blade name text id, read by getBladeName (1.0.0: 0x71003027f4); original member name unknown.
  mm::mtl::FixStr<64> unknown280;                           // Inferred role: blade name; original member name unknown.
  mm::mtl::FixStr<16> unknown2c4;                           // Inferred role: resource name model, to SDataBlade 0x70c; original member name unknown.
  mm::mtl::FixStr<16> unknown2d8;                           // Inferred role: resource name motion, to SDataBlade 0x734; original member name unknown.
  mm::mtl::FixStr<32> unknown2ec;                           // Inferred role: se pack, to SDataBlade 0x7fc; original member name unknown.
  mm::mtl::FixStr<16> unknown310;                           // Inferred role: voice str, to SDataBlade 0x770; original member name unknown.
  mm::mtl::FixedArray<u8, 4> unknown324;                    // Inferred role: extra parts, to SDataBlade 0xc0; original member name unknown.
  u32 unknown328;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown32c;                                           // Inferred role: driver blade name text id, tested by getBladeName for a rare result (1.0.0: 0x710030280c); original member name unknown.
  u32 unknown330;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown334;                                           // Inferred role: icon data, to SDataBlade 0x70a; original member name unknown.
  SDataIdea unknown338;                                     // Inferred role: idea of the blade, to SDataBlade 0x0c; original member name unknown.
  u32 unknown358;                                           // Inferred role: personality, to SDataBlade 0x824; original member name unknown.
  u32 unknown35c;                                           // Inferred role: equip orb max, to SDataBlade 0x822; original member name unknown.
  u32 unknown360;                                           // Inferred role: kizuna link set, to SDataBlade 0x84a; original member name unknown.
  unknown108 unknown364;                                    // Inferred role: arts ex, to SDataBlade 0x84; original member name unknown.
  u32 unknown370;                                           // Inferred role: unknown; original member name unknown.
  u32 unknown374;                                           // Inferred role: hp max rev, to SDataBlade 0x840; original member name unknown.
  u32 unknown378;                                           // Inferred role: strength rev, to SDataBlade 0x841; original member name unknown.
  u32 unknown37c;                                           // Inferred role: power ether rev, to SDataBlade 0x842; original member name unknown.
  u32 unknown380;                                           // Inferred role: dex rev, to SDataBlade 0x843; original member name unknown.
  u32 unknown384;                                           // Inferred role: agility rev, to SDataBlade 0x844; original member name unknown.
  u32 unknown388;                                           // Inferred role: luck rev, to SDataBlade 0x845; original member name unknown.
  u32 unknown38c;                                           // Inferred role: p armor, to SDataBlade 0x83e; original member name unknown.
  u32 unknown390;                                           // Inferred role: e armor, to SDataBlade 0x83f; original member name unknown.
  mm::mtl::FixedArray<unknown108, 3> unknown394;            // Inferred role: arts, to SDataBlade 0x3c; original member name unknown.
  mm::mtl::FixedArray<unknown108, 3> unknown3b8;            // Inferred role: n arts, to SDataBlade 0x60; original member name unknown.
  mm::mtl::FixedArray<unknown109, 3> unknown3dc;            // Inferred role: skills, to SDataBlade 0x9c; original member name unknown.
  mm::mtl::FixedArray<unknown110, 3> unknown3ee;            // Inferred role: field skills, to SDataBlade 0xae; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown400; // Inferred role: arts achievements, to SDataBlade 0xc4; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown5b0; // Inferred role: skill achievements, to SDataBlade 0x274; original member name unknown.
  mm::mtl::FixedArray<SDataBladeAchievement, 3> unknown760; // Inferred role: field skill achievements, to SDataBlade 0x424; original member name unknown.
  SDataBladeAchievement m_achievInfo;                       // Inferred role: key achievement, to SDataBlade 0x5d4; original member name unknown.
  mm::mtl::FixedArray<unknown112, 2> unknown9a0;            // Inferred role: favorites, to SDataBlade 0x666; original member name unknown.
  mm::mtl::FixedVector<u16, 64> unknown9b0;                 // Inferred role: unknown, cleared by clear (count at 0xa30); original member name unknown.
  u16 unknowna38;                                           // Inferred role: unknown; original member name unknown.
  bool unknowna3a;                                          // Inferred role: result valid; original member name unknown.
  bool unknowna3b;                                          // Inferred role: unknown; original member name unknown.
  u32 unknowna3c;                                           // Inferred role: crystal kind; original member name unknown.
  u32 unknowna40;                                           // Inferred role: idea category; original member name unknown.
  u32 unknowna44;                                           // Inferred role: rare list entry; original member name unknown.
  u32 unknowna48;                                           // Inferred role: unknown; original member name unknown.
  int unknowna4c;                                           // Inferred role: rare blade of the result; original member name unknown.
  u32 unknowna50;                                           // Inferred role: power 0-15, written by the helper 0x7100304434 from the CmnBl_Power table; original member name unknown.
};

static_assert(offsetof(GfBladeCreateInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfBladeCreateInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfBladeCreateInfo, unknown210) == 0x210, "");
static_assert(offsetof(GfBladeCreateInfo, unknown230) == 0x230, "");
static_assert(offsetof(GfBladeCreateInfo, unknown240) == 0x240, "");
static_assert(offsetof(GfBladeCreateInfo, unknown244) == 0x244, "");
static_assert(offsetof(GfBladeCreateInfo, unknown248) == 0x248, "");
static_assert(offsetof(GfBladeCreateInfo, unknown258) == 0x258, "");
static_assert(offsetof(GfBladeCreateInfo, unknown268) == 0x268, "");
static_assert(offsetof(GfBladeCreateInfo, unknown27c) == 0x27c, "");
static_assert(offsetof(GfBladeCreateInfo, unknown280) == 0x280, "");
static_assert(offsetof(GfBladeCreateInfo, unknown2c4) == 0x2c4, "");
static_assert(offsetof(GfBladeCreateInfo, unknown2d8) == 0x2d8, "");
static_assert(offsetof(GfBladeCreateInfo, unknown2ec) == 0x2ec, "");
static_assert(offsetof(GfBladeCreateInfo, unknown310) == 0x310, "");
static_assert(offsetof(GfBladeCreateInfo, unknown324) == 0x324, "");
static_assert(offsetof(GfBladeCreateInfo, unknown32c) == 0x32c, "");
static_assert(offsetof(GfBladeCreateInfo, unknown338) == 0x338, "");
static_assert(offsetof(GfBladeCreateInfo, unknown358) == 0x358, "");
static_assert(offsetof(GfBladeCreateInfo, unknown364) == 0x364, "");
static_assert(offsetof(GfBladeCreateInfo, unknown370) == 0x370, "");
static_assert(offsetof(GfBladeCreateInfo, unknown374) == 0x374, "");
static_assert(offsetof(GfBladeCreateInfo, unknown394) == 0x394, "");
static_assert(offsetof(GfBladeCreateInfo, unknown3b8) == 0x3b8, "");
static_assert(offsetof(GfBladeCreateInfo, unknown3dc) == 0x3dc, "");
static_assert(offsetof(GfBladeCreateInfo, unknown3ee) == 0x3ee, "");
static_assert(offsetof(GfBladeCreateInfo, unknown400) == 0x400, "");
static_assert(offsetof(GfBladeCreateInfo, unknown5b0) == 0x5b0, "");
static_assert(offsetof(GfBladeCreateInfo, unknown760) == 0x760, "");
static_assert(offsetof(GfBladeCreateInfo, m_achievInfo) == 0x910, "");
static_assert(offsetof(GfBladeCreateInfo, unknown9a0) == 0x9a0, "");
static_assert(offsetof(GfBladeCreateInfo, unknown9b0) == 0x9b0, "");
static_assert(offsetof(GfBladeCreateInfo, unknowna38) == 0xa38, "");
static_assert(offsetof(GfBladeCreateInfo, unknowna3a) == 0xa3a, "");
static_assert(offsetof(GfBladeCreateInfo, unknowna4c) == 0xa4c, "");
static_assert(sizeof(GfBladeCreateInfo) == 0xa58, "");

// GfBladeCreateInfo is a base class: the game's GfBladeCreate constructor (0x71003011a0) is a tail call to the base-object constructor _ZN2gf17GfBladeCreateInfoC2Ev.
class GfBladeCreate : public GfBladeCreateInfo {
public:
  GfBladeCreate();
  void clear();
  void setupDriver(u32 driver);
  bool setupCoreCrystal(u32 crystal);
  void setupAddBooster(u32 booster);
  bool isEnableAddBlade() const;
  bool createBladeNewVersion();
  bool isResultRare() const;
  bool getResultBlade(SDataBlade &blade) const;
  static void setupSDataBlade(SDataBlade &blade, const GfBladeCreateInfo &info);
};

} // namespace gf
