#include "gf/field/gf_field_locator.h"

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_door.h"
#include "gmk/gmk_elevator.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_event.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_landmark.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_map_gimmick.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_precious.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_tbox.h"
#include "gmk/gmk_warp.h"
#include "mm_mtl/fixstr.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

// Temporary device (decision 51 in docs/decisions.md): LocatorPrecious::create calls GmkManager::traverseGmkInst<LocatorPrecious> out of line (0x71002dd354, 0x14c bytes),
// and the instance this template body gives does not match: the game calls onTraverse through the unknown134 base subobject (`add x20, x2, #24`, slot 0, hoisted
// before the loop), where the body calls it through LocatorPrecious's own vtable (slot 7, no adjustment), 82 instructions against 83. The body matches the other instances
// (GfGmkBladeTraverser, GfUnpopBladeIds, GmkInstDispTraverserByBdatId...), so it stays; this declaration only keeps the non-matching instance from being emitted. The
// instance remains a target listed by `check`. Remove the declaration as soon as the instance matches.
extern template bool gmk::GmkManager::traverseGmkInst<gf::LocatorPrecious>(gmk::GmkType, gf::LocatorPrecious &) const;

namespace gf {

bool getPopPos(mm::Vec3 &position, const gmk::AGmkBase &gmk) {
  gmk::GmkType type = gmk.getGmkType();
  if (type == gmk::GMK_TYPE_ENEMY) {
    position = gmk.m_createBaseInfo.m_xform->unknown00;
    return true;
  }
  if (type == gmk::GMK_TYPE_ROUTED_ENEMY) {
    if (static_cast<const gmk::GmkRoute &>(gmk).getRoutePointPos(position, 0)) {
      return true;
    }
  }
  return false;
}

// Inferred helper: the pop info of an enemy gimmick (GmkEnemy, GmkRoutedEnemy); original name unknown.
// LocatorBat_EnemyID::update (0x71002dad74) matches only with it (390 instructions; the member chain written at each use
// gives 391): the helper is merged into one GEP (&enemy->m_gmkEnemyInsts.m_popInfo) before it is inlined, where the chain
// shares a GEP to &m_gmkEnemyInsts with the other uses, which InstCombine cannot merge for GmkRoutedEnemy (offset 0x50 is
// [1][1] of AGmkBase: `add x8, #80; add x0, x8, #56` against the game's `add x0, #136`) and which CSE hoists above the
// getGobInstNum call (the game computes the address after it, in the loop preheader, and again for isQuestDead).
template <typename T> static const gmk::GmkEnemyInsts::PopInfo &unknown003(const T &enemy) { return enemy.m_gmkEnemyInsts.m_popInfo; }

LocatorBat_EnemyID::LocatorBat_EnemyID(QuestID quest, u16 enemyId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyId != 0) {
    create(quest, enemyId);
  }
}

void LocatorBat_EnemyID::create(QuestID quest, u16 enemyId) {
  dispose();
  m_questID = quest;
  unknown14 = enemyId;
  u8 zoneId = Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE), "ZoneID", unknown14, gmk::BDAT_TYPE_UNKNOWN_1);
  if (zoneId) {
    m_mapBdatId = zoneId;
    unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    unknown001(GfQuestTarget::getIconTypeBattle(1, enemyId, m_questID, unknown020, true));
  } else {
    dispose();
  }
}

void LocatorBat_EnemyID::dispose() {
  m_pos.clear();
  unknown428.clear();
  unknown20.clear();
  unknown14 = 0;
}

