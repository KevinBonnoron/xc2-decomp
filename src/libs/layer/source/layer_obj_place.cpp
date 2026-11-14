#include "layer/layer_obj_place.h"

#include <math.h>

#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_res_node.h"
#include "mm_math/mm_pnt.h"

namespace layer {

LayerObjPlace::LayerObjPlace() {}

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

f32 LayerObjPlace::updateGblFrm() {
  f32 add = unknown298->unknown00->unknown1c * LayerManager::get()->unknown80 * unknown1f8;
  if (unknowna8 & 0x200) {
    add = 0.0f;
    unknown2b8 = unknown2b0->unknown00;
  }
  if (!(unknowna8 & 0x40)) {
    unknown2b0->unknown00 += add;
  }
  f32 frame = unknown2b0->unknown00 - unknown2b8;
  if (unknown1f8 >= 0.0f) {
    if (unknown298->unknown80 < unknown2b0->unknown00) {
      if (unknowna8 & 0x80) {
        unknown2b0->unknown00 = unknown298->unknown84 + fmodf(unknown2b0->unknown00, unknown298->unknown80);
      } else {
        unknown2b0->unknown00 = unknown298->unknown80;
      }
    }
  } else if (unknown2b0->unknown00 < 0.0f) {
    if (unknowna8 & 0x80) {
      unknown2b0->unknown00 = unknown298->unknown80 - unknown2b0->unknown00;
    } else {
      unknown2b0->unknown00 = unknown298->unknown84;
    }
  }
  unknown2b8 = unknown2b0->unknown00;
  unknown2b0->unknown04 = unknown2b0->unknown00;
  return frame;
}

void LayerObjPlace::calcNodePos(f32 frame) {
  s32 count = unknown298->unknown40;
  const unknown087 *entry = reinterpret_cast<const unknown087 *>(unknown298->unknown38);
  LayerResNode *node = unknown298->unknown70;
  for (s32 i = 0; i < count; i++, entry++, node++) {
    node->unknown36 &= ~1;
    const LyrPlaceData *place = reinterpret_cast<const LyrPlaceData *>(unknown298->unknown28) + entry->unknown06;
    const unknown086 *keys = reinterpret_cast<const unknown086 *>(unknown298->unknown20 + place->unknown04);
    const LayerResNode *parent = nullptr;
    if (entry->unknown04 != -1) {
      parent = &unknown298->unknown70[entry->unknown04];
      if (parent->unknown36 & 1) {
        node->unknown36 |= 1;
        if (entry->unknown00 & 1) {
          unknown003 *param = unknown2b0 + entry->unknown02;
          param->unknown00 = 0.0f;
          node->unknown34 = 0;
        }
        continue;
      }
    }
    if (place->unknown32 & 2) {
      node->unknown34 = 0;
    } else {
      unknown003 *param = unknown2b0 + entry->unknown02;
      if (entry->unknown00 & 1) {
        param->unknown00 += frame;
        param->unknown04 = param->unknown00;
      }
      if (place->unknown38 < param->unknown04) {
        node->unknown34 = place->unknown00 - 1;
        node->unknown36 |= 1;
        continue;
      }
      if (place->unknown3a > param->unknown04) {
        node->unknown34 = 0;
        node->unknown36 |= 1;
        continue;
      }
      if (entry->unknown00 & 1) {
        if (unknown1f8 >= 0.0f) {
          if (place->unknown3c < param->unknown00) {
            param->unknown00 = fmodf(param->unknown00, place->unknown3c);
            param->unknown04 = param->unknown00;
          }
        } else if (param->unknown00 < 0.0f) {
          param->unknown00 = place->unknown3c - param->unknown00;
          param->unknown04 = param->unknown00;
        }
      }
      if (place->unknown32 & 1) {
        node->unknown34 = 0;
      } else if (place->unknown34 < param->unknown04) {
        node->unknown34 = place->unknown00 - 1;
      } else {
        s32 keyCount = place->unknown00;
        for (s32 k = 0; k < keyCount; k++) {
          if (keys[k].unknown00 <= param->unknown04) {
            node->unknown34 = k;
          }
        }
      }
    }
    if (keys[node->unknown34].unknown02 & 1) {
      node->unknown36 |= 1;
    } else {
      s_resCallPlaceReset[entry->unknown01](node);
      calcPartsNodePos(node, place, node->unknown34);
      if (parent != nullptr) {
        LayerObjUtil::calcPlaceNode(node, parent);
      }
    }
  }
}

void LayerObjPlace::calcPartsNodePos(LayerResNode *node, const LyrPlaceData *data, s32 index) {
  u32 count = data->unknown30;
  for (u32 i = 0; i != count; i++) {
    s_resCallPlaceFormat[data->unknown2c[i]](node, data->unknown28[i], unknown298->unknown20 + data->unknown08[i], unknown298->unknown20 + data->unknown18[i], index);
  }
}

// Evidence: the game places it between LayerObjPlace::calcPartsNodePos and placeReset_Off, and calcNodePos inlines it.
void LayerObjUtil::calcPlaceNode(LayerResNode *node, const LayerResNode *parent) {
  f32 m00 = node->unknown08.x * parent->unknown08.x + node->unknown10.x * parent->unknown10.y;
  f32 m01 = parent->unknown08.x * node->unknown10.y + parent->unknown10.y * node->unknown08.y;
  f32 x = parent->unknown00.x + (parent->unknown08.x * node->unknown00.x + parent->unknown10.y * node->unknown00.y);
  f32 m10 = node->unknown08.x * parent->unknown10.x + node->unknown10.x * parent->unknown08.y;
  f32 m11 = node->unknown10.y * parent->unknown10.x + node->unknown08.y * parent->unknown08.y;
  f32 y = parent->unknown00.y + (node->unknown00.x * parent->unknown10.x + node->unknown00.y * parent->unknown08.y);
  node->unknown10.x = m10;
  node->unknown10.y = m01;
  node->unknown00.x = x;
  node->unknown00.y = y;
  node->unknown08.x = m00;
  node->unknown08.y = m11;
  node->unknown28[0] = parent->unknown28[0] + node->unknown28[0];
  node->unknown28[1] = parent->unknown28[1] + node->unknown28[1];
  node->unknown28[2] = parent->unknown28[2] + node->unknown28[2];
  node->unknown18[0] = parent->unknown18[0] * node->unknown18[0];
  node->unknown18[1] = parent->unknown18[1] * node->unknown18[1];
  node->unknown18[2] = parent->unknown18[2] * node->unknown18[2];
  node->unknown18[3] = parent->unknown18[3] * node->unknown18[3];
}

} // namespace layer
