#include "layer/layer_anime_obj.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerAnimeObj::LayerAnimeObj(int count) : unknown10(nullptr), unknown18(0), unknown1c(0), unknown28(0), unknown30(0) {
  unknown20 = LayerManager::get()->unknown28;
  unknown10 = static_cast<LayerAnimeInfo *>(mtl::MemManager::allocate(unknown20, static_cast<size_t>(static_cast<u32>(count)) * sizeof(LayerAnimeInfo), 0x10, false, "no name", 0));
  unknown18 = 0;
  unknown1c = count;
  unknown08[0] = 0;
  unknown08[1] = 0;
  unknown00 = 0.0f;
  unknown04 = 0;
  unknown06 = 0;
}

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

void LayerAnimeObj::calcParm(LayerResParmInfo &parm, const LayerAnimeInfo &info, f32 rate) {
  if (info.unknown00 & 0x1) {
    parm.unknown00.unknown00 += (info.unknown08 - parm.unknown00.unknown00) * rate;
    parm.unknown00.unknown04 += (info.unknown0c - parm.unknown00.unknown04) * rate;
  }
  if (info.unknown00 & 0x2) {
    parm.unknown00.unknown08 += (info.unknown10 - parm.unknown00.unknown08) * rate;
  }
  if (info.unknown00 & 0x4) {
    parm.unknown00.unknown0c += (info.unknown14 - parm.unknown00.unknown0c) * rate;
    parm.unknown00.unknown10 += (info.unknown18 - parm.unknown00.unknown10) * rate;
  }
  if (info.unknown00 & 0x8) {
    parm.unknown00.unknown14 += (info.unknown1c - parm.unknown00.unknown14) * rate;
    parm.unknown00.unknown18 += (info.unknown20 - parm.unknown00.unknown18) * rate;
  }
  if (info.unknown00 & 0x10) {
    parm.unknown1c.unknown10.r += (info.unknown34 - parm.unknown1c.unknown10.r) * rate;
    parm.unknown1c.unknown10.g += (info.unknown38 - parm.unknown1c.unknown10.g) * rate;
    parm.unknown1c.unknown10.b += (info.unknown3c - parm.unknown1c.unknown10.b) * rate;
  }
  if (info.unknown00 & 0x20) {
    parm.unknown1c.unknown00.r += (info.unknown24 - parm.unknown1c.unknown00.r) * rate;
    parm.unknown1c.unknown00.g += (info.unknown28 - parm.unknown1c.unknown00.g) * rate;
    parm.unknown1c.unknown00.b += (info.unknown2c - parm.unknown1c.unknown00.b) * rate;
    parm.unknown1c.unknown00.a += (info.unknown30 - parm.unknown1c.unknown00.a) * rate;
  }
}

} // namespace layer
