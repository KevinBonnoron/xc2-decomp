#include "gf/menu/gf_menu_str_linker.h"

namespace gf {

GfMenuStrLinker::GfMenuStrLinker(mm::mtl::IAllocator *allocator) : allocator(allocator), strings(), freeIds(), selectStrings() {
  for (u32 i = 0; i < STRING_MAX; i++) {
    freeIds.push_back(i);
  }
}

GfMenuStrLinker::~GfMenuStrLinker() {}

void GfMenuStrLinker::delString(u16 id) {
  if (id < STRING_MAX) {
    strings[id].release();
    freeIds.push_back(id);
  }
}

const ui::UIStr &GfMenuStrLinker::getString(u16 id) {
  if (id < STRING_MAX) {
    return strings[id];
  }
  static ui::UIStr invalid;
  return invalid;
}

void GfMenuStrLinker::addSelectString(const ui::UIStr &string) {
  if (selectStrings.size() != selectStrings.capacity()) {
    selectStrings.push_back(string);
  }
}

void GfMenuStrLinker::clearSelectString() { selectStrings.clear(); }

} // namespace gf
