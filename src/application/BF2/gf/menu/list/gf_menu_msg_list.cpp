#include "gf/menu/list/gf_menu_msg_list.h"

#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {

GfMenuMsgList::GfMenuMsgList() : nameBdat(nullptr), msgBdat(nullptr) {}

GfMenuMsgList::~GfMenuMsgList() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

GfMenuMsgList *GfMenuMsgList::create() {
  // __LINE__ must be 41 as in the original source: it is the line argument of operator new.
#line 41
  GfMenuMsgList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuMsgList();
  list->addRef();
  return list;
}

void GfMenuMsgList::setBdat(u32 nameBdatId, u32 msgBdatId) {
  u8 *names = nullptr;
  if (nameBdatId != 0) {
    names = GfDataBdat::getFP(nameBdatId);
    if (names == nullptr) {
      return;
    }
  }
  u8 *msgs = GfDataBdat::getFP(msgBdatId);
  if (msgs != nullptr) {
    nameBdat = names;
    msgBdat = msgs;
  }
}

} // namespace gf
