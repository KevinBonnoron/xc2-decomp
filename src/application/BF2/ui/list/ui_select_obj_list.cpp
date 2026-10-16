#include "ui/list/ui_select_obj_list.h"

#include "framework/memory/framework_memory.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UISelectObjList::UISelectObjList() {}

UISelectObjList::~UISelectObjList() { ; }

UISelectObjList *UISelectObjList::create(const CreateParam &param) {
// __LINE__ is the line argument of the operator new call.
#line 38
  UISelectObjList *list = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UISelectObjList();
  SetupParam setup;
  setup.pageRowSize = 32;
  list->setup(param.allocator, setup);
  list->addRef();
  return list;
}

void UISelectObjList::setObject(u32 index, u32 handle) {
  if (index < getSize() && index < contents.size()) {
    contents[index] = handle;
  }
}

void UISelectObjList::addObject(u32 handle) {
  for (u32 i = 0; i < getSize(); i++) {
    if (getContents(i) == handle) {
      return;
    }
  }
  addContents(handle);
}

void UISelectObjList::insertObject(u32 index, u32 handle) {
  for (u32 i = 0; i < getSize(); i++) {
    if (getContents(i) == handle) {
      return;
    }
  }

  if (index < getSize()) {
    u32 *it = contents.begin();
    for (u32 i = 0; i < index; i++) {
      ++it;
    }
    contents.insert(it, handle);
    addSize(1);
    contentsChanged = true;
  } else {
    addContents(handle);
  }
}

void UISelectObjList::delObject(u32 handle) {
  for (u32 i = 0; i < getSize(); i++) {
    if (getContents(i) == handle) {
      contents.erase(contents.begin() + i);
      subSize(1);
      contentsChanged = true;
      return;
    }
  }
}

void UISelectObjList::pickupObject(u32 parent, const char *format, u32 start) {
  UIObjectAcc acc(parent);
  if (acc.isValid()) {
    mm::mtl::FixStr<32> name;
    u32 number = start;
    name.format(format, number);
    u32 child = acc.searchChild(name.c_str());
    while (child != 0) {
      addContents(child);
      name.format(format, ++number);
      child = acc.searchChild(name.c_str());
    }
  }
}

u32 UISelectObjList::getObject(u32 index) { return getContents(index); }

u32 UISelectObjList::getSelectObject() { return getContents(getIndex(false)); }

} // namespace ui
