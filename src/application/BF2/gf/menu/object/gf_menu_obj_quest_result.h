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
    ListListener(GfMenuObjQuestResult *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjQuestResult *unknown20; // Inferred role: owner; original member name unknown.
    u8 _28[0x30 - 0x28];
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
