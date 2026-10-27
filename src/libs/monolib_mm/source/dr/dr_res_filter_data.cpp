#include "dr/dr_res_filter_data.h"

#include "grlib/cglib_texture_buffer.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResFilterData::~DrResFilterData() { clear(); }

void DrResFilterData::clear() {
  if (unknownf8 != 0) {
    for (int i = 0; i < unknownf8; i++) {
      unknownf0[i].~CGLibTextureBuffer();
    }
    if (unknownf0 != nullptr) {
      mtl::MemManager::deallocate(unknownf0, 0, false);
      unknownf0 = nullptr;
    }
    unknownf8 = 0;
  }
}

void DrResFilterData::set2LayerFilterTex(int index, int first, int second, f32 time) {
  unknown10[index].unknown20 = first;
  unknown10[index].unknown22 = second;
  unknown10[index].unknown30 = time;
}

void DrResFilterData::setFilterTex(int index, int texture, f32 time) {
  unknown10[index].unknown22 = texture;
  unknown10[index].unknown20 = texture;
  unknown10[index].unknown30 = time;
}

grlib::CGLibTextureBuffer *DrResFilterData::findFilterTexture(u32 id) const {
  for (int i = 0; i < unknownf8; i++) {
    if (unknown08[i].unknown08 == id) {
      return &unknownf0[i];
    }
  }
  return unknownf0;
}

} // namespace ml