void LocatorBat_EnemyID::update() {
  if (unknown14 != 0 && unknown18 > 0) {
    unknown20.clear();
    unknown428.clear();
    const gmk::GmkSet *gmkSet = gmk::GmkManager::get()->findGmkSet(unknown18);
    if (gmkSet != nullptr) {
      const gmk::IGmkList *enemyList = gmkSet->getGmkList(gmk::GMK_TYPE_ENEMY);
      if (enemyList != nullptr) {
        u32 num = enemyList->getInstNum();
        for (u32 index = 0; index < num; index++) {
          const gmk::AGmkBase *gmk = enemyList->getInst(index);
          if (gmk->isValid()) {
            const gmk::GmkEnemy &enemy = static_cast<const gmk::GmkEnemy &>(*gmk);
            if (unknown003(enemy).hasEneID(unknown14, true) && enemy.m_gmkEnemyInsts.m_bdatInfo.isPopCondMatched()) {
              gmk::GmkAcc::CreateInfo info;
              if (gmk != nullptr) {
                info.validate(*gmk);
              }
              unknown20.push_back(gmk::GmkAcc(info));
            }
          }
        }
      }
      const gmk::IGmkList *routedList = gmkSet->getGmkList(gmk::GMK_TYPE_ROUTED_ENEMY);
      if (routedList != nullptr) {
        u32 num = routedList->getInstNum();
        for (u32 index = 0; index < num; index++) {
          const gmk::AGmkBase *gmk = routedList->getInst(index);
          if (gmk->isValid()) {
            const gmk::GmkRoutedEnemy &enemy = static_cast<const gmk::GmkRoutedEnemy &>(*gmk);
            if (unknown003(enemy).hasEneID(unknown14, true) && enemy.m_gmkEnemyInsts.m_bdatInfo.isPopCondMatched()) {
              gmk::GmkAcc::CreateInfo info;
              if (gmk != nullptr) {
                info.validate(*gmk);
              }
              unknown428.push_back(gmk::GmkAcc(info));
            }
          }
        }
      }
      m_pos.clear();
      size_t enemyNum = unknown20.size();
      for (size_t index = 0; index < enemyNum; index++) {
        gmk::GmkAcc &acc = unknown20[index];
        if (acc.isValid()) {
          const gmk::GmkEnemy *enemy = static_cast<const gmk::GmkEnemy *>(acc.m_aGmkBase);
          u32 gobNum = unknown003(*enemy).getGobInstNum();
          if (gobNum != 0) {
            bool isFound = false;
            for (u32 gobIndex = 0; gobIndex < gobNum; gobIndex++) {
              GF_OBJ_HANDLE *handle = enemy->m_gmkEnemyInsts.getGobInst(gobIndex);
              GfObjAcc objAcc(handle);
              if (objAcc.isValidTransform() && !GfGameUtil::isGameObjWait(handle)) {
                m_pos.push_back(objAcc.getWorldTransformNoSync().unknown00);
                isFound = true;
              }
            }
            if (isFound) {
              continue;
            }
          }
          if (!(enemy->m_gmkEnemyInsts.unknown170 > 0.0f) && !enemy->m_gmkEnemyInsts.isQuestDead()) {
            m_pos.push_back(enemy->m_createBaseInfo.m_xform->unknown00);
          }
        }
      }
      size_t routedNum = unknown428.size();
      for (size_t index = 0; index < routedNum; index++) {
        gmk::GmkAcc &acc = unknown428[index];
        if (acc.isValid()) {
          const gmk::GmkRoutedEnemy *enemy = static_cast<const gmk::GmkRoutedEnemy *>(acc.m_aGmkBase);
          u32 gobNum = unknown003(*enemy).getGobInstNum();
          if (gobNum != 0) {
            bool isFound = false;
            for (u32 gobIndex = 0; gobIndex < gobNum; gobIndex++) {
              GF_OBJ_HANDLE *handle = enemy->m_gmkEnemyInsts.getGobInst(gobIndex);
              GfObjAcc objAcc(handle);
              if (objAcc.isValidTransform() && !GfGameUtil::isGameObjWait(handle)) {
                m_pos.push_back(objAcc.getWorldTransformNoSync().unknown00);
                isFound = true;
              }
            }
            if (isFound) {
              continue;
            }
          }
          if (!(enemy->m_gmkEnemyInsts.unknown170 > 0.0f) && !enemy->m_gmkEnemyInsts.isQuestDead()) {
            mm::Vec3 position(0.0f, 0.0f, 0.0f);
            if (enemy->getRoutePointPos(position, 0)) {
              m_pos.push_back(position);
            }
          }
        }
      }
    }
  }
}

u32 LocatorBat_EnemyID::getPosNum() const { return m_pos.size(); }

const mm::Vec3 *LocatorBat_EnemyID::getPos(u32 index) const { return &m_pos[index]; }

LocatorBat_EnemyGroupID::LocatorBat_EnemyGroupID(QuestID quest, u16 enemyGroupId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyGroupId != 0) {
    create(quest, enemyGroupId);
  }
}

