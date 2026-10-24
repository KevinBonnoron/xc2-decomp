#include "layer/layer_obj_place.h"

#include "layer/layer_res_node.h"
#include "mm_math/mm_vec2.h"

namespace layer {

void LayerObjPlace::placeReset_Off(LayerResNode *node) {}

void LayerObjPlace::placeReset_Pos(LayerResNode *node) {
  node->pos.x = 0.0f;
  node->pos.y = 0.0f;
}

void LayerObjPlace::placeReset_Srt(LayerResNode *node) {
  node->rot.x = node->rot.y = 0.0f;
  node->scl.x = node->scl.y = 1.0f;
}

void LayerObjPlace::placeReset_Pos_Srt(LayerResNode *node) {
  node->pos.x = 0.0f;
  node->pos.y = 0.0f;
  node->scl.x = 1.0f;
  node->scl.y = 1.0f;
  node->rot.x = 0.0f;
  node->rot.y = 0.0f;
}

void LayerObjPlace::placeReset_Col(LayerResNode *node) {
  node->mulColor[0] = 1.0f;
  node->mulColor[1] = 1.0f;
  node->mulColor[2] = 1.0f;
  node->mulColor[3] = 1.0f;
  node->addColor[0] = 0.0f;
  node->addColor[1] = 0.0f;
  node->addColor[2] = 0.0f;
}

void LayerObjPlace::placeReset_Pos_Col(LayerResNode *node) {
  node->mulColor[0] = 1.0f;
  node->mulColor[1] = 1.0f;
  node->mulColor[2] = 1.0f;
  node->mulColor[3] = 1.0f;
  node->addColor[0] = 0.0f;
  node->addColor[1] = 0.0f;
  node->addColor[2] = 0.0f;
  node->pos.x = 0.0f;
  node->pos.y = 0.0f;
}

void LayerObjPlace::placeReset_Srt_Col(LayerResNode *node) {
  node->mulColor[0] = 1.0f;
  node->mulColor[1] = 1.0f;
  node->mulColor[2] = 1.0f;
  node->mulColor[3] = 1.0f;
  node->addColor[0] = 0.0f;
  node->addColor[1] = 0.0f;
  node->addColor[2] = 0.0f;
  node->rot.x = node->rot.y = 0.0f;
  node->scl.x = node->scl.y = 1.0f;
}

void LayerObjPlace::placeReset_Pos_Srt_Col(LayerResNode *node) {
  node->mulColor[0] = 1.0f;
  node->mulColor[1] = 1.0f;
  node->mulColor[2] = 1.0f;
  node->mulColor[3] = 1.0f;
  node->addColor[0] = 0.0f;
  node->addColor[1] = 0.0f;
  node->addColor[2] = 0.0f;
  node->pos.x = 0.0f;
  node->pos.y = 0.0f;
  node->scl.x = 1.0f;
  node->scl.y = 1.0f;
  node->rot.x = 0.0f;
  node->rot.y = 0.0f;
}

void LayerObjPlace::placeFormat_u8(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, values[index]); }

void LayerObjPlace::placeFormat_u16(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, reinterpret_cast<const u16 *>(values)[index]); }

void LayerObjPlace::placeFormat_u32(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, reinterpret_cast<const u32 *>(values)[index]); }

void LayerObjPlace::placeAnm_Pos(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->pos.x = values[0];
  node->pos.y = values[1];
}

void LayerObjPlace::placeAnm_Scl(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->scl.x = values[0];
  node->scl.y = values[1];
}

void LayerObjPlace::placeAnm_Rot(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->rot.x = values[0];
  node->rot.y = values[1];
}

void LayerObjPlace::placeAnm_Srt(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 4;
  node->rot.x = values[0];
  node->rot.y = values[1];
  node->scl.x = values[2];
  node->scl.y = values[3];
}

void LayerObjPlace::placeAnm_AddCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 4;
  node->addColor[0] = values[0] * (1.0f / 255.0f);
  node->addColor[1] = values[1] * (1.0f / 255.0f);
  node->addColor[2] = values[2] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_MulCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 4;
  node->mulColor[0] = values[0] * (1.0f / 255.0f);
  node->mulColor[1] = values[1] * (1.0f / 255.0f);
  node->mulColor[2] = values[2] * (1.0f / 255.0f);
  node->mulColor[3] = values[3] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_AllCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 8;
  node->mulColor[0] = values[0] * (1.0f / 255.0f);
  node->mulColor[1] = values[1] * (1.0f / 255.0f);
  node->mulColor[2] = values[2] * (1.0f / 255.0f);
  node->mulColor[3] = values[3] * (1.0f / 255.0f);
  node->addColor[0] = values[4] * (1.0f / 255.0f);
  node->addColor[1] = values[5] * (1.0f / 255.0f);
  node->addColor[2] = values[6] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_Blend(LayerResNode *node, const u8 *data, u32 index) {
  node->blend = index;
  node->flags |= 2;
}

} // namespace layer
