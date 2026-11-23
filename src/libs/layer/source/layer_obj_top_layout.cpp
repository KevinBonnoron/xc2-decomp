#include "layer/layer_obj_top_layout.h"

#include <math.h>

#include "dr/dr_draw_work_info.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace layer {

LayerObjTopLayout::LayerObjTopLayout(const void *data) : m_layerObjSortLayout(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
  workLayoutCreate(data);
}

void LayerObjTopLayout::workLayoutCreate(const void *data) {
  m_resData = data;
  const u8 *base = static_cast<const u8 *>(data);
  const LayerAccLayoutBinary::unknown002 *header = static_cast<const LayerAccLayoutBinary::unknown002 *>(data);
  unknown2a0.unknown00 = base + header->unknown14;
  const LyrLayoutPosData *pos = reinterpret_cast<const LyrLayoutPosData *>(base + header->unknown1c);
  unknown2a0.m_lyrLayoutPosData = pos;
  const LayerAccLayoutBinary::unknown003 *resNames = reinterpret_cast<const LayerAccLayoutBinary::unknown003 *>(base + header->unknown10);
  const LayerAccLayoutBinary::unknown001 *resTable = reinterpret_cast<const LayerAccLayoutBinary::unknown001 *>(base + resNames->unknown00);
  s32 posNum = header->unknown20;
  for (s32 i = 0; i < posNum; i++, pos++) {
    if (pos->unknown00 & 0x2) {
      u32 resOffset = resTable[pos->unknown0c].unknown04;
      LayerObj *object = static_cast<LayerObj *>(LayerObjManager::createStaticObj(static_cast<const u8 *>(m_resData) + resOffset));
      f32 info[4];
      LayerObjUtil::getLayoutInfo(info,
                                  pos,
                                  static_cast<LayerCenterType>(object->m_layerResRenderInfo.m_centerType),
                                  static_cast<u16>(object->m_layerResRenderInfo.m_pixelWidth),
                                  static_cast<u16>(object->m_layerResRenderInfo.m_pixelHeight));
      object->setInitPosScl(info[0], info[1], info[2], info[3]);
      unknown258.unknown002(object);
    }
  }
  m_layerResRenderInfo.unknown00 = 1.0f;
  m_layerResRenderInfo.unknown04 = 1.0f;
  m_layerResRenderInfo.unknown08 = 1.0f;
  m_layerResRenderInfo.unknown0c = 1.0f;
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = 0;
  m_layerResRenderInfo.m_pixelHeight = 0;
}

LayerObjTopLayout::LayerObjTopLayout() : m_layerObjSortLayout(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
}

LayerObjTopLayout::~LayerObjTopLayout() {
  baseRelease();
  workLayoutRelease();
  workListRelease();
}

void LayerObjTopLayout::apply(LayerSortMan *sortMan, const LayerRenderView *view) {
  updateFast();
  LayerResUpdateInfo info;
  if (!(unknowna8 & 0x10000)) {
    info.unknown50 = true;
    info.unknown00 = unknown20[unknownc2];
    info.unknown54 = static_cast<LAYER_SPACE_TYPE>(m_space);
    info.unknown58 = m_blendType;
    info.m_layerResDispInfo.unknown001();
    info.m_layerObjTopMaskObj = static_cast<const LayerObjTopMaskObj *>(m_maskObj);
    updateSpace(info);
    updateBeginLayout(info, view);
    LayerResMatrix matrix;
    if (m_space == LAYER_SPACE_TYPE_UNKNOWN_2) {
      LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(matrix, m_layerResParmInfo[2].m_layerBasePos);
    } else {
      LayerObjUtil::calcLayerTransRotScaleLaoutMatrix(matrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
    }
    info.m_layerResMatrix = &matrix;
    info.m_layerResColor = &m_layerResParmInfo[2].m_layerResColor;
    updateEndLayout(view, info);
    m_layerResDispInfo.unknown001();
    LayerObjUtil::calcLayoutDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
    setDrawList(sortMan, true);
  } else {
    info.unknown50 = false;
    info.unknown54 = static_cast<LAYER_SPACE_TYPE>(m_space);
    info.unknown58 = m_blendType;
    info.m_layerObjTopMaskObj = nullptr;
    updateDispOffLayout(info, view);
  }
}

void LayerObjTopLayout::updateFast() {
  addListInfo();
  updatePriTbl();
  updateCtrlSpd(1.0f);
  updateAction();
  updateDefPos();
  updateAnimObj();
}

void LayerObjTopLayout::updateDispOffLayout(LayerResUpdateInfo &info, const LayerRenderView *view) { unknown001(info, view); }

void LayerObjTopLayout::updateSpace(const LayerResUpdateInfo &info) {
  switch (info.unknown54) {
  case LAYER_SPACE_TYPE_UNKNOWN_1:
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, info.unknown00);
    unknowna8 |= 0x400;
    break;
  case LAYER_SPACE_TYPE_UNKNOWN_2:
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, info.unknown00);
    unknowna8 |= 0xc00;
    break;
  default:
    unknown1fc = 0.0f;
    break;
  }
}

