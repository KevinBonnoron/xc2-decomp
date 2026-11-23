#pragma once
#include <stddef.h>

#include "dr/dr_draw_callback.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_handle_allocator.h"
#include "layer/layer_mem_handle_allocator.h"
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
class LayerRceManager;
class LayerShdManager;

class LayerManager : public ml::IDrDrawCallback, public mm::mtl::PtrSingleton<LayerManager> {
public:
  void setFrameRate(f32 rate);
  f32 getScreenWidth() const;
  f32 getScreenHeight() const;
  void openDebugWindow(ml::WinProc *window);
  LayerManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, unsigned int size);
  void beginFastSetup();
  ~LayerManager() override;
  void tail();
  f32 getScreenDivWidth() const;
  f32 getScreenDivHeight() const;
  f32 getScreenCalcSclWidth() const;
  f32 getScreenCalcSclHeight() const;
  f32 getScreenCalcPosWidth() const;
  f32 getScreenCalcPosHeight() const;
  f32 getScreenRatioHeight() const;
  void begin() override;
  void end() override;
  void apply(const ml::IDrDrawWorkInfo *info) override;
  void finalRender(const ml::IDrDrawWorkInfo *info) override;
  void loadWait();
  void defSetup();
  void reLoadShd();
  void opacityRender(const ml::IDrDrawWorkInfo *info) override;
  void alphaRender(const ml::IDrDrawWorkInfo *info) override;
  void lastRender(const ml::IDrDrawWorkInfo *info) override;

  static s32 s_nStkIdx;
  static s32 s_nDebIdx;
  static s32 s_nTriIdx;

  void (LayerManager::*unknown10)();                 // Inferred role: setup func; original member name unknown.
  mtl::ALLOC_HANDLE unknown20;                       // Inferred role: top mem; original member name unknown.
  mtl::ALLOC_HANDLE unknown24;                       // Inferred role: data mem; original member name unknown.
  mtl::ALLOC_HANDLE unknown28;                       // Inferred role: work mem; original member name unknown.
  mtl::ALLOC_HANDLE unknown2c;                       // Inferred role: gx mem; original member name unknown.
  LayerHandleAllocator unknown30;                    // Inferred role: work mem allocator; original member name unknown.
  LayerHandleAllocator unknown40;                    // Inferred role: gx mem allocator; original member name unknown.
  ml::Scn *unknown50;                                // Inferred role: scn; original member name unknown.
  LayerShdManager *m_layerShdManager;                // Inferred role: shd manager; original member name unknown.
  LayerObjManager *m_layerObjManager;                // Inferred role: object manager; original member name unknown.
  LayerFontManager *m_layerFontManager;              // Inferred role: font manager; original member name unknown.
  LayerRceManager *m_layerRceManager;                // Inferred role: rce manager; original member name unknown.
  u32 unknown78;                                     // Inferred role: flags; original member name unknown.
  f32 m_frameRate;                                   // Inferred role: frame rate; named after the game accessor layer::LayerAccManager::getFrameRate.
  f32 unknown80;                                     // Inferred role: frame time; original member name unknown.
  f32 m_fontBorderWeight;                            // Inferred role: font border weight; named after the game accessor layer::LayerAccManager::getFontBorderWeight.
  f32 m_screenPosWidth;                              // Inferred role: screen pos width; named after the game accessor layer::LayerAccManager::getScreenPosWidth.
  f32 m_screenPosHeight;                             // Inferred role: screen pos height; named after the game accessor layer::LayerAccManager::getScreenPosHeight.
  f32 unknown90;                                     // Inferred role: screen scl width; original member name unknown.
  f32 m_screenSclHeight;                             // Inferred role: screen scl height; named after the game accessor layer::LayerAccManager::getScreenSclHeight.
  f32 unknown98;                                     // Inferred role: initialised to 0.003125; original member name unknown.
  LayerCoordinate m_coordinate;                      // Inferred role: coordinate; named after the game accessor layer::LayerAccManager::getCoordinate.
  LayerMemHandleAllocator m_layerMemHandleAllocator; // Inferred role: work mem allocator; original member name unknown.
};

static_assert(offsetof(LayerManager, unknown10) == 0x10, "");
static_assert(offsetof(LayerManager, unknown20) == 0x20, "");
static_assert(offsetof(LayerManager, m_layerShdManager) == 0x58, "");
static_assert(offsetof(LayerManager, m_frameRate) == 0x7c, "");
static_assert(offsetof(LayerManager, m_coordinate) == 0x9c, "");
static_assert(sizeof(LayerManager) == 0xb0, "");

} // namespace layer
