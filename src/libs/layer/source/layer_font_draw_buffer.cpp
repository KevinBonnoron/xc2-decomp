#include "layer/layer_font_draw_buffer.h"

#include <new>
#include <string.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "layer/layer_acc_font_style.h"
#include "layer/layer_font_icon_obj.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_font.h"
#include "layer/layer_obj_sort_font.h"
#include "layer/layer_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {
class LayerSortObj;

void LayerFontDrawBuffer::reset() {
  unknown68 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown78 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown4b8 = 0;
  unknown4bc = 0;
  unknown494[0] = -(m_layerFontResObj->unknown70 * m_lyrFontStyleData->unknown0c);
  unknown494[1] = -(m_layerFontResObj->unknown70 * m_lyrFontStyleData->unknown10);
  unknown49c = 0;
  unknown4c0[0] = 0;
  unknown4c0[1] = 0;
}

LayerResFontInfo *LayerFontDrawBuffer::createChar(const u8 *text) {
  LayerTagWork work = {};
  getWorkSize(work, text);
  createWorkBuffer(work, text);
  createWork(text);
  endWorkSetup();
  return m_layerResFontInfo;
}

void LayerFontDrawBuffer::createWorkBuffer(const LayerTagWork &work, const u8 *text) {
  u32 size = sizeof(LayerResFontInfo) + sizeof(LayerObjSortFont) + sizeof(grlib::CGLibVtxOneInstans) + sizeof(grlib::CGLibDblUniformBlock) + work.unknown08 * sizeof(u32) +
             (unknown49c + 1) * sizeof(unknown026) + work.unknown14;
  u8 *buffer = static_cast<u8 *>(mtl::MemManager::allocate(LayerManager::get()->unknown2c, size, 0x10, false, "no name", 0));
  m_layerResFontInfo = reinterpret_cast<LayerResFontInfo *>(buffer);
  memset(m_layerResFontInfo, 0, sizeof(LayerResFontInfo));
  m_layerResFontInfo->m_layerFontResObj = m_layerFontResObj;
  u32 offset = sizeof(LayerResFontInfo);
  m_layerResFontInfo->m_layerSortObj = reinterpret_cast<LayerSortObj *>(buffer + offset);
  new (m_layerResFontInfo->m_layerSortObj) LayerObjSortFont(m_layerObjFont);
  offset += sizeof(LayerObjSortFont);
  m_layerResFontInfo->unknown60 = reinterpret_cast<grlib::CGLibVtxOneInstans *>(buffer + offset);
  offset += sizeof(grlib::CGLibVtxOneInstans);
  m_layerResFontInfo->unknown68 = reinterpret_cast<grlib::CGLibDblUniformBlock *>(buffer + offset);
  offset += sizeof(grlib::CGLibDblUniformBlock);
  m_layerResFontInfo->unknown20 = reinterpret_cast<u32 *>(buffer + offset);
  m_layerResFontInfo->unknown28 = work.unknown08;
  offset += work.unknown08 * sizeof(u32);
  m_layerResFontInfo->unknown30 = work.unknown0c;
  m_layerResFontInfo->unknown48 = reinterpret_cast<unknown026 *>(buffer + offset);
  m_layerResFontInfo->unknown50 = unknown49c;
  offset += (unknown49c + 1) * sizeof(unknown026);
  m_layerResFontInfo->unknown10 = buffer + offset;
  m_layerResFontInfo->unknown18 = work.unknown14;
  m_layerResFontInfo->unknown40 = work.unknown00 + work.unknown04;
  m_layerResFontInfo->unknown04 = (work.unknown00 + work.unknown04 + work.unknown0c) * sizeof(unknown001);
  m_layerResFontInfo->unknown2c = (work.unknown00 + work.unknown04) * sizeof(unknown001);
  m_layerResFontInfo->unknown58 = 0;
  new (m_layerResFontInfo->unknown60) grlib::CGLibVtxOneInstans();
  new (m_layerResFontInfo->unknown68) grlib::CGLibDblUniformBlock();
  m_layerResFontInfo->unknown68->setup(LayerObjUtil::getUniformBlockSizeAlOff(LAYER_UNI_TYPE_UNKNOWN_5));
  m_layerResFontInfo->unknown60->createInstansBuffer(m_layerResFontInfo->unknown04);
  m_layerResFontInfo->unknown00 |= 1;
  m_layerResFontInfo->unknown48[0].unknown00 = 0;
  m_layerResFontInfo->unknown48[0].unknown04 = -1;
  m_layerResFontInfo->unknown48[0].unknown06 = 0;
  m_layerResFontInfo->unknown48[0].unknown0c = -1;
  m_layerResFontInfo->unknown48[0].unknown0e = 0;
  unknown001 *instances = static_cast<unknown001 *>(m_layerResFontInfo->unknown60->getBuff());
  unknown48 = instances;
  unknown50 = instances;
  unknown001 *icons = reinterpret_cast<unknown001 *>(reinterpret_cast<u8 *>(instances) + m_layerResFontInfo->unknown2c);
  unknown58 = icons;
  unknown60 = icons;
  for (u32 i = 0; i < m_layerResFontInfo->unknown18; i++) {
    m_layerResFontInfo->unknown10[i] = text[i];
  }
}

