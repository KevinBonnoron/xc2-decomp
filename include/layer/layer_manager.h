#pragma once
#include <stddef.h>

#include "dr/dr_draw_callback.h"
#include "layer/layer_acc_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class Scn;
class WinProc;
} // namespace ml

namespace layer {

class LayerFontManager;
class LayerObjManager;
class LayerShdManager;

class LayerManager : public ml::IDrDrawCallback, public mm::mtl::PtrSingleton<LayerManager> {
public:
  void setFrameRate(f32 rate);
  f32 getScreenWidth() const;
  f32 getScreenHeight() const;
  void openDebugWindow(ml::WinProc *window);
  LayerManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, unsigned int size);
  ~LayerManager() override;
  void tail();
  void begin() override;
  void end() override;
  void apply(const ml::IDrDrawWorkInfo *info) override;
  void opacityRender(const ml::IDrDrawWorkInfo *info) override;
  void alphaRender(const ml::IDrDrawWorkInfo *info) override;
  void lastRender(const ml::IDrDrawWorkInfo *info) override;
  void finalRender(const ml::IDrDrawWorkInfo *info) override;

  static s32 s_nStkIdx;
  static s32 s_nDebIdx;

  u8 _10[0x20 - 0x10];
  mtl::ALLOC_HANDLE m_topMem;
  mtl::ALLOC_HANDLE m_dataMem;
  mtl::ALLOC_HANDLE m_workMem;
  mtl::ALLOC_HANDLE m_gxMem;
  u8 _30[0x58 - 0x30];
  LayerShdManager *m_shdManager;
  LayerObjManager *m_objManager;
  LayerFontManager *m_fontManager;
  u8 _70[0x7c - 0x70];
  f32 m_frameRate;
  f32 m_frameTime;
  f32 m_fontBorderWeight;
  f32 m_screenPosWidth;
  f32 m_screenPosHeight;
  f32 m_screenSclWidth;
  f32 m_screenSclHeight;
  u8 _98[0x9c - 0x98];
  LayerCoordinate m_coordinate;
  u8 _a0[0xb0 - 0xa0];
};

static_assert(offsetof(LayerManager, m_topMem) == 0x20, "");
static_assert(offsetof(LayerManager, m_shdManager) == 0x58, "");
static_assert(offsetof(LayerManager, m_frameRate) == 0x7c, "");
static_assert(offsetof(LayerManager, m_coordinate) == 0x9c, "");
static_assert(sizeof(LayerManager) == 0xb0, "");

} // namespace layer
