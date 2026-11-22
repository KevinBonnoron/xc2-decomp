#include "gf/game/blade/gf_blade_manager.h"

#include <math.h>
#include <new>
#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_create.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/blade/gf_blade_create.h"
#include "gf/game/gf_game_cond.h"
#include "gf/gf_allocator.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_util.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

namespace _gfdbm {

u32 s_outofname = 1;

} // namespace _gfdbm

constexpr u32 RARE_BLADE_APPEAR_TYPE_UNKNOWN_5 = 5; // Inferred role: rare blade appear type count; original name unknown.

GfBladeManager::GfBladeManager(const GfSetupParam &param) {
  _gfdbm::s_outofname = 1;
  initialize(param);
}

void GfBladeManager::initialize(const GfSetupParam &) { unknown08 = true; }

GfBladeManager::~GfBladeManager() {}

void GfBladeManager::build(const GfSetupParam &param) {
  // __LINE__ must be 146 as in the original file: its value changes the instruction order.
#line 146
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBladeManager(param);
}

void GfBladeManager::destroy() {
  GfBladeManager *bladeManager = get();
  bladeManager->finalize();
  delete bladeManager;
}

void GfBladeManager::finalize() { unknown08 = false; }

bool GfBladeManager::isInitialized() {
  GfBladeManager *bladeManager = get();
  return bladeManager != nullptr ? bladeManager->unknown08 : false;
}

void GfBladeManager::setupGame() {
  if (GfDataBladeCreate::getRareBladeAppearType() != 0) {
    return;
  }

  GfDataBladeCreate::setRareBladeAppearType(ml::mtRand(RARE_BLADE_APPEAR_TYPE_UNKNOWN_5) + 1);
  GfDataBladeCreate::resetAssureCount();
}

int GfBladeManager::getRandom(u32 max) { return ml::mtRand(max); }

f32 GfBladeManager::getRandomF1() { return ml::mtRandf2(); }

bool GfBladeManager::isBindRareBladeCrystal(u32 item) {
  if (item == 0 || GfItemUtil::getType(item) != ItemType::ITEM_TYPE_UNKNOWN_11) {
    return false;
  }

  return GfBdatItem::get() != nullptr && GfBdatItem::get()->getCrystalListBladeID(item) != 0;
}

GfBladeCreate::GfBladeCreate() {}

void GfBladeCreateInfo::clear() {
  unknown00 = 0;
  unknown04 = 0;
  unknown08.clear();
  new (&unknown210) SDataIdea();
  unknown230 = 0;
  unknown234 = 0;
  unknown238 = 0;
  unknown23c = 0;
  unknown240 = -1;
  unknown244 = false;
  unknown248.clear();
  unknown258.clear();
  unknown268 = 1;
  unknown26c = 0;
  unknown270 = 0;
  unknown274 = 0;
  unknown278 = 0;
  unknown27c = 0;
  unknown280.clear();
  unknown2c4.clear();
  unknown2d8.clear();
  unknown2ec.clear();
  unknown310.clear();
  unknown324.assign(0);
  unknown328 = 0;
  unknown32c = 0;
  unknown330 = 1;
  unknown334 = 0;
  new (&unknown338) SDataIdea();
  unknown358 = 0;
  unknown35c = 0;
  unknown360 = 0;
  new (&unknown364) unknown108();
  unknown370 = 100;
  unknown374 = 0;
  unknown378 = 0;
  unknown37c = 0;
  unknown380 = 0;
  unknown384 = 0;
  unknown388 = 0;
  unknown38c = 0;
  unknown390 = 0;
  unknown394.assign(unknown108());
  unknown3b8.assign(unknown108());
  unknown3dc.assign(unknown109());
  unknown3ee.assign(unknown110());
  unknown400.assign(AchievInfo());
  unknown5b0.assign(AchievInfo());
  unknown760.assign(AchievInfo());
  m_achievInfo = AchievInfo();
  unknown9a0.assign(unknown112());
  unknown9b0.clear();
  unknowna38 = 0;
  unknowna3a = false;
  unknowna3b = false;
  unknowna3c = 0;
  unknowna40 = 0;
  unknowna44 = 0;
  unknowna48 = 0;
  unknowna4c = 0;
  unknowna50 = 0;
}

// The game compiles GfBladeCreate in this unit: its functions (0x71003011a0 to 0x7100303c54, with their unnamed helpers up to 0x7100306d74) follow
// GfBladeManager::isBindRareBladeCrystal (0x7100301148) and precede this unit's deferred PtrSingleton<GfBladeManager> destructors (0x7100306d74).
void GfBladeCreate::clear() { GfBladeCreateInfo::clear(); }

void GfBladeCreate::setupDriver(u32 driver) { unknown00 = driver; }

bool GfBladeCreate::setupCoreCrystal(u32 crystal) {
  if (!GfItemUtil::isValidCrystal(crystal)) {
    return false;
  }
  unknown04 = crystal;
  return true;
}

void GfBladeCreate::setupAddBooster(u32 booster) {
  unknown08.push_back(booster);
  int idea = GfBdatItem::get()->getBoosterIdea(booster);
  u32 category = GfBdatItem::get()->getBoosterCategory(booster);
  unknown210.setLevel(category, unknown210.unknown00[category].unknown04 + idea);
}

bool GfBladeCreate::isEnableAddBlade() const { return GfDataBlade::getEnableCountForCreateBlade() != 0; }

bool GfBladeCreate::isResultRare() const { return unknown244 || unknowna4c != 0; }

bool GfBladeCreate::getResultBlade(SDataBlade &blade) const {
  if (!unknowna3a) {
    return false;
  }
  setupSDataBlade(blade, *this);
  return true;
}

void GfBladeCreate::setupSDataBlade(SDataBlade &blade, const GfBladeCreateInfo &info) {
  if (!info.unknown244 && info.unknowna4c == 0) {
    GfDataBlade::setupSDataBlade(blade, info.unknown32c, false);
    blade.m_idea = info.unknown338;
    blade.m_personality = info.unknown358;
    blade.unknown770 = info.unknown310;
    blade.unknown84a = info.unknown360;
    blade.unknown83e = info.unknown38c;
    blade.unknown83f = info.unknown390;
    blade.unknown840 = info.unknown374;
    blade.unknown841 = info.unknown378;
    blade.unknown842 = info.unknown37c;
    blade.unknown843 = info.unknown380;
    blade.unknown844 = info.unknown384;
    blade.unknown845 = info.unknown388;
    blade.unknown823 = info.unknown278;
    blade.m_weaponType = info.unknown270;
    blade.m_equipWeapon = info.unknown274;
    blade.unknown70c = info.unknown2c4;
    blade.unknown720 = "";
    blade.unknown734 = info.unknown2d8;
    blade.unknown748 = "";
    blade.unknownc0 = info.unknown324;
    blade.unknown7fc = info.unknown2ec;
    if (info.unknown334 != 0) {
      blade.m_iconData = info.unknown334;
    }
    blade.unknown822 = info.unknown35c;
    blade.unknown858 = GfDataBlade::getName(blade, 0);
    blade.unknown834 = info.unknown27c;
    blade.unknown832 = 0;
    blade.unknown02 = info.unknown00;
    blade.unknown3c = info.unknown394;
    blade.unknown84 = info.unknown364;
    blade.unknown60 = info.unknown3b8;
    blade.unknown9c = info.unknown3dc;
    blade.unknownae = info.unknown3ee;
    blade.unknown666 = info.unknown9a0;
    blade.unknownc4 = info.unknown400;
    blade.unknown274 = info.unknown5b0;
    blade.unknown424 = info.unknown760;
    blade.m_achievInfo = info.m_achievInfo;
    blade.m_normalTalk = GfDataBlade::makeNormalTalkByPersonality(info.unknown358);
  } else {
    u32 target = info.unknown32c;
    if (target == 0) {
      target = info.unknowna4c;
    }
    if (!GfDataBlade::isAttachedParty(target)) {
      GfDataBlade::setupSDataBlade(blade, target, false);
    } else {
      blade = GfDataBlade::getSDataBlade(target);
    }
    blade.unknown02 = info.unknown00;
    blade.unknown89f = 1;
  }
}

bool GfBladeCreateInfo::getBladeName(u8 *&bdat, u32 &textId) const {
  if (unknown27c == 0) {
    return false;
  }
  if (!unknown244) {
    bdat = GfBdatMsg::getFpCommonBladeName();
  } else {
    if (unknown32c == 0) {
      return false;
    }
    bdat = GfBdatMsg::getFpChrDr();
  }
  textId = unknown27c;
  return true;
}

