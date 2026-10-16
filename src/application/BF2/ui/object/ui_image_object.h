#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ui_object.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIImageObject : public UIObject {
public:
  static mm::mtl::RTTI m_rtti;

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

  u8 _108[0x118 - 0x108];
  bool playbackControl;
};

static_assert(offsetof(UIImageObject, playbackControl) == 0x118, "");

} // namespace ui
