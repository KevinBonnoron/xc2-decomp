#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ui_object.h"
#include "ui/ui_str.h"

namespace layer {
class LayerBase;
}

namespace mm {
namespace mtl {
class IAllocator;
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UILayoutObject;

class UITextObject : public UIObject {
public:
  static mm::mtl::RTTI m_rtti;

  UITextObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name);
  virtual ~UITextObject();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void apply();
  virtual void getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const;
  virtual void getTransformPosOffs(mm::Vec2 &offset);
  virtual u32 duplicateImpl(u32 parent);

  static UITextObject *create(UILayoutObject *parent, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator);
  void applyText(const char *text);
  void setText(const UIStr &text);
  const char *getBaseText();
  void getStyleSize(u16 &width, u16 &height);
  void setTextAlignH(u8 align);
  void setTextAlignV(u8 align);
  u8 getTextAlignH();
  u8 getTextAlignV();
  void setBorderWeight(f32 weight);
  f32 getBorderWeight();
  void setSlopeRot(f32 rot);
  f32 getSlopeRot();
  void setTextFacePattern(u32 index);
  void reloadText();

  UIStr unknown108; // Inferred role: base text; original member name unknown.
  UIStr unknown120; // Inferred role: text; original member name unknown.
  u16 unknown138;   // Inferred role: style; original member name unknown.
  u32 unknown13c;   // Inferred role: face pattern index; original member name unknown.
};

static_assert(offsetof(UITextObject, unknown108) == 0x108, "");
static_assert(offsetof(UITextObject, unknown120) == 0x120, "");
static_assert(offsetof(UITextObject, unknown138) == 0x138, "");
static_assert(offsetof(UITextObject, unknown13c) == 0x13c, "");
static_assert(sizeof(UITextObject) == 0x140, "");

} // namespace ui
