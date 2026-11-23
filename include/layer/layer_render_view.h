#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

struct LayerResViewPortInfo;

// Evidence: LayerObjUtil::calcLayerRenderView copies it as three 8 byte words; LayerObjManager::apply clears m_layerResViewPortInfo
// and unknown10 of the one it holds at 0x78. Original member names unknown.
struct LayerRenderView {
  u8 _00[0x08];
  LayerResViewPortInfo *m_layerResViewPortInfo; // Inferred role: view port info; original member name unknown.
  u16 unknown10;                                // Inferred role: cleared by LayerObjManager::apply; original member name unknown.
  u8 _12[0x18 - 0x12];
};

static_assert(offsetof(LayerRenderView, m_layerResViewPortInfo) == 0x08, "");
static_assert(offsetof(LayerRenderView, unknown10) == 0x10, "");
static_assert(sizeof(LayerRenderView) == 0x18, "");

} // namespace layer