void LocatorBat_EnemyGroupID::create(QuestID quest, u16 enemyGroupId) {
  dispose();
  m_questID = quest;
  unknown14 = enemyGroupId;
  u8 *group = GfDataBdat::getFP(BDAT_FLD_ENEMY_GROUP);
  u8 *arrange = GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE);
  mm::mtl::FixStr<16> name;
  for (int i = 1; i < 9; i++) {
    name.format("EnemyID%d", i);
    u16 enemyId = Bdat::getValCheck(group, name.c_str(), enemyGroupId, gmk::BDAT_TYPE_UNKNOWN_2);
    if (enemyId != 0) {
      unknown20.push_back(enemyId);
      u8 zoneId = Bdat::getValCheck(arrange, "ZoneID", enemyId, gmk::BDAT_TYPE_UNKNOWN_1);
      if (!zoneId) {
        zoneId = GfGameManager::getMapID();
      }
      unknown48.push_back(zoneId);
    }
  }
  if (unknown20.empty()) {
    dispose();
    return;
  }
  u8 zoneId = Bdat::getValCheck(arrange, "ZoneID", unknown20.front(), gmk::BDAT_TYPE_UNKNOWN_1);
  if (zoneId) {
    m_mapBdatId = zoneId;
    unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    unknown001(GfQuestTarget::getIconTypeBattle(2, enemyGroupId, quest, unknown020, true));
  } else {
    dispose();
  }
}

void LocatorBat_EnemyGroupID::dispose() {
  m_pos.clear();
  unknown48.clear();
  unknown20.clear();
  unknown14 = 0;
}

u32 LocatorBat_EnemyGroupID::getPosNum() const { return m_pos.size(); }

const mm::Vec3 *LocatorBat_EnemyGroupID::getPos(u32 index) const { return &m_pos[index]; }

LocatorBat_EnemySpeciesID::LocatorBat_EnemySpeciesID(QuestID quest, u8 enemySpeciesId) : unknown14(0), unknown18(-1) {
  if (!quest.empty() && enemySpeciesId != 0) {
    create(quest, enemySpeciesId);
  }
}

void LocatorBat_EnemySpeciesID::create(QuestID quest, u8 enemySpeciesId) {
  dispose();
  m_questID = quest;
  unknown14 = enemySpeciesId;
  m_mapBdatId = GfGameManager::getMapID();
  unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(m_mapBdatId);
  unknown001(GfQuestTarget::getIconTypeBattle(3, enemySpeciesId, quest, unknown020, true));
}

void LocatorBat_EnemySpeciesID::dispose() {
  m_pos.clear();
  unknown14 = 0;
}

u32 LocatorBat_EnemySpeciesID::getPosNum() const { return m_pos.size(); }

const mm::Vec3 *LocatorBat_EnemySpeciesID::getPos(u32 index) const { return &m_pos[index]; }

LocatorTalk_NpcID::LocatorTalk_NpcID(QuestID quest, u16 mapId, u16 npcId) : unknown14(0), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && mapId != 0 && npcId != 0) {
    create(quest, mapId, npcId);
  }
}

void LocatorTalk_NpcID::create(QuestID quest, u16 mapId, u16 npcId) {
  dispose();
  m_mapBdatId = mapId;
  m_questID = quest;
  unknown14 = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(mapId);
  unknown18 = npcId;
  unknown001(GfQuestTarget::getIconTypeTalk(npcId, m_questID, mapId, true));
}

LocatorTalk_NpcID::LocatorTalk_NpcID(QuestID quest, u8 *bdat, int id) : unknown14(0), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  u16 mapId = Bdat::getValCheck(bdat, "MapID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 npcId = Bdat::getValCheck(bdat, "NpcID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  if (mapId && npcId) {
    create(quest, mapId, npcId);
  }
}

void LocatorTalk_NpcID::dispose() {
  unknown18 = 0;
  unknown14 = 0;
}

void LocatorTalk_NpcID::createPreorder(u16 npcId) {
  dispose();
  m_mapBdatId = GfGameManager::getMapID();
  unknown14 = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(m_mapBdatId);
  unknown18 = npcId;
  unknown001(2);
}

void LocatorTalk_NpcID::update() {
  if (unknown14 > 0 && unknown18 != 0) {
    m_posNum = 0;
    const gmk::GmkSet *gmkSet = gmk::GmkManager::get()->findGmkSet(unknown14);
    if (gmkSet != nullptr) {
      const gmk::GmkNpcIdInfo *info = gmkSet->m_gmkNpcManager.getNpcIdInfoByNpcId(unknown18);
      GfObjAcc acc(info->unknown30);
      if (acc.isValidTransform()) {
        m_pos = acc.getWorldTransformNoSync().unknown00;
      } else {
        gmk::AGmkNpc *npc = info->m_aGmkNpc;
        if (npc == nullptr || !npc->isPopCondMatched()) {
          return;
        }
        mm::Vec3 rotation;
        if (!npc->findPopPosRot(m_pos, rotation)) {
          return;
        }
      }
      m_posNum = 1;
    }
  }
}

LocatorReach::LocatorReach(QuestID quest, int reachId) : unknown14(0), unknown16(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && reachId > 0) {
    create(quest, reachId);
  }
}