// Inferred role: the rare list blade 1022 stands for 1050 once 1050 is in the party; no game symbol (inlined at every use), original name unknown.
static u32 unknown005(u32 blade) {
  if (blade == BLADE_UNKNOWN_1022) {
    blade = GfDataBlade::isAttachedParty(BLADE_UNKNOWN_1050) ? BLADE_UNKNOWN_1050 : BLADE_UNKNOWN_1022;
  }
  return blade;
}

// Inferred role: fills the info from the result blade unknowna4c (0x7100303c54); original name unknown. The status id is written straight into `unknown32c`, tested there and overwritten from
// `unknowna4c` when 0: the game stores it twice (`str w0, [x19, #0x32c]` at 0x7100303c8c, `str w21, [x19, #0x32c]` at 0x7100303c98, P3). With a local holding the id the first store is
// dead and gone: 422 instructions against the game's 423.
static void unknown001(GfBladeCreateInfo &create) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  create.unknown244 = true;
  create.unknown32c = bdatBlade->getBladeListStatusID(create.unknown23c);
  if (create.unknown32c == 0) {
    create.unknown32c = create.unknowna4c;
  }
  u32 blade = create.unknown32c;
  SDataBlade &dataBlade = GfDataBlade::getSDataBlade(create.unknowna4c);
  u16 textId = dataBlade.unknown832;
  create.unknown27c = textId;
  create.unknown280 = GfDataBlade::getName(blade, textId);
  create.unknown268 = dataBlade.unknown846;
  create.unknown26c = dataBlade.m_gender;
  create.unknown270 = dataBlade.m_weaponType;
  create.unknown274 = dataBlade.m_equipWeapon;
  create.unknown278 = dataBlade.unknown823;
  create.unknown358 = dataBlade.m_personality;
  create.unknown334 = dataBlade.m_iconData;
  create.unknown374 = dataBlade.unknown840;
  create.unknown384 = dataBlade.unknown844;
  create.unknown380 = dataBlade.unknown843;
  create.unknown388 = dataBlade.unknown845;
  create.unknown37c = dataBlade.unknown842;
  create.unknown378 = dataBlade.unknown841;
  create.unknown38c = dataBlade.unknown83e;
  create.unknown390 = dataBlade.unknown83f;
  create.unknown35c = dataBlade.unknown822;
  create.unknown338 = dataBlade.m_idea;
  create.unknown394 = dataBlade.unknown3c;
  create.unknown364 = dataBlade.unknown84;
  create.unknown3dc = dataBlade.unknown9c;
  create.unknown3ee = dataBlade.unknownae;
  create.unknown9a0 = dataBlade.unknown666;
  create.unknown400 = dataBlade.unknownc4;
  create.unknown5b0 = dataBlade.unknown274;
  create.unknown760 = dataBlade.unknown424;
  create.m_achievInfo = dataBlade.m_achievInfo;
  GfDataBladeCreate::resetAssurePoint();
}

