#pragma once
#include "gf/game/quest/gf_quest_info.h"
#include "types.h"

namespace gf {

struct GfMapjumpInfo;
struct GfSequentialPlaySignal;
struct ParamReturnTitle;
struct QuestID;

enum MAINMENU {
  MAINMENU_TOP,
  MAINMENU_SYSTEM,
  MAINMENU_SKIP_TRAVEL,
};

class GfPlayFactory {
public:
  static bool createReturnTitle(const ParamReturnTitle &param);
  static void createOpenMenu2(u32 type, MAINMENU menu, GfSequentialPlaySignal *signal);
  static void createMapjump(const GfMapjumpInfo &info);
  static bool createEventMapjump(const GfMapjumpInfo &info);
  static void createOneEvent(u32 event);
  static bool createTheaterEvent(int event);
  static void createMenuQuestList();
  static bool createQuestUIOrder(QuestID quest, bool isEntry, bool isForce);
  static bool createQuestUIComplete(QuestID quest, QuestID child, QSTATE state);
  static bool createQuestUIComplete(QuestID quest);
  static void createHoodHomuraBattou();
};

} // namespace gf
