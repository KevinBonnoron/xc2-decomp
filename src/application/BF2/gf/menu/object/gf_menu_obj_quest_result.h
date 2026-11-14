#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
struct QuestID;

class GfMenuObjQuestResult : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjQuestResult *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: screen state, 0 summary, 1 summary shown, 2 result fade, 3 result shown, 4 closing; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjQuestResult *unknown20; // Inferred role: owner; original member name unknown.
    u32 unknown28;                   // Inferred role: handle of the registered timer; original member name unknown.
    u8 _2c[0x30 - 0x2c];
  };

  static void close();
  static void fadeOut(u32 handle);
  static void fadeIn(u32 handle);
  static void setScreenMode(u32 handle, u32 mode);
  static void setupScreen(u32 handle, QuestID quest);
  static void open(GfMenuCallContext *context, QuestID quest);
  static void createAdapter(u32 handle, const char *name, QuestID quest, u32 type);
  GfMenuObjQuestResult(u32 handle);
  ~GfMenuObjQuestResult() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjQuestResult::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjQuestResult::ListListener) == 0x30, "");

} // namespace gf
