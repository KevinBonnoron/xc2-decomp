#include "gf/data/gf_data_event.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_shop.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_EVENT_PLAY = 0x8a5f,
  FLAG_WATCHED_BLADE_QUEST_EVENT = 0xb6c2,
  FLAG_WATCHED_BLADE_CREATE_EVENT = 0xb78b,
};

enum {
  EVENT_SCENARIO_FIRST = 10001,
  EVENT_BLADE_CREATE_FIRST = 19001,
  EVENT_BLADE_QUEST_FIRST = 20707,
};

constexpr u32 EVENT_SCENARIO_COUNT = 604;
constexpr u32 EVENT_BLADE_CREATE_COUNT = 58;
constexpr u32 EVENT_BLADE_QUEST_COUNT = 504;
constexpr int EVENT_PLAY_FLAG_COUNT = 2000;

struct EventListBdat {
  u32 bdat;
  int playFlagCount;
};

static const EventListBdat eventListBdats[] = {
    {BDAT_EVT_LIST_BF, 100},
    {BDAT_EVT_LIST_BL, 100},
    {BDAT_EVT_LIST_QST01, 100},
    {BDAT_EVT_LIST_FEV01, 100},
    {BDAT_EVT_LIST_TLK01, 100},
};

static const u16 saveScenarioEvents[] = {
    10001, 10003, 10007, 10008, 10009, 10011, 10012, 10013, 10015, 10018, 10022, 10023, 10025, 10026, 10029, 10032, 10033, 10035, 10037, 10039, 10043, 10044, 10049, 10051, 10052, 10055, 10058,
    10062, 10064, 10067, 10068, 10069, 10072, 10073, 10075, 10076, 10077, 10078, 10079, 10082, 10085, 10086, 10090, 10091, 10092, 10093, 10094, 10095, 10096, 10097, 10098, 10099, 10100, 10102,
    10105, 10106, 10108, 10109, 10110, 10112, 10113, 10114, 10116, 10119, 10125, 10128, 10130, 10131, 10139, 10140, 10141, 10145, 10146, 10148, 10149, 10150, 10151, 10152, 10153, 10154, 10156,
    10157, 10159, 10162, 10163, 10164, 10165, 10168, 10172, 10173, 10174, 10176, 10178, 10179, 10180, 10181, 10182, 10185, 10186, 10188, 10189, 10191, 10195, 10200, 10201, 10202, 10204, 10205,
    10206, 10211, 10212, 10214, 10215, 10216, 10220, 10225, 10230, 10231, 10232, 10233, 10235, 10236, 10237, 10239, 10240, 10242, 10246, 10252, 10253, 10256, 10259, 10261, 10262, 10263, 10264,
    10265, 10266, 10270, 10276, 10277, 10278, 10279, 10280, 10286, 10287, 10289, 10290, 10295, 10297, 10300, 10303, 10304, 10306, 10314, 10318, 10319, 10325, 10326, 10327, 10333, 10334, 10335,
    10336, 10344, 10345, 10348, 10350, 10355, 10360, 10361, 10362, 10363, 10366, 10367, 10370, 10371, 10372, 10376, 10381, 10382, 10384, 10386, 10391, 10392, 10395, 10397, 10399, 10400, 10404,
    10405, 10406, 10410, 10411, 10418, 10428, 10433, 10437, 10439, 10444, 10451, 10456, 10458, 10461, 10463, 10464, 10465, 10468, 10471, 10473, 10485, 10488, 10491, 10494,
};

int GfDataEvent::getEventPlayFlag(u32 event) {
  if (event == 0) {
    return -1;
  }

  for (int list = 0; list < static_cast<int>(sizeof(eventListBdats) / sizeof(eventListBdats[0])); list++) {
    u8 *bdat = GfDataBdat::getFP(eventListBdats[list].bdat);
    if (static_cast<int>(event) < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat)) {
      if (Bdat::getIdCount(bdat) >= eventListBdats[list].playFlagCount) {
        return -1;
      }

      int flag = Bdat::getIdTop(bdat) - event + list * 100;
      if (flag >= EVENT_PLAY_FLAG_COUNT) {
        return -1;
      }

      return flag + FLAG_EVENT_PLAY;
    }
  }

  return -1;
}

bool GfDataEvent::isBladeCreateEvent(u32 event) { return event - EVENT_BLADE_CREATE_FIRST < EVENT_BLADE_CREATE_COUNT; }

bool GfDataEvent::isBladeQuestEvent(u32 event) { return event - EVENT_BLADE_QUEST_FIRST < EVENT_BLADE_QUEST_COUNT; }

bool GfDataEvent::isScenarioEvent(u32 event) { return event - EVENT_SCENARIO_FIRST < EVENT_SCENARIO_COUNT; }

bool GfDataEvent::isSaveScenarioEvent(u32 event) {
  for (u32 index = 0; index < sizeof(saveScenarioEvents) / sizeof(saveScenarioEvents[0]); index++) {
    if (saveScenarioEvents[index] == event) {
      return true;
    }
  }

  return false;
}

void GfDataEvent::setWatchedEventFlag(u32 event) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  u32 flagBase;
  if (isBladeQuestEvent(event)) {
    flagBase = FLAG_WATCHED_BLADE_QUEST_EVENT;
  } else if (isBladeCreateEvent(event)) {
    flagBase = FLAG_WATCHED_BLADE_CREATE_EVENT;
  } else {
    return;
  }

  u32 theater = bdatShop->getMNU_EventTheaterStart();
  u32 end = bdatShop->getMNU_EventTheaterEnd();
  while (true) {
    if (theater >= end) {
      return;
    }

    if (bdatShop->getMNU_EventTheaterevent_id(theater) == event) {
      break;
    }

    theater++;
  }

  if (theater == 0) {
    return;
  }

  u32 flagIndex = bdatShop->getMNU_EventTheaterflag_index(theater);
  if (flagIndex == 0) {
    return;
  }

  GfGameFlag::setLocal(1, flagIndex + flagBase, 1);
}

bool GfDataEvent::isWatchedEventFlag(u32 event) { return isWatchedEventFlag(*GfDataManager::getDataGame(), event); }

bool GfDataEvent::isSaveEvent(u32 event) {
  if (isBladeCreateEvent(event) || isBladeQuestEvent(event)) {
    return true;
  }

  return isSaveScenarioEvent(event);
}

bool GfDataEvent::isSavedEvent(u32 event, const SDataGame &dataGame) {
  for (u32 index = 0; index < dataGame.unknown1171d4; index++) {
    if (dataGame.unknown10ae84[index].unknown00 == event) {
      return true;
    }
  }

  return false;
}

u32 GfDataEvent::getBladeQuestDriver(u32 event) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  u32 theater = bdatShop->getMNU_EventTheaterStart();
  u32 end = bdatShop->getMNU_EventTheaterEnd();
  for (; theater < end; theater++) {
    if (bdatShop->getMNU_EventTheaterevent_id(theater) == event) {
      u32 blade = bdatShop->getMNU_EventTheaterblade_id(theater);
      if (blade == 0) {
        return blade;
      }

      return GfDataBlade::getSDataBlade(blade)->unknown02;
    }
  }

  return 0;
}

} // namespace gf