void LocatorReach::create(QuestID quest, int reachId) {
  dispose();
  m_questID = quest;
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_REACH);
  unknown14 = Bdat::getValCheck(bdat, "Category", reachId, gmk::BDAT_TYPE_UNKNOWN_1);
  unknown16 = Bdat::getValCheck(bdat, "PlaceID", reachId, gmk::BDAT_TYPE_UNKNOWN_2);
  m_mapBdatId = static_cast<u16>(Bdat::getValCheck(bdat, "MapID", reachId, gmk::BDAT_TYPE_UNKNOWN_2));
  GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA);
  int mapId = getMapBdatId();
  unknown001(GfQuestTarget::getIconTypeReachPlace(unknown14, unknown16, m_questID, mapId, true));
}

void LocatorReach::dispose() {
  m_posNum = 0;
  unknown16 = 0;
  unknown14 = 0;
  m_questID = QuestID();
}

void LocatorReach::update() {
  if (hasPlace()) {
    m_posNum = 0;
    switch (unknown14) {
    case 1:
    case 2: {
      const gmk::AGmkBase *gmk = gmk::GmkManager::get()->findFirstGmkInstByBdatId(gmk::GmkLandmark::GMK_TYPE, unknown16);
      if (gmk == nullptr || !static_cast<const gmk::GmkLandmark *>(gmk)->getBdatInfo()->isCondMatched()) {
        return;
      }
      m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
      break;
    }
    case 3: {
      const gmk::AGmkBase *gmk = gmk::GmkManager::get()->findFirstGmkInstByBdatId(gmk::GmkEvent::GMK_TYPE, unknown16);
      if (gmk == nullptr || !static_cast<const gmk::GmkEvent *>(gmk)->unknownf0) {
        return;
      }
      m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
      break;
    }
    default:
      return;
    }
    m_posNum = 1;
  }
}

LocatorTbox::LocatorTbox(QuestID quest, u16 tboxId) : unknown14(0), m_posNum(0) {
  if (!quest.empty() && tboxId != 0) {
    create(quest, tboxId);
  }
}

void LocatorTbox::create(QuestID quest, u16 tboxId) {
  dispose();
  m_questID = quest;
  unknown14 = tboxId;
  int gmkSetId = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(gmk::GmkTbox::GMK_TYPE, tboxId);
  if (gmkSetId <= 0) {
    dispose();
  } else {
    m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
    unknown001(GfQuestTarget::getIconTypeCollect(1, tboxId, m_questID, m_mapBdatId, true));
  }
}

void LocatorTbox::dispose() {
  m_posNum = 0;
  unknown14 = 0;
}

void LocatorTbox::update() {
  if (unknown14 != 0) {
    m_posNum = 0;
    unknown002(m_gmkAcc, gmk::GmkTbox::GMK_TYPE, unknown14);
    if (m_gmkAcc.isValid()) {
      const gmk::GmkTbox *tbox = static_cast<const gmk::GmkTbox *>(m_gmkAcc.m_aGmkBase);
      if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist() || tbox->getProgress() == gmk::GmkTbox::PROGRESS_UNKNOWN_1) {
        return;
      }
      m_pos = m_gmkAcc.m_aGmkBase->m_createBaseInfo.m_xform->unknown00;
    }
    m_posNum = 1;
  }
}

LocatorTalk_DummyGroup::LocatorTalk_DummyGroup(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup) : unknown14(0), unknown18(0), unknown1a(0) {
  if (!quest.empty() && dummyGroup != 0) {
    create(quest, mapId, npcId, dummyGroup);
  }
}

void LocatorTalk_DummyGroup::create(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup) {
  dispose();
  m_mapBdatId = mapId;
  m_questID = quest;
  unknown18 = npcId;
  unknown1a = dummyGroup;
  unknown14 = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(mapId);
  if (npcId != 0) {
    unknown20.push_back(npcId);
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_TALK_DUMMY_GROUP);
  mm::mtl::FixStr<16> name;
  for (int i = 1; i < 10; i++) {
    name.format("NpcID%d", i);
    u16 id = Bdat::getValCheck(bdat, name.c_str(), dummyGroup, gmk::BDAT_TYPE_UNKNOWN_2);
    if (id) {
      unknown20.push_back(id);
    }
  }
  if (unknown20.empty()) {
    dispose();
  }
}

void LocatorTalk_DummyGroup::dispose() {
  m_pos.clear();
  unknown20.clear();
  unknown18 = 0;
  unknown14 = 0;
}

