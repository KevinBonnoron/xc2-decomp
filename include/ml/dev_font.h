#pragma once
#include "ml/dev_base.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace ml {
class DevFontLayer;
enum FONT_STYLE : int;

class FontLayer {
public:
  virtual ~FontLayer();
  void font(int x, int y, const char *format, ...);
  void fontColor(const mm::Col4 &color);
  void fontBack(const mm::Col4 &color);
  void fontShadow(bool isShadow);
  void fontFlush(bool isFlush);
  void fontScale(f32 x, f32 y);
  void fontStyle(FONT_STYLE style);
  void fontZ(u32 z);

  u8 _08[0x10 - 0x08];
};

class DevFont : public FontLayer, public DevBase, public mm::mtl::PtrSingleton<DevFont> {
public:
  static bool isInitialized();
  static DevFontLayer *createLayer(const FontLayer *layer);
  static void fontLayer(const FontLayer *layer, int x, int y, const char *text);
  static void fontLayerColor(const FontLayer *layer, const mm::Col4 &color);
  static void fontLayerBack(const FontLayer *layer, const mm::Col4 &color);
  static void fontLayerShadow(const FontLayer *layer, bool isShadow);
  static void fontLayerFlush(const FontLayer *layer, bool isFlush);
  static void fontLayerScale(const FontLayer *layer, f32 x, f32 y);
  static void fontLayerStyle(const FontLayer *layer, FONT_STYLE style);
  static void fontLayerZ(const FontLayer *layer, u32 z);
};

} // namespace ml
