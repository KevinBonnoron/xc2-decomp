#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjExpGet : public GfMenuObject {
public:
  // Layout from open, which reads it, and from the copy the queued ExpGetInfo keeps.
  struct OpenParam {
    int unknown00; // Inferred role: kind of gain (0 exp, 1 sp, 2 wp, 3 level up, from setupScreen); original member name unknown.
    int unknown04; // Inferred role: amount, open does nothing when 0; original member name unknown.
    u8 unknown08;  // Inferred role: bonus flag; original member name unknown.
    u8 _09[0x10 - 0x09];
    GF_OBJ_HANDLE *unknown10; // Inferred role: handle of the character; original member name unknown.
    u32 unknown18;            // Inferred role: value sent to the object as a 16-bit word; original member name unknown.
  };

  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base. The Queue::erase and push_back
  // instances copy the open parameter in one 32-byte move at 0x10.
  struct ExpGetInfo : GfMenuManyObjects::InfoType {
    OpenParam unknown10; // Inferred role: open parameter of the queued gain; original member name unknown.
  };

  GfMenuObjExpGet(u32 handle);
  ~GfMenuObjExpGet() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
  static void close(u32 handle);
  static void close2(u32 handle);
  static void removeObject(ui::UIObjectAcc acc);
  static void removeObject2(ui::UIObjectAcc acc);
  static void sendOpen(u32 handle, const ExpGetInfo &info);
};

static_assert(offsetof(GfMenuObjExpGet::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjExpGet::OpenParam, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjExpGet::OpenParam) == 0x20, "");
static_assert(offsetof(GfMenuObjExpGet::ExpGetInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjExpGet::ExpGetInfo) == 0x30, "");

} // namespace gf
