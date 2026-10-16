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
    CATE_BGM,
    CATE_VOI,
    CATE_BTL,
    CATE_FLD,
    CATE_GMK,
    CATE_ENV,
    CATE_WEA,
    CATE_EVTCS,
    CATE_EVTVOI,
    CATE_EVTSE,
    CATE_CHRSE,
    CATE_NOSLOW,
    CATE_ENEVOI,
    CATE_NAREVOI,
    CATE_COUNT,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_DETAIL = 1 << 1,
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
  void setSeamlessVolume(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, VolumeSeamless::RESET_VOLUME_COUNT> *resetVolumes);
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
  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      dispFlags |= flag;
    } else {
      dispFlags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  mm::mtl::FixedArray<f32, CATE_COUNT> mResetCategoryVolumes;
  VolumeSeamless mSeamless;
  VolumeSkip mSkip;
};

static_assert(sizeof(VolumeManager) == 0xf0, "");

} // namespace event
