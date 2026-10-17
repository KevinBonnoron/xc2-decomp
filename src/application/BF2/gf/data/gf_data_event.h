#pragma once
#include "types.h"

namespace gf {

struct SDataGame;

struct SDataSavedEvent {
  u16 event;
  u8 _02[0x64 - 0x02];
};

static_assert(sizeof(SDataSavedEvent) == 0x64, "");

class GfDataEvent {
public:
  static int getEventType(u32 event);
  static int getEventAfterScriptStartID(u32 event);
  static const char *getEventAfterScriptName(u32 event);
  static int getEventPlayFlag(u32 event);
  static u32 getMapjumpID(u32 event);
  static bool isBladeCreateEvent(u32 event);
  static bool isBladeQuestEvent(u32 event);
  static bool isScenarioEvent(u32 event);
  static bool isSaveScenarioEvent(u32 event);
  static void setWatchedEventFlag(u32 event);
  static bool isWatchedEventFlag(u32 event);
  static bool isWatchedEventFlag(const SDataGame &dataGame, u32 event);
  static bool isSaveEvent(u32 event);
  static bool isSavedEvent(u32 event, const SDataGame &dataGame);
  static u32 getBladeQuestDriver(u32 event);
};

} // namespace gf
