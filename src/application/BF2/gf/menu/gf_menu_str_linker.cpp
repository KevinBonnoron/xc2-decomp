#include "gf/menu/gf_menu_str_linker.h"

namespace gf {

GfMenuStrLinker::GfMenuStrLinker(mm::mtl::IAllocator *allocator) : unknown08(allocator), unknown10(), unknownc10(), unknowne18() {
  for (u32 i = 0; i < STRING_MAX; i++) {
    unknownc10.push_back(i);
  }
}

GfMenuStrLinker::~GfMenuStrLinker() {}

void GfMenuStrLinker::delString(u16 id) {
  if (id < STRING_MAX) {
    unknown10[id].release();
    unknownc10.push_back(id);
  }
}

const ui::UIStr &GfMenuStrLinker::getString(u16 id) {
  if (id < STRING_MAX) {
    return unknown10[id];
  }
  static ui::UIStr invalid;
  return invalid;
}

void GfMenuStrLinker::addSelectString(const ui::UIStr &string) {
  if (unknowne18.size() != unknowne18.capacity()) {
    unknowne18.push_back(string);
  }
}

void GfMenuStrLinker::clearSelectString() { unknowne18.clear(); }

} // namespace gf
