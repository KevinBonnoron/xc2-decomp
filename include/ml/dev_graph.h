#pragma once
#include <stddef.h>

#include "ml/dev_base.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class CriticalSection;
class DevGraphQue;

enum FONT_STYLE : int {
  FONT_STYLE_NORMAL = 0,
};

enum DevGraphModeType {};

namespace dg {

extern s32 s_nVSync;
extern s32 s_nVSyncOld;
extern bool s_bIgnore;
extern DevGraphModeType s_eGraphMode;

CriticalSection &getCriticalSection();

} // namespace dg

class DevGraph : public DevBase, public mm::mtl::PtrSingleton<DevGraph> {
public:
  ~DevGraph() override;
  static f32 fontGetWidth(const char *text, FONT_STYLE style, f32 scale);
  static f32 fontGetHeight(FONT_STYLE style, f32 scale);
  static bool isIgnore();
  static void setIgnore(bool isIgnore);
  static void setRenderMode(DevGraphModeType mode);
  static DevGraphModeType getRenderMode();
  static void grSetViewport(const mm::Rect<int> &viewport, int index);
  static void grSetScissor(const mm::Rect<int> &scissor);
  static void grClearScreen();
  static void grSetClearCol(const mm::Col4 &color);
  static void grSetDoubleSide(bool isDoubleSide);
  static void grSetZMode(bool isTest, bool isWrite);
  static void grSetAlphaBlend(bool isBlend);
  static void grInitContext();
  static void grFlushViewport();
  static int getRootWidth();
  static int getRootHeight();
  static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void setMemPoolBuffer(void *buffer, u32 size);
  static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void releaseMemPoolBuffer(void *buffer);
  static void cmdOpenDisplayList(u32 size);
  static void cmdCloseDisplayList();
  static void cmdAddCreatedList(void *list, u32 size);
  static void cmdSuspendDisplayList(bool isSuspend, bool isFlush);
  static void *cmdGetCurrentAdr();
  static u32 cmdGetRemainSize();
  static void cmdExecDisplayList();
  static void cmdAddDisplayList(void *list, u32 size, u32 flags);
  static bool cmdIsOpenDisplayList();
  static void pushRect(const mm::Rect<int> &viewport, const mm::Rect<int> &scissor, const mm::Rect<int> &renderRect, bool isFlush);
  static void popRect();
  static void getPers(mm::Mat44 &matrix, f32 fovy, f32 near, f32 far);
  static void getOrtho(mm::Mat44 &matrix);
  static f32 getAspect();
  static const mm::Rect<int> &getViewport();
  static const mm::Rect<int> &getRenderPort();
  static int getRenderW();
  static int getRenderH();
  static f32 getScreenScaleW();
  static f32 getVSyncSec();
  static f32 getFrameSyncSec();
  static int getVSync();
  static f32 getMicro2FrameRatio(u32 micro);
  static void setEnableFrustum(bool isEnable);
  static bool getEnableFrustum();
  static void setFrustumPort(const mm::Rect<int> &port);
  static const mm::Rect<int> &getFrustumPort();
  static void renderEnd();
  static void renderSync();
  static void resetSize(s16 width, s16 height);
  static f32 getCost();
  static DevGraphQue *getGraphQue();
  static bool isInitialized();
  static void setVSync(int vsync);
  void wkStandby() override;
  void wkUpdate() override;
  static void setFrameSpd(f32 speed);
  static void addOuterRender(void (*render)());
  static void removeOuterRender(void (*render)());
  static void createGraphDeveice();
  virtual void cmdAddDisplayListFast(void *list, u32 size, u32 flags);
  virtual void grSetViewportSys(const mm::Rect<int> &viewport, int index) = 0;
  virtual void grSetScissorSys(const mm::Rect<int> &scissor) = 0;
  virtual void grInitContextSys();
  virtual void getPersSys(mm::Mat44 &matrix, f32 fovy, f32 near, f32 far) = 0;
  virtual void getOrthoSys(mm::Mat44 &matrix) = 0;
  virtual int getRootWidthSys() = 0;
  virtual int getRootHeightSys() = 0;
  virtual f32 getScreenScaleWSys() = 0;
  virtual f32 getVSyncSecSys() const = 0;
  virtual void renderBeginSys() = 0;
  virtual void renderEndSys() = 0;
  virtual void renderSyncSys() = 0;
  virtual void resetSizeSys(s16 width, s16 height) = 0;
  virtual void fontDrawSys(s16 x, s16 y, f32 scaleX, f32 scaleY, const char *text, const mm::Col4 *color, bool isShadow) = 0;
  virtual f32 fontGetWidthSys(const char *text, FONT_STYLE style, f32 scale) = 0;
  virtual f32 fontGetHeightSys(FONT_STYLE style, f32 scale) = 0;
  virtual f32 getCostSys() const = 0;
  virtual void cmdExecDisplayListSys();
  virtual void cmdAddDisplayListSys(void *list, u32 size, u32 flags);
  virtual void cmdSetupDisplayListSys();
  virtual void cmdTermDisplayListSys();
  virtual void *cmdOpenDisplayListSys(u32 size, bool isSuspend, bool isFlush);
  virtual bool cmdCloseDisplayListSys(bool isFlush);
  virtual void cmdAddCreatedListSys(void *list, u32 size);
  virtual void cmdSuspendDisplayListSys(bool isSuspend, bool isFlush);
  virtual void *cmdGetCurrentAdrSys();
  virtual u32 cmdGetRemainSizeSys() const;
  virtual void *cmdAllocSys(u32 size, u32 alignment);
  virtual void *cmdAlignSys(u32 alignment);
  virtual void *cmdAddOfsSys(u32 offset);
  virtual bool cmdIsOpenDisplayListSys() const;

