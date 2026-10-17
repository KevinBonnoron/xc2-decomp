#include "gf/menu/list/gf_menu_arts_list.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuArtsList::GfMenuArtsList() {}

GfMenuArtsList::~GfMenuArtsList() { ; }

GfMenuArtsList *GfMenuArtsList::create() {
  // __LINE__ must be 35 as in the original source: it is the line argument of operator new.
#line 35
  GfMenuArtsList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuArtsList();
  list->addRef();
  return list;
}

} // namespace gf
