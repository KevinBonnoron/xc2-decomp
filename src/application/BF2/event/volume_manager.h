#pragma once
#include "event/i_manager.h"
#include "event/volume_seamless.h"
#include "event/volume_skip.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class VolumeManager : public IManager, public mm::mtl::Singleton<VolumeManager> {
public:
  enum CATE {
    CATE_UNKNOWN_0,  // Inferred role: bgm; original name unknown.
    CATE_UNKNOWN_1,  // Inferred role: voi; original name unknown.
    CATE_UNKNOWN_2,  // Inferred role: btl; original name unknown.
    CATE_UNKNOWN_3,  // Inferred role: fld; original name unknown.
    CATE_UNKNOWN_4,  // Inferred role: gmk; original name unknown.
    CATE_UNKNOWN_5,  // Inferred role: env; original name unknown.
    CATE_UNKNOWN_6,  // Inferred role: wea; original name unknown.
    CATE_UNKNOWN_7,  // Inferred role: evtcs (label "EVTCS" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_8,  // Inferred role: evtvoi (label "EVTVO" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_9,  // Inferred role: evtse (label "EVTSE" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_10, // Inferred role: chrse (label "CHRSE" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_11, // Inferred role: noslow (label "(NOSLOW)" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_12, // Inferred role: enevoi (label "ENEVO" of VolumeManager::render); original name unknown.
    CATE_UNKNOWN_13, // Inferred role: narevoi (label "NAREVO" of VolumeManager::render); original name unknown.
    CATE_COUNT,
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
    DISP_FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: detail flag; original name unknown.
  };

  VolumeManager();
  virtual ~VolumeManager() {}
  void clear();
  void setResetCategoryVolume(const mm::mtl::FixedArray<f32, CATE_COUNT> *volumes);
  void resetCategoryVolume(CATE cate, f32 frame);
  void init();
  void update();
  void render();
  void changeCategoryVolume(CATE cate, f32 volume, f32 frame);
  void setSeamlessVolume(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, VolumeSeamless::RESET_VOLUME_UNKNOWN_13> *resetVolumes);
  void startSeamlessVolume(f32 frame);
  void endSeamlessVolume(f32 frame);
  void maskSeamlessVolume(VolumeSeamless::MASK_TYPE type, bool isMask);
  void setSkipVolume(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, CATE_COUNT> *resetVolumes);
  void startSkipVolume();
  void endSkipVolume();
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setDispDetail(bool isDisp);
  bool isDispDetail() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  u32 unknown10;                                  // Inferred role: flags; original member name unknown.
  u32 unknown14;                                  // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedArray<f32, CATE_COUNT> unknown18; // Inferred role: reset category volumes; original member name unknown.
  VolumeSeamless unknown50;                       // Inferred role: seamless; original member name unknown.
  VolumeSkip unknowna0;                           // Inferred role: skip; original member name unknown.
};

static_assert(sizeof(VolumeManager) == 0xf0, "");

} // namespace event
