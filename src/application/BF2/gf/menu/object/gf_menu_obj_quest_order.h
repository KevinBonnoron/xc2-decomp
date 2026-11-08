#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct QuestID;

class GfMenuObjQuestOrder : public GfMenuObject {
public:
  static void close();
  static void open(GfMenuCallContext *context, QuestID quest);
  GfMenuObjQuestOrder(u32 handle);
  ~GfMenuObjQuestOrder() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
