#include "layer/layer_obj_top_layout.h"

#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "types.h"

namespace layer {

LayerObjTopLayout::LayerObjTopLayout(const void *data) : unknown400(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
  workLayoutCreate(data);
}

void LayerObjTopLayout::workLayoutCreate(const void *data) {
  unknownb8 = data;
  const u8 *base = static_cast<const u8 *>(data);
  const LayerAccLayoutBinary::unknown002 *header = static_cast<const LayerAccLayoutBinary::unknown002 *>(data);
  unknown2a0.unknown00 = base + header->unknown14;
  const LyrLayoutPosData *pos = reinterpret_cast<const LyrLayoutPosData *>(base + header->unknown1c);
  unknown2a0.unknown08 = pos;
  const LayerAccLayoutBinary::unknown003 *resNames = reinterpret_cast<const LayerAccLayoutBinary::unknown003 *>(base + header->unknown10);
  const LayerAccLayoutBinary::unknown001 *resTable = reinterpret_cast<const LayerAccLayoutBinary::unknown001 *>(base + resNames->unknown00);
  s32 posNum = header->unknown20;
  for (s32 i = 0; i < posNum; i++, pos++) {
    if (pos->unknown00 & 0x2) {
      u32 resOffset = resTable[pos->unknown0c].unknown04;
      LayerObj *object = static_cast<LayerObj *>(LayerObjManager::createStaticObj(static_cast<const u8 *>(unknownb8) + resOffset));
      f32 info[4];
      LayerObjUtil::getLayoutInfo(info, pos, static_cast<LayerCenterType>(object->unknown198), object->unknown194, object->unknown196);
      object->setInitPosScl(info[0], info[1], info[2], info[3]);
      unknown258.unknown002(object);
    }
  }
  unknown180 = 1.0f;
  unknown184 = 1.0f;
  unknown188 = 1.0f;
  unknown18c = 1.0f;
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = 0;
  unknown196 = 0;
}

LayerObjTopLayout::LayerObjTopLayout() : unknown400(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
}

LayerObjTopLayout::~LayerObjTopLayout() {
  baseRelease();
  workLayoutRelease();
  workListRelease();
}

void LayerObjTopLayout::finalRender() {
  if (unknown2a0.unknown30 != nullptr) {
    unknown2a0.unknown30->finalRender();
  }
  if ((unknown2a0.unknown118.unknown00 & 0xc) == 0xc) {
    LayerShdManager *shader = LayerManager::get()->unknown58;
    shader->setShaderMaskOff();
    shader->setupMainRenderTarget();
    shader->resetViewPort();
    LayerObjTopTexObj *texture = unknown2a0.unknown118.unknown20;
    if (!(texture->unknowna8 & 0x90000)) {
      texture->finalRender();
    }
  }
}

} // namespace layer
