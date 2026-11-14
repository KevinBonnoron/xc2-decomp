#pragma once
#include <stddef.h>

#include "font/font_sys.h"
#include "ml/dev_graph.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevGraphNx : public DevGraph {
public:
  DevGraphNx(const char *name, WorkObj *parent);
  int getRootWidthSys() override;
  int getRootHeightSys() override;
  f32 getCostSys() const override;
  void grSetViewportSys(const mm::Rect<int> &viewport, int index) override;
  void grSetScissorSys(const mm::Rect<int> &scissor) override;
  void getPersSys(mm::Mat44 &matrix, f32 fovy, f32 near, f32 far) override;
  void getOrthoSys(mm::Mat44 &matrix) override;
  void renderBeginSys() override;
  void renderEndSys() override;
  void renderSyncSys() override;
  static u32 thSync(void *argument, void *userData);
  void resetSizeSys(s16 width, s16 height) override;
  u32 fontGetWidthSys(const char *text, FONT_STYLE style, f32 scale) override;
  u32 fontGetHeightSys(FONT_STYLE style, f32 scale) override;
  void fontDrawSys(s16 x, s16 y, f32 scaleX, f32 scaleY, const char *text, const mm::Col4 *color, bool isShadow) override;
  void wkUpdate() override;
  void wkRender() override;
  bool wkStandbyLogin() override;
  static u32 thInitialize(void *argument, void *userData);
  bool wkStandbyLogout() override;
  static u32 thDestroy(void *argument, void *userData);
  static bool initGL();
  static void entrySasakiFont(const char *name);
  f32 getScreenScaleWSys() override { return 1.0f; }
  f32 getVSyncSecSys() const override { return 1.0f / 60.0f; }

  s32 unknown370;     // Inferred role: unknown, cleared by the constructor; original member name unknown.
  FontSys unknown378; // Inferred role: system font; original member name unknown.
  void *unknown6d0;   // Inferred role: font file data; original member name unknown.
  u8 _6d8[0x6e0 - 0x6d8];
};

static_assert(offsetof(DevGraphNx, unknown370) == 0x370, "");
static_assert(offsetof(DevGraphNx, unknown378) == 0x378, "");
static_assert(offsetof(DevGraphNx, unknown6d0) == 0x6d0, "");
static_assert(sizeof(DevGraphNx) == 0x6e0, "");

} // namespace ml
