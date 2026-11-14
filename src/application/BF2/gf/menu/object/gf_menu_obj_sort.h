#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjSort : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjSort *owner) : unknown0c(0), unknown10(0), _14(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: number of listed sort types; original member name unknown.
    u32 unknown10; // Inferred role: selected index; original member name unknown.
    u8 _14[0x1c - 0x14];
    GfMenuObjSort *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjSort(u32 handle);
  ~GfMenuObjSort() override;
  static void open(u32 object, u32 label, u16 type, u16 index);
  static void close();
  static u16 getSortID(u16 id, u16 index);
  static void setSortLabelText(u16 id, u32 handle);
  void refreshItem(u32 selected, u32 count);
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24; // Inferred role: handle of the sort object; original member name unknown.
  u32 unknown28; // Inferred role: handle of the label object showing the selected sort; original member name unknown.
  u32 unknown2c; // Inferred role: sort table id; original member name unknown.
  u32 unknown30; // Inferred role: sort type count; original member name unknown.
};

static_assert(offsetof(GfMenuObjSort, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjSort, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjSort::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjSort::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjSort::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjSort::MainListener) == 0x28, "");

} // namespace gf
