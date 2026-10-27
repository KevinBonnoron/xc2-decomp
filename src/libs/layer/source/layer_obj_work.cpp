#include "layer/layer_obj_work.h"

#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"
#include "layer/layer_vertex_obj.h"
#include "mtl/mem_manager.h"

namespace layer {

f32 LayerObjWork::getMaxSecond() const { return unknown298->unknown00->unknown18 * unknown298->unknown00->unknown1c * LayerManager::get()->unknown7c; }

f32 LayerObjWork::getSecond() const { return unknown2b0->unknown00 * LayerManager::get()->unknown7c; }

void LayerObjWork::setSecond(f32 second) { unknown2b0->unknown00 = LayerManager::get()->unknown80 * second; }

void LayerObjWork::resetAddTexutre(u32 index) { unknown2c0.resetAddTexutre(index); }

void LayerObjWork::resetAddAllTexutre() { unknown2c0.resetAddAllTexutre(); }

namespace {

struct unknown004 {
  u8 _00[0x10];
  u32 unknown10; // Inferred role: offset of the vertex resource; original member name unknown.
};

} // namespace

void LayerObjWork::workCreate() {
  u32 offset = static_cast<const unknown004 *>(unknownb8)->unknown10;
  if (offset != 0) {
    unknown270 = LayerManager::get()->unknown58->unknown38->createVertexObj(static_cast<const u8 *>(unknownb8) + offset);
  }
}

void LayerObjWork::workRelease() {
  unknown2c0.clear();
  if (unknown270 != nullptr) {
    unknown270->release();
    unknown270 = nullptr;
  }
  if (unknown278 != nullptr) {
    unknown278->release();
    unknown278 = nullptr;
  }
  if (unknown290 != nullptr) {
    mtl::MemManager::deallocate(unknown290, 0, false);
    unknown290 = nullptr;
  }
}

void LayerObjWork::setupDefTexList() {
  for (s32 i = 0; i < static_cast<s32>(unknown288); i++) {
    unknown280[i] = unknown278->getTexture(i);
  }
}

void LayerObjWork::updapteAddTexList() { unknown2c0.updateTexutre(unknown280, unknown278); }

void LayerObjWork::calcFrmParm(s32 count) {
  for (s32 i = 0; i < count; i++) {
    unknown2b0[i].unknown00 = 0.0f;
    unknown2b0[i].unknown04 = 0.0f;
  }
  unknown298->unknown80 = static_cast<f32>(unknown298->unknown00->unknown18);
  unknown298->unknown84 = 0;
  unknown2b8 = 0;
}

} // namespace layer
