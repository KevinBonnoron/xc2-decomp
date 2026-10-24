#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ui_object.h"

namespace fw {
class ModelObject;
}

namespace layer {
class LayerBase;
}

namespace ml {
class ScnRenderDrViewCtrl;
}

namespace mm {
namespace mtl {
class IAllocator;
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UILayoutObject;

class UIScreenObject : public UIObject {
public:
  enum Mode {
    MODE_RENDER_VIEW = 0,
    MODE_ON_MEMORY = 1,
  };

  struct OnMemoryInfo {
    u8 textureSlot;
    u8 memType;
  };

  static mm::mtl::RTTI m_rtti;

  UIScreenObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name);
  virtual ~UIScreenObject();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual u32 duplicateImpl(u32 parent);

  static UIScreenObject *create(UILayoutObject *parent, ml::ScnRenderDrViewCtrl *viewCtrl, fw::ModelObject *model, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  static UIScreenObject *createOnMemory(UILayoutObject *parent, u32 width, u32 height, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator, const OnMemoryInfo &info);
  u32 getOnMemoryPixelSize() const;
  void *getOnMemoryBuffer() const;
  void swapOnMemoryBuffer();

  u32 mode;
  u8 _10c[0x110 - 0x10c];
  union {
    u32 renderIndex;
    OnMemoryInfo onMemoryInfo;
  };
  u8 _114[0x118 - 0x114];
  fw::ModelObject *model;
};

static_assert(offsetof(UIScreenObject, mode) == 0x108, "");
static_assert(offsetof(UIScreenObject, renderIndex) == 0x110, "");
static_assert(offsetof(UIScreenObject, onMemoryInfo) == 0x110, "");
static_assert(offsetof(UIScreenObject, model) == 0x118, "");
static_assert(sizeof(UIScreenObject) == 0x120, "");

} // namespace ui
