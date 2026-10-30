#include "gf/field/gf_field_locator.h"

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/game/gf_game_manager.h"
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
#include "gmk/gmk_event.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_map_gimmick.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_precious.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_tbox.h"
#include "gmk/gmk_warp.h"
#include "mm_mtl/fixstr.h"

namespace gf {

LocatorBat_EnemyID::LocatorBat_EnemyID(QuestID quest, u16 enemyId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyId != 0) {
    create(quest, enemyId);
  }
}

void LocatorBat_EnemyID::create(QuestID quest, u16 enemyId) {
  dispose();
  unknown08 = quest;
  unknown14 = enemyId;
  u8 zoneId = Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE), "ZoneID", unknown14, gmk::BDAT_TYPE_U8);
  if (zoneId) {
    m_mapBdatId = zoneId;
    unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    unknown001(GfQuestTarget::getIconTypeBattle(1, enemyId, unknown08, INVALID_HANDLE, true));
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

LocatorBat_EnemyGroupID::LocatorBat_EnemyGroupID(QuestID quest, u16 enemyGroupId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyGroupId != 0) {
    create(quest, enemyGroupId);
  }
}

void LocatorBat_EnemyGroupID::create(QuestID quest, u16 enemyGroupId) {
  dispose();
  unknown08 = quest;
  unknown14 = enemyGroupId;
  u8 *group = GfDataBdat::getFP(BDAT_FLD_ENEMY_GROUP);
  u8 *arrange = GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE);
  mm::mtl::FixStr<16> name;
  for (int i = 1; i < 9; i++) {
    name.format("EnemyID%d", i);
    u16 enemyId = Bdat::getValCheck(group, name.c_str(), enemyGroupId, gmk::BDAT_TYPE_U16);
    if (enemyId != 0) {
      unknown20.push_back(enemyId);
      u8 zoneId = Bdat::getValCheck(arrange, "ZoneID", enemyId, gmk::BDAT_TYPE_U8);
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
  u8 zoneId = Bdat::getValCheck(arrange, "ZoneID", unknown20.front(), gmk::BDAT_TYPE_U8);
  if (zoneId) {
    m_mapBdatId = zoneId;
    unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(getMapBdatId());
    unknown001(GfQuestTarget::getIconTypeBattle(2, enemyGroupId, quest, INVALID_HANDLE, true));
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

LocatorBat_EnemySpeciesID::LocatorBat_EnemySpeciesID(QuestID quest, u8 enemySpeciesId) : unknown14(0), unknown18(-1) {
  if (!quest.empty() && enemySpeciesId != 0) {
    create(quest, enemySpeciesId);
  }
}

void LocatorBat_EnemySpeciesID::create(QuestID quest, u8 enemySpeciesId) {
  dispose();
  unknown08 = quest;
  unknown14 = enemySpeciesId;
  m_mapBdatId = GfGameManager::getMapID();
  unknown18 = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(m_mapBdatId);
  unknown001(GfQuestTarget::getIconTypeBattle(3, enemySpeciesId, quest, INVALID_HANDLE, true));
}

void LocatorBat_EnemySpeciesID::dispose() {
  m_pos.clear();
  unknown14 = 0;
}

LocatorTalk_NpcID::LocatorTalk_NpcID(QuestID quest, u16 mapId, u16 npcId) : unknown14(0), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && mapId != 0 && npcId != 0) {
    create(quest, mapId, npcId);
  }
}

void LocatorTalk_NpcID::create(QuestID quest, u16 mapId, u16 npcId) {
  dispose();
  m_mapBdatId = mapId;
  unknown08 = quest;
  unknown14 = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(mapId);
  unknown18 = npcId;
  unknown001(GfQuestTarget::getIconTypeTalk(npcId, unknown08, mapId, true));
}

LocatorTalk_NpcID::LocatorTalk_NpcID(QuestID quest, u8 *bdat, int id) : unknown14(0), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  u16 mapId = Bdat::getValCheck(bdat, "MapID", id, gmk::BDAT_TYPE_U16);
  u16 npcId = Bdat::getValCheck(bdat, "NpcID", id, gmk::BDAT_TYPE_U16);
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
      const gmk::GmkNpcIdInfo *info = gmkSet->unknown178.getNpcIdInfoByNpcId(unknown18);
      GfObjAcc acc(info->unknown30);
      if (acc.isValidTransform()) {
        m_pos = acc.getWorldTransformNoSync().unknown00;
      } else {
        gmk::AGmkNpc *npc = info->unknown18;
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
  unknown08 = quest;
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_REACH);
  unknown14 = Bdat::getValCheck(bdat, "Category", reachId, gmk::BDAT_TYPE_U8);
  unknown16 = Bdat::getValCheck(bdat, "PlaceID", reachId, gmk::BDAT_TYPE_U16);
  m_mapBdatId = static_cast<u16>(Bdat::getValCheck(bdat, "MapID", reachId, gmk::BDAT_TYPE_U16));
  GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA);
  int mapId = getMapBdatId();
  unknown001(GfQuestTarget::getIconTypeReachPlace(unknown14, unknown16, unknown08, mapId, true));
}

