#include "layer/layer_obj_place.h"

#include "layer/layer_res_node.h"
#include "mm_math/mm_vec2.h"

namespace layer {

void LayerObjPlace::placeReset_Off(LayerResNode *node) {}

void LayerObjPlace::placeReset_Pos(LayerResNode *node) {
  node->unknown00.x = 0.0f;
  node->unknown00.y = 0.0f;
}

void LayerObjPlace::placeReset_Srt(LayerResNode *node) {
  node->unknown10.x = node->unknown10.y = 0.0f;
  node->unknown08.x = node->unknown08.y = 1.0f;
}

void LayerObjPlace::placeReset_Pos_Srt(LayerResNode *node) {
  node->unknown00.x = 0.0f;
  node->unknown00.y = 0.0f;
  node->unknown08.x = 1.0f;
  node->unknown08.y = 1.0f;
  node->unknown10.x = 0.0f;
  node->unknown10.y = 0.0f;
}

void LayerObjPlace::placeReset_Col(LayerResNode *node) {
  node->unknown18[0] = 1.0f;
  node->unknown18[1] = 1.0f;
  node->unknown18[2] = 1.0f;
  node->unknown18[3] = 1.0f;
  node->unknown28[0] = 0.0f;
  node->unknown28[1] = 0.0f;
  node->unknown28[2] = 0.0f;
}

void LayerObjPlace::placeReset_Pos_Col(LayerResNode *node) {
  node->unknown18[0] = 1.0f;
  node->unknown18[1] = 1.0f;
  node->unknown18[2] = 1.0f;
  node->unknown18[3] = 1.0f;
  node->unknown28[0] = 0.0f;
  node->unknown28[1] = 0.0f;
  node->unknown28[2] = 0.0f;
  node->unknown00.x = 0.0f;
  node->unknown00.y = 0.0f;
}

void LayerObjPlace::placeReset_Srt_Col(LayerResNode *node) {
  node->unknown18[0] = 1.0f;
  node->unknown18[1] = 1.0f;
  node->unknown18[2] = 1.0f;
  node->unknown18[3] = 1.0f;
  node->unknown28[0] = 0.0f;
  node->unknown28[1] = 0.0f;
  node->unknown28[2] = 0.0f;
  node->unknown10.x = node->unknown10.y = 0.0f;
  node->unknown08.x = node->unknown08.y = 1.0f;
}

void LayerObjPlace::placeReset_Pos_Srt_Col(LayerResNode *node) {
  node->unknown18[0] = 1.0f;
  node->unknown18[1] = 1.0f;
  node->unknown18[2] = 1.0f;
  node->unknown18[3] = 1.0f;
  node->unknown28[0] = 0.0f;
  node->unknown28[1] = 0.0f;
  node->unknown28[2] = 0.0f;
  node->unknown00.x = 0.0f;
  node->unknown00.y = 0.0f;
  node->unknown08.x = 1.0f;
  node->unknown08.y = 1.0f;
  node->unknown10.x = 0.0f;
  node->unknown10.y = 0.0f;
}

void LayerObjPlace::placeFormat_u8(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, values[index]); }

void LayerObjPlace::placeFormat_u16(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, reinterpret_cast<const u16 *>(values)[index]); }

void LayerObjPlace::placeFormat_u32(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index) { s_resCallPlaceAnim[type](node, data, reinterpret_cast<const u32 *>(values)[index]); }

void LayerObjPlace::placeAnm_Pos(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->unknown00.x = values[0];
  node->unknown00.y = values[1];
}

void LayerObjPlace::placeAnm_Scl(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->unknown08.x = values[0];
  node->unknown08.y = values[1];
}

void LayerObjPlace::placeAnm_Rot(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 2;
  node->unknown10.x = values[0];
  node->unknown10.y = values[1];
}

void LayerObjPlace::placeAnm_Srt(LayerResNode *node, const u8 *data, u32 index) {
  const f32 *values = reinterpret_cast<const f32 *>(data) + index * 4;
  node->unknown10.x = values[0];
  node->unknown10.y = values[1];
  node->unknown08.x = values[2];
  node->unknown08.y = values[3];
}

void LayerObjPlace::placeAnm_AddCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 4;
  node->unknown28[0] = values[0] * (1.0f / 255.0f);
  node->unknown28[1] = values[1] * (1.0f / 255.0f);
  node->unknown28[2] = values[2] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_MulCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 4;
  node->unknown18[0] = values[0] * (1.0f / 255.0f);
  node->unknown18[1] = values[1] * (1.0f / 255.0f);
  node->unknown18[2] = values[2] * (1.0f / 255.0f);
  node->unknown18[3] = values[3] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_AllCol(LayerResNode *node, const u8 *data, u32 index) {
  const u8 *values = data + index * 8;
  node->unknown18[0] = values[0] * (1.0f / 255.0f);
  node->unknown18[1] = values[1] * (1.0f / 255.0f);
  node->unknown18[2] = values[2] * (1.0f / 255.0f);
  node->unknown18[3] = values[3] * (1.0f / 255.0f);
  node->unknown28[0] = values[4] * (1.0f / 255.0f);
  node->unknown28[1] = values[5] * (1.0f / 255.0f);
  node->unknown28[2] = values[6] * (1.0f / 255.0f);
}

void LayerObjPlace::placeAnm_Blend(LayerResNode *node, const u8 *data, u32 index) {
  node->unknown37 = index;
  node->unknown36 |= 2;
}

void LayerObjPlace::updatePlace() {
  f32 frame = updateGblFrm();
  calcNodePos(frame);
}

void LayerObjPlace::calcPartsNodePos(LayerResNode *node, const LyrPlaceData *data, s32 index) {
  u32 count = data->unknown30;
  for (u32 i = 0; i != count; i++) {
    s_resCallPlaceFormat[data->unknown2c[i]](node, data->unknown28[i], unknown298->unknown20 + data->unknown08[i], unknown298->unknown20 + data->unknown18[i], index);
  }
}

} // namespace layer