void LayerObjTopLayout::updateBeginLayout(LayerResUpdateInfo &info, const LayerRenderView *view) {
  unknown001(info, view);
  f32 aspect = 1.0f;
  if (info.m_layerResDispInfo.unknown00 == -100000.0f) {
    m_layerResRenderInfo.m_pixelX = 0;
    m_layerResRenderInfo.m_pixelY = 0;
    m_layerResRenderInfo.m_pixelWidth = 0;
    m_layerResRenderInfo.m_pixelHeight = 0;
  } else {
    const LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
    m_layerResRenderInfo.m_pixelX = info.m_layerResDispInfo.unknown08.x * shader->m_screenWidth;
    m_layerResRenderInfo.m_pixelY = info.m_layerResDispInfo.unknown08.y * shader->m_screenHeight;
    m_layerResRenderInfo.m_pixelWidth = info.m_layerResDispInfo.unknown00 * shader->m_screenWidth;
    m_layerResRenderInfo.m_pixelHeight = info.m_layerResDispInfo.unknown04 * shader->m_screenHeight;
    m_layerResRenderInfo.m_pixelWidth -= m_layerResRenderInfo.m_pixelX;
    m_layerResRenderInfo.m_pixelHeight -= m_layerResRenderInfo.m_pixelY;
    if (m_layerResRenderInfo.m_pixelWidth != 0) {
      aspect = static_cast<f32>(m_layerResRenderInfo.m_pixelHeight) / static_cast<f32>(m_layerResRenderInfo.m_pixelWidth);
    }
  }
  m_layerResRenderInfo.unknown0c = aspect;
  LayerBasePos &pos = m_layerResParmInfo[2].m_layerBasePos;
  switch (unknown2a0.m_autoAnchorMode) {
  case LAYER_ANCHOR_UNKNOWN_1:
    if (fabsf(info.m_layerResDispInfo.unknown00) >= 0.001f) {
      pos.unknown14 = info.m_layerResDispInfo.unknown08.x / info.m_layerResDispInfo.unknown00;
    } else {
      pos.unknown14 = 0.0f;
    }
    if (fabsf(info.m_layerResDispInfo.unknown04) >= 0.001f) {
      pos.unknown18 = info.m_layerResDispInfo.unknown08.y / info.m_layerResDispInfo.unknown04;
    } else {
      pos.unknown18 = 0.0f;
    }
    break;
  case LAYER_ANCHOR_UNKNOWN_2:
    if (fabsf(info.m_layerResDispInfo.unknown00) >= 0.001f) {
      f32 anchor = info.m_layerResDispInfo.unknown08.x / info.m_layerResDispInfo.unknown00;
      pos.unknown14 = anchor + (1.0f - anchor) * 0.5f;
    } else {
      pos.unknown14 = 0.0f;
    }
    if (fabsf(info.m_layerResDispInfo.unknown04) >= 0.001f) {
      f32 anchor = info.m_layerResDispInfo.unknown08.y / info.m_layerResDispInfo.unknown04;
      pos.unknown18 = anchor + (1.0f - anchor) * 0.5f;
    } else {
      pos.unknown18 = 0.0f;
    }
    break;
  }
}

void LayerObjTopLayout::updateEndLayout(const LayerRenderView *view, LayerResUpdateInfo &info) {
  if (unknown3f8 != nullptr) {
    delete unknown3f8;
    unknown3f8 = nullptr;
  }
  LayerRenderView layoutView;
  const LayerRenderView *listView;
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    LayerObjUtil::calcLayerRenderView(layoutView, unknown2a0.m_layerResViewPortInfo, unknown3f0, unknown2a0.unknown118.unknown04, view, info.m_layerResMatrix);
    unknown2a0.m_layerResViewPortInfo.unknown10 = unknown2a0.unknown118.unknown18;
    unknown2a0.m_layerResViewPortInfo.unknown20 = unknown2a0.unknown118.unknown28;
    unknown2a0.m_layerResViewPortInfo.unknown30 = 0;
    listView = &layoutView;
  } else if (unknowna8 & 0x10) {
    LayerObjUtil::calcLayerRenderView(layoutView, unknown2a0.m_layerResViewPortInfo, unknown3f0, unknown2a0.unknown10, view, info.m_layerResMatrix);
    unknown2a0.m_layerResViewPortInfo.unknown10 = nullptr;
    unknown2a0.m_layerResViewPortInfo.unknown30 = 0;
    listView = &layoutView;
  } else {
    unknown3f8 = unknown3f0;
    unknown3f0 = nullptr;
    listView = view;
  }
  LayerBase *node = unknown258.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    static_cast<LayerObj *>(node)->applyEnd(info, listView);
    node = next;
  }
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    unknown2a0.unknown118.m_layerObjTopTexObj->applyEnd(info, view);
  }
}

