#pragma once
namespace gf {

class GfMenuCallContext;
struct QuestID;

class GfMenuObjQuestLog {
public:
  static void complete(GfMenuCallContext *context, QuestID quest);
};

} // namespace gf
