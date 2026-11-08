#include "gf/field/gf_dropitem_params.h"

#include "bdat.h"
#include "gf/gf_allocator.h"

// Vector<GfDropitemParam>::resize is instantiated in gf_dropitem_param.cpp.
extern template void mm::mtl::Vector<gf::GfDropitemParam>::resize(size_t);

namespace gf {

GfDropitemParams::GfDropitemParams() { unknown08.setAllocator(getAllocator(ALLOCATOR_DEFAULT)); }

GfDropitemParams::~GfDropitemParams() { unknown08.destroy(); }

bool GfDropitemParams::isBdatIdValid(u32 bdatId) const {
  if (bdatId < unknown30) {
    return false;
  }
  return bdatId - unknown30 < unknown08.size();
}

const GfDropitemParam &GfDropitemParams::getParamByBdatId(u32 bdatId) const { return unknown08[bdatId - unknown30]; }

void GfDropitemParams::create() {
  dispose();
  update();
}

void GfDropitemParams::dispose() {
  unknown30 = 0;
  unknown08.clear();
}

void GfDropitemParams::update() {
  if (unknown08.size() == 0) {
    u8 *bdat = Bdat::isExistFP("RSC_dropitemParam");
    if (bdat != nullptr) {
      unknown08.resize(Bdat::getIdCount(bdat));
      unknown30 = Bdat::getIdTop(bdat);
      int count = Bdat::getIdCount(bdat);
      for (int i = 0; i < count; i++) {
        int id = i + unknown30;
        unknown08[i].loadFromBdat(id);
      }
    }
  }
}

} // namespace gf
