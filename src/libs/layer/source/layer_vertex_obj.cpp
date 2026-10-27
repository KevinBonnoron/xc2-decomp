#include "layer/layer_vertex_obj.h"

#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerVertexMan::LayerVertexMan(LayerManager *manager) : unknown18(manager) {}

LayerVertexObj::LayerVertexObj(const u8 *data, LayerManager *manager, LayerVertexMan *vertexMan) : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(1), unknown60(vertexMan) {
  unknown1c = -1;
  unknown20 = nullptr;
  unknown28 = 0;
  unknown2c = 0;
  setupVertex(data, manager);
}

void LayerVertexObj::vertexRelease() {
  if (unknown20 != nullptr) {
    for (s32 i = 0; i < unknown28; i++) {
      unknown48[i].~CGLibVtxVertex();
    }
    for (s32 i = 0; i < unknown2c; i++) {
      unknown50[i].~CGLibVtxIndex();
    }
    unknown58->~CGLibVtlMemPool();
    if (unknown20 != nullptr) {
      mtl::MemManager::deallocate(unknown20, 0, false);
      unknown20 = nullptr;
    }
  }
}

bool LayerVertexObj::setVertex(u32 index) {
  if (unknown1c == index) {
    return false;
  }
  unknown1c = index;
  grlib::CGLibCtlVertex::setVertex(unknown48[index]);
  return true;
}

void LayerVertexObj::render(u32 index) { unknown50[index].drawIndex(); }

void LayerVertexObj::release() {
  LayerLinkList<LayerVertexObj> *list = unknown60;
  s32 count = unknown18 - 1;
  if (unknown18 <= 0) {
    count = 0;
  }
  unknown18 = count;
  if (count <= 0) {
    list->unknown001(this);
    vertexRelease();
    delete this;
  }
}

void LayerVertexMan::releaseVertexObj(LayerVertexObj *vertexObj) {
  s32 count = vertexObj->unknown18 - 1;
  if (vertexObj->unknown18 <= 0) {
    count = 0;
  }
  vertexObj->unknown18 = count;
  if (count <= 0) {
    unknown001(vertexObj);
    vertexObj->vertexRelease();
    delete vertexObj;
  }
}

LayerVertexObj *LayerVertexMan::createVertexObj(const u8 *data) {
  for (LayerVertexObj *vertexObj = unknown00; vertexObj != nullptr; vertexObj = vertexObj->unknown08) {
    if (vertexObj->unknown10 == data) {
      vertexObj->unknown18++;
      return vertexObj;
    }
  }

  LayerVertexObj *vertexObj = new (unknown18->unknown28) LayerVertexObj(data, unknown18, this);
  if (vertexObj != nullptr) {
    unknown002(vertexObj);
  }
  return vertexObj;
}

LayerVertexMan::~LayerVertexMan() {
  LayerVertexObj *vertexObj = unknown00;
  while (vertexObj != nullptr) {
    LayerVertexObj *next = vertexObj->unknown08;
    vertexObj->vertexRelease();
    delete vertexObj;
    vertexObj = next;
  }
  unknown10 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void LayerVertexObj::begin() { unknown1c = -1; }

} // namespace layer
