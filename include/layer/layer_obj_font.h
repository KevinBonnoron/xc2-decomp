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
  const LayerFontResObj *m_res;
  const LayerFontStyleObj *m_style;
  const LayerFontIconObj *m_icon;
  u8 _290[0x298 - 0x290];
  u32 m_msgFlags;
  u8 _29c[0x2a0 - 0x29c];
  u16 m_fontPixelX;
  u16 m_fontPixelY;
  u16 m_fontPixelWidth;
  u16 m_fontPixelHeight;
  u32 m_horizontal;
  u32 m_vertical;
  u32 m_displayArea;
  u32 m_dispSetting;
};

static_assert(offsetof(LayerObjFont, m_res) == 0x278, "");
static_assert(offsetof(LayerObjFont, m_msgFlags) == 0x298, "");
static_assert(offsetof(LayerObjFont, m_fontPixelX) == 0x2a0, "");
static_assert(offsetof(LayerObjFont, m_dispSetting) == 0x2b4, "");

} // namespace layer
