#include "dr/dr_ibl_obj.h"

#include "grlib/cglib_texture_buffer.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ml {

bool DrIBLObj::hasValidIBL() const { return unknown38 != nullptr; }

u32 DrIBLObj::getIBLNum() const {
  if (unknown00 != nullptr) {
    return unknown00->unknown08;
  }
  return 0;
}

u32 DrIBLObj::getPriority() const {
  if (unknown38 != nullptr) {
    return unknown38->unknown08;
  }
  return 0xffffffff;
}

grlib::CGLibTextureBuffer *DrIBLObj::getAlbedoTexture() const {
  if (unknown38 != nullptr) {
    return &unknown48[unknown38->unknown06];
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::getNormalTexture() const {
  if (unknown38 != nullptr) {
    return &unknown50[unknown38->unknown06];
  }
  return nullptr;
}

const char *DrIBLObj::getIBLName(u32 index) const {
  if (unknown08 != nullptr) {
    return reinterpret_cast<const char *>(unknown00) + unknown08[index].unknown0c;
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::debug_getAlbedoTexture(u32 index) const {
  if ((unknown58 & 1) == 0) {
    return nullptr;
  }
  if (index < unknown40) {
    return unknown48 + index;
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::debug_getNormalTexture(u32 index) const {
  if ((unknown58 & 1) == 0) {
    return nullptr;
  }
  if (index < unknown40) {
    return unknown50 + index;
  }
  return nullptr;
}

} // namespace ml

template mm::mtl::FixedList<ml::DrIBLObj *, 32>::iterator mm::mtl::FixedList<ml::DrIBLObj *, 32>::erase(mm::mtl::FixedList<ml::DrIBLObj *, 32>::iterator);
