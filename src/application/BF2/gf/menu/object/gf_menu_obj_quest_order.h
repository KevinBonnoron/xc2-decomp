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
    ListListener(GfMenuObjQuestOrder *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjQuestOrder *unknown20; // Inferred role: owner; original member name unknown.
    u8 _28[0x38 - 0x28];
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
