#include "gf/menu/list/gf_menu_driver_list.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuDriverList::GfMenuDriverList() {}

GfMenuDriverList::~GfMenuDriverList() { ; }

GfMenuDriverList *GfMenuDriverList::create() {
  // __LINE__ must be 42 as in the original source: it is the line argument of operator new.
#line 42
  GfMenuDriverList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuDriverList();
  list->addRef();
  return list;
}

} // namespace gf
