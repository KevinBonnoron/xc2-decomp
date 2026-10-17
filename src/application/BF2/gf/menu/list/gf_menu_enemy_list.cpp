#include "gf/menu/list/gf_menu_enemy_list.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuEnemyList::GfMenuEnemyList() {}

GfMenuEnemyList::~GfMenuEnemyList() { ; }

GfMenuEnemyList *GfMenuEnemyList::create() {
  // __LINE__ must be 40 as in the original source: it is the line argument of operator new.
#line 40
  GfMenuEnemyList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuEnemyList();
  list->addRef();
  return list;
}

} // namespace gf
