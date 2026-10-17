#pragma once
#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {
struct LayerResNode;

class LayerObjPlace : public LayerObjWork {
public:
  static void placeReset_Off(LayerResNode *node);
  static void placeReset_Pos(LayerResNode *node);
  static void placeReset_Srt(LayerResNode *node);
  static void placeReset_Pos_Srt(LayerResNode *node);
  static void placeReset_Col(LayerResNode *node);
  static void placeReset_Pos_Col(LayerResNode *node);
  static void placeReset_Srt_Col(LayerResNode *node);
  static void placeReset_Pos_Srt_Col(LayerResNode *node);
  static void placeFormat_u8(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeFormat_u16(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeFormat_u32(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeAnm_Pos(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Scl(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Rot(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Srt(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_AddCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_MulCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_AllCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Blend(LayerResNode *node, const u8 *data, u32 index);

  static void (*s_resCallPlaceAnim[])(LayerResNode *node, const u8 *data, u32 index);
};

} // namespace layer
