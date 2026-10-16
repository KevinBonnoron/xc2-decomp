#pragma once
#include "layer/layer_obj_manager.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
}

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class WinProc;
} // namespace ml

namespace layer {

class LayerBase;

enum LayerCoordinate {
  LAYER_COORDINATE_PIXEL = 0,
  LAYER_COORDINATE_NORMALIZED = 1,
};

class LayerAccManager {
public:
  LayerAccManager();
  LayerBase *createObj(const void *data);
  LayerBase *createMaskObj(const void *data);
  LayerBase *createFontObj();
  LayerBase *createLayoutObj();
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
  LayerBase *createMemObj(u32 width, u32 height, LayerMemType type);
  LayerBase *createPolyObj(u32 vertexNum, u32 indexNum, u16 width, u16 height, LayerPrimitiveType type);
  LayerBase *createFilterObj();
  LayerBase *createFontResObj(const void *data);
  LayerBase *createFontIconObj(const void *data);
  LayerBase *createFontStyleObj(const void *data);
  LayerBase *createFontColorMapObj(const void *data);
  f32 getFrameRate() const;
  void setFrameRate(f32 rate);
  f32 getScreenWidth() const;
  f32 getScreenHeight() const;
  f32 getScreenSclWidth() const;
  f32 getScreenSclHeight() const;
  f32 getScreenPosWidth() const;
  f32 getScreenPosHeight() const;
  void setScreenSclWidth(f32 width);
  void setScreenSclHeight(f32 height);
  void setScreenPosWidth(f32 width);
  void setScreenPosHeight(f32 height);
  void setScreenOrgSize(f32 width, f32 height);
  f32 getFontBorderWeight() const;
  void setFontBorderWeight(f32 weight);
  LayerCoordinate getCoordinate() const;
  static bool getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &pos);
  void setCoordinate(LayerCoordinate coordinate);
  f32 getGamma() const;
  void setGamma(f32 gamma);
  void openDebugWindow(ml::WinProc *window);
};

} // namespace layer
