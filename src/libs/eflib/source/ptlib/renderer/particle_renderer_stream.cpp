#include "ptlib/renderer/particle_renderer_stream.h"

#include "eflib/effect_system_manager.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_instans.h"
#include "mm/mm_std_base.h"
#include "ptlib/renderer/particle_renderer_eff_state.h"

namespace ptlib {
namespace renderer {

void StreamObj::init(STREAM_SIZE_TYPE sizeType, u32 count, FxVertexType vertexType) {
  unknown50 = true;
  unknown44 = sizeType;
  unknown4c = vertexType;
  unknown48 = 0;
  if (vertexType == FX_VERTEX_TYPE_UNKNOWN_0) {
    unknown10 = &EffStateManager::get()->unknown500;
    unknown40 = 0;
  } else if (vertexType == FX_VERTEX_TYPE_UNKNOWN_1) {
    unknown18.createVertexBuff(0x9600, 0x60);
    unknown40 = 2;
    unknown10 = &unknown18;
  }
  initFetchVertex();
}

void StreamObj::initSub() {
  initVertex();
  initFetchVertex();
}

void StreamObj::release() {
  unknown18.delayRelease();
  unknown10 = nullptr;
}

void StreamObj::releaseSub() {
  unknown18.delayRelease();
  unknown10 = nullptr;
}

void StreamObj::initVertex() {
  if (unknown4c == FX_VERTEX_TYPE_UNKNOWN_0) {
    unknown10 = &EffStateManager::get()->unknown500;
    unknown40 = 0;
  } else if (unknown4c == FX_VERTEX_TYPE_UNKNOWN_1) {
    unknown18.createVertexBuff(0x9600, 0x60);
    unknown40 = 2;
    unknown10 = &unknown18;
  }
}

void StreamObj::initFetchVertex() {
  if (unknown4c == FX_VERTEX_TYPE_UNKNOWN_1) {
    unknown08 = &EffStateManager::get()->unknown400[1];
    unknown00 = &EffStateManager::get()->unknown400[1];
  } else {
    switch (unknown44) {
    case STREAM_SIZE_TYPE_UNKNOWN_20:
      unknown08 = &EffStateManager::get()->unknown470[1];
      unknown00 = &EffStateManager::get()->unknown400[1];
      break;
    case STREAM_SIZE_TYPE_UNKNOWN_24:
      unknown08 = &EffStateManager::get()->unknown470[2];
      unknown00 = &EffStateManager::get()->unknown400[2];
      break;
    case STREAM_SIZE_TYPE_UNKNOWN_28:
      unknown08 = &EffStateManager::get()->unknown470[3];
      unknown00 = &EffStateManager::get()->unknown400[3];
      break;
    case STREAM_SIZE_TYPE_UNKNOWN_32:
      unknown08 = &EffStateManager::get()->unknown470[4];
      unknown00 = &EffStateManager::get()->unknown400[4];
      break;
    case STREAM_SIZE_TYPE_UNKNOWN_36:
      unknown08 = &EffStateManager::get()->unknown470[5];
      unknown00 = &EffStateManager::get()->unknown400[5];
      break;
    case STREAM_SIZE_TYPE_UNKNOWN_40:
      unknown08 = &EffStateManager::get()->unknown470[6];
      unknown00 = &EffStateManager::get()->unknown400[6];
      break;
    default:
#line 172
      MM_ASSERT(0);
      break;
    }
  }
}

void *StreamObj::lockStream(const DrDrawWorkInfoEF *info) {
  if (unknown4c == FX_VERTEX_TYPE_UNKNOWN_1) {
    u32 size;
    void *buffer;
    unknown10->lock(&buffer, &size);
    u8 *data = static_cast<u8 *>(buffer);
    return effect::SystemManager::getPtr()->unknown7824d != 0 ? data + 0x4b00 : data;
  }
  unknown48 = EffStateManager::get()->unknown618.unknown08;
  return EffStateManager::get()->unknown618.getNextInstansBuff();
}

void StreamObj::unlockStream(const DrDrawWorkInfoEF *info, u32 count) {
  if (unknown4c == FX_VERTEX_TYPE_UNKNOWN_1) {
    if (effect::SystemManager::getPtr()->unknown7824d != 0) {
      unknown10->unlock(0x4b00, 0x4b00);
    } else {
      unknown10->unlock(0, 0x4b00);
    }
    return;
  }
  unknown48 = EffStateManager::get()->unknown618.unknown08;
  EffStateManager *manager = EffStateManager::get();
  manager->unknown618.unknown08 += count * unknown44 * 4;
  EffStateManager::get()->unknown618.updateInstansBuff();
}

grlib::CGLibSampler *StreamObj::getSampler(u32 clamp) {
  switch (clamp) {
  case 0:
  case 1:
    return EffStateManager::get()->unknown00;
  case 2:
  case 3:
    return &EffStateManager::get()->unknown00[13];
  case 4:
  case 5:
    return &EffStateManager::get()->unknown00[26];
  default:
    return EffStateManager::get()->unknown00;
  }
}

grlib::CGLibSampler *StreamObj::getSampler(u32 clampS, u32 clampT) {
  int s = clampS;
  if (s > 2) {
    s = 0;
  }
  EffStateManager *manager = EffStateManager::get();
  int t = clampT * 3;
  if (static_cast<int>(clampT) > 2) {
    t = 0;
  }
  return &manager->unknown00[t + s];
}

grlib::CGLibSampler *StreamObj::getSampler(u32 clampS, u32 clampT, u32 clampR) {
  int s = clampS;
  if (s > 2) {
    s = 0;
  }
  EffStateManager *manager = EffStateManager::get();
  int t = clampT * 3;
  if (static_cast<int>(clampT) > 2) {
    t = 0;
  }
  int index = t + s;
  int r = clampR * 9;
  if (static_cast<int>(clampR) > 2) {
    r = 0;
  }
  return &manager->unknown00[index + r];
}

} // namespace renderer
} // namespace ptlib
