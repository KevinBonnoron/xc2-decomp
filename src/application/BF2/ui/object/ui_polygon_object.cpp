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
    : UIObject(layer, name, UI_OBJECT_TYPE_POLYGON), unknown108(nullptr), unknown130(0), _134(), unknown138(nullptr) {}

UIPolygonObject::~UIPolygonObject() {
  if (unknown108 != nullptr) {
    delete unknown108;
    unknown108 = nullptr;
  }
}

UIPolygonObject *UIPolygonObject::create(UILayoutObject *parent, const PolygonInfo &info, const void *data, u32 streamId, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  if (data != nullptr) {
    layer::LayerAccFormat format(data);
    if (format.unknown05) {
      return nullptr;
    }
  }

  UIPolygonObject *polygon = createObject(parent, info, name, allocator);
  if (polygon == nullptr) {
    return nullptr;
  }

  if (polygon->unknown110.unknown08 == SHAPE_TYPE_PARTICLE) {
    polygon->unknown98.set(UI_OBJECT_FLAG_IGNORE_ROT);
  }
  polygon->unknown130 = streamId;
  polygon->unknown138 = nullptr;
  if (data != nullptr) {
    layer::LayerAccPolyObj acc(polygon->unknownc8);
    acc.setTexutre(data);
  }
  return polygon;
}

UIPolygonObject *UIPolygonObject::createObject(UILayoutObject *parent, const PolygonInfo &info, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  UIShape *shape = createShape(info, allocator);
  if (shape == nullptr) {
    return nullptr;
  }

  layer::LayerBase *layer;
  if (parent != nullptr) {
    layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
    layer = layoutAcc.createPolyObj(info.unknown00, info.unknown04, shape->unknown08.size(), shape->unknown20.size(), static_cast<layer::LayerPrimitiveType>(0));
  } else {
    layer::LayerAccManager manager;
    layer = manager.createPolyObj(info.unknown00, info.unknown04, shape->unknown08.size(), shape->unknown20.size(), static_cast<layer::LayerPrimitiveType>(0));
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
  polygon->unknown110 = info;
  polygon->unknown108 = shape;
  return polygon;
}

UIPolygonObject *UIPolygonObject::create(UILayoutObject *parent, const PolygonInfo &info, ml::ScnRenderDrCapture *capture, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  UIPolygonObject *polygon = createObject(parent, info, name, allocator);
  if (polygon == nullptr) {
    return nullptr;
  }
  polygon->unknown130 = 0;
  polygon->unknown138 = capture;
  layer::LayerAccPolyObj acc(polygon->unknownc8);
  acc.setTexutre(*capture->texture);
  return polygon;
}

void UIPolygonObject::apply() {
  UIObject::apply();
  if (unknown108 == nullptr) {
    return;
  }

  unknown108->update(unknowne8);
  if (!unknown108->unknown3c || unknown108->unknown38 == 0) {
    return;
  }

  layer::LayerAccPolyObj acc(unknownc8);
  acc.LockVertex();
  for (u32 i = 0; i < static_cast<u32>(unknown108->unknown08.size()); i++) {
    layer::LayerPolyVertex vertex = unknown108->unknown08[i];
    vertex.unknown00 = vertex.unknown00 * 0.5f + 0.5f;
    vertex.unknown04 = vertex.unknown04 * 0.5f + 0.5f;
    acc.setVertex(i, vertex);
  }
  acc.UnlockVertex();
  acc.LockIndex();
  for (u32 i = 0; i < static_cast<u32>(unknown108->unknown20.size()); i++) {
    acc.setIndex(i, unknown108->unknown20[i]);
  }
  acc.UnlockIndex();
  acc.setIndexInfo(0, unknown108->unknown38);
  unknown108->unknown3c = false;
}

u32 UIPolygonObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  layer::LayerAccObjBase acc(unknownc8);
  UIPolygonObject *polygon;
  if (unknown138 != nullptr) {
    polygon = create(layout, unknown110, unknown138, unknowna0.c_str(), UIUtil::getProgAllocator());
  } else {
    polygon = create(layout, unknown110, acc.getResData(), unknown130, unknowna0.c_str(), UIUtil::getProgAllocator());
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
  switch (info.unknown08) {
  case SHAPE_TYPE_SIMPLE_FACE:
// __LINE__ is the line argument of the operator new call.
#line 239
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeSimpleFace(info.vertexNum);
    break;
  case SHAPE_TYPE_RING:
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeRing(info.ring.unknown00, info.ring.unknown04);
    break;
  case SHAPE_TYPE_PARTICLE:
    shape = new (allocator, 16, __FILE__, __LINE__) UIShapeParticle(info.particle.unknown00, info.particle.unknown08, info.unknown00, info.unknown04);
    break;
  }
  return shape;
}

const mm::mtl::RTTI *UIPolygonObject::getRTTI() const { return &m_rtti; }

} // namespace ui
