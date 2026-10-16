#include "event/se_obj.h"

#include "event/skip_manager.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum SoundCategory : int;
}

namespace event {

static constexpr fw::SoundCategory SOUND_CATEGORY_EVENT_SE = static_cast<fw::SoundCategory>(12);
static constexpr f32 SKIP_FRAME = 99999.0f;

SeObj::SeObj() : flags(0) {}

SeObj::~SeObj() { clear(); }

void SeObj::clear() {
  stop();
  panValue = 0.0f;
  name = "";
  flags = 0;
}

void SeObj::stop() {
  if (handle.isValid()) {
    gf::GfSound::get()->stopSe(handle, 0.0f);
    handle.clear();
  }
}

void SeObj::exec(f32 delta) {
  if ((flags & (FLAG_PLAY | FLAG_END)) != FLAG_PLAY) {
    return;
  }
  if (gf::GfSound::get()->isPlaying(handle) && !mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    playFrame += delta;
    if ((flags & FLAG_VOLUME_ANM) != 0) {
      if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        volumeAnm.update(SKIP_FRAME);
      } else if ((flags & FLAG_PAUSE) == 0) {
        volumeAnm.update(1.0f);
      } else {
        volumeAnm.update(0.0f);
      }
      volume = volumeAnm.getValue();
      mm::clampRef(volume, 0.0f, 1.0f);
      gf::GfSound::get()->setVolume(handle, volume, 0.0f);
      if (volumeAnm.isEnd()) {
        flags &= ~FLAG_VOLUME_ANM;
      }
    }
    if ((flags & FLAG_FADE_IN) != 0) {
      f32 rate = __builtin_fminf(playFrame / fadeIn, 1.0f);
      f32 fadeVolume = volume * rate;
      mm::clampRef(fadeVolume, 0.0f, 1.0f);
      gf::GfSound::get()->setVolume(handle, fadeVolume, 0.0f);
      setFlag(FLAG_FADE_IN, playFrame < fadeIn);
    }
    if ((flags & FLAG_FADE_OUT) != 0) {
      f32 rate = __builtin_fmaxf(life / fadeOut, 0.0f);
      if (rate < 1.0f) {
        f32 fadeVolume = rate * volume;
        mm::clampRef(fadeVolume, 0.0f, 1.0f);
        gf::GfSound::get()->setVolume(handle, fadeVolume, 0.0f);
      }
    }
    if ((flags & FLAG_PAN_ANM) != 0) {
      if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        panAnm.update(SKIP_FRAME);
      } else if ((flags & FLAG_PAUSE) == 0) {
        panAnm.update(1.0f);
      } else {
        panAnm.update(0.0f);
      }
      panValue = panAnm.getValue();
      gf::GfSound::get()->setPan(handle, panValue, 0.0f);
      if (panAnm.isEnd()) {
        flags &= ~FLAG_PAN_ANM;
      }
    }
    if ((flags & FLAG_LIFE) == 0) {
      return;
    }
    life -= delta;
    if (life < 0.0f) {
      stop();
      flags = (flags & ~(FLAG_LIFE | FLAG_END)) | FLAG_END;
    }
    return;
  }
  stop();
  flags |= FLAG_END;
}

void SeObj::play(const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume) {
  mm::clampRef(volume, 0.0f, 1.0f);
  if (!isPlay() || __builtin_strcmp(this->name.c_str(), name) != 0) {
    clear();
    handle = gf::GfSound::get()->playSe(name, SOUND_CATEGORY_EVENT_SE);
    handle.isValid();
  }
  flags |= FLAG_PLAY;
  setFlag(FLAG_LIFE, life > 0.0f);
  setFlag(FLAG_FADE_IN, fadeIn > 0.0f);
  setFlag(FLAG_FADE_OUT, fadeOut > 0.0f && life > 0.0f);
  this->name = name;
  playFrame = 0.0f;
  this->life = life;
  this->fadeIn = fadeIn;
  this->fadeOut = fadeOut;
  this->volume = volume;
  panValue = 0.0f;
  gf::GfSound::get()->setVolume(handle, volume, 0.0f);
}

void SeObj::changeVolume(f32 volume, f32 frame) {
  if (!handle.isValid()) {
    return;
  }
  f32 changeFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  mm::clampRef(volume, 0.0f, 1.0f);
  if (changeFrame <= 0.0f) {
    this->volume = volume;
    volumeAnm.clear();
    flags &= ~FLAG_VOLUME_ANM;
    gf::GfSound::get()->setVolume(handle, volume, 0.0f);
    return;
  }
  volumeAnm.clear();
  volumeAnm.append(0.0f, this->volume, CV_TYPE_STEP);
  volumeAnm.append(changeFrame, volume, CV_TYPE_LINEAR);
  flags |= FLAG_VOLUME_ANM;
}

void SeObj::pan(f32 pan, f32 frame, CV_TYPE cv) {
  if (!handle.isValid()) {
    return;
  }
  f32 changeFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  if (changeFrame <= 0.0f) {
    panValue = pan;
    panAnm.clear();
    flags = (flags & ~FLAG_PAN_ANM) | FLAG_PAN;
    gf::GfSound::get()->setPan(handle, pan, 0.0f);
    return;
  }
  panAnm.clear();
  panAnm.append(0.0f, panValue, CV_TYPE_STEP);
  panAnm.append(changeFrame, pan, cv);
  flags |= FLAG_PAN_ANM | FLAG_PAN;
}

void SeObj::pause(bool isPause) {
  if (!handle.isValid()) {
    return;
  }
  if (isPause) {
    if ((flags & FLAG_PAUSE) != 0) {
      return;
    }
    gf::GfSound::get()->setPause(handle, true, 0.0f);
    flags |= FLAG_PAUSE;
  } else {
    if ((flags & FLAG_PAUSE) == 0) {
      return;
    }
    gf::GfSound::get()->setPause(handle, false, 0.0f);
    flags &= ~FLAG_PAUSE;
  }
}

} // namespace event
