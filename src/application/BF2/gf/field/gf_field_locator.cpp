#include "gf/field/gf_field_locator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/gf_allocator.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"

namespace gf {

LocatorBat_EnemyID::LocatorBat_EnemyID(QuestID quest, u16 enemyId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyId != 0) {
    create(quest, enemyId);
  }
}

LocatorBat_EnemyGroupID::LocatorBat_EnemyGroupID(QuestID quest, u16 enemyGroupId) : unknown14(0), unknown18(0) {
  if (!quest.empty() && enemyGroupId != 0) {
    create(quest, enemyGroupId);
  }
}

LocatorTalk_DummyGroup::LocatorTalk_DummyGroup(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup) : unknown14(0), unknown18(0), unknown1a(0) {
  if (!quest.empty() && dummyGroup != 0) {
    create(quest, mapId, npcId, dummyGroup);
  }
}

LocatorPrecious::LocatorPrecious(QuestID quest, u16 itemId) : unknown20(0) {
  if (!quest.empty() && itemId != 0) {
    create(quest, itemId);
  }
}

LocatorGimmick::LocatorGimmick(QuestID quest, u16 gimmickId) : unknown14(gmk::GMK_TYPE_INVALID), unknown18(0), m_posNum(0), m_pos(mm::Vec3::zero) {
  if (!quest.empty() && gimmickId != 0) {
    create(quest, gimmickId);
  }
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

void GfFieldLocator::update() {
  if (unknown18 != nullptr) {
    unknown18->update();
  }
}

} // namespace gf