// Inferred role: collects the rare list entries the assure counter may hand out (0x71003042f0); original name unknown. `appearIndex` places the getRareBladeAppearType call before the two
// list bound calls (0x7100304310) and holds its result minus one for the whole loop: the game subtracts in the loop preheader (0x7100304348; P2). With the call result in a local and `- 1`
// at the use in the loop, the subtraction is hoisted ahead of the `m_size` address and GVN makes a phi of the two addresses: 83 instructions against the game's 81.
static bool unknown002(mm::mtl::FixedVector<u16, 64> &candidates) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  int appearIndex = GfDataBladeCreate::getRareBladeAppearType() - 1;
  u32 start = bdatBlade->getBLD_RareListStart();
  u32 end = bdatBlade->getBLD_RareListEnd();
  for (u32 i = start; i < end; i++) {
    u32 blade = bdatBlade->getBLD_RareListBlade(i);
    if (blade != 0) {
      blade = unknown005(blade);
      if (GfDataBlade::isActivateUnuse(blade)) {
        u32 condition = bdatBlade->getBLD_RareListCondition(i);
        if ((condition == 0 || GfGameCond::isGameCond(condition)) && !GfDataBlade::isAttachedParty(blade) && bdatBlade->getBLD_RareListAssure(i, appearIndex) != 0) {
          candidates.push_back(i);
        }
      }
    }
  }
  return !candidates.empty();
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Picks the idea category of the blade to create: the category of the first booster, else a random one of the driver's highest ideas (user: createBladeNewVersion,
// 0x7100302848). Forms tried without the helper, in createBladeNewVersion (the game has 1283 instructions): the body inline in a scope or bare, with the size of `ideas` in a local or
// the pick as one expression, with `ideas` declared after `item`: 1320 instructions for every form (the size of `ideas` is reloaded after each call: the vector has more than 20 uses of
// its size once crystalName.format has escaped, so GVN does not forward it). All five helpers of createBladeNewVersion inline: 1333.
static void selectIdeaCategory(GfBladeCreate &create) {
  mm::mtl::FixedVector<u32, 4> ideas;
  GfBdatItem *item = GfBdatItem::get();
  SDataIdea *driverIdea = GfDataDriver::getSDataIdea(create.unknown00);
  if (!create.unknown08.empty()) {
    ideas.push_back(item->getBoosterCategory(create.unknown08.front()));
  } else {
    int maxLevel = 0;
    for (u32 i = 0; i < SDataIdea::IDEA_UNKNOWN_4; i++) {
      if (driverIdea->unknown00[i].unknown04 > maxLevel) {
        maxLevel = driverIdea->unknown00[i].unknown04;
      }
    }
    for (u32 i = 0; i < SDataIdea::IDEA_UNKNOWN_4; i++) {
      if (driverIdea->unknown00[i].unknown04 == maxLevel) {
        ideas.push_back(i);
      }
    }
  }
  u32 ideaIndex = ml::mtRand(ideas.size());
  create.unknowna40 = ideas[ideaIndex];
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The rare roll of createBladeNewVersion (user: 0x7100302848): collects the available rare list entries, rolls the chance of each (rare table, crystal, luck, idea) and keeps one
// (matching the idea, then the lowest probability, then at random) in unknowna44. Forms tried without the helper, in createBladeNewVersion (the game has 1283 instructions): the body
// inline in a scope 1291, bare 1297, with `picked` declared before `candidates` 1274.
static void rollRareBlade(GfBladeCreate &create) {
  GfBdatItem *rareItem = GfBdatItem::get();
  GfBdatBlade *rareBdat = GfBdatBlade::get();
  u32 appearIndex = GfDataBladeCreate::getRareBladeAppearType() - 1;
  SDataIdea *idea = GfDataDriver::getSDataIdea(create.unknown00);
  int ideaLevel = idea->unknown00[create.unknowna40].unknown04;
  int boosters = create.unknown08.size();
  int ideaPoint = boosters + ideaLevel;
  mm::mtl::FixedVector<u16, 64> candidates;
  u32 start = rareBdat->getBLD_RareListStart();
  u32 end = rareBdat->getBLD_RareListEnd();
  for (u32 i = start; i < end; i++) {
    u32 blade = rareBdat->getBLD_RareListBlade(i);
    if (blade != 0 && GfDataBlade::isActivateUnuse(blade)) {
      u32 condition = rareBdat->getBLD_RareListCondition(i);
      if ((condition == 0 || GfGameCond::isGameCond(condition)) && !GfDataBlade::isUnselect(blade)) {
        blade = unknown005(blade);
        if (GfDataBlade::isActivateUnuse(blade) && !GfDataBlade::isUnselect(blade) && (!GfDataBlade::isAttachedParty(blade) || GfDataBlade::isReleasedRareBlade(blade))) {
          candidates.push_back(i);
        }
      }
    }
  }
  mm::mtl::FixedVector<u16, 64> picked;
  if (!candidates.empty()) {
    for (u32 j = 0; j < candidates.size(); j++) {
      u32 entry = candidates[j];
      unknown005(rareBdat->getBLD_RareListBlade(entry));
      f32 chance = rareBdat->getBLD_RareListProb(entry, appearIndex) * (rareItem->getCrystalListRareBladeRev(create.unknown04) * 0.01f);
      {
        DataParamAcc acc(3, create.unknown00, GimmickType());
        f32 luck = sqrtf(acc.getLuck(false)) * 0.01f * 1.3f + 0.95f;
        if (luck <= 1.0f) {
          luck = 1.0f;
        }
        chance *= luck;
      }
      if (GfDataBlade::isMatchIdeaAttribute(rareBdat->getBLD_RareListBlade(entry), create.unknowna40)) {
        chance *= rareBdat->getBLD_IdeaProbRev(ideaPoint) * 0.01f;
      }
      if (chance >= ml::mtRandf2() * 100.0f) {
        picked.push_back(entry);
      }
    }
    if (picked.size() > 1) {
      mm::mtl::FixedVector<u16, 64> matching;
      for (const u16 &entry : picked) {
        if (GfDataBlade::isMatchIdeaAttribute(unknown005(rareBdat->getBLD_RareListBlade(entry)), create.unknowna40)) {
          matching.push_back(entry);
        }
      }
      if (!matching.empty()) {
        picked = matching;
        for (const u16 &entry : matching) {
          unknown005(rareBdat->getBLD_RareListBlade(entry));
        }
      }
    }
    if (picked.size() > 1) {
      f32 lowest = 100.0f;
      for (const u16 &entry : picked) {
        f32 prob = rareBdat->getBLD_RareListProb(entry, appearIndex);
        if (!(prob > lowest)) {
          lowest = prob;
        }
      }
      mm::mtl::FixedVector<u16, 64> rarest;
      for (const u16 &entry : picked) {
        if (!(rareBdat->getBLD_RareListProb(entry, appearIndex) > lowest)) {
          rarest.push_back(entry);
        }
      }
      if (!rarest.empty()) {
        picked = rarest;
        for (const u16 &entry : rarest) {
          unknown005(rareBdat->getBLD_RareListBlade(entry));
        }
      }
    }
    if (picked.size() > 1) {
      u32 index = ml::mtRand(picked.size());
      u16 chosen = picked[index];
      picked.clear();
      picked.push_back(chosen);
    }
    if (!picked.empty()) {
      GfDataBladeCreate::resetAssurePoint();
      create.unknowna44 = picked[0];
    }
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The pity pick of createBladeNewVersion (user: 0x7100302848): one of the assure candidates, a roulette over their probabilities when there are several. Forms tried without
// the helper, in createBladeNewVersion (the game has 1283 instructions): the body inline in a scope, the empty pool tested last, 1288; with a `goto` over the empty pool 1296.
static void rollAssureBlade(GfBladeCreate &create) {
  GfBdatBlade *pickBdat = GfBdatBlade::get();
  mm::mtl::FixedVector<u16, 64> pool;
  unknown002(pool);
  if (pool.size() > 1) {
    int appearIndex = GfDataBladeCreate::getRareBladeAppearType() - 1;
    f32 total = 0.0f;
    mm::mtl::FixedVector<f32, 64> weights;
    for (const u16 &entry : pool) {
      f32 weight = pickBdat->getBLD_RareListProb(entry, appearIndex);
      weights.push_back(weight);
      total += weight;
    }
    f32 scale = 100.01f / total;
    for (f32 &weight : weights) {
      weight *= scale;
    }
    f32 roll = ml::mtRandf2() * 100.0f;
    int selected = -1;
    f32 sum = 0.0f;
    for (const f32 &weight : weights) {
      selected++;
      sum += weight;
      if (sum > roll) {
        break;
      }
    }
    u16 chosen = pool[selected];
    pool.clear();
    pool.push_back(chosen);
  } else if (pool.empty()) {
    return;
  }
  create.unknowna44 = pool[0];
  GfDataBladeCreate::resetAssureCount();
}

static void unknown003(GfBladeCreateInfo *info);

bool GfBladeCreate::createBladeNewVersion() {
  if (unknown04 == 0) {
    return false;
  }
  GfBdatItem *bdatItem = GfBdatItem::get();
  // The `crystalName` and `bladeName` buffers live in their own scope (without it: 1285 instructions against the game's 1283).
  {
    mm::mtl::FixStr<128> crystalName;
    crystalName.format("%s[%d]", util::debugUTF8ToSJIS(GfDataItem::getName(unknown04)), unknown04);
    if (bdatItem->getCrystalListBladeID(unknown04) == 0) {
      unknowna3c = bdatItem->getCrystalListCommonID(unknown04) != 0;
    } else {
      u32 blade = bdatItem->getCrystalListBladeID(unknown04);
      unknowna3c = 2;
      mm::mtl::FixStr<128> bladeName;
      bladeName = util::debugUTF8ToSJIS(GfDataBlade::getName(blade, 0));
      if (!GfDataBlade::isActivateUnuse(blade)) {
        return false;
      }
    }
  }
  GfBdatItem *crystal = GfBdatItem::get();
  if (unknowna3c == 2) {
    unknowna4c = unknown005(crystal->getCrystalListBladeID(unknown04));
    unknown001(*this);
  } else {
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    GfDataBladeCreate::getAssurePoint();
    GfDataBladeCreate::addAssurePoint(crystal->getCrystalListAssureP(unknown04));
    selectIdeaCategory(*this);
    u32 rareProb = crystal->getCrystalListRareTableProb(unknown04);
    if (rareProb > ml::mtRand(100) + 1) {
      rollRareBlade(*this);
      if (unknowna44 != 0) {
        unknowna4c = unknown005(bdatBlade->getBLD_RareListBlade(unknowna44));
        unknown001(*this);
      }
    }
    if (unknowna44 == 0) {
      u32 assurePoint = GfDataBladeCreate::getAssurePoint();
      u32 assureBase = bdatBlade->getCreateConfigValue(0x28);
      u32 assureStep = bdatBlade->getCreateConfigValue(0x29);
      u32 assureCount = GfDataBladeCreate::getAssureCount();
      // The pity candidates live in their own scope (kept outside it the function has the game's 1283 instructions but does not match).
      {
        mm::mtl::FixedVector<u16, 64> assured;
        if (unknown002(assured) && assurePoint >= assureBase + assureCount * assureStep) {
          GfDataBladeCreate::resetAssurePoint();
          GfDataBladeCreate::addAssureCount(1);
          for (const u16 &entry : assured) {
            unknown005(bdatBlade->getBLD_RareListBlade(entry));
          }
          rollAssureBlade(*this);
          if (unknowna44 != 0) {
            unknowna4c = unknown005(bdatBlade->getBLD_RareListBlade(unknowna44));
            unknown001(*this);
          }
        }
      }
      if (unknowna44 == 0) {
        unknown003(this);
      }
    }
    // Inferred role: create config rows of the common and the rare result; original names unknown.
    static const u16 unknown006[3] = {0x2b, 0x2c, 0x2d};
    static const u16 unknown007[3] = {0x2e, 0x2f, 0x2d};
    bool resultRare = unknown244;
    GfBdatBlade *configBdat = GfBdatBlade::get();
    u32 roll = ml::mtRand(100);
    const u16 *configs = resultRare ? unknown007 : unknown006;
    u32 sum = 0;
    u32 configIndex = 0;
    do {
      sum += configBdat->getCreateConfigValue(configs[configIndex]);
      configIndex++;
    } while (configIndex < 3 && sum < roll);
    mm::mtl::FixedVector<u16, 422> blades;
    // The two picks of the common blade pool (0x7100302848): a random rare list blade matching the chosen idea, then one that does not match it and is not in the party. Each pick is
    // scoped with its result in a local `u16`, pushed after the scope. Measured against the game's 1283 instructions: unscoped 1299; pushed into `blades` inside the scope 1283 with other
    // registers and slots.
    u16 matchingBlade = 0;
    {
      u32 idea = unknowna40;
      GfBdatBlade *listBdat = GfBdatBlade::get();
      mm::mtl::FixedVector<u16, 422> matching;
      u32 start = listBdat->getBLD_RareListStart();
      u32 end = listBdat->getBLD_RareListEnd();
      for (u32 i = start; i < end; i++) {
        u32 blade = unknown005(listBdat->getBLD_RareListBlade(i));
        if (GfDataBlade::isMatchIdeaAttribute(blade, idea) && GfDataBlade::getAttribute(blade) != 7) {
          u32 condition = listBdat->getBLD_RareListCondition(i);
          if ((condition == 0 || GfGameCond::isGameCond(condition)) && GfDataBlade::isActivateUnuse(blade) && !GfDataBlade::isUnselect(blade)) {
            matching.push_back(blade);
          }
        }
      }
      if (!matching.empty()) {
        u32 index = ml::mtRand(matching.size());
        matchingBlade = matching[index];
      }
    }
    if (matchingBlade) {
      blades.push_back(unknown005(matchingBlade));
    }
    u16 otherBlade = 0;
    {
      GfBdatBlade *listBdat = GfBdatBlade::get();
      u32 idea = unknowna40;
      mm::mtl::FixedVector<u16, 422> others;
      u32 start = listBdat->getBLD_RareListStart();
      u32 end = listBdat->getBLD_RareListEnd();
      for (u32 i = start; i < end; i++) {
        u32 blade = unknown005(listBdat->getBLD_RareListBlade(i));
        if (!GfDataBlade::isMatchIdeaAttribute(blade, idea) && GfDataBlade::getAttribute(blade) != 7) {
          u32 condition = listBdat->getBLD_RareListCondition(i);
          if ((condition == 0 || GfGameCond::isGameCond(condition)) && GfDataBlade::isActivateUnuse(blade) && !GfDataBlade::isAttachedParty(blade)) {
            others.push_back(blade);
          }
        }
      }
      if (!others.empty()) {
        u32 index = ml::mtRand(others.size());
        otherBlade = others[index];
      }
    }
    if (otherBlade) {
      blades.push_back(unknown005(otherBlade));
    }
    // `firstModel` and `lastModel` live in their own scope with the creation loop (without it: 1282 instructions against the game's 1283).
    {
      mm::mtl::FixStr<16> firstModel;
      mm::mtl::FixStr<16> lastModel;
      int created = 0;
      int status;
      do {
        GfBladeCreateInfo info;
        info.unknown00 = unknown00;
        info.unknowna3b = true;
        unknown003(&info);
        if (firstModel.length() != 0 && strcmp(firstModel.c_str(), info.unknown2c4.c_str()) == 0) {
          status = 4;
        } else {
          if (firstModel.length() == 0) {
            firstModel = info.unknown2c4;
          }
          lastModel = info.unknown2c4;
          SDataBlade dataBlade;
          setupSDataBlade(dataBlade, info);
          dataBlade.unknown832 = 0;
          if (info.unknown268 == 1 || info.unknown268 == 2) {
            if (info.unknown26c == 1) {
              dataBlade.unknown834 = bdatBlade->getNameListCategory(1);
            } else {
              dataBlade.unknown834 = bdatBlade->getNameListCategory(11);
            }
          }
          u32 uiBlade = GfDataBlade::getStartUiCommonBlade() + created;
          GfDataBlade::setUiCommonBlade(dataBlade, uiBlade);
          blades.push_back(uiBlade);
          created++;
          status = created > 1 ? 5 : 0;
        }
      } while (status != 5);
    }
    do {
      int index = ml::mtRand(blades.size());
      unknown258.push_back(blades[index]);
      for (u16 *it = blades.begin(); it != blades.end(); it++) {
        if (*it == blades[index]) {
          blades.erase(it);
          break;
        }
      }
      if (blades.empty()) {
        break;
      }
    } while (unknown258.size() != 2);
  }
  unknowna3a = true;
  SCOM_ACHIEV_INC::createBladeCreate();
  return false;
}

// Original name unknown. Inferred role: collect the ids of the achievement sets of a category that hold `count` achievements, until the vector is full.
// 0x7100306ba8, 115 instructions. The game keeps the cleanup destination of the loop body (4 = continue, 2 = break, 0 = fall through; leaving the loop is the
// `(x | 4) & 7 != 4` test, `orr w8, w27, #4; and w8, w8, #7; cmp w8, #4` at 0x7100306d34, with the destination 4 set at 0x7100306cdc and 2 at 0x7100306d2c). The block around the count
// scope is what keeps it (ruling 3: the evidence is this dispatch, not a stack slot): the `continue` of a count mismatch leaves a scope nested in the one of `setCategory`, so the
// destination has a second user (the dispatch of the outer scope) and clang narrows it as `trunc` of a wide PHI, which JumpThreading cannot see through (it only looks through casts of
// i1). Without the block, or with the push inside it, the dispatch is threaded away (110 instructions).
static void unknown004(mm::mtl::FixedVector<u16, 32> &sets, int category, u32 count) {
  QuestListAcc *acc = QuestListAcc::get();
  for (u32 set = acc->getFLD_AchievementSetStart(); set < acc->getFLD_AchievementSetEnd(); set++) {
    if (acc->getFLD_AchievementSetAchievementID1(set) == 0 && acc->getFLD_AchievementSetAchievementID2(set) == 0 && acc->getFLD_AchievementSetAchievementID3(set) == 0 &&
        acc->getFLD_AchievementSetAchievementID4(set) == 0 && acc->getFLD_AchievementSetAchievementID5(set) == 0) {
      continue;
    }
    u32 setCategory = acc->getFLD_AchievementSetCategory(set);
    if (setCategory == 0 || setCategory != category) {
      continue;
    }
    {
      u32 num = 0;
      for (u32 i = 0; i < 5; i++) {
        if (acc->getFLD_AchievementSetAchievementID(set, i) != 0) {
          num++;
        }
      }
      if (num != count) {
        continue;
      }
    }
    sets.push_back(set);
    if (sets.size() == sets.capacity()) {
      break;
    }
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The field skill roll of unknown003 (user: 0x7100304434): number of field skills by the driver level, candidates by the common list category, picks and levels. The chance rows
// are separate tables (the game takes five addresses) and are tested from the highest level down, so every level above 15 ends with the second row (the game's own order). Forms tried without
// the helper, in unknown003 (the game has 2525 instructions): the section inline in a scope 2523, bare 2524, with the stack slots of the first locals at other offsets (#104 for #80).
static void rollFieldSkills(GfBladeCreateInfo *info) {
  u32 commonId = info->unknowna48;
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 category = bdatBlade->getCommonListFskill(commonId);
  DataParamAcc driverAcc(OBJECT_TYPE_PC, info->unknown00, GIMMICK_TYPE_UNKNOWN_0);
  u32 level = driverAcc.getLevel(false);
  // Inferred role: chances in percent of one, two and three field skills for the driver level ranges (the game keeps the five rows as five tables); original names unknown.
  static const u32 unknown012[3] = {50, 45, 5};
  static const u32 unknown013[3] = {40, 45, 15};
  static const u32 unknown014[3] = {30, 45, 25};
  static const u32 unknown015[3] = {20, 45, 35};
  static const u32 unknown016[3] = {10, 45, 45};
  const u32 *chances = unknown012;
  if (level > 60) {
    chances = unknown016;
  }
  if (level > 45) {
    chances = unknown015;
  }
  if (level > 30) {
    chances = unknown014;
  }
  if (level > 15) {
    chances = unknown013;
  }
  u32 random = ml::mtRand(100);
  u32 sum = 0;
  u32 fieldSkillNum = 0;
  for (u32 i = 0; i < 3; i++) {
    sum += chances[i];
    if (sum > random) {
      fieldSkillNum = i + 1;
      break;
    }
  }
  QuestListAcc *questListAcc = QuestListAcc::get();
  Bdat::getFP("fld_fieldskilltxt");
  u32 fieldSkillStart = questListAcc->getFLD_FieldSkillListStart();
  u32 fieldSkillEnd = questListAcc->getFLD_FieldSkillListEnd();
  mm::mtl::FixedVector<u32, 256> candidates;
  if (fieldSkillStart < fieldSkillEnd) {
    for (u32 id = fieldSkillStart; id < fieldSkillEnd; id++) {
      u32 fieldSkillCategory = questListAcc->getFLD_FieldSkillListCategory(id);
      if ((fieldSkillCategory >> 1 & 1) != 0) {
        u32 attribute = questListAcc->getFLD_FieldSkillListAttirbute(id);
        if (attribute == 0 || attribute == info->unknown278) {
          u32 name = questListAcc->getFLD_FieldSkillListName(id);
          if (name != 0) {
            candidates.push_back(id);
            GfBdatMsg::getNameFieldSkill(name);
            break;
          }
        }
      }
    }
    for (u32 id = fieldSkillStart; id < fieldSkillEnd; id++) {
      u32 fieldSkillCategory = questListAcc->getFLD_FieldSkillListCategory(id);
      if ((fieldSkillCategory & category) != 0) {
        u32 attribute = questListAcc->getFLD_FieldSkillListAttirbute(id);
        if (attribute == 0 || attribute == info->unknown278) {
          u32 name = questListAcc->getFLD_FieldSkillListName(id);
          if (name != 0) {
            candidates.push_back(id);
            GfBdatMsg::getNameFieldSkill(name);
            if (candidates.size() > 255) {
              break;
            }
          }
        }
      }
    }
  }
  mm::mtl::FixedVector<unknown110, 3> fieldSkills;
  if (fieldSkillNum != 0) {
    for (u32 n = 0; n < fieldSkillNum; n++) {
      if (n >= candidates.size()) {
        break;
      }
      u32 random = ml::mtRand(candidates.size());
      u32 pick = n == 0 ? 0 : random;
      unknown110 fieldSkill;
      fieldSkill.m_fieldSkill = candidates[pick];
      fieldSkills.push_back(fieldSkill);
      u32 i = 0;
      for (u32 *it = candidates.begin(); it != candidates.end(); ++it, ++i) {
        if (i == pick) {
          candidates.erase(it);
          break;
        }
      }
    }
    if (fieldSkills.size() != 0) {
      for (u32 i = 0; i < fieldSkills.size(); i++) {
        u32 minLevel = questListAcc->getFLD_FieldSkillListMinLevel(fieldSkills[i].m_fieldSkill);
        u32 maxLevel = questListAcc->getFLD_FieldSkillListMaxLevel(fieldSkills[i].m_fieldSkill);
        u32 fieldSkillLevel = ml::mtRand(1 - minLevel + maxLevel) + minLevel;
        fieldSkills[i].unknown04 = fieldSkillLevel;
        fieldSkills[i].m_fieldSkillLevel = 1;
        if (fieldSkills[i].unknown04 > 3) {
          fieldSkills[i].unknown04 = 3;
        }
        GfBdatMsg::getNameFieldSkill(questListAcc->getFLD_FieldSkillListName(fieldSkills[i].m_fieldSkill));
      }
      for (u32 i = 0; i < fieldSkills.size(); i++) {
        info->unknown3ee[i] = fieldSkills[i];
      }
    }
  }
}

// Original type name unknown. Inferred role: candidate of the new blade arts table, with its weight.
struct unknown010 {
  u16 unknown00; // Inferred role: arts slot; original member name unknown.
  u16 unknown02; // Inferred role: weight; original member name unknown.
};

// Original type name unknown. Inferred role: candidate of the common list, with its ratio.
struct unknown008 {
  f32 unknown00; // Inferred role: ratio; original member name unknown.
  u16 unknown04; // Inferred role: common list row; original member name unknown.
};

// Original type name unknown. Inferred role: candidate of the blade model list.
struct unknown009 {
  u16 unknown00; // Inferred role: blade model list row; original member name unknown.
  u8 unknown02;  // Inferred role: first model weight; original member name unknown.
  u8 unknown03;  // Inferred role: second model weight; original member name unknown.
};

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Row of the first common list candidate, the pick when the list holds one entry (user: unknown003, 0x7100304434). The game tests `index < size()` of this read
// with `cbnz x19` (size != 0). Written in rollCommonList itself, InstCombine folds that test to `size == 1` (`cmp x19, #1; b.eq`) because the roulette's `size > 1`
// branch dominates it and EarlyCSE has merged the two `m_size` loads; a separately optimised body already holds the test as `size == 0` and the fold does not apply.
// Forms tried without the helper, in unknown003 (the game has 2525 instructions): the read inline 2526, `front()` (no assert) 2518, a local copy of the row 2526; and, with the same
// `cmp #1; b.eq` or an added store (not measured again): dead store in the else branch, `!= 1`, `size() < 2` first, `== 1` first, switch, `empty()`, a local copy of the element, the read
// before the `if`, two separate `if`s, `else if`.
static u16 firstCandidateRow(mm::mtl::FixedVector<unknown008, 512> &candidates) { return candidates[0].unknown04; }

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Rolls the common list row, the attribute (a roulette over eight weights) and the weapon type of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003
// (the game has 2525 instructions): the body inline in a scope 2541, bare 2541.
static void rollCommonList(GfBladeCreateInfo *info) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  mm::mtl::FixedVector<unknown008, 512> candidates;
  u32 start = bdatBlade->getCommonListStart();
  u32 end = bdatBlade->getCommonListEnd();
  u32 ideaBit = 1 << info->unknowna40;
  f32 total = 0.0f;
  for (u32 row = start; row < end; row++) {
    if ((bdatBlade->getCommonListIdeaType(row) & ideaBit) != 0) {
      u32 ideaMin = bdatBlade->getCommonListIdeaMin(row);
      u32 ideaMax = bdatBlade->getCommonListIdeaMax(row);
      SDataIdea *ideas = GfDataDriver::getSDataIdea(info->unknown00);
      u32 ideaLevel = ideas->unknown00[info->unknowna40].unknown04;
      if (ideaLevel >= ideaMin && ideaLevel <= ideaMax) {
        f32 ratio = bdatBlade->getCommonListRatio(row);
        unknown008 candidate = {ratio, static_cast<u16>(row)};
        candidates.push_back(candidate);
        total += ratio;
      }
    }
  }
  if (candidates.size() == 0) {
    unknown008 candidate = {0.0f, static_cast<u16>(ml::mtRand(end - start) + 1)};
    candidates.push_back(candidate);
  }
  if (candidates.size() > 1) {
    f32 roll = total * ml::mtRandf1();
    f32 sum = 0.0f;
    for (const unknown008 &candidate : candidates) {
      sum += candidate.unknown00;
      if (sum >= roll) {
        info->unknowna48 = candidate.unknown04;
        break;
      }
    }
  } else {
    info->unknowna48 = firstCandidateRow(candidates);
  }
  f32 config = bdatBlade->getCreateConfigValue(0x2a);
  f32 weights[9];
  for (u32 i = 0; i < 9; i++) {
    weights[i] = 50.0f - config;
  }
  {
    mm::mtl::FixedVector<u32, 2> attributes;
    GfDataIdea::getIdeaAttribute(attributes, info->unknowna40);
    for (const u32 *attribute = attributes.begin(); attribute != attributes.end(); attribute++) {
      weights[*attribute] = config;
    }
    weights[7] = 0.0f;
    f32 total = 0.0f;
    for (u32 i = 1; i < 9; i++) {
      total += weights[i];
    }
    f32 limits[8];
    f32 sum = 0.0f;
    for (u32 i = 0; i < 8; i++) {
      sum = weights[i + 1] + sum;
      limits[i] = sum;
    }
    f32 roll = ml::mtRandf2() * total;
    u32 attribute = 0;
    for (u32 i = 0; i < 8; i++) {
      if (attribute == 0 && !(limits[i] < roll)) {
        attribute = i + 1;
      }
    }
    if (attribute != 0) {
      info->unknown278 = attribute;
    } else if (info->unknown278 == 0) {
      info->unknown278 = 1;
    }
  }
  // Inferred role: weapon types a common blade can have, the first is the animal type (race 2); original name unknown.
  static const u16 unknown011[8] = {3, 10, 11, 12, 13, 14, 15, 16};
  u32 weaponIndex = ml::mtRand(8);
  info->unknown270 = unknown011[weaponIndex];
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Picks the blade model, motion and parts of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525 instructions): the body inline in a
// scope 2528, bare 2528.
static void pickModel(GfBladeCreateInfo *info) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  mm::mtl::FixedVector<unknown009, 256> models;
  u16 start = bdatBlade->getBladeModelListStart();
  u32 end = bdatBlade->getBladeModelListEnd();
  SDataIdea *ideas = GfDataDriver::getSDataIdea(info->unknown00);
  u32 ideaLevel = ideas->unknown00[info->unknowna40].unknown04;
  u32 total = 0;
  for (u16 id = start; id < end; id++) {
    if (info->unknown268 == bdatBlade->getBladeModelListQuestRace(id) && info->unknown26c == bdatBlade->getBladeModelListGender(id) && ideaLevel >= bdatBlade->getBladeModelListIdeaMin(id)) {
      u32 ideaMax = bdatBlade->getBladeModelListIdeaMax(id);
      if (models.size() != 256 && ideaLevel <= ideaMax) {
        u32 model1 = bdatBlade->getBladeModelListModel1(id);
        u32 model2 = bdatBlade->getBladeModelListModel2(id);
        unknown009 candidate = {id, static_cast<u8>(model1), static_cast<u8>(model2)};
        models.push_back(candidate);
        total += candidate.unknown02 + candidate.unknown03;
      }
    }
  }
  u32 pick = ml::mtRand(total);
  u32 sum = 0;
  for (unknown009 entry : models) {
    sum += entry.unknown03 + entry.unknown02;
    if (sum >= pick) {
      models.clear();
      models.push_back(entry);
      break;
    }
  }
  u32 model = models[0].unknown00;
  bool isVariant;
  if (info->unknown268 == 1 && info->unknown26c == 1) {
    u32 variantRoll = ml::mtRand(101);
    isVariant = variantRoll > models[0].unknown02;
  } else {
    isVariant = false;
  }
  u32 &weaponType = info->unknown270;
  if (weaponType == 3) {
    info->unknown32c = 0x430;
    info->unknown330 = 4;
  } else if (info->unknown26c == 2) {
    info->unknown32c = weaponType + 0x41f;
    info->unknown330 = 2;
  } else if (isVariant) {
    info->unknown32c = weaponType + 0x418;
    info->unknown330 = 3;
  } else {
    info->unknown32c = weaponType + 0x411;
    info->unknown330 = 1;
  }
  info->unknown2c4 = GfBdatChrBl::get()->getChrBlModel(info->unknown32c);
  info->unknown2d8 = GfBdatChrBl::get()->getChrBlMotion(info->unknown32c);
  info->unknown2ec = GfBdatChrBl::get()->getChrBlSePack(info->unknown32c);
  u32 partsTotal =
      bdatBlade->getBladeModelListParts(model, 0) + bdatBlade->getBladeModelListParts(model, 1) + bdatBlade->getBladeModelListParts(model, 2) + bdatBlade->getBladeModelListParts(model, 3);
  u32 partsPick = ml::mtRand(partsTotal);
  u32 partsSum = 0;
  for (u32 i = 0; i < 4; i++) {
    partsSum += bdatBlade->getBladeModelListParts(model, i);
    if (partsSum >= partsPick) {
      info->unknown324[i] = 1;
      break;
    }
  }
  info->unknown274 = GfBdatChrBl::get()->getChrBlDefWeapon(info->unknown32c);
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Picks the blade name of unknown003 among the common names not used by an owned blade (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525
// instructions): the body inline in a scope 2526, with `names` declared first or after `bdatBlade` 2526, bare 2578; the name loop takes other registers than the game's.
static void pickName(GfBladeCreateInfo *info) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 start = bdatBlade->getNameListStart();
  u32 end = bdatBlade->getNameListEnd();
  mm::mtl::FixedVector<u32, 1024> names;
  for (u32 id = start; id < end; id++) {
    u32 race = bdatBlade->getNameListRace(id);
    u32 gender = bdatBlade->getNameListGender(id);
    if (((info->unknown268 == 1 ? 2 : 4) & race) != 0 && (info->unknown26c & gender) != 0) {
      const char *name = GfDataBlade::getCommonBladeName(id);
      u32 i;
      for (i = 0; i < BLADE_UNKNOWN_422; i++) {
        u32 blade = GfDataBlade::getBladeID(i);
        if (!GfDataBlade::isActivateUnuse(blade)) {
          DataParamAcc bladeAcc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
          if (strcmp(bladeAcc.getName(), name) == 0) {
            break;
          }
        }
      }
      if (i >= BLADE_UNKNOWN_422) {
        names.push_back(id);
      }
    }
  }
  if (names.size() != 0) {
    u32 index = ml::mtRand(names.size());
    u32 pick = names[index];
    info->unknown280 = GfDataBlade::getCommonBladeName(pick);
    info->unknown27c = bdatBlade->getNameListCategory(pick);
  } else {
    info->unknown280.format("OutofName%d", _gfdbm::s_outofname);
    _gfdbm::s_outofname = _gfdbm::s_outofname == 0xffffffff ? 1 : _gfdbm::s_outofname + 1;
    info->unknown27c = bdatBlade->getNameListCategory(bdatBlade->getNameListStart());
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The new blade arts roll of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525 instructions): the body inline in a scope 2523,
// bare 2524.
static void rollNewBladeArts(GfBladeCreateInfo *info) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 random = ml::mtRand(100);
  u32 nartsNum = 3;
  for (u32 k = 0, sum = 0; k < 3; k++) {
    sum += bdatBlade->getCmnBl_CapacityNartsNumProb(info->unknowna50, k);
    if (sum > random) {
      nartsNum = k + 1;
      break;
    }
  }
  u32 weaponType = info->unknown270;
  bdatBlade = GfBdatBlade::get();
  u32 row = 0;
  u32 nbaStart = bdatBlade->getCmnBl_NewBlArtsStart();
  u32 nbaEnd = bdatBlade->getCmnBl_NewBlArtsEnd();
  for (u32 i = nbaStart; i < nbaEnd; i++) {
    if (bdatBlade->getCmnBl_NewBlArtsWpnType(i) == weaponType) {
      row = i;
      break;
    }
  }
  mm::mtl::FixedVector<unknown010, 8> nba;
  for (u32 i = 0; i < 8; i++) {
    unknown010 candidate = {static_cast<u16>(i), static_cast<u16>(bdatBlade->getCmnBl_NewBlArtsNBA(row, i))};
    nba.push_back(candidate);
  }
  for (u32 n = 0; n < nartsNum; n++) {
    u32 total = 0;
    for (u32 i = 0; i < static_cast<u32>(nba.size()); i++) {
      total += nba[i].unknown02;
    }
    u32 pick = ml::mtRand(total);
    u32 sum = 0;
    for (u32 i = 0; i < static_cast<u32>(nba.size()); i++) {
      u32 weight = nba[i].unknown02;
      if (weight != 0) {
        sum += weight;
        if (sum >= pick) {
          unknown010 chosen = nba[i];
          info->unknown3b8[n].unknown00 = chosen.unknown00 + 1;
          unknown010 target = nba[i];
          unknown010 *it = nba.begin();
          while (it != nba.end() && !(it->unknown00 == target.unknown00 && it->unknown02 == target.unknown02)) {
            it++;
          }
          nba.erase(it);
          break;
        }
      }
    }
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The skill roll of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525 instructions): the body inline in a scope 2532, bare 2539.
static void rollSkills(GfBladeCreateInfo *info) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 random = ml::mtRand(100);
  u32 skillNum = 3;
  for (u32 k = 0, sum = 0; k < 3; k++) {
    sum += bdatBlade->getCmnBl_CapacitySkillNumProb(info->unknowna50, k);
    if (sum > random) {
      skillNum = k + 1;
      break;
    }
  }
  mm::mtl::FixedVector<unknown109, 3> skills;
  u32 weaponType = info->unknown270;
  bdatBlade = GfBdatBlade::get();
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 role = GfDataBlade::getRoleByWpnType(weaponType);
  u32 skillStart = bdatBtl->getBTL_Skill_BlStart();
  u32 skillEnd = bdatBtl->getBTL_Skill_BlEnd();
  {
    mm::mtl::FixedVector<u32, 256> candidates;
    for (u32 id = skillStart; id < skillEnd; id++) {
      if (bdatBtl->isBTL_Skill_BlFlagcommon(id)) {
        u32 flags = bdatBtl->getBTL_Skill_BlTank(id) != 0;
        flags |= (bdatBtl->getBTL_Skill_BlAttacker(id) != 0) << 1;
        flags |= (bdatBtl->getBTL_Skill_BlHealer(id) != 0) << 2;
        if ((flags & (1 << (role - 1))) != 0) {
          candidates.push_back(id);
        }
      }
    }
    if (candidates.size() != 0) {
      u32 n = 0;
      while (true) {
        u32 pick = ml::mtRand(candidates.size());
        unknown109 skill;
        skill.unknown00 = candidates[pick];
        skills.push_back(skill);
        u32 i = 0;
        for (u32 *it = candidates.begin(); it != candidates.end(); ++it, ++i) {
          if (i == pick) {
            candidates.erase(it);
            break;
          }
        }
        n++;
        if (n >= skillNum || candidates.size() == 0) {
          break;
        }
      }
      for (u32 i = 0; i < skills.size(); i++) {
        int random = ml::mtRand(100);
        int sum = 0;
        u32 level;
        for (level = 0; level < 5;) {
          sum += bdatBlade->getCmnBl_CapacitySkillLvProb(info->unknowna50, level);
          level++;
          if (sum >= random) {
            skills[i].unknown04 = level;
            skills[i].unknown03 = 1;
            break;
          }
        }
        if (skills[i].unknown04 == 0) {
          skills[i].unknown04 = 1;
        }
      }
    }
  }
  for (u32 i = 0; i < skills.size(); i++) {
    info->unknown3dc[i] = skills[i];
    GfDataBladeSkill::getName(info->unknown3dc[i].unknown00);
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The arts picks and level rolls of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525 instructions): the body inline in a scope
// 2523, bare 2520.
static void rollArts(GfBladeCreateInfo *info) {
  u32 power = info->unknowna50;
  u32 weaponType = info->unknown270;
  u32 bladeType = info->unknown330;
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 artsStart = bdatBtl->getArtsBlStart();
  u32 artsEnd = bdatBtl->getArtsBlEnd();
  mm::mtl::FixedVector<u16, 32> arts[3];
  for (u16 id = artsStart; id < artsEnd; id++) {
    if (bdatBtl->isArtsBlFlagcommon(id) && bdatBtl->getArtsBlWpnType(id) == weaponType && bdatBtl->getArtsBlCmnBlType(id) == bladeType) {
      u32 level = bdatBtl->getArtsBlSpLv(id) - 1;
      if (level < 3) {
        arts[level].push_back(id);
      }
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (arts[i].size() != 0) {
      u32 pick = ml::mtRand(arts[i].size());
      info->unknown394[i].unknown00 = arts[i][pick];
    }
  }
  for (u32 i = 0; i < 3; i++) {
    int probs[5];
    int total = 0;
    for (u32 j = 0; j < 5; j++) {
      probs[j] = bdatBlade->getCmnBl_CapacityArtsLvProb(power, j);
      total += probs[j];
    }
    int random = ml::mtRand(total);
    int sum = 0;
    size_t k = 0;
    u32 level;
    for (;;) {
      sum += probs[k];
      level = k + 1;
      if (k == 4 || sum >= random) {
        break;
      }
      k++;
    }
    info->unknown394[i].unknown08 = level;
    info->unknown394[i].m_bladeArtsLevel = 1;
    u32 revCon = bdatBlade->getCmnBl_CapacityArtsRevCon(power);
    u32 revRand = bdatBlade->getCmnBl_CapacityArtsRevRand(power);
    info->unknown394[i].unknown02 = ml::mtRand(revRand) + revCon;
  }
}

// Inferred role: status list row of a category 2 blade list entry, else 0 (the game inlines it at every use); original name unknown.
static u32 unknown018(u32 blade) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  return bdatBlade->getBladeListCategory(blade) == 2 ? bdatBlade->getBladeListStatusID(blade) : 0;
}

// Inferred role: keeps a set within the three categories of slot i (first, first + 9, first + 18 for slots 0 to 2), else the first of that slot; original name unknown.
static u32 unknown019(u32 set, u32 i, u32 first) {
  u32 category = set;
  if (i == 0) {
    category = set - first > 2 ? first : set;
  } else if (i == 1) {
    category = set - (first + 9) > 2 ? first + 9 : set;
  } else if (i == 2) {
    category = set - (first + 18) > 2 ? first + 18 : set;
  }
  return category;
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. The achievement set rolls (arts, skills, field skills, key) of unknown003 (user: 0x7100304434). Forms tried without the helper, in unknown003 (the game has 2525 instructions):
// the three loops inline in a scope or bare, 2525 with the pointer induction variables of the arts and achievement arrays in the other registers (x19 and x27 swapped, the increments in
// the opposite order); with `QuestListAcc::get()` at each use 2530; with a reference to the achievement entry 2525 and the same swap.
static void rollAchievements(GfBladeCreateInfo *info) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 i = 0; i < 3; i++) {
    if (info->unknown394[i].unknown00 != 0) {
      mm::mtl::FixedVector<u16, 32> sets;
      u32 statusId = unknown018(info->unknown23c);
      u32 set = GfBdatBlade::get()->getCommonListArtsAchievementSet(statusId, i);
      u32 category = unknown019(set, i, 1);
      unknown004(sets, category, info->unknown394[i].unknown08);
      if (sets.size() != 0) {
        u32 pick = ml::mtRand(sets.size());
        info->unknown400[i].unknown00 = sets[pick];
        for (u32 k = 0; k < 5; k++) {
          questListAcc->getFLD_AchievementSetAchievementID(info->unknown400[i].unknown00, k);
        }
      }
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (info->unknown3dc[i].unknown00 != 0) {
      mm::mtl::FixedVector<u16, 32> sets;
      u32 statusId = unknown018(info->unknown23c);
      u32 set = GfBdatBlade::get()->getCommonListSkillAchievementSet(statusId, i);
      u32 category = unknown019(set, i, 4);
      unknown004(sets, category, info->unknown3dc[i].unknown04);
      if (sets.size() != 0) {
        u32 pick = ml::mtRand(sets.size());
        info->unknown5b0[i].unknown00 = sets[pick];
        for (u32 k = 0; k < 5; k++) {
          questListAcc->getFLD_AchievementSetAchievementID(info->unknown5b0[i].unknown00, k);
        }
      }
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (info->unknown3ee[i].m_fieldSkill != 0) {
      mm::mtl::FixedVector<u16, 32> sets;
      u32 statusId = unknown018(info->unknown23c);
      u32 set = GfBdatBlade::get()->getCommonListFskillAchivementSet(statusId, i);
      u32 category = unknown019(set, i, 7);
      unknown004(sets, category, info->unknown3ee[i].unknown04);
      if (sets.size() != 0) {
        u32 pick = ml::mtRand(sets.size());
        info->unknown760[i].unknown00 = sets[pick];
        for (u32 k = 0; k < 5; k++) {
          questListAcc->getFLD_AchievementSetAchievementID(info->unknown760[i].unknown00, k);
        }
      }
    }
  }
  {
    mm::mtl::FixedVector<u16, 32> sets;
    u32 statusId = unknown018(info->unknown23c);
    u32 set = GfBdatBlade::get()->getCommonListKeyAchievementSet(statusId);
    u32 category = set - 0x1c > 2 ? 0x1c : set;
    unknown004(sets, category, 5);
    if (sets.size() != 0 || (unknown004(sets, 10, 5), sets.size() != 0)) {
      u32 pick = ml::mtRand(sets.size());
      info->m_achievInfo.unknown00 = sets[pick];
      for (u32 k = 0; k < 5; k++) {
        questListAcc->getFLD_AchievementSetAchievementID(info->m_achievInfo.unknown00, k);
      }
    }
  }
}

// Original name unknown. Inferred role: when the blade model id contains `prefix`, rolls a voice id of `count` values from `base` (4 users in unknown003).
static bool unknown020(const char *bladeId, const char *prefix, u32 count, u32 base, u32 *voice) {
  if (strstr(bladeId, prefix) == nullptr) {
    return false;
  }
  *voice = ml::mtRand(count) + base;
  return true;
}

// Original name unknown. Inferred role: build a random common blade into the creation info.
static void unknown003(GfBladeCreateInfo *info) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  {
    DataParamAcc driverAcc(OBJECT_TYPE_PC, info->unknown00, GIMMICK_TYPE_UNKNOWN_0);
    u32 level = driverAcc.getLevel(false);
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    u32 rate = 0;
    u32 powerStart = bdatBlade->getCmnBl_PowerStart();
    u32 powerEnd = bdatBlade->getCmnBl_PowerEnd();
    for (u32 power = powerStart; power < powerEnd; power++) {
      if (bdatBlade->getCmnBl_PowerMinLv(power) <= level && bdatBlade->getCmnBl_PowerMaxLv(power) >= level) {
        f32 threshold = ml::mtRandf2() * 100.0f;
        f32 best = 0.0f;
        f32 total = 0.0f;
        u32 index;
        u32 bestIndex = 0;
        for (index = 0; index < 10; index++) {
          f32 weight = bdatBlade->getCmnBl_PowerPow(power, index) * 0.1f;
          if (weight == 0.0f) {
            continue;
          }
          total += weight;
          if (total >= threshold) {
            break;
          }
          if (best < weight) {
            best = weight;
            bestIndex = index;
          }
        }
        rate = bestIndex + 1;
        break;
      }
    }
    u32 result;
    if (rate == 0) {
      result = 1;
    } else {
      GfBdatItem *crystalItem = GfBdatItem::get();
      SDataIdea *ideas = GfDataDriver::getSDataIdea(info->unknown00);
      u32 ideaLevel = ideas->unknown00[info->unknowna40].unknown04;
      u32 boosters = info->unknown08.size();
      u32 boosterIdea = boosters + ideaLevel;
      result = crystalItem->getCrystalListCommonPow(info->unknown04) + rate + boosterIdea / 5;
      if (result > 15) {
        result = 15;
      }
    }
    info->unknowna50 = result;
  }
  u32 commonId = bdatItem->getCrystalListCommonID(info->unknown04);
  if (commonId == 0) {
    rollCommonList(info);
  } else {
    u32 weaponType = bdatItem->getCrystalListCommonWpn(info->unknown04);
    u32 attribute = bdatItem->getCrystalListCommonAtr(info->unknown04);
    if (weaponType == 0) {
      weaponType = ml::mtRand(7) + 10;
    }
    if (attribute == 0) {
      attribute = ml::mtRand(8) + 1;
    }
    info->unknowna48 = commonId;
    info->unknown270 = weaponType;
    info->unknown278 = attribute;
  }
  info->unknown268 = info->unknown270 == 3 ? 2 : 1;
  u32 random = ml::mtRand(100);
  u32 gender = 2 - (random & 1);
  info->unknown26c = info->unknown268 == 2 ? 1 : gender;
  pickModel(info);
  pickName(info);
  info->unknown334 = GfBdatChrBl::get()->getChrBlStill(info->unknown32c);
  u32 voice;
  const char *bladeId = info->unknown2c4.c_str();
  if (!unknown020(bladeId, "bl200101", 12, 0x3d, &voice) && !unknown020(bladeId, "bl200201", 12, 0x49, &voice) && !unknown020(bladeId, "bl200301", 4, 0x55, &voice) &&
      !unknown020(bladeId, "bl200401", 4, 0x59, &voice)) {
    voice = 0x3d;
  }
  info->unknown328 = voice;
  info->unknown310.format("%d", info->unknown328);
  {
    GfBdatBtl *bdatBtl = GfBdatBtl::get();
    u32 personalityStart = bdatBtl->getBTL_Bl_PersonalityStart();
    u32 personalityEnd = bdatBtl->getBTL_Bl_PersonalityEnd();
    for (u32 personality = personalityStart; personality < personalityEnd; personality++) {
      if (bdatBtl->isBTL_Bl_PersonalityFlagcommon(personality) && info->unknown328 == bdatBtl->getBTL_Bl_PersonalityVoiceID(personality)) {
        info->unknown358 = personality;
        break;
      }
    }
    bdatBtl = GfBdatBtl::get();
    u32 linkStart = bdatBtl->getBTL_Bl_KizunaLinkSetStart();
    u32 linkEnd = bdatBtl->getBTL_Bl_KizunaLinkSetEnd();
    for (u32 link = linkStart; link < linkEnd; link++) {
      if (info->unknown328 == bdatBtl->getBTL_Bl_KizunaLinkSetVoiceID(link)) {
        info->unknown360 = link;
      }
    }
  }
  {
    DataParamAcc driverAcc(OBJECT_TYPE_PC, info->unknown00, GIMMICK_TYPE_UNKNOWN_0);
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    u32 random = ml::mtRand(100);
    u32 orbs = 0;
    u32 sum = 0;
    for (u32 i = 0; i < 4; i++) {
      sum += bdatBlade->getCmnBl_CapacityOrbNumProb(info->unknowna50, i);
      if (sum > random) {
        orbs = i;
        break;
      }
    }
    info->unknown35c = orbs;
  }
  {
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    u32 stat = 0;
    u32 statStart = bdatBlade->getCmnBl_StatusTypeStart();
    u32 statEnd = bdatBlade->getCmnBl_StatusTypeEnd();
    u32 row = statStart;
    for (; row < statEnd; row++) {
      if (info->unknown270 == bdatBlade->getCmnBl_StatusTypeWpnType(row)) {
        break;
      }
    }
    if (row < statEnd && row != 0) {
      u32 random = ml::mtRand(100);
      u32 i;
      u32 sum = 0;
      for (i = 0; i < 6; i++) {
        sum += bdatBlade->getCmnBl_StatusTypeStatus(row, i);
        if (sum >= random) {
          stat = i + 1;
          break;
        }
      }
    }
    u32 revCon = bdatBlade->getCmnBl_CapacityStatusRevCon(info->unknowna50);
    u32 revRand = bdatBlade->getCmnBl_CapacityStatusRevRand(info->unknowna50);
    u32 rev = ml::mtRand(revRand) + revCon;
    switch (stat) {
    case 1:
      info->unknown374 = rev;
      break;
    case 2:
      info->unknown378 = rev;
      break;
    case 3:
      info->unknown37c = rev;
      break;
    case 4:
      info->unknown380 = rev;
      break;
    case 5:
      info->unknown384 = rev;
      break;
    case 6:
      info->unknown388 = rev;
      break;
    }
  }
  {
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    u32 row = 0;
    u32 armorStart = bdatBlade->getCmnBl_ArmorStart();
    u32 armorEnd = bdatBlade->getCmnBl_ArmorEnd();
    for (u32 i = armorStart; i < armorEnd; i++) {
      if (info->unknown270 == bdatBlade->getCmnBl_ArmorWpnType(i)) {
        row = i;
        break;
      }
    }
    u32 pArmorCon = bdatBlade->getCmnBl_ArmorPArmorCon(row);
    u32 pArmorRand = bdatBlade->getCmnBl_ArmorPArmorRand(row);
    info->unknown38c = ml::mtRand(pArmorRand) + pArmorCon;
    u32 eArmorCon = bdatBlade->getCmnBl_ArmorEArmorCon(row);
    u32 eArmorRand = bdatBlade->getCmnBl_ArmorEArmorRand(row);
    info->unknown390 = ml::mtRand(eArmorRand) + eArmorCon;
  }
  rollArts(info);
  for (u32 i = 0; i < 3; i++) {
    GfDataBladeArts::getName(info->unknown394[i].unknown00);
  }
  {
    u32 power = info->unknowna50;
    u32 weaponType = info->unknown270;
    u32 bladeType = info->unknown330;
    GfBdatBlade *bdatBlade = GfBdatBlade::get();
    GfBdatBtl *bdatBtl = GfBdatBtl::get();
    u32 spStart = bdatBtl->getArtsBlSpStart();
    u32 spEnd = bdatBtl->getArtsBlSpEnd();
    mm::mtl::FixedVector<u16, 32> spArts;
    for (u16 id = spStart; id < spEnd; id++) {
      if (bdatBtl->getArtsBlSpCmnBlType(id) == bladeType && bdatBtl->getArtsBlSpWpnType(id) == weaponType) {
        spArts.push_back(id);
      }
    }
    u32 spPick = ml::mtRand(spArts.size());
    info->unknown364.unknown00 = spArts[spPick];
    u32 revCon = bdatBlade->getCmnBl_CapacitySpArtsRevCon(power);
    u32 revRand = bdatBlade->getCmnBl_CapacitySpArtsRevRand(power);
    info->unknown364.unknown02 = ml::mtRand(revRand) + revCon;
  }
  rollNewBladeArts(info);
  rollSkills(info);
  rollFieldSkills(info);
  rollAchievements(info);
  // Inferred role: favorite categories a common blade can like; original name unknown.
  static const u16 unknown017[12] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 listId = info->unknown23c;
  if (bdatBlade->getBladeListCategory(listId) != 2 || (listId = bdatBlade->getBladeListStatusID(listId)) == 0) {
    listId = info->unknowna48;
  }
  u32 categoryMax = bdatBlade->getCommonListFavoriteCategoryMax(listId);
  u32 categoryNum = categoryMax < 3 ? categoryMax : 2;
  if (categoryNum == 1) {
    u32 index = ml::mtRand(12);
    info->unknown9a0[0].unknown00 = unknown017[index];
  } else if (categoryNum == 2) {
    u32 tries = 0;
    u32 index;
    do {
      index = ml::mtRand(12);
      info->unknown9a0[0].unknown00 = unknown017[index];
      index = ml::mtRand(12);
      info->unknown9a0[1].unknown00 = unknown017[index];
      if (info->unknown9a0[0].unknown00 != info->unknown9a0[1].unknown00) {
        break;
      }
      tries++;
    } while (tries < 16);
    if (tries >= 16) {
      info->unknown9a0[1].unknown00 = 0;
    }
  }
  GfBdatItem *favoriteItem = GfBdatItem::get();
  u32 itemMax = bdatBlade->getCommonListFavoriteItemMax(listId);
  u32 itemNum = itemMax < 3 ? itemMax : 2;
  int favoriteStart = favoriteItem->getFavoriteStart();
  int favoriteEnd = favoriteItem->getFavoriteEnd();
  if (itemNum == 1) {
    info->unknown9a0[0].unknown02 = ml::mtRand(favoriteEnd - favoriteStart) + favoriteStart;
  } else if (itemNum == 2) {
    u32 tries = 0;
    do {
      info->unknown9a0[0].unknown02 = ml::mtRand(favoriteEnd - favoriteStart) + favoriteStart;
      int item = ml::mtRand(favoriteEnd - favoriteStart) + favoriteStart;
      info->unknown9a0[1].unknown02 = item;
      if (info->unknown9a0[0].unknown02 != static_cast<u16>(item)) {
        return;
      }
      tries++;
    } while (tries < 16);
    info->unknown9a0[1].unknown02 = 0;
  }
}

} // namespace gf
