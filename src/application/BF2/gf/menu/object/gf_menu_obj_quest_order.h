#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
struct QuestID;

class GfMenuObjQuestOrder : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjQuestOrder *owner) : unknown0c(0), unknown10(0), _14(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: whether the confirmation window is open; original member name unknown.
    u32 unknown10; // Inferred role: displayed quest, as packed QuestID; original member name unknown.
    u8 _14[0x1c - 0x14];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjQuestOrder *unknown20; // Inferred role: owner; original member name unknown.
    u8 _28[0x30 - 0x28];
    GfMenuCallContext *unknown30; // Inferred role: confirmation window call; original member name unknown.
  };

  static void close();
  static void open(GfMenuCallContext *context, QuestID quest);
  static void createAdapter(u32 handle, const char *name, QuestID quest, u32 type);
  GfMenuObjQuestOrder(u32 handle);
  ~GfMenuObjQuestOrder() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjQuestOrder::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjQuestOrder::ListListener) == 0x38, "");

} // namespace gf
