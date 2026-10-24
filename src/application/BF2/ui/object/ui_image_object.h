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

class UIImageObject : public UIObject {
public:
  static mm::mtl::RTTI m_rtti;

  UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name);
  UIImageObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name, u32 type);
  virtual ~UIImageObject();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual u32 duplicateImpl(u32 parent);
  virtual void changeBin(const void *data);

  static UIImageObject *create(UILayoutObject *parent, const void *data, u32 streamId, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator, bool mask);
  static UIImageObject *create(UILayoutObject *parent, ml::ScnRenderDrCapture *capture, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  void setMaskObject(UIImageObject *mask);
  void setImageIndex(u16 index);
  u16 getImageMax();
  u16 getImageIndex();
  void setHFlip(bool flip);
  void setVFlip(bool flip);
  void setExtType(u32 type);
  u32 getExtType();
  void setExtParam(f32 param);
  f32 getExtParam();
  bool hasAnimation();
  void startAnimation(const char *name, bool loop);
  void startAnimationFromID(u32 id, bool loop);
  void startAnimationFromIndex(u32 index, bool loop);
  void stopAnimation();
  bool isPlayingAnimation();
  u32 getAnimationMax();
  const char *getAnimationName(u32 index);
  f32 getAnimationPlaybackLength();
  f32 getAnimationPlaybackTime();
  void setAnimationPlaybackTime(f32 time);
  void applyCapture();

  u32 unknown108;                     // Inferred role: stream id; original member name unknown.
  u16 unknown10c;                     // Inferred role: image index; original member name unknown.
  ml::ScnRenderDrCapture *unknown110; // Inferred role: capture; original member name unknown.
  bool unknown118;                    // Inferred role: playback control; original member name unknown.
};

static_assert(offsetof(UIImageObject, unknown108) == 0x108, "");
static_assert(offsetof(UIImageObject, unknown10c) == 0x10c, "");
static_assert(offsetof(UIImageObject, unknown110) == 0x110, "");
static_assert(offsetof(UIImageObject, unknown118) == 0x118, "");
static_assert(sizeof(UIImageObject) == 0x120, "");

} // namespace ui
