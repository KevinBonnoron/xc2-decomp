#include "dr/dr_shd_lgt_tile_based_dr.h"

#include "mtl/mem_manager.h"

namespace ml {

DrShdLgtTileBasedDr::~DrShdLgtTileBasedDr() {
  if (unknown378 != nullptr) {
    mtl::MemManager::deallocate(unknown378, 0, false);
    unknown378 = nullptr;
  }
}

void DrShdLgtTileBasedDr::createWork() {
  for (int i = 0; i < 4; i++) {
    int num = i == 0 ? 0x100 : 0x10;
    int pntSize = num * 0x30;
    int sptSize = num * 0x40;
    unknown001 &view = unknown18[i];
    view.unknown00.setup(pntSize);
    view.unknown38.setup(sptSize);
    view.unknown70.setup(0x280);
    view.unknowna8.setupArray(0x1b);
    u32 size = 0x10;
    view.unknowna8.unknown0c = 0;
    for (int j = 0; j < 0x1b; j++) {
      view.unknowna8.unknown0c += (size + (-size & 0xff)) * 2;
    }
    view.unknowna8.unknown002();
    for (int j = 0; j < 0x1b; j++) {
      view.unknowna8.unknown0c += view.unknowna8[j].setupArray(size, view.unknowna8.unknown18, view.unknowna8.unknown0c);
    }
  }
  addViewInfo(0);
}

void DrShdLgtTileBasedDr::stockBegin() {
  unknown001 &view = unknown18[unknown08];
  view.unknownd0 = 0;
  view.unknownd4 = 0;
  unknown380 = view.unknown00.m_size;
  unknown384 = view.unknown38.m_size;
  unknown388 = view.unknown00.getBuff();
  unknown390 = view.unknown38.getBuff();
}

void DrShdLgtTileBasedDr::update() {}

void DrShdLgtTileBasedDr::addViewInfo(int cate) {}

void DrShdLgtTileBasedDr::delViewInfo(int cate) {}

void DrShdLgtTileBasedDr::debugRender() {}

void DrShdLgtTileBasedDr::stockEnd() {}

} // namespace ml
