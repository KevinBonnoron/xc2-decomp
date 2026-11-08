#include "gf/menu/object/gf_menu_obj_sort.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x83;

GfMenuObjSort::GfMenuObjSort(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(0) {}

GfMenuObjSort::~GfMenuObjSort() { ; }

void GfMenuObjSort::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSort::update() {
  if (unknown24 != 0) {
    ui::UIObjectAcc acc(unknown24);
    if (!acc.isValid() || acc.isTerm()) {
      unknown155(unknown001, GfMenuTypes::unknown003_34);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjSort::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjSort::refreshItem(u32 selected, u32 count) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < count; i++) {
    name.format("TXT_list_name@%02d", i + 1);
    ui::UIObjectAcc(main.unknown10, name.c_str()).setAlpha(selected == i ? 0.0f : 1.0f);
    name.format("TXT_list_select@%02d", i + 1);
    ui::UIObjectAcc(main.unknown10, name.c_str()).setAlpha(selected == i ? 1.0f : 0.0f);
  }
}

u16 GfMenuObjSort::getSortID(u16 id, u16 index) {
  u32 sortID = 0;
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SORT_TABLE);
  if (GfMenuBdat::isValidBdatID(bdat, id)) {
    mm::mtl::FixStr<32> name;
    name.format("sort_type%d", index + 1);
    if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
      sortID = Bdat::getVal(bdat, name.c_str(), id).valueU32;
    }
  }
  return sortID;
}

void GfMenuObjSort::setSortLabelText(u16 id, u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (GfMenuBdat::isValidBdatID(GfDataBdat::getFP(BDAT_MNU_MSG_ITEM_SORT), id)) {
    u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_SORT, id);
    acc.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_SORT_CATEGORY), textId));
  }
}

} // namespace gf