void LocatorReach::dispose() {
  m_posNum = 0;
  unknown16 = 0;
  unknown14 = 0;
  unknown08 = QuestID();
}

LocatorTbox::LocatorTbox(QuestID quest, u16 tboxId) : unknown14(0), m_posNum(0) {
  if (!quest.empty() && tboxId != 0) {
    create(quest, tboxId);
  }
}

void LocatorTbox::create(QuestID quest, u16 tboxId) {
  dispose();
  unknown08 = quest;
  unknown14 = tboxId;
  int gmkSetId = gmk::GmkManager::get()->findFirstBdatId_RSC_GmkSetList(gmk::GmkTbox::GMK_TYPE, tboxId);
  if (gmkSetId <= 0) {
    dispose();
  } else {
    m_mapBdatId = GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(gmkSetId);
    unknown001(GfQuestTarget::getIconTypeCollect(1, tboxId, unknown08, m_mapBdatId, true));
  }
}

void LocatorTbox::dispose() {
  m_posNum = 0;
  unknown14 = 0;
}

LocatorTalk_DummyGroup::LocatorTalk_DummyGroup(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup) : unknown14(0), unknown18(0), unknown1a(0) {
  if (!quest.empty() && dummyGroup != 0) {
    create(quest, mapId, npcId, dummyGroup);
  }
}

