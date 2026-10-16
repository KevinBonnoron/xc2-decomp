#include "gf/data/gf_bdat_quest.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {

GfBdatQuest::GfBdatQuest()
    : unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr),
      unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr),
      unknown80(nullptr), unknown88(nullptr), unknown90(nullptr), unknown98(nullptr), unknowna0(nullptr), unknowna8(nullptr), unknownb0(nullptr),
      unknownb8(nullptr), unknownc0(nullptr), unknownc8(nullptr), unknownd0(nullptr), unknownd8(nullptr), unknowne0(nullptr), unknowne8(nullptr),
      unknownf0(nullptr), unknownf8(nullptr), unknown100(nullptr), unknown108(nullptr), unknown110(nullptr), unknown118(nullptr), unknown120(nullptr),
      unknown128(nullptr) {
  mQuestListAcc = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) QuestListAcc();
  bdatRefresh();
}

GfBdatQuest::~GfBdatQuest() {
  if (mQuestListAcc != nullptr) {
    delete mQuestListAcc;
    mQuestListAcc = nullptr;
  }

  destroyFP();
}

void GfBdatQuest::destroyFP() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }

  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }

  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }

  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }

  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }

  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }

  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }

  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }

  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }

  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }

  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }

  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }

  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }

  if (unknownb8 != nullptr) {
    delete unknownb8;
    unknownb8 = nullptr;
  }

  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }

  if (unknown90 != nullptr) {
    delete unknown90;
    unknown90 = nullptr;
  }

  if (unknown98 != nullptr) {
    delete unknown98;
    unknown98 = nullptr;
  }

  if (unknowna0 != nullptr) {
    delete unknowna0;
    unknowna0 = nullptr;
  }

  if (unknowna8 != nullptr) {
    delete unknowna8;
    unknowna8 = nullptr;
  }

  if (unknownb0 != nullptr) {
    delete unknownb0;
    unknownb0 = nullptr;
  }

  if (unknownc8 != nullptr) {
    delete unknownc8;
    unknownc8 = nullptr;
  }

  if (unknownc0 != nullptr) {
    delete unknownc0;
    unknownc0 = nullptr;
  }

  if (unknownd0 != nullptr) {
    delete unknownd0;
    unknownd0 = nullptr;
  }

  if (unknownd8 != nullptr) {
    delete unknownd8;
    unknownd8 = nullptr;
  }

  if (unknowne0 != nullptr) {
    delete unknowne0;
    unknowne0 = nullptr;
  }

  if (unknowne8 != nullptr) {
    delete unknowne8;
    unknowne8 = nullptr;
  }

  if (unknownf0 != nullptr) {
    delete unknownf0;
    unknownf0 = nullptr;
  }

  if (unknownf8 != nullptr) {
    delete unknownf8;
    unknownf8 = nullptr;
  }

  if (unknown100 != nullptr) {
    delete unknown100;
    unknown100 = nullptr;
  }

  if (unknown108 != nullptr) {
    delete unknown108;
    unknown108 = nullptr;
  }

  if (unknown110 != nullptr) {
    delete unknown110;
    unknown110 = nullptr;
  }

  if (unknown118 != nullptr) {
    delete unknown118;
    unknown118 = nullptr;
  }

  if (unknown120 != nullptr) {
    delete unknown120;
    unknown120 = nullptr;
  }

  if (unknown128 != nullptr) {
    delete unknown128;
    unknown128 = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatQuest::createFP() {
// The line numbers passed to the allocator decide between mov and orr.
#line 128
  unknown10 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST);
  unknown18 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_NORMAL);
  unknown20 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MINI);
  unknown28 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MERCENARIES);
  unknown30 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_ACHIEVEMENT);
  unknown38 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_BLADE);
  unknown40 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_COLLECT);
  unknown48 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK);
  unknown50 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_NORMAL);
  unknown58 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MINI);
  unknown60 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MERCENARIES);
  unknown68 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_ACHIEVEMENT);
  unknown70 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_BLADE);
  unknown78 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_BATTLE);
  unknown80 = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_ITEM_SET);
  unknownb8 = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_BLADE);
  unknown88 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_USE);
  unknown90 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REACH);
  unknown98 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK);
  unknowna0 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK_DUMMY_GROUP);
  unknowna8 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_GIMMICK);
  unknownb0 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_FIELD_SKILL_COUNT);
  unknownc8 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_HINTS);
  unknownc0 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_CONDITION);
  unknownd0 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_EVENT);
  unknownd8 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD);
  unknowne0 = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD_RANDOM);
  unknowne8 = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT);
  unknownf0 = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_SET);
  unknownf8 = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_LIST);
  unknown100 = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_CONFIG);
  unknown108 = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_MISSION);
  unknown110 = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_LIST);
  unknown118 = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_SETTING);
  unknown120 = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_RANDOM);
  unknown128 = NEW_BDAT_WRAPPER(BDAT_FLD_DEVELOPMENT_LEVEL);
}

} // namespace gf
