#include "layer/layer_obj_top_def.h"

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_obj_res_tex.h"

namespace layer {

void LayerObjTopDef::updateResCheck() {
  if (unknown2c0.updateTexutre(unknown280, unknown278)) {
    unknowna8 &= ~0x400000;
    GrlSurfaceFormat format = unknown280[0]->getFormat();
    if (format == GRL_SURFACE_FORMAT_BPTC_UNORM || format == GRL_SURFACE_FORMAT_BPTC_SIGNED_FLOAT || format == GRL_SURFACE_FORMAT_BPTC_UNSIGNED_FLOAT) {
      unknowna8 |= 0x400000;
    }
  }
}

} // namespace layer
