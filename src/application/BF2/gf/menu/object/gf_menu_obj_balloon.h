#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_bdat.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct GF_OBJ_HANDLE;

class GfMenuObjBalloon {
public:
  struct NextParam {
    u8 *bdat;
    u32 textId;
  };

  struct OpenParam : NextParam {
    OpenParam() : nameBdat(nullptr), nameId(0) {}

    u8 *nameBdat;
    u32 nameId;
    GF_OBJ_HANDLE *handle;
    u8 _28[0x30 - 0x28];
    MenuOffset offset;
    u8 _48[0x50 - 0x48];
  };

  struct OpenSelectParam : OpenParam {
    OpenSelectParam() : selectBdat(nullptr) {}

    u8 *selectBdat;
    mm::mtl::FixedVector<u32, 2> selectIds;
    u8 _68[0x70 - 0x68];
  };

  struct OpenSelectBoxParam : NextParam {
    u8 *selectBdat;
    mm::mtl::FixedVector<u32, 3> selectIds;
  };

  struct OpenSelectMoneyParam {
    OpenSelectMoneyParam() : textId(0), messageId(0) {}

    u8 *bdat;
    u32 textId;
    u16 messageId;
    mm::mtl::FixedVector<u32, 3> moneys;
    mm::mtl::FixedVector<u16, 3> nameIds;
  };

  struct OpenGetItemParam {
    u32 item;
  };

  static void openEvent(GfMenuCallContext *context, const OpenParam &param);
  static void openEventSelect(GfMenuCallContext *context, const OpenSelectParam &param);
  static void close(GfMenuCallContext *context, bool isImmediate);
  static void nextEvent(GfMenuCallContext *context, const NextParam &param);
  static void openEventSelectBox(GfMenuCallContext *context, const OpenSelectBoxParam &param);
  static void openEventSelectMoney(GfMenuCallContext *context, const OpenSelectMoneyParam &param);
  static bool openGetItem(GfMenuCallContext *context, const OpenGetItemParam &param);
};

static_assert(offsetof(GfMenuObjBalloon::OpenParam, nameBdat) == 0x10, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, handle) == 0x20, "");
static_assert(offsetof(GfMenuObjBalloon::OpenParam, offset) == 0x30, "");
static_assert(sizeof(GfMenuObjBalloon::OpenParam) == 0x50, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectParam, selectIds) == 0x58, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectParam) == 0x70, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectBoxParam, selectIds) == 0x18, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectBoxParam) == 0x30, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, messageId) == 0x0c, "");
static_assert(offsetof(GfMenuObjBalloon::OpenSelectMoneyParam, nameIds) == 0x28, "");
static_assert(sizeof(GfMenuObjBalloon::OpenSelectMoneyParam) == 0x38, "");

} // namespace gf
