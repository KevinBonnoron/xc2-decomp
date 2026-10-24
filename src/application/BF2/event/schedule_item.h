#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace event {

class ScheduleItem {
public:
  typedef void (ScheduleItem::*Func)(gf::GF_OBJ_HANDLE *handle);

  static const f32 FADE_SP;

  ScheduleItem(gf::GF_OBJ_HANDLE *handle);
  virtual ~ScheduleItem() {}
  void clear();
  void update();
  void fadeout();
  bool hasItem();
  void func_fadeout(gf::GF_OBJ_HANDLE *handle);
  void fadein();
  void func_fadein(gf::GF_OBJ_HANDLE *handle);
  void func_fadewait(gf::GF_OBJ_HANDLE *handle);
  bool isFading() const { return unknown10 == &ScheduleItem::func_fadeout || unknown10 == &ScheduleItem::func_fadein; }

  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  Func unknown10;               // Inferred role: func; original member name unknown.
  f32 unknown20;                // Inferred role: alpha; original member name unknown.
};

static_assert(sizeof(ScheduleItem) == 0x28, "");

} // namespace event
