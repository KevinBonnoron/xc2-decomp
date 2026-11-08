#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuObjOperationInfo : public GfMenuObject {
public:
  struct DupItem {
    u32 unknown00; // Inferred role: duplicated item object; original member name unknown.
    u32 unknown04; // Inferred role: button icon; original member name unknown.
    u32 unknown08; // Inferred role: text; original member name unknown.
    u16 unknown0c; // Inferred role: sort key; original member name unknown.
    u8 unknown0e;  // Inferred role: displayed flag; original member name unknown.
  };

  struct InputObj {
    struct unknown001 {
      u32 unknown00; // Inferred role: input action; original member name unknown.
      u32 unknown04; // Inferred role: text index; original member name unknown.
    };

    u32 unknown00;                                 // Inferred role: input layer object; original member name unknown.
    mm::mtl::FixedVector<unknown001, 8> unknown08; // Inferred role: text overrides; original member name unknown.
  };

  GfMenuObjOperationInfo(u32 handle);
  ~GfMenuObjOperationInfo() override;
  static void open(u32 handle, u32 unknown0, u32 unknown1, u32 unknown2);
  static void close();
  static void setDisp(bool isDisp);
  static void setGuideText(u32 param0, u32 param1);
  static void setGuideDisp(bool param0);
  static void add(u32 param0, u32 param1, u32 param2, u32 param3);
  static void remove(u32 param0, u32 param1, u32 param2, u32 param3);
  static void changeText(u32 param0, u32 param1, bool param2);
  static void changeText(u32 param0, u32 param1, u32 param2);
  static void setActionEnable(u32 param0, u32 param1, bool param2);
  static void moveGuide(u32 param0, bool param1);
  static void fadeGuide(bool param0);
  static void dupClose(mm::mtl::FixedVector<DupItem, 16> &table);
  static void setupScreen(u32 handle, mm::mtl::FixedVector<DupItem, 16> &table);
  static void dispOffIconTable(mm::mtl::FixedVector<DupItem, 16> &table, u32 index);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<DupItem, 16> unknown28;   // Inferred role: duplicated items; original member name unknown.
  mm::mtl::FixedVector<InputObj, 16> unknown130; // Inferred role: input objects; original member name unknown.
};

static_assert(sizeof(GfMenuObjOperationInfo::DupItem) == 0x10, "");
static_assert(offsetof(GfMenuObjOperationInfo::DupItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjOperationInfo::DupItem, unknown0e) == 0x0e, "");
static_assert(sizeof(GfMenuObjOperationInfo::InputObj) == 0x50, "");
static_assert(offsetof(GfMenuObjOperationInfo::InputObj, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjOperationInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjOperationInfo, unknown130) == 0x130, "");
static_assert(sizeof(GfMenuObjOperationInfo) == 0x638, "");

} // namespace gf
