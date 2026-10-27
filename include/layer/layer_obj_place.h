#pragma once
#include <stddef.h>

#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {
struct LayerResNode;

struct LyrPlaceData {
  u8 _00[0x08];
  u32 unknown08[4]; // Inferred role: offsets of the first source values; original member name unknown.
  u32 unknown18[4]; // Inferred role: offsets of the second source values; original member name unknown.
  u8 unknown28[4];  // Inferred role: value types; original member name unknown.
  u8 unknown2c[4];  // Inferred role: format indices; original member name unknown.
  u16 unknown30;    // Inferred role: format count; original member name unknown.
};

static_assert(offsetof(LyrPlaceData, unknown28) == 0x28, "");
static_assert(offsetof(LyrPlaceData, unknown30) == 0x30, "");

class LayerObjPlace : public LayerObjWork {
public:
  void updatePlace();
  f32 updateGblFrm();
  void calcNodePos(f32 frame);
  void calcPartsNodePos(LayerResNode *node, const LyrPlaceData *data, s32 index);
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

  static void (*s_resCallPlaceFormat[])(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void (*s_resCallPlaceAnim[])(LayerResNode *node, const u8 *data, u32 index);
};

} // namespace layer
