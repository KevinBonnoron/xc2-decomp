#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace layer {

class LayerBase;

enum LayerFontHorizontal {};
enum LayerFontVertical {};
enum LayerFontDisplayArea {};
enum LayerFontSetting {
  LAYER_FONT_SETTING_VERTICAL = 2,
};

class LayerAccFontObj : public LayerAccObjBase {
public:
  LayerAccFontObj(LayerBase *layer);
  void setHorizontal(LayerFontHorizontal horizontal);
  void setVertical(LayerFontVertical vertical);
  void setDisplayArea(LayerFontDisplayArea area);
  void setDispSetting(LayerFontSetting setting);
  void setBorderWeight(f32 weight);
  void setSlopeRot(f32 rot);
  LayerFontHorizontal getHorizontal() const;
  LayerFontVertical getVertical() const;
  LayerFontDisplayArea getDisplayArea() const;
  LayerFontSetting getDispSetting() const;
  f32 getBorderWeight() const;
  f32 getSlopeRot() const;
  u16 getFontPixelX() const;
  u16 getFontPixelY() const;
  u16 getFontPixelWidth() const;
  u16 getFontPixelHeight() const;
  void setMsg(const char *text, const LayerBase *res, const LayerBase *style, u32 flags);
  void setMsg(const wchar_t *text, const LayerBase *res, const LayerBase *style, u32 flags);
  void setMsg(const char *text, const LayerBase *res, u32 flags);
  void setMsg(const wchar_t *text, const LayerBase *res, u32 flags);
  void setMsg(const char *text);
  void setMsg(const wchar_t *text);
  void setColorMap(const LayerBase *colorMap, u32 index);
};

} // namespace layer