  u8 _1b8[0x208 - 0x1b8];
  mm::Rect<int> unknown208; // Inferred role: viewport; original member name unknown.
  mm::Rect<int> unknown218; // Inferred role: render port; original member name unknown.
  u8 _228[0x230 - 0x228];
  int unknown230;           // Inferred role: render w; original member name unknown.
  int unknown234;           // Inferred role: render h; original member name unknown.
  mm::Rect<int> unknown238; // Inferred role: frustum port; original member name unknown.
  u8 _248[0x310 - 0x248];
  bool unknown310; // Inferred role: enable frustum; original member name unknown.
  u8 _311[0x318 - 0x311];
  mm::Col4 unknown318; // Inferred role: clear col; original member name unknown.
  f32 unknown328;      // Inferred role: clear depth; original member name unknown.
  u8 _32c[0x330 - 0x32c];
  DevGraphQue *unknown330; // Inferred role: graph que; original member name unknown.
  u8 _338[0x348 - 0x338];
  f32 unknown348; // Inferred role: frame spd; original member name unknown.
  u8 _34c[0x350 - 0x34c];
  void (*unknown350[4])(); // Inferred role: outer renders; original member name unknown.
};

static_assert(offsetof(DevGraph, unknown208) == 0x208, "");
static_assert(offsetof(DevGraph, unknown230) == 0x230, "");
static_assert(offsetof(DevGraph, unknown310) == 0x310, "");
static_assert(offsetof(DevGraph, unknown318) == 0x318, "");
static_assert(offsetof(DevGraph, unknown330) == 0x330, "");
static_assert(offsetof(DevGraph, unknown348) == 0x348, "");
static_assert(offsetof(DevGraph, unknown350) == 0x350, "");

class DevGraphQue {
public:
  u32 getEven();
  bool getOdd();
  void flushViewport();
  void pushRect(const mm::Rect<int> &viewport, const mm::Rect<int> &scissor, const mm::Rect<int> &renderRect, bool isFlush);
  void popRect();

  s32 unknown00; // Inferred role: view; original member name unknown.
};

} // namespace ml
