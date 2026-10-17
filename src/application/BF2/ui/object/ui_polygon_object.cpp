#include "ui/object/ui_polygon_object.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_format.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_acc_poly_obj.h"
#include "layer/layer_obj_manager.h"
#include "mm_mtl/array.h"
#include "mm_mtl/bitflag.h"
#include "scn/scn_render_dr_sys.h"
#include "ui/object/ui_layout_object.h"
#include "ui/shape/ui_shape.h"
#include "ui/shape/ui_shape_particle.h"
#include "ui/shape/ui_shape_ring.h"
#include "ui/shape/ui_shape_simple_face.h"
#include "ui/ui_object_base.h"
#include "ui/ui_util.h"

namespace ui {

UIPolygonObject::UIPolygonObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name)
    : UIObject(layer, name, UI_OBJECT_TYPE_POLYGON), shape(nullptr), streamId(0), _134(), capture(nullptr) {}

UIPolygonObject::~UIPolygonObject() {
  if (shape != nullptr) {
    delete shape;
    shape = nullptr;
  }
}

UIPolygonObject *UIPolygonObject::create(UILayoutObject *parent, const PolygonInfo &info, const void *data, u32 streamId,
                                         const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  if (data != nullptr) {
    layer::LayerAccFormat format(data);
    if (format.mask) {
      return nullptr;
    }
  }

  UIPolygonObject *polygon = createObject(parent, info, name, allocator);
  if (polygon == nullptr) {
    return nullptr;
  }

  if (polygon->info.shapeType == SHAPE_TYPE_PARTICLE) {
    polygon->flags.set(UI_OBJECT_FLAG_IGNORE_ROT);
  }
  polygon->streamId = streamId;
  polygon->capture = nullptr;
  if (data != nullptr) {
    layer::LayerAccPolyObj acc(polygon->layer);
    acc.setTexutre(data);
  }
  return polygon;
}

UIPolygonObject *UIPolygonObject::createObject(UILayoutObject *parent, const PolygonInfo &info, const mm::mtl::FixStr<32> &name,
                                               mm::mtl::IAllocator *allocator) {
  UIShape *shape = createShape(info, allocator);
  if (shape == nullptr) {
    return nullptr;
  }

  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->layer);
    layer =
        layoutAcc.createPolyObj(info.width, info.height, shape->vertices.size(), shape->indices.size(), static_cast<layer::LayerPrimitiveType>(0));
  } else {
    layer::LayerAccManager manager;
    layer = manager.createPolyObj(info.width, info.height, shape->vertices.size(), shape->indices.size(), static_cast<layer::LayerPrimitiveType>(0));
  }
  if (layer == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 222
  UIPolygonObject *polygon = new (allocator, 16, __FILE__, __LINE__) UIPolygonObject(layer, name.c_str());
  if (polygon == nullptr) {
    return nullptr;
  }
  polygon->info = info;
  polygon->shape = shape;
  return polygon;
}

UIPolygonObject *UIPolygonObject::create(UILayoutObject *parent, const PolygonInfo &info, ml::ScnRenderDrCapture *capture,
                                         const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  UIPolygonObject *polygon = createObject(parent, info, name, allocator);
  if (polygon == nullptr) {
    return nullptr;
  }
  polygon->streamId = 0;
  polygon->capture = capture;
  layer::LayerAccPolyObj acc(polygon->layer);
  acc.setTexutre(*capture->texture);
  return polygon;
}

void UIPolygonObject::apply() {
  UIObject::apply();
  if (shape == nullptr) {
    return;
  }

  shape->update(handle);
  if (!shape->dirty || shape->indexRange == 0) {
    return;
  }

  layer::LayerAccPolyObj acc(layer);
  acc.LockVertex();
  for (u32 i = 0; i < static_cast<u32>(shape->vertices.size()); i++) {
    layer::LayerPolyVertex vertex = shape->vertices[i];
    vertex.x = vertex.x * 0.5f + 0.5f;
    vertex.y = vertex.y * 0.5f + 0.5f;
    acc.setVertex(i, vertex);
  }
  acc.UnlockVertex();
  acc.LockIndex();
  for (u32 i = 0; i < static_cast<u32>(shape->indices.size()); i++) {
    acc.setIndex(i, shape->indices[i]);
  }
  acc.UnlockIndex();
  acc.setIndexInfo(0, shape->indexRange);
  shape->dirty = false;
}

u32 UIPolygonObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  layer::LayerAccObjBase acc(layer);
  UIPolygonObject *polygon;
  if (capture != nullptr) {
    polygon = create(layout, info, capture, name.c_str(), UIUtil::getProgAllocator());
  } else {
    polygon = create(layout, info, acc.getResData(), streamId, name.c_str(), UIUtil::getProgAllocator());
  }
  if (polygon == nullptr) {
    return 0;
  }

  polygon->addRef();
  u32 handle = layout->addChild(parent, polygon);
  polygon->release();
  return handle;
}

UIShape *UIPolygonObject::createShape(const PolygonInfo &info, mm::mtl::IAllocator *allocator) {
  UIShape *shape = nullptr;
  switch (info.shapeType) {
  case SHAPE_TYPE_SIMPLE_FACE:
// __LINE__ is the line argument of the operator new call.
#line 239
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeSimpleFace(info.vertexNum);
    break;
  case SHAPE_TYPE_RING:
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeRing(info.ring.num, info.ring.weight);
    break;
  case SHAPE_TYPE_PARTICLE:
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeParticle(info.particle.data, info.particle.size, info.width, info.height);
    break;
  }
  return shape;
}

const mm::mtl::RTTI *UIPolygonObject::getRTTI() const { return &m_rtti; }

} // namespace ui