void LayerObjTopLayout::applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view) {
  updateFast();
  LayerResUpdateInfo child;
  if (!info.unknown50 || (unknowna8 & 0x10000)) {
    unknowna8 |= 0x10000;
    child.unknown50 = false;
    child.m_layerObjTopMaskObj = nullptr;
    updateDispOffLayout(child, view);
    return;
  }
  LAYER_SPACE_TYPE space = info.unknown54;
  if (space == LAYER_SPACE_TYPE_UNKNOWN_0) {
    space = static_cast<LAYER_SPACE_TYPE>(m_space);
  }
  child.m_layerResDispInfo.unknown001();
  child.unknown50 = true;
  const LayerObjTopMaskObj *mask = static_cast<const LayerObjTopMaskObj *>(m_maskObj);
  if (mask == nullptr) {
    mask = info.m_layerObjTopMaskObj;
  }
  child.m_layerObjTopMaskObj = mask;
  if (info.unknown54 == LAYER_SPACE_TYPE_UNKNOWN_0) {
    child.unknown54 = static_cast<LAYER_SPACE_TYPE>(m_space);
    child.unknown00 = unknown20[unknownc2];
  } else {
    child.unknown54 = info.unknown54;
    child.unknown00.unknown009(unknown20[unknownc2], info.unknown00);
  }
  if (m_blendType == 5) {
    child.unknown58 = info.unknown58;
  } else {
    child.unknown58 = m_blendType;
  }
  updateSpace(child);
  updateBeginLayout(child, view);
  if (space == LAYER_SPACE_TYPE_UNKNOWN_2) {
    LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(m_layerResMatrix, m_layerResParmInfo[2].m_layerBasePos);
  } else {
    LayerObjUtil::calcLayerTransRotScaleLaoutMatrix(m_layerResMatrix, m_layerResParmInfo[2].m_layerBasePos, m_layerResRenderInfo);
  }
  LayerObjUtil::calcLayoutDispInfo(info.m_layerResDispInfo, m_layerResMatrix, m_layerResRenderInfo);
}

void LayerObjTopLayout::applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view) {
  if (unknowna8 & 0x10000) {
    return;
  }
  LayerResMatrix matrix;
  LayerObjUtil::calcLayerMatrix(matrix, m_layerResMatrix, *info.m_layerResMatrix);
  LayerResColor color;
  LayerObjUtil::calcLayerColor(color, m_layerResParmInfo[2].m_layerResColor, *info.m_layerResColor);
  LayerResUpdateInfo child;
  child.m_layerResMatrix = &matrix;
  child.m_layerResColor = &color;
  child.unknown50 = true;
  child.unknown58 = m_blendType;
  const LayerObjTopMaskObj *mask = static_cast<const LayerObjTopMaskObj *>(m_maskObj);
  if (mask == nullptr) {
    mask = info.m_layerObjTopMaskObj;
  }
  child.m_layerObjTopMaskObj = mask;
  updateEndLayout(view, child);
  m_layerResDispInfo.unknown001();
  LayerObjUtil::calcLayoutDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
}

void LayerObjTopLayout::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  LayerSortMan *listSortMan = sortMan;
  bool listIs3D = is3D;
  if (unknown2a0.m_layerSortMan != nullptr) {
    listSortMan = unknown2a0.m_layerSortMan;
    listIs3D = !(unknowna8 & 0x400) && is3D;
    listSortMan->begin(LayerManager::get()->m_layerObjManager->unknown00->unknownb0);
  }
  LayerBase *node = unknown258.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    static_cast<LayerObj *>(node)->setDrawList(listSortMan, listIs3D);
    node = next;
  }
  if (unknown2a0.m_layerSortMan != nullptr) {
    listSortMan->end();
    if (is3D && (unknowna8 & 0x400)) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortLayout, unknown200);
    } else {
      sortMan->set2DSpace(&m_layerObjSortLayout, m_priority);
    }
  } else if (unknown2a0.unknown118.unknown00 & 0x4) {
    if (is3D && (unknowna8 & 0x400)) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortLayout, unknown200);
    } else {
      sortMan->set2DSpace(&m_layerObjSortLayout, m_priority);
    }
  }
}

void LayerObjTopLayout::finalRender() {
  if (unknown2a0.m_layerSortMan != nullptr) {
    unknown2a0.m_layerSortMan->finalRender();
  }
  if ((unknown2a0.unknown118.unknown00 & 0xc) == 0xc) {
    LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
    shader->setShaderMaskOff();
    shader->setupMainRenderTarget();
    shader->resetViewPort();
    LayerObjTopTexObj *texture = unknown2a0.unknown118.m_layerObjTopTexObj;
    if (!(texture->unknowna8 & 0x90000)) {
      texture->finalRender();
    }
  }
}

} // namespace layer