void LocatorTalk_DummyGroup::create(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup) {
  dispose();
  m_mapBdatId = mapId;
  unknown08 = quest;
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
    u16 id = Bdat::getValCheck(bdat, name.c_str(), dummyGroup, gmk::BDAT_TYPE_U16);
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
      const gmk::GmkNpcManager &npcManager = gmkSet->unknown178;
      for (u16 npcId : unknown20) {
        int iconType = GfQuestTarget::getIconTypeTalk(npcId, unknown08, mapId, true);
        if (iconType != 0) {
          m_iconBdatId = gmk::getBdatIdOfQuestTargetIcon(iconType);
          const gmk::GmkNpcIdInfo *info = npcManager.getNpcIdInfoByNpcId(npcId);
          if (info->unknown30 == INVALID_HANDLE) {
            gmk::AGmkNpc *npc = info->unknown18;
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

void LocatorPrecious::dispose() {
  m_pos.clear();
  unknown28.clear();
  unknown20 = 0;
}

LocatorGimmick::LocatorGimmick(QuestID quest, u16 gimmickId) : unknown14(gmk::GMK_TYPE_INVALID), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && gimmickId != 0) {
    create(quest, gimmickId);
  }
}

void LocatorGimmick::create(QuestID quest, u16 gimmickId) {
  dispose();
  unknown08 = quest;
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_GIMMICK);
  m_mapBdatId = static_cast<u16>(Bdat::getValCheck(bdat, "MapID", gimmickId, gmk::BDAT_TYPE_U16));
  u16 doorId = Bdat::getValCheck(bdat, "DoorGimmickID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 elevatorId = Bdat::getValCheck(bdat, "ElevatorGimmickID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 jumpId = Bdat::getValCheck(bdat, "JumpGimmickID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 mapGimmickId = Bdat::getValCheck(bdat, "MapGimmickID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 warpId = Bdat::getValCheck(bdat, "WarpGimmickID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 salvagePointId = Bdat::getValCheck(bdat, "SalvagePointID", gimmickId, gmk::BDAT_TYPE_U16);
  u16 tboxPopId = Bdat::getValCheck(bdat, "TboxPopID", gimmickId, gmk::BDAT_TYPE_U16);
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
  unknown14 = gmk::GMK_TYPE_INVALID;
}

void LocatorGimmick::update() {
  m_posNum = 0;
  if (unknown14 == gmk::GMK_TYPE_INVALID || unknown18 == 0) {
    return;
  }
  unknown001(GfQuestInfo::isScenarioQuest(unknown08) ? 1 : 3);
  const gmk::AGmkBase *gmk = gmk::GmkManager::get()->findFirstGmkInstByBdatId(unknown14, unknown18);
  if (gmk == nullptr || !gmk->isValid()) {
    return;
  }
  switch (unknown14) {
  case gmk::GmkTbox::GMK_TYPE: {
    const gmk::GmkTbox *tbox = static_cast<const gmk::GmkTbox *>(gmk);
    if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist() || tbox->getProgress() == gmk::GmkTbox::PROGRESS_OPENED) {
      return;
    }
    m_pos = gmk->unknown08.unknown08->unknown00;
    break;
  }
  case gmk::GmkSalvage::GMK_TYPE:
    if (!static_cast<const gmk::GmkSalvage *>(gmk)->getBdatInfo()->isCondMatched()) {
      return;
    }
    m_pos = gmk->unknown08.unknown08->unknown00;
    break;
  case gmk::GmkMapGimmick::GMK_TYPE: {
    const gmk::GmkMapGimmick *mapGimmick = static_cast<const gmk::GmkMapGimmick *>(gmk);
    if (!mapGimmick->isNotSolved() || !mapGimmick->getBdatInfo()->isPopCondMatched()) {
      return;
    }
    m_pos = gmk->unknown08.unknown08->unknown00;
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
    m_pos = gmk->unknown08.unknown08->unknown00;
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
  unknown14 = gmk.unknown20.unknown18;
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

LocatorPreciousPreorder::LocatorPreciousPreorder(const gmk::GmkPrecious *gmk) : unknown14(0), m_posNum(0) {
  if (gmk != nullptr) {
    create(*gmk);
  }
}

void LocatorPreciousPreorder::create(const gmk::GmkPrecious &gmk) {
  dispose();
  unknown14 = gmk.unknown20.unknown18;
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

GfFieldLocator::GfFieldLocator(const CreateInfoByQuest *info) : unknown18(nullptr) {
  if (info != nullptr) {
    createByQuest(*info);
  }
}

#line 2390
void GfFieldLocator::createByQuest(const CreateInfoByQuest &info) {
  dispose();
  unknown08 = info;
  gmk::getCurrentMapBdatId();
  switch (info.unknown04) {
  case TASK_TYPE_BATTLE: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_BATTLE);
    u16 enemyId = Bdat::getValCheck(bdat, "EnemyID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 enemyGroupId = Bdat::getValCheck(bdat, "EnemyGroupID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 enemySpeciesId = Bdat::getValCheck(bdat, "EnemySpeciesID", info.unknown08, gmk::BDAT_TYPE_U16);
    if (enemyId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorBat_EnemyID(info.unknown00, enemyId);
    } else if (enemyGroupId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorBat_EnemyGroupID(info.unknown00, enemyGroupId);
    } else if (enemySpeciesId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorBat_EnemySpeciesID(info.unknown00, enemySpeciesId);
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_COLLECT: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_COLLECT);
    u16 tboxId = Bdat::getValCheck(bdat, "TresureID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 enemyId = Bdat::getValCheck(bdat, "EnemyID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 npcId = Bdat::getValCheck(bdat, "NpcID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 itemId = Bdat::getValCheck(bdat, "ItemID", info.unknown08, gmk::BDAT_TYPE_U16);
    if (tboxId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTbox(info.unknown00, tboxId);
    } else if (enemyId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorBat_EnemyID(info.unknown00, enemyId);
    } else if (npcId) {
      unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.unknown00, bdat, info.unknown08);
    } else if (itemId) {
      int id = itemId;
      u8 *precious = GfDataBdat::getFP(BDAT_ITM_PRECIOUS_LIST);
      int top = Bdat::getIdTop(precious);
      int end = Bdat::getIdTop(precious) + Bdat::getIdCount(precious);
      if (top <= id && id < end) {
        unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorPrecious(info.unknown00, itemId);
      } else {
        dispose();
      }
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_REACH:
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorReach(info.unknown00, info.unknown08);
    break;
  case TASK_TYPE_TALK: {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_QUEST_TALK);
    u16 mapId = Bdat::getValCheck(bdat, "MapID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 npcId = Bdat::getValCheck(bdat, "NpcID", info.unknown08, gmk::BDAT_TYPE_U16);
    u16 dummyGroup = Bdat::getValCheck(bdat, "DummyGroup", info.unknown08, gmk::BDAT_TYPE_U16);
    if (npcId || dummyGroup) {
      if (dummyGroup) {
        unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_DummyGroup(info.unknown00, mapId, npcId, dummyGroup);
      } else {
        unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.unknown00, GfDataBdat::getFP(BDAT_FLD_QUEST_TALK), info.unknown08);
      }
    } else {
      dispose();
    }
    break;
  }
  case TASK_TYPE_UNKNOWN_2:
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.unknown00, GfDataBdat::getFP(BDAT_FLD_REQUEST_ITEM_SET), info.unknown08);
    break;
  case TASK_TYPE_CONDITION:
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_NpcID(info.unknown00, GfDataBdat::getFP(BDAT_FLD_QUEST_CONDITION), info.unknown08);
    break;
  case TASK_TYPE_GIMMICK:
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorGimmick(info.unknown00, info.unknown08);
    break;
  case TASK_TYPE_USE:
  case TASK_TYPE_UNKNOWN_7:
  case TASK_TYPE_REQUEST_BLADE:
  case TASK_TYPE_FIELD_SKILL_COUNT:
  case TASK_TYPE_ACHIEVEMENT:
    dispose();
    break;
  }
}

GfFieldLocator::GfFieldLocator(const GfFieldLocator &other) : unknown18(nullptr) {
  if (!other.unknown08.unknown00.empty() && other.unknown08.unknown04 >= 0 && other.unknown08.unknown08 >= 0) {
    createByQuest(other.unknown08);
  }
}

int AFieldLocator::getIconBdatId() const { return m_iconBdatId; }

int AFieldLocator::getMapBdatId() const { return m_mapBdatId; }

bool GfFieldLocator::isOtherMap() const { return unknown18->getMapBdatId() != gmk::getCurrentMapBdatId(); }

void GfFieldLocator::dispose() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  unknown08 = CreateInfoByQuest();
}

void GfFieldLocator::createLocatorTalkPreorder(u16 npcId) {
  dispose();
  LocatorTalk_NpcID *locator = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorTalk_NpcID();
  locator->createPreorder(npcId);
  unknown18 = locator;
}

void GfFieldLocator::createLocatorEventPreorder(const gmk::GmkEvent &gmk) {
  dispose();
  unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorEventPreorder(&gmk);
}

void GfFieldLocator::createLocatorPreciousPreorder(const gmk::GmkPrecious &gmk) {
  dispose();
  unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) LocatorPreciousPreorder(&gmk);
}

void GfFieldLocator::update() {
  if (unknown18 != nullptr) {
    unknown18->update();
  }
}

bool GfFieldLocator::isIconIdPreorder(int iconId) { return Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA), 1, 0x10, gmk::BDAT_TYPE_U16).valueU16 == iconId; }

} // namespace gf
