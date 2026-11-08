#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct SDataIdea;

class GfMenuObjIdeaGram : public GfMenuObject {
public:
  GfMenuObjIdeaGram(u32 handle);
  ~GfMenuObjIdeaGram() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setIdeaPoint(GfMenuCallContext *context, u8 type, u32 point);
  static void setIdeaPointFromDriver(GfMenuCallContext *context, u32 driver);
  static void setIdeaPointFromData(GfMenuCallContext *context, const SDataIdea &data);
  static void setIdeaPointFromBlade(GfMenuCallContext *context, u32 blade);
  static void addIdeaPoint(GfMenuCallContext *context, u8 type, int value, bool flag);
  static void addIdeaLevel(GfMenuCallContext *context, u8 type, int value, bool flag);
};

} // namespace gf
