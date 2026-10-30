#include "layer/layer_acc_layout_binary.h"

#include <string.h>

#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"

namespace layer {

LayerAccLayoutBinary::LayerAccLayoutBinary(const void *data) {
  unknown00 = static_cast<const u8 *>(data);
  const unknown002 *header = static_cast<const unknown002 *>(data);
  unknown08 = header->unknown20;
  unknown10 = reinterpret_cast<const LyrLayoutPosData *>(unknown00 + header->unknown1c);
  if (header->unknown10 != 0) {
    const unknown003 *resNames = reinterpret_cast<const unknown003 *>(unknown00 + header->unknown10);
    unknown20 = reinterpret_cast<const unknown001 *>(unknown00 + resNames->unknown00);
    unknown18 = resNames->unknown04;
  } else {
    unknown20 = nullptr;
    unknown18 = 0;
  }
}

u32 LayerAccLayoutBinary::getPosIdx(const char *name) const {
  for (s32 i = 0; i < static_cast<s32>(unknown08); i++) {
    if (strcmp(name, reinterpret_cast<const char *>(unknown00 + unknown10[i].unknown04)) == 0) {
      return i;
    }
  }
  return 0xffffffff;
}

const char *LayerAccLayoutBinary::getPosName(u32 index) const {
  if (index < unknown08) {
    return reinterpret_cast<const char *>(unknown00 + unknown10[index].unknown04);
  }
  return nullptr;
}

u32 LayerAccLayoutBinary::getResIdx(const char *name) const {
  for (s32 i = 0; i < unknown18; i++) {
    if (strcmp(name, reinterpret_cast<const char *>(unknown00 + unknown20[i].unknown00)) == 0) {
      return i;
    }
  }
  return 0xffffffff;
}

const char *LayerAccLayoutBinary::getResName(u32 index) const {
  if (index < static_cast<u32>(unknown18)) {
    return reinterpret_cast<const char *>(unknown00 + unknown20[index].unknown00);
  }
  return nullptr;
}

void LayerAccLayoutBinary::setLayoutPosData(f32 &x, f32 &y, u32 index) {
  const LyrLayoutPosData *table = unknown10;
  if (index < unknown08) {
    const LyrLayoutPosData &data = table[index];
    if (LayerManager::get()->unknown9c == LAYER_COORDINATE_PIXEL) {
      x = data.unknown2c;
      x = data.unknown2e;
    } else {
      x = data.unknown20;
      x = data.unknown24;
    }
  }
}

void LayerAccLayoutBinary::setLayoutPosData(f32 &x, f32 &y, const char *name) {
  u32 index = getPosIdx(name);
  if (index == 0xffffffff) {
    return;
  }
  setLayoutPosData(x, y, index);
}

void LayerAccLayoutBinary::setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, u32 index) {
  const LyrLayoutPosData *table = unknown10;
  if (index < unknown08) {
    const LyrLayoutPosData &data = table[index];
    if (LayerManager::get()->unknown9c == LAYER_COORDINATE_PIXEL) {
      x = data.unknown2c;
      y = data.unknown2e;
      width = data.unknown30 - data.unknown2c;
      height = data.unknown32 - data.unknown2e;
    } else {
      x = data.unknown20;
      y = data.unknown24;
      width = data.unknown18;
      height = data.unknown1c;
    }
  }
}

void LayerAccLayoutBinary::setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, const char *name) {
  u32 index = getPosIdx(name);
  if (index == 0xffffffff) {
    return;
  }
  setLayoutPosData(x, y, width, height, index);
}

void LayerAccLayoutBinary::setLayoutObj(LayerObj *object, u32 index, bool initScale) {
  if (index < unknown08) {
    f32 info[4];
    LayerObjUtil::getLayoutInfo(info, &unknown10[index], static_cast<LayerCenterType>(object->unknown198), object->unknown194, object->unknown196);
    if (initScale) {
      object->setInitPosScl(info[0], info[1], info[2], info[3]);
    } else {
      object->setInitPos(info[0], info[1]);
    }
  }
}

void LayerAccLayoutBinary::setLayoutObj(LayerObj *object, const char *name, bool initScale) {
  u32 index = getPosIdx(name);
  if (index == 0xffffffff) {
    return;
  }
  setLayoutObj(object, index, initScale);
}

} // namespace layer
