#include "gf/menu/gf_menu_str_linker.h"

namespace gf {

GfMenuStrLinker::GfMenuStrLinker(mm::mtl::IAllocator *allocator) : unknown08(allocator), unknown10(), unknownc10(), unknowne18() {
  for (u32 i = 0; i < STRING_UNKNOWN_128; i++) {
    unknownc10.push_back(i);
  }
}

GfMenuStrLinker::~GfMenuStrLinker() {}

u16 GfMenuStrLinker::addString(const ui::UIStr &string) {
  u32 id = unknownc10.front();
  unknown10[id].copy(string);
  unknownc10.erase(unknownc10.begin());
  return id;
}

void GfMenuStrLinker::delString(u16 id) {
  if (id < STRING_UNKNOWN_128) {
    unknown10[id].release();
    unknownc10.push_back(id);
  }
}

const ui::UIStr &GfMenuStrLinker::getString(u16 id) {
  if (id < STRING_UNKNOWN_128) {
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