LayerResFontInfo *LayerFontDrawBuffer::createChar(const wchar_t *text) {
  LayerTagWork work = {};
  getWorkSize(work, text);
  createWorkBuffer(work, reinterpret_cast<const u8 *>(text));
  createWork(text);
  endWorkSetup();
  return m_layerResFontInfo;
}

void LayerFontDrawBuffer::fontCnt() {
  unknown026 *line = &m_layerResFontInfo->unknown48[unknown49c];
  if (line->unknown04 == -1) {
    line->unknown04 = unknown4b8;
  }
  m_layerResFontInfo->unknown48[unknown49c].unknown06 = unknown4b8;
  unknown4b8++;
}

void LayerFontDrawBuffer::createFontIcon(u16 code) {
  if (m_layerFontIconObj != nullptr && unknown49c < m_lyrFontStyleData->unknown1a) {
    const LayerFontResObj::unknown002 *texture = m_layerFontResObj->unknown58;
    f32 uv[6];
    m_layerFontIconObj->getFontUvParms(uv, code);
    unknown001 *instance = unknown60;
    f32 size[2];
    size[0] = uv[0] * m_lyrFontStyleData->unknown10;
    size[1] = uv[1] * m_lyrFontStyleData->unknown10;
    instance->unknown00[0] = size[0];
    instance->unknown00[1] = size[1];
    instance->unknown00[2] = unknown494[0];
    instance->unknown00[3] = unknown494[1];
    if (unknown38 == 0) {
      instance->unknown00[3] += ((static_cast<f32>(texture->unknown0c) - m_layerFontResObj->unknown74) * m_lyrFontStyleData->unknown10 - uv[1]) * 0.5f;
    } else {
      instance->unknown00[2] += ((static_cast<f32>(texture->unknown08) - m_layerFontResObj->unknown74) * m_lyrFontStyleData->unknown10 - uv[0]) * 0.5f;
    }
    instance->unknown00[4] = uv[2];
    instance->unknown00[5] = uv[3];
    instance->unknown00[6] = uv[4];
    instance->unknown00[7] = uv[5];
    unknown002(unknown60);
    u32 axis = unknown3c;
    if (m_lyrFontStyleData->unknown18 >= unknown494[axis] + static_cast<s32>(size[axis])) {
      unknown494[axis] += static_cast<s32>(size[axis]) + m_lyrFontStyleData->unknown1e;
      if (unknown4c0[axis] < unknown494[axis]) {
        unknown4c0[axis] = unknown494[axis];
      }
      s32 other = unknown494[unknown40] + static_cast<s32>(size[unknown40]) + m_lyrFontStyleData->unknown1c;
      if (unknown4c0[unknown40] < other) {
        unknown4c0[unknown40] = other;
      }
      m_layerResFontInfo->unknown48[unknown49c].unknown00 = unknown494[axis];
      unknown026 *line = &m_layerResFontInfo->unknown48[unknown49c];
      if (line->unknown0c == -1) {
        line->unknown0c = unknown4bc;
      }
      m_layerResFontInfo->unknown48[unknown49c].unknown0e = unknown4bc;
      unknown60++;
      unknown4bc++;
    }
  }
}

void LayerFontDrawBuffer::createLineBreak() {
  const LayerFontResObj::unknown002 *texture = m_layerFontResObj->unknown58;
  if (unknown38 == 0) {
    unknown494[0] = 0;
    unknown494[1] += static_cast<s32>((static_cast<f32>(texture->unknown0c) - m_layerFontResObj->unknown74) * m_lyrFontStyleData->unknown0c) + m_lyrFontStyleData->unknown1c;
  } else {
    unknown494[1] = 0;
    s32 width = static_cast<s32>((static_cast<f32>(texture->unknown08) - m_layerFontResObj->unknown74) * m_lyrFontStyleData->unknown10);
    if (unknown38 == LAYER_FONT_SETTING_VERTICAL) {
      unknown494[0] -= m_lyrFontStyleData->unknown1c + width;
    } else {
      unknown494[0] += m_lyrFontStyleData->unknown1c + width;
    }
  }
  unknown49c++;
  m_layerResFontInfo->unknown48[unknown49c].unknown00 = 0;
  m_layerResFontInfo->unknown48[unknown49c].unknown04 = -1;
  m_layerResFontInfo->unknown48[unknown49c].unknown06 = 0;
  m_layerResFontInfo->unknown48[unknown49c].unknown0c = -1;
  m_layerResFontInfo->unknown48[unknown49c].unknown0e = 0;
}

} // namespace layer
