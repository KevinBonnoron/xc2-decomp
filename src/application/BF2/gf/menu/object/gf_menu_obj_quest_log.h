#pragma once
#include "gf/menu/gf_menu_object.h"
namespace gf {

class GfMenuCallContext;
struct QuestID;

class GfMenuObjQuestLog : public GfMenuObject {
public:
  static void changeActiveQuest();
  static void updateTask();
  static void closeLog();
  static void openLog();
  bool seqLogNextEnd();
  bool seqLogStart();
  bool seqOrderWait();
  bool seqTitleEndWait();
  void initialize() override;
  void finalize() override;
  static void order(GfMenuCallContext *context, QuestID quest);
  static void complete(GfMenuCallContext *context, QuestID quest);
  static void lockLogOpen();
  static void unlockLogOpen();
};

} // namespace gf
