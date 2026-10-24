#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ui_object.h"

namespace layer {
class LayerBase;
}

namespace ml {
class ScnRenderDrCapture;
}

namespace mm {
namespace mtl {
class IAllocator;
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UILayoutObject;
class UIShape;

class UIPolygonObject : public UIObject {
public:
  enum ShapeType {
    SHAPE_TYPE_SIMPLE_FACE = 1,
    SHAPE_TYPE_RING = 2,
    SHAPE_TYPE_PARTICLE = 3,
  };

  struct RingInfo {
    u32 unknown00; // Inferred role: num; original member name unknown.
    f32 unknown04; // Inferred role: weight; original member name unknown.
  };

  struct ParticleInfo {
    void *unknown00; // Inferred role: data; original member name unknown.
    u32 unknown08;   // Inferred role: size; original member name unknown.
  };

  struct PolygonInfo {
    u32 unknown00; // Inferred role: width; original member name unknown.
    u32 unknown04; // Inferred role: height; original member name unknown.
    u32 unknown08; // Inferred role: shape type; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    union {
      u32 vertexNum;
      RingInfo ring;
      ParticleInfo particle;
    };
  };

  static mm::mtl::RTTI m_rtti;

  UIPolygonObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name);
  virtual ~UIPolygonObject();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void apply();
  virtual u32 duplicateImpl(u32 parent);

  static UIPolygonObject *create(UILayoutObject *parent, const PolygonInfo &info, const void *data, u32 streamId, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  static UIPolygonObject *createObject(UILayoutObject *parent, const PolygonInfo &info, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  static UIPolygonObject *create(UILayoutObject *parent, const PolygonInfo &info, ml::ScnRenderDrCapture *capture, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  static UIShape *createShape(const PolygonInfo &info, mm::mtl::IAllocator *allocator);

  UIShape *unknown108;    // Inferred role: shape; original member name unknown.
  PolygonInfo unknown110; // Inferred role: info; original member name unknown.
  u32 unknown130;         // Inferred role: stream id; original member name unknown.
  u8 _134[0x136 - 0x134];
  ml::ScnRenderDrCapture *unknown138; // Inferred role: capture; original member name unknown.
};

static_assert(offsetof(UIPolygonObject::PolygonInfo, vertexNum) == 0x10, "");
static_assert(sizeof(UIPolygonObject::PolygonInfo) == 0x20, "");
static_assert(offsetof(UIPolygonObject, unknown108) == 0x108, "");
static_assert(offsetof(UIPolygonObject, unknown110) == 0x110, "");
static_assert(offsetof(UIPolygonObject, unknown130) == 0x130, "");
static_assert(offsetof(UIPolygonObject, unknown138) == 0x138, "");
static_assert(sizeof(UIPolygonObject) == 0x140, "");

} // namespace ui
