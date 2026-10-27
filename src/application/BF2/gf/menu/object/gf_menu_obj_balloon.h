#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct GF_OBJ_HANDLE;

class GfMenuObjBalloon : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  struct NextParam {
    u8 *unknown00; // Inferred role: bdat; original member name unknown.
    u32 unknown08; // Inferred role: text id; original member name unknown.
  };

  struct OpenParam : NextParam {
    OpenParam() : unknown10(nullptr), unknown18(0) {}

    u8 *unknown10;            // Inferred role: name bdat; original member name unknown.
    u32 unknown18;            // Inferred role: name id; original member name unknown.
    GF_OBJ_HANDLE *unknown20; // Inferred role: handle; original member name unknown.
    u8 _28[0x30 - 0x28];
    MenuOffset unknown30; // Inferred role: offset; original member name unknown.
    u8 _48[0x50 - 0x48];
  };

  struct OpenSelectParam : OpenParam {
    OpenSelectParam() : unknown50(nullptr) {}

    u8 *unknown50;                          // Inferred role: select bdat; original member name unknown.
    mm::mtl::FixedVector<u32, 2> unknown58; // Inferred role: select ids; original member name unknown.
    u8 _68[0x70 - 0x68];
  };

  struct OpenSelectBoxParam : NextParam {
    u8 *unknown10;                          // Inferred role: select bdat; original member name unknown.
    mm::mtl::FixedVector<u32, 3> unknown18; // Inferred role: select ids; original member name unknown.
  };

  struct OpenSelectMoneyParam {
    OpenSelectMoneyParam() : unknown08(0), unknown0c(0) {}

    u8 *unknown00;                          // Inferred role: bdat; original member name unknown.
    u32 unknown08;                          // Inferred role: text id; original member name unknown.
    u16 unknown0c;                          // Inferred role: message id; original member name unknown.
    mm::mtl::FixedVector<u32, 3> unknown10; // Inferred role: moneys; original member name unknown.
    mm::mtl::FixedVector<u16, 3> unknown28; // Inferred role: name ids; original member name unknown.
  };

  struct OpenGetItemParam {
    u32 unknown00; // Inferred role: item; original member name unknown.
  };

  static void openEvent(GfMenuCallContext *context, const OpenParam &param);
  static void openEventSelect(GfMenuCallContext *context, const OpenSelectParam &param);
  static void close(GfMenuCallContext *context, bool isImmediate);
  static void nextEvent(GfMenuCallContext *context, const NextParam &param);
  static void openEventSelectBox(GfMenuCallContext *context, const OpenSelectBoxParam &param);
  static void openEventSelectMoney(GfMenuCallContext *context, const OpenSelectMoneyParam &param);
  static bool openGetItem(GfMenuCallContext *context, const OpenGetItemParam &param);
};

static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjBalloon::OpenParam) == 0x50, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectParam, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectParam) == 0x70, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectBoxParam, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectBoxParam) == 0x30, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectMoneyParam) == 0x38, "");

} // namespace gf