void LocatorTalk_DummyGroup::update() {
  if (unknown14 > 0 && !unknown20.empty()) {
    m_pos.clear();
    const gmk::GmkSet *gmkSet = gmk::GmkManager::get()->findGmkSet(unknown14);
    if (gmkSet != nullptr) {
      int mapId = getMapBdatId();
      const gmk::GmkNpcManager &npcManager = gmkSet->m_gmkNpcManager;
      for (u16 npcId : unknown20) {
        int iconType = GfQuestTarget::getIconTypeTalk(npcId, m_questID, mapId, true);
        if (iconType != 0) {
          m_iconBdatId = gmk::getBdatIdOfQuestTargetIcon(iconType);
          const gmk::GmkNpcIdInfo *info = npcManager.getNpcIdInfoByNpcId(npcId);
          if (info->unknown30 == unknown020) {
            gmk::AGmkNpc *npc = info->m_aGmkNpc;
            mm::Vec3 position;
            mm::Vec3 rotation;
            if (npc != nullptr && npc->isPopCondMatched() && npc->findPopPosRot(position, rotation)) {
              m_pos.push_back(position);
            }
          } else {
            GfObjAcc acc(info->unknown30);
            if (acc.isValidTransform()) {
              m_pos.push_back(acc.getWorldTransformNoSync().unknown00);
            }
          }
        }
      }
    }
  }
}

LocatorPrecious::LocatorPrecious(QuestID quest, u16 itemId) : unknown20(0) {
  if (!quest.empty() && itemId != 0) {
    create(quest, itemId);
  }
}

void LocatorPrecious::create(QuestID quest, u16 itemId) {
  dispose();
  m_questID = quest;
  unknown20 = itemId;
  int gmkSetId = -1;
  if (gmk::GmkManager::get()->traverseGmkInst(gmk::GmkPrecious::GMK_TYPE, *this) && !unknown28.empty()) {
    const gmk::GmkPrecious *precious = static_cast<const gmk::GmkPrecious *>(unknown28[0].m_aGmkBase);
    if (precious->m_createInfo.unknown18 > 0) {
      gmkSetId = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(gmk::GmkPrecious::GMK_TYPE, precious->m_createInfo.unknown18);
    }
  } else {
    u8 *mapBdat = gmk::GmkManager::get()->unknown190;
    int count = Bdat::getIdCount(mapBdat);
    int top = Bdat::getIdTop(mapBdat);
    for (int id = top; id < top + count; id++) {
      const char *sheetName = gmk::GmkManager::get()->getSheetnameByType(id, gmk::GmkPrecious::GMK_TYPE);
      if (sheetName != nullptr && sheetName[0] != '\0') {
        u8 *bdat = Bdat::isExistFP(sheetName);
        if (bdat != nullptr) {
          int rowCount = Bdat::getIdCount(bdat);
          int rowTop = Bdat::getIdTop(bdat);
          // `!found` is tested before `row < end`. With `row < end && !found` SimplifyCFG folds the two tests into
          // `or (row >= end), (==)` and the DAG re-emits the `==` compare (`cmp; b.ne`, 136 instructions as a guarded
          // do-while, 130 as a `while`) where the game keeps `cset ne; tbnz` (0x71002dd244).
          bool found = false;
          int row = rowTop;
          while (!found && row < rowTop + rowCount) {
            found = static_cast<u16>(Bdat::getValCheck(bdat, "itmID", row, gmk::BDAT_TYPE_UNKNOWN_2)) == itemId;
            if (found) {
              gmkSetId = id;
            }
            row++;
          }
          if (gmkSetId > 0) {
            break;
          }
        }
      }
    }
  }
  if (gmkSetId >= 0) {
    m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
    unknown001(GfQuestTarget::getIconTypeCollect(2, itemId, m_questID, m_mapBdatId, true));
    return;
  }
  dispose();
}

void LocatorPrecious::dispose() {
  m_pos.clear();
  unknown28.clear();
  unknown20 = 0;
}

u32 LocatorPrecious::getPosNum() const { return m_pos.size(); }

const mm::Vec3 *LocatorPrecious::getPos(u32 index) const { return &m_pos[index]; }

void LocatorPrecious::update() {
  if (unknown20 != 0) {
    m_pos.clear();
    for (gmk::GmkAcc *acc = unknown28.begin(); acc != unknown28.end(); acc++) {
      if (!acc->isValid()) {
        create(m_questID, unknown20);
        return;
      }
      const gmk::GmkPrecious *precious = static_cast<const gmk::GmkPrecious *>(acc->m_aGmkBase);
      if (!precious->isObtained() && precious->getBdatInfo()->isPopCondMatched()) {
        m_pos.push_back(acc->m_aGmkBase->m_createBaseInfo.m_xform->unknown00);
      }
    }
  }
}

