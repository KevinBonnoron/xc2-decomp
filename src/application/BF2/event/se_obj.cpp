#include "event/se_obj.h"

#include "event/skip_manager.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum SoundCategory : int;
}

namespace event {

static constexpr fw::SoundCategory SOUND_CATEGORY_UNKNOWN_12 = static_cast<fw::SoundCategory>(12); // Inferred role: sound category event se; original name unknown.
static constexpr f32 unknown022 = 99999.0f;                                                        // Inferred role: skip frame; original name unknown.

SeObj::SeObj() : unknown08(0) {}

SeObj::~SeObj() { clear(); }

void SeObj::clear() {
  stop();
  unknown180 = 0.0f;
  unknown14 = "";
  unknown08 = 0;
}

void SeObj::stop() {
  if (unknown0c.isValid()) {
    gf::GfSound::get()->stopSe(unknown0c, 0.0f);
    unknown0c.clear();
  }
}

void SeObj::exec(f32 delta) {
  if ((unknown08 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != FLAG_UNKNOWN_0) {
    return;
  }
  if (gf::GfSound::get()->isPlaying(unknown0c) && !mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    unknown58 += delta;
    if ((unknown08 & FLAG_UNKNOWN_6) != 0) {
      if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        unknown70.update(unknown022);
      } else if ((unknown08 & FLAG_UNKNOWN_2) == 0) {
        unknown70.update(1.0f);
      } else {
        unknown70.update(0.0f);
      }
      unknown68 = unknown70.getValue();
      mm::clampRef(unknown68, 0.0f, 1.0f);
      gf::GfSound::get()->setVolume(unknown0c, unknown68, 0.0f);
      if (unknown70.isEnd()) {
        unknown08 &= ~FLAG_UNKNOWN_6;
      }
    }
    if ((unknown08 & FLAG_UNKNOWN_4) != 0) {
      f32 rate = __builtin_fminf(unknown58 / unknown60, 1.0f);
      f32 fadeVolume = unknown68 * rate;
      mm::clampRef(fadeVolume, 0.0f, 1.0f);
      gf::GfSound::get()->setVolume(unknown0c, fadeVolume, 0.0f);
      setFlag(FLAG_UNKNOWN_4, unknown58 < unknown60);
    }
    if ((unknown08 & FLAG_UNKNOWN_5) != 0) {
      f32 rate = __builtin_fmaxf(unknown5c / unknown64, 0.0f);
      if (rate < 1.0f) {
        f32 fadeVolume = rate * unknown68;
        mm::clampRef(fadeVolume, 0.0f, 1.0f);
        gf::GfSound::get()->setVolume(unknown0c, fadeVolume, 0.0f);
      }
    }
    if ((unknown08 & FLAG_UNKNOWN_7) != 0) {
      if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        unknown188.update(unknown022);
      } else if ((unknown08 & FLAG_UNKNOWN_2) == 0) {
        unknown188.update(1.0f);
      } else {
        unknown188.update(0.0f);
      }
      unknown180 = unknown188.getValue();
      gf::GfSound::get()->setPan(unknown0c, unknown180, 0.0f);
      if (unknown188.isEnd()) {
        unknown08 &= ~FLAG_UNKNOWN_7;
      }
    }
    if ((unknown08 & FLAG_UNKNOWN_3) == 0) {
      return;
    }
    unknown5c -= delta;
    if (unknown5c < 0.0f) {
      stop();
      unknown08 = (unknown08 & ~(FLAG_UNKNOWN_3 | FLAG_UNKNOWN_1)) | FLAG_UNKNOWN_1;
    }
    return;
  }
  stop();
  unknown08 |= FLAG_UNKNOWN_1;
}

void SeObj::play(const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume) {
  mm::clampRef(volume, 0.0f, 1.0f);
  if (!isPlay() || __builtin_strcmp(this->unknown14.c_str(), name) != 0) {
    clear();
    unknown0c = gf::GfSound::get()->playSe(name, SOUND_CATEGORY_UNKNOWN_12);
    unknown0c.isValid();
  }
  unknown08 |= FLAG_UNKNOWN_0;
  setFlag(FLAG_UNKNOWN_3, life > 0.0f);
  setFlag(FLAG_UNKNOWN_4, fadeIn > 0.0f);
  setFlag(FLAG_UNKNOWN_5, fadeOut > 0.0f && life > 0.0f);
  this->unknown14 = name;
  unknown58 = 0.0f;
  this->unknown5c = life;
  this->unknown60 = fadeIn;
  this->unknown64 = fadeOut;
  this->unknown68 = volume;
  unknown180 = 0.0f;
  gf::GfSound::get()->setVolume(unknown0c, volume, 0.0f);
}

void SeObj::changeVolume(f32 volume, f32 frame) {
  if (!unknown0c.isValid()) {
    return;
  }
  f32 changeFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  mm::clampRef(volume, 0.0f, 1.0f);
  if (changeFrame <= 0.0f) {
    this->unknown68 = volume;
    unknown70.clear();
    unknown08 &= ~FLAG_UNKNOWN_6;
    gf::GfSound::get()->setVolume(unknown0c, volume, 0.0f);
    return;
  }
  unknown70.clear();
  unknown70.append(0.0f, this->unknown68, CV_TYPE_UNKNOWN_0);
  unknown70.append(changeFrame, volume, CV_TYPE_UNKNOWN_1);
  unknown08 |= FLAG_UNKNOWN_6;
}

void SeObj::pan(f32 pan, f32 frame, CV_TYPE cv) {
  if (!unknown0c.isValid()) {
    return;
  }
  f32 changeFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  if (changeFrame <= 0.0f) {
    unknown180 = pan;
    unknown188.clear();
    unknown08 = (unknown08 & ~FLAG_UNKNOWN_7) | FLAG_UNKNOWN_8;
    gf::GfSound::get()->setPan(unknown0c, pan, 0.0f);
    return;
  }
  unknown188.clear();
  unknown188.append(0.0f, unknown180, CV_TYPE_UNKNOWN_0);
  unknown188.append(changeFrame, pan, cv);
  unknown08 |= FLAG_UNKNOWN_7 | FLAG_UNKNOWN_8;
}

void SeObj::pause(bool isPause) {
  if (!unknown0c.isValid()) {
    return;
  }
  if (isPause) {
    if ((unknown08 & FLAG_UNKNOWN_2) != 0) {
      return;
    }
    gf::GfSound::get()->setPause(unknown0c, true, 0.0f);
    unknown08 |= FLAG_UNKNOWN_2;
  } else {
    if ((unknown08 & FLAG_UNKNOWN_2) == 0) {
      return;
    }
    gf::GfSound::get()->setPause(unknown0c, false, 0.0f);
    unknown08 &= ~FLAG_UNKNOWN_2;
  }
}

} // namespace event
