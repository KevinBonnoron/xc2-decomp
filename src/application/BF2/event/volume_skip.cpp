#include "event/volume_skip.h"

#include "event/volume_player.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VolumeSkip::DEF_VOL = 0.0f;
const f32 VolumeSkip::DEF_IN_FR = 15.0f;
const f32 VolumeSkip::DEF_OUT_FR = 15.0f;

VolumeSkip::VolumeSkip() { clear(); }

void VolumeSkip::clear() {
  unknown08 = 0;
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    unknown0c[i] = 1.0f;
  }
  unknown44 = DEF_VOL;
}

void VolumeSkip::set(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, TYPE_COUNT> *resetVolumes) {
  if (isEnable) {
    unknown08 |= FLAG_ENABLE;
  } else {
    unknown08 &= ~FLAG_ENABLE;
  }
  unknown44 = volume;
  unknown48 = inFrame;
  unknown4c = outFrame;
  if (resetVolumes != nullptr) {
    for (u32 i = 0; i < TYPE_COUNT; i++) {
      unknown0c[i] = (*resetVolumes)[i];
    }
  } else {
    for (u32 i = 0; i < TYPE_COUNT; i++) {
      unknown0c[i] = 1.0f;
    }
  }
}

void VolumeSkip::start() {
  if ((unknown08 & (FLAG_ENABLE | FLAG_START)) != FLAG_ENABLE) {
    return;
  }
  mm::mtl::Singleton<VolumePlayer>::get().change(1, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(2, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(4, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(5, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(6, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(7, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(8, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(9, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(11, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(12, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(13, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(14, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(15, unknown44, unknown48);
  mm::mtl::Singleton<VolumePlayer>::get().change(16, unknown44, unknown48);
  unknown08 |= FLAG_START;
}

void VolumeSkip::end() {
  if ((unknown08 & FLAG_START) == 0) {
    return;
  }
  mm::mtl::Singleton<VolumePlayer>::get().reset(1, unknown0c[0], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(2, unknown0c[1], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(4, unknown0c[2], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(5, unknown0c[3], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(6, unknown0c[4], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(7, unknown0c[5], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(8, unknown0c[6], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(9, unknown0c[7], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(11, unknown0c[8], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(12, unknown0c[9], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(13, unknown0c[10], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(14, unknown0c[11], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(15, unknown0c[12], unknown4c);
  mm::mtl::Singleton<VolumePlayer>::get().reset(16, unknown0c[13], unknown4c);
  unknown08 &= ~FLAG_START;
}

void VolumeSkip::setResetVolume(TYPE type, f32 volume) { unknown0c[type] = volume; }

} // namespace event