void LocatorPrecious::onTraverse(const gmk::AGmkBase &gmk) {
  const gmk::GmkPrecious &precious = static_cast<const gmk::GmkPrecious &>(gmk);
  if (gmk.isValid() && precious.getBdatInfo()->unknown00 == unknown20 && !precious.isObtained()) {
    gmk::GmkAcc::CreateInfo info;
    info.validate(gmk);
    unknown28.push_back(gmk::GmkAcc(info));
    m_pos.push_back(gmk.m_createBaseInfo.m_xform->unknown00);
  }
}

LocatorGimmick::LocatorGimmick(QuestID quest, u16 gimmickId) : unknown14(gmk::GMK_TYPE_UNKNOWN_59), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && gimmickId != 0) {
    create(quest, gimmickId);
  }
}

void LocatorGimmick::create(QuestID quest, u16 gimmickId) {
  dispose();
  m_questID = quest;
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_GIMMICK);
  m_mapBdatId = static_cast<u16>(Bdat::getValCheck(bdat, "MapID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2));
  u16 doorId = Bdat::getValCheck(bdat, "DoorGimmickID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 elevatorId = Bdat::getValCheck(bdat, "ElevatorGimmickID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 jumpId = Bdat::getValCheck(bdat, "JumpGimmickID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 mapGimmickId = Bdat::getValCheck(bdat, "MapGimmickID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 warpId = Bdat::getValCheck(bdat, "WarpGimmickID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 salvagePointId = Bdat::getValCheck(bdat, "SalvagePointID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 tboxPopId = Bdat::getValCheck(bdat, "TboxPopID", gimmickId, gmk::BDAT_TYPE_UNKNOWN_2);
  if (doorId) {
    unknown14 = gmk::GmkDoor::GMK_TYPE;
    unknown18 = doorId;
  } else if (elevatorId) {
    unknown14 = gmk::GmkElevator::GMK_TYPE;
    unknown18 = elevatorId;
  } else if (jumpId) {
    unknown14 = gmk::GmkJump::GMK_TYPE;
    unknown18 = jumpId;
  } else if (mapGimmickId) {
    unknown14 = gmk::GmkMapGimmick::GMK_TYPE;
    unknown18 = mapGimmickId;
  } else if (warpId) {
    unknown14 = gmk::GmkWarp::GMK_TYPE;
    unknown18 = warpId;
  } else if (salvagePointId) {
    unknown14 = gmk::GmkSalvage::GMK_TYPE;
    unknown18 = salvagePointId;
  } else if (tboxPopId) {
    unknown14 = gmk::GmkTbox::GMK_TYPE;
    unknown18 = tboxPopId;
  }
}

void LocatorGimmick::dispose() {
  m_posNum = 0;
  unknown18 = 0;
  unknown14 = gmk::GMK_TYPE_UNKNOWN_59;
}

void LocatorGimmick::update() {
  m_posNum = 0;
  if (unknown14 == gmk::GMK_TYPE_UNKNOWN_59 || unknown18 == 0) {
    return;
  }
  unknown001(GfQuestInfo::isScenarioQuest(m_questID) ? 1 : 3);
  const gmk::AGmkBase *gmk = gmk::GmkManager::get()->findFirstGmkInstByBdatId(unknown14, unknown18);
  if (gmk == nullptr || !gmk->isValid()) {
    return;
  }
  switch (unknown14) {
  case gmk::GmkTbox::GMK_TYPE: {
    const gmk::GmkTbox *tbox = static_cast<const gmk::GmkTbox *>(gmk);
    if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist() || tbox->getProgress() == gmk::GmkTbox::PROGRESS_UNKNOWN_1) {
      return;
    }
    m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
    break;
  }
  case gmk::GmkSalvage::GMK_TYPE:
    if (!static_cast<const gmk::GmkSalvage *>(gmk)->getBdatInfo()->isCondMatched()) {
      return;
    }
    m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
    break;
  case gmk::GmkMapGimmick::GMK_TYPE: {
    const gmk::GmkMapGimmick *mapGimmick = static_cast<const gmk::GmkMapGimmick *>(gmk);
    if (!mapGimmick->isNotSolved() || !mapGimmick->getBdatInfo()->isPopCondMatched()) {
      return;
    }
    m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
    break;
  }
  case gmk::GmkJump::GMK_TYPE: {
    const gmk::GmkJump *jump = static_cast<const gmk::GmkJump *>(gmk);
    if (!jump->getBdatInfo()->isPopCondMatched()) {
      return;
    }
    m_pos = jump->getData()->position;
    break;
  }
  case gmk::GmkWarp::GMK_TYPE: {
    const gmk::GmkWarp *warp = static_cast<const gmk::GmkWarp *>(gmk);
    if (!warp->unknown002()->isPopCondCommonMatched()) {
      return;
    }
    m_pos = warp->unknown003()->unknown00;
    break;
  }
  case gmk::GmkDoor::GMK_TYPE:
    if (!static_cast<const gmk::GmkDoor *>(gmk)->getBdatInfo()->isPopCondMatched()) {
      return;
    }
    m_pos = gmk->m_createBaseInfo.m_xform->unknown00;
    break;
  case gmk::GmkElevator::GMK_TYPE:
    if (!static_cast<const gmk::GmkElevator *>(gmk)->getPosForCompass(m_pos)) {
      return;
    }
    break;
  default:
    m_pos = mm::Vec3::zero;
    break;
  }
  m_posNum = 1;
}

LocatorEventPreorder::LocatorEventPreorder(const gmk::GmkEvent *gmk) : unknown14(0), m_posNum(0) {
  if (gmk != nullptr) {
    create(*gmk);
  }
}

void LocatorEventPreorder::create(const gmk::GmkEvent &gmk) {
  dispose();
  unknown14 = gmk.m_createInfo.unknown18;
  int gmkSetId = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(gmk::GmkEvent::GMK_TYPE, unknown14);
  if (gmkSetId <= 0) {
    dispose();
  } else {
    m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
    m_iconBdatId = gmk.unknown001()->unknown04;
  }
}

void LocatorEventPreorder::dispose() {
  m_posNum = 0;
  unknown14 = 0;
}

void LocatorEventPreorder::update() {
  if (unknown14 != 0) {
    m_posNum = 0;
    unknown002(m_gmkAcc, gmk::GmkEvent::GMK_TYPE, unknown14);
    if (m_gmkAcc.isValid()) {
      if (!static_cast<const gmk::GmkEvent *>(m_gmkAcc.m_aGmkBase)->unknownf0) {
        return;
      }
      m_pos = m_gmkAcc.m_aGmkBase->m_createBaseInfo.m_xform->unknown00;
    }
    m_posNum = 1;
  }
}

LocatorPreciousPreorder::LocatorPreciousPreorder(const gmk::GmkPrecious *gmk) : unknown14(0), m_posNum(0) {
  if (gmk != nullptr) {
    create(*gmk);
  }
}

void LocatorPreciousPreorder::create(const gmk::GmkPrecious &gmk) {
  dispose();
  unknown14 = gmk.m_createInfo.unknown18;
  int gmkSetId = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(gmk::GmkPrecious::GMK_TYPE, unknown14);
  if (gmkSetId <= 0) {
    dispose();
  } else {
    m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
    unknown001(2);
  }
}

void LocatorPreciousPreorder::dispose() {
  m_posNum = 0;
  unknown14 = 0;
}

void LocatorPreciousPreorder::update() {
  if (unknown14 != 0) {
    m_posNum = 0;
    unknown002(m_gmkAcc, gmk::GmkPrecious::GMK_TYPE, unknown14);
    if (m_gmkAcc.isValid()) {
      const gmk::GmkPrecious *precious = static_cast<const gmk::GmkPrecious *>(m_gmkAcc.m_aGmkBase);
      if (precious->isObtained() || !precious->getBdatInfo()->isPopCondMatched()) {
        return;
      }
      m_pos = m_gmkAcc.m_aGmkBase->m_createBaseInfo.m_xform->unknown00;
    }
    m_posNum = 1;
  }
}

GfFieldLocator::GfFieldLocator(const CreateInfoByQuest *info) : m_aFieldLocator(nullptr) {
  if (info != nullptr) {
    createByQuest(*info);
  }
}

#line 2390
void GfFieldLocator::createByQuest(const CreateInfoByQuest &info) {
  dispose();
  m_createInfoByQuest = info;
  gmk::getCurrentMapBdatId();
  switch (info.unknown04) {
  case TASK_TYPE_UNKNOWN_1: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_BATTLE);
    u16 enemyId = Bdat::getValCheck(bdat, "EnemyID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 enemyGroupId = Bdat::getValCheck(bdat, "EnemyGroupID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 enemySpeciesId = Bdat::getValCheck(bdat, "EnemySpeciesID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    if (enemyId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorBat_EnemyID(info.m_questID, enemyId);
    } else if (enemyGroupId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorBat_EnemyGroupID(info.m_questID, enemyGroupId);
    } else if (enemySpeciesId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorBat_EnemySpeciesID(info.m_questID, enemySpeciesId);
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_UNKNOWN_3: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_COLLECT);
    u16 tboxId = Bdat::getValCheck(bdat, "TresureID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 enemyId = Bdat::getValCheck(bdat, "EnemyID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 npcId = Bdat::getValCheck(bdat, "NpcID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 itemId = Bdat::getValCheck(bdat, "ItemID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    if (tboxId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTbox(info.m_questID, tboxId);
    } else if (enemyId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorBat_EnemyID(info.m_questID, enemyId);
    } else if (npcId) {
      m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.m_questID, bdat, info.unknown08);
    } else if (itemId) {
      int id = itemId;
      u8 *precious = GfDataBdat::getFP(BDAT_ITM_PRECIOUS_LIST);
      int top = Bdat::getIdTop(precious);
      int end = Bdat::getIdTop(precious) + Bdat::getIdCount(precious);
      if (top <= id && id < end) {
        m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorPrecious(info.m_questID, itemId);
      } else {
        dispose();
      }
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_UNKNOWN_5:
    m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorReach(info.m_questID, info.unknown08);
    break;
  case TASK_TYPE_UNKNOWN_6: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_TALK);
    u16 mapId = Bdat::getValCheck(bdat, "MapID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 npcId = Bdat::getValCheck(bdat, "NpcID", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    u16 dummyGroup = Bdat::getValCheck(bdat, "DummyGroup", info.unknown08, gmk::BDAT_TYPE_UNKNOWN_2);
    if (npcId || dummyGroup) {
      if (dummyGroup) {
        m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_DummyGroup(info.m_questID, mapId, npcId, dummyGroup);
      } else {
        m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.m_questID, GfDataBdat::getFP(BDAT_FLD_QUEST_TALK), info.unknown08);
      }
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_UNKNOWN_2:
    m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.m_questID, GfDataBdat::getFP(BDAT_FLD_REQUEST_ITEM_SET), info.unknown08);
    break;
  case TASK_TYPE_UNKNOWN_10:
    m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.m_questID, GfDataBdat::getFP(BDAT_FLD_QUEST_CONDITION), info.unknown08);
    break;
  case TASK_TYPE_UNKNOWN_8:
    m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorGimmick(info.m_questID, info.unknown08);
    break;
  case TASK_TYPE_UNKNOWN_4:
  case TASK_TYPE_UNKNOWN_7:
  case TASK_TYPE_UNKNOWN_9:
  case TASK_TYPE_UNKNOWN_11:
  case TASK_TYPE_UNKNOWN_12:
    dispose();
    break;
  }
}

GfFieldLocator::GfFieldLocator(const GfFieldLocator &other) : m_aFieldLocator(nullptr) {
  if (!other.m_createInfoByQuest.m_questID.empty() && other.m_createInfoByQuest.unknown04 >= 0 && other.m_createInfoByQuest.unknown08 >= 0) {
    createByQuest(other.m_createInfoByQuest);
  }
}

int AFieldLocator::getIconBdatId() const { return m_iconBdatId; }

int AFieldLocator::getMapBdatId() const { return m_mapBdatId; }

bool GfFieldLocator::isOtherMap() const { return m_aFieldLocator->getMapBdatId() != gmk::getCurrentMapBdatId(); }

void GfFieldLocator::dispose() {
  if (m_aFieldLocator != nullptr) {
    delete m_aFieldLocator;
    m_aFieldLocator = nullptr;
  }
  m_createInfoByQuest = CreateInfoByQuest();
}

void GfFieldLocator::createLocatorTalkPreorder(u16 npcId) {
  dispose();
  LocatorTalk_NpcID *locator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorTalk_NpcID();
  locator->createPreorder(npcId);
  m_aFieldLocator = locator;
}

void GfFieldLocator::createLocatorEventPreorder(const gmk::GmkEvent &gmk) {
  dispose();
  m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorEventPreorder(&gmk);
}

void GfFieldLocator::createLocatorPreciousPreorder(const gmk::GmkPrecious &gmk) {
  dispose();
  m_aFieldLocator = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LocatorPreciousPreorder(&gmk);
}

void GfFieldLocator::update() {
  if (m_aFieldLocator != nullptr) {
    m_aFieldLocator->update();
  }
}

bool GfFieldLocator::isIconIdPreorder(int iconId) { return Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA), 1, 0x10, gmk::BDAT_TYPE_UNKNOWN_2).valueU16 == iconId; }

} // namespace gf

#include "gf/field/gf_gmk_locator.cpp"
#include "gf/field/gf_gmk_locator_atlas.cpp"
