// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/menu/list/gf_menu_quest_list.cpp.
#include "gf/menu/list/gf_menu_quest_list.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuQuestList::GfMenuQuestList() {}

GfMenuQuestList::~GfMenuQuestList() { ; }

GfMenuQuestList *GfMenuQuestList::create() {
  // __LINE__ must be 41 as in the original source: it is the line argument of operator new.
#line 41
  GfMenuQuestList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuQuestList();
  list->addRef();
  return list;
}

} // namespace gf
