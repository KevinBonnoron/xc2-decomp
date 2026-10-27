#include "layer/layer_res_add_tex_obj.h"

namespace layer {

LayerResAddTexObj::LayerResAddTexObj(const void *data, u32 index) : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(nullptr) {
  unknown22 = 0;
  unknown20 = index;
}

LayerResAddTexObj::LayerResAddTexObj(grlib::CGLibTextureBuffer *texture, u32 index) {
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown22 = 0x400;
  unknown20 = index;
  unknown10 = texture;
  unknown18 = nullptr;
}

} // namespace layer
