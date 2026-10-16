#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

namespace GfMenuTypes {
struct Param;
} // namespace GfMenuTypes

class GfMenuFullScreen : public mm::mtl::PtrSingleton<GfMenuFullScreen> {
public:
  static void enableSwitching();
  static void disableSwitching();
  static void overrideFadeOutFrame(u32 frame);
  static bool setInputObject(u32 layer, u32 object);
  static u32 getInputObject(u32 layer);
  static void enableInput(u32 layer);
  static void disableInput();
  static bool isActiveInput(u32 layer);
  static void registLayerParam(u32 layer, const GfMenuTypes::Param &param);
  static bool getLayerParam(u32 layer, GfMenuTypes::Param &param);
  static void removeLayerParam(u32 layer);
  static void registLayerObject(u32 layer, u32 object);
  static void setShadowLayer(u32 layer, bool shadow);
  static u16 getLayerGroup(u32 layer);
};

} // namespace gf
