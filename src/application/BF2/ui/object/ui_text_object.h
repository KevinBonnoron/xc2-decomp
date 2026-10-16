#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ui_object.h"
#include "ui/ui_str.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UITextObject : public UIObject {
public:
  static mm::mtl::RTTI m_rtti;

  void applyText(const char *text);
  void setText(const UIStr &text);
  void setTextAlignH(u8 align);
  void setTextAlignV(u8 align);
  u8 getTextAlignH();
  u8 getTextAlignV();
  void setBorderWeight(f32 weight);
  f32 getBorderWeight();
  void setSlopeRot(f32 rot);
  f32 getSlopeRot();
  void setTextFacePattern(u32 index);

  UIStr baseText;
  UIStr text;
  u16 style;
  u32 facePatternIndex;
};

static_assert(offsetof(UITextObject, baseText) == 0x108, "");
static_assert(offsetof(UITextObject, text) == 0x120, "");
static_assert(offsetof(UITextObject, style) == 0x138, "");
static_assert(offsetof(UITextObject, facePatternIndex) == 0x13c, "");

} // namespace ui
