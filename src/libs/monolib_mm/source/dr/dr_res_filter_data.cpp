#include "dr/dr_res_filter_data.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_texture_buffer.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResFilterData::DrResFilterData(DrMan *man) {
  unknown00 = man;
  unknown100 = 0;
  unknownf0 = nullptr;
  unknownf8 = 0;
  for (int i = 0; i < 4; i++) {
    unknown10[i].unknown20 = 0;
    unknown10[i].unknown22 = 0;
    unknown10[i].unknown24 = 0;
    unknown10[i].unknown26 = 0;
    unknown10[i].unknown2c = 1000.0f;
    unknown10[i].unknown30 = 60.0f;
    unknown10[i].unknown34 = 1.0f;
  }
}

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

void DrResFilterData::update(int index) {
  DrMan *man = DrMan::get();
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  bool isColTblOn = postParm->getColTblOn();
  if (index == 0) {
    if (!isColTblOn || !postParm->m_colorFilterTransZ) {
      setFilterTex(0, postParm->unknown26c, postParm->unknown270);
    } else {
      set2LayerFilterTex(0, postParm->unknown26c, postParm->unknown278, postParm->unknown270);
    }
  } else if (isColTblOn) {
    if (!postParm->m_colorFilterTransZ) {
      setFilterTex(index, postParm->unknown26c, postParm->unknown270);
    } else {
      set2LayerFilterTex(index, postParm->unknown26c, postParm->unknown278, postParm->unknown270);
    }
  }
  updateColorFileter(index);
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
