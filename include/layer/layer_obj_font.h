#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

class LayerFontIconObj;
class LayerFontResObj;
class LayerFontStyleObj;

class LayerObjFont : public LayerObj {
public:
  void setMsg(const u8 *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags);
  void setMsg(const wchar_t *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags);
  void setColorMap(const LayerFontIconObj *colorMap, u32 index);
  void setBorderWeight(f32 weight);
  void setSlopeRot(f32 rot);
  f32 getBorderWeight() const;
  f32 getSlopeRot() const;

  u8 _250[0x278 - 0x250];
  const LayerFontResObj *unknown278;   // Inferred role: res; original member name unknown.
  const LayerFontStyleObj *unknown280; // Inferred role: style; original member name unknown.
  const LayerFontIconObj *unknown288;  // Inferred role: icon; original member name unknown.
  u8 _290[0x298 - 0x290];
  u32 unknown298; // Inferred role: msg flags; original member name unknown.
  u8 _29c[0x2a0 - 0x29c];
  u16 unknown2a0; // Inferred role: font pixel x; original member name unknown.
  u16 unknown2a2; // Inferred role: font pixel y; original member name unknown.
  u16 unknown2a4; // Inferred role: font pixel width; original member name unknown.
  u16 unknown2a6; // Inferred role: font pixel height; original member name unknown.
  u32 unknown2a8; // Inferred role: horizontal; original member name unknown.
  u32 unknown2ac; // Inferred role: vertical; original member name unknown.
  u32 unknown2b0; // Inferred role: display area; original member name unknown.
  u32 unknown2b4; // Inferred role: disp setting; original member name unknown.
};

static_assert(offsetof(LayerObjFont, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjFont, unknown298) == 0x298, "");
static_assert(offsetof(LayerObjFont, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjFont, unknown2b4) == 0x2b4, "");

} // namespace layer
