#pragma once
#include "types.h"

namespace gf {

struct SDataGame;

// Inferred role: save data saved event; original type name unknown.
struct unknown125 {
  u16 unknown00; // Inferred role: event; original member name unknown.
  u8 _02[0x64 - 0x02];
};

static_assert(sizeof(unknown125) == 0x64, "");

class GfDataEvent {
public:
  static int getEventType(u32 event);
  static int getEventAfterScriptStartID(u32 event);
  static const char *getEventAfterScriptName(u32 event);
  static u32 getEventID(const char *name);
  static const char *getEventName(u32 event);
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
