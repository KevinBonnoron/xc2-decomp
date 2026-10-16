#include "event/volume_skip.h"

#include "event/volume_player.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VolumeSkip::DEF_VOL = 0.0f;
const f32 VolumeSkip::DEF_IN_FR = 15.0f;
const f32 VolumeSkip::DEF_OUT_FR = 15.0f;

VolumeSkip::VolumeSkip() { clear(); }

void VolumeSkip::clear() {
  flags = 0;
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    mResetVolumes[i] = 1.0f;
  }
  mVolume = DEF_VOL;
}

void VolumeSkip::set(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, TYPE_COUNT> *resetVolumes) {
  if (isEnable) {
    flags |= FLAG_ENABLE;
  } else {
    flags &= ~FLAG_ENABLE;
  }
  mVolume = volume;
  mInFrame = inFrame;
  mOutFrame = outFrame;
  if (resetVolumes != nullptr) {
    for (u32 i = 0; i < TYPE_COUNT; i++) {
      mResetVolumes[i] = (*resetVolumes)[i];
    }
  } else {
    for (u32 i = 0; i < TYPE_COUNT; i++) {
      mResetVolumes[i] = 1.0f;
    }
  }
}

void VolumeSkip::start() {
  if ((flags & (FLAG_ENABLE | FLAG_START)) != FLAG_ENABLE) {
    return;
  }
  mm::mtl::Singleton<VolumePlayer>::get().change(1, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(2, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(4, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(5, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(6, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(7, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(8, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(9, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(11, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(12, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(13, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(14, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(15, mVolume, mInFrame);
  mm::mtl::Singleton<VolumePlayer>::get().change(16, mVolume, mInFrame);
  flags |= FLAG_START;
}

void VolumeSkip::end() {
  if ((flags & FLAG_START) == 0) {
    return;
  }
  mm::mtl::Singleton<VolumePlayer>::get().reset(1, mResetVolumes[0], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(2, mResetVolumes[1], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(4, mResetVolumes[2], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(5, mResetVolumes[3], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(6, mResetVolumes[4], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(7, mResetVolumes[5], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(8, mResetVolumes[6], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(9, mResetVolumes[7], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(11, mResetVolumes[8], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(12, mResetVolumes[9], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(13, mResetVolumes[10], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(14, mResetVolumes[11], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(15, mResetVolumes[12], mOutFrame);
  mm::mtl::Singleton<VolumePlayer>::get().reset(16, mResetVolumes[13], mOutFrame);
  flags &= ~FLAG_START;
}

void VolumeSkip::setResetVolume(TYPE type, f32 volume) { mResetVolumes[type] = volume; }

} // namespace event
