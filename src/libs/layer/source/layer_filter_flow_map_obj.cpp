#include "layer/layer_filter_flow_map_obj.h"

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

namespace {

struct unknown001 {
  u8 _00[0x24];
  u32 unknown24; // Inferred role: offset of the flow map texture resource; original member name unknown.
};

static_assert(offsetof(unknown001, unknown24) == 0x24, "");

} // namespace

LayerFilterFlowMapObj::LayerFilterFlowMapObj(u32 width, u32 height, const void *data) {
  m_filterType = 2;
  unknown430 = 0.2f;
  unknown434 = 0.02f;
  unknown428 = width;
  unknown42c = height;
  unknown438 = 0.0f;
  unknown43c = 0.5f;
  unknown418 = data;
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown24 != 0) {
    unknown420 = LayerManager::get()->unknown58->unknown40->createTextureObj(static_cast<const u8 *>(data) + header->unknown24);
  }
}

LayerFilterFlowMapObj::~LayerFilterFlowMapObj() {
  if (unknown420 != nullptr) {
    unknown420->release();
    unknown420 = nullptr;
  }
}

void LayerFilterFlowMapObj::resourceInit() {
  unknown18.setTextureInfo(static_cast<f32>(unknown428), static_cast<f32>(unknown42c), GRL_SURFACE_FORMAT_R11G11B10F, false, 0);
  unknown3e0.setup(LayerObjUtil::getUniformBlockSizeAlOff(LAYER_UNI_TYPE_UNKNOWN_10));
  unknown420->setupResource();
}

grlib::CGLibTextureBuffer *LayerFilterFlowMapObj::getTexture() { return unknown18.unknown70; }

void LayerFilterFlowMapObj::setParameter(f32 speed, f32 strength) {
  unknown430 = speed;
  unknown434 = strength;
}

} // namespace layer
