#include "layer/layer_anime_obj.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerAnimeObj::LayerAnimeObj(int count) : m_layerAnimeInfo(nullptr), unknown18(0), unknown1c(0), unknown28(0), unknown30(0) {
  m_ALLOC_HANDLE = LayerManager::get()->unknown28;
  m_layerAnimeInfo = static_cast<LayerAnimeInfo *>(mtl::MemManager::allocate(m_ALLOC_HANDLE, static_cast<size_t>(static_cast<u32>(count)) * sizeof(LayerAnimeInfo), 0x10, false, "no name", 0));
  unknown18 = 0;
  unknown1c = count;
  unknown08[0] = 0;
  unknown08[1] = 0;
  unknown00 = 0.0f;
  unknown04 = 0;
  unknown06 = 0;
}

LayerAnimeObj::~LayerAnimeObj() {
  unknown18 = 0;
  if (m_ALLOC_HANDLE.isValid() && m_layerAnimeInfo != nullptr) {
    mtl::MemManager::deallocate(m_layerAnimeInfo, 0, false);
    m_layerAnimeInfo = nullptr;
  }
  unknown1c = 0;
  m_layerAnimeInfo = nullptr;
  m_ALLOC_HANDLE = mtl::ALLOC_HANDLE();
}

LayerAnimeObj *LayerAnimeObj::createAnimObj(int id) { return new (LayerManager::get()->unknown28) LayerAnimeObj(id); }

void LayerAnimeObj::release() { unknown06 |= 0x8000; }

void LayerAnimeObj::setAnimeLoop(bool loop) {
  if (loop) {
    unknown06 |= 0x1;
  } else {
    unknown06 &= ~0x1;
  }
}

void LayerAnimeObj::setAnimeCorrection(bool correction) {
  if (correction) {
    unknown06 |= 0x2;
  } else {
    unknown06 &= ~0x2;
  }
}

void LayerAnimeObj::setSelectNumber(bool selectNumber) {
  if (selectNumber) {
    unknown06 |= 0x4;
  } else {
    unknown06 &= ~0xc;
  }
}

void LayerAnimeObj::setSelectIdx(u32 idx) {
  if (idx < static_cast<u32>(unknown18)) {
    unknown08[LayerManager::s_nStkIdx] = idx + 1;
  } else {
    unknown08[LayerManager::s_nStkIdx] = unknown18;
  }
}

void LayerAnimeObj::calcParm(LayerResParmInfo &parm, const LayerAnimeInfo &info, f32 rate) {
  if (info.unknown00 & 0x1) {
    parm.m_layerBasePos.unknown00 += (info.unknown08 - parm.m_layerBasePos.unknown00) * rate;
    parm.m_layerBasePos.unknown04 += (info.unknown0c - parm.m_layerBasePos.unknown04) * rate;
  }
  if (info.unknown00 & 0x2) {
    parm.m_layerBasePos.unknown08 += (info.unknown10 - parm.m_layerBasePos.unknown08) * rate;
  }
  if (info.unknown00 & 0x4) {
    parm.m_layerBasePos.unknown0c += (info.unknown14 - parm.m_layerBasePos.unknown0c) * rate;
    parm.m_layerBasePos.unknown10 += (info.unknown18 - parm.m_layerBasePos.unknown10) * rate;
  }
  if (info.unknown00 & 0x8) {
    parm.m_layerBasePos.unknown14 += (info.unknown1c - parm.m_layerBasePos.unknown14) * rate;
    parm.m_layerBasePos.unknown18 += (info.unknown20 - parm.m_layerBasePos.unknown18) * rate;
  }
  if (info.unknown00 & 0x10) {
    parm.m_layerResColor.m_addCol.r += (info.unknown34 - parm.m_layerResColor.m_addCol.r) * rate;
    parm.m_layerResColor.m_addCol.g += (info.unknown38 - parm.m_layerResColor.m_addCol.g) * rate;
    parm.m_layerResColor.m_addCol.b += (info.unknown3c - parm.m_layerResColor.m_addCol.b) * rate;
  }
  if (info.unknown00 & 0x20) {
    parm.m_layerResColor.m_mulCol.r += (info.unknown24 - parm.m_layerResColor.m_mulCol.r) * rate;
    parm.m_layerResColor.m_mulCol.g += (info.unknown28 - parm.m_layerResColor.m_mulCol.g) * rate;
    parm.m_layerResColor.m_mulCol.b += (info.unknown2c - parm.m_layerResColor.m_mulCol.b) * rate;
    parm.m_layerResColor.m_mulCol.a += (info.unknown30 - parm.m_layerResColor.m_mulCol.a) * rate;
  }
}

} // namespace layer

// The game builds these files in one unit with this one, in this order.
// clang-format off
#include "layer_sort_man.cpp"
#include "layer_texture_obj.cpp"
#include "layer_vertex_obj.cpp"
#include "layer_res_add_tex_obj.cpp"
#include "layer_res_sec_texture.cpp"
#include "layer_rce_manager.cpp"
#include "layer_rce_obj.cpp"
// clang-format on
