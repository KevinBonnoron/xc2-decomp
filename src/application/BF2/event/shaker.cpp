#include "event/shaker.h"

#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "rcha/rcha_cam.h"

namespace event {

static constexpr f32 PLAY_FRAME_MAX = 99999.0f;

Shaker::Shaker() : flags(0), resCount(1), current(nullptr) {}

void Shaker::create() {
  updater.clear();
  flags = 0;
  current = nullptr;
}

void Shaker::destroy() {
  while (resCount > 1) {
    resList[--resCount].destroy();
  }
  create();
}

void Shaker::exec(f32 delta, f32 streamDelta) {
  for (u32 i = 1; i < resCount; i++) {
    resList[i].update();
  }
  if (!isPlay()) {
    return;
  }
  if ((flags & FLAG_LIFE) != 0) {
    life -= delta;
    if (life < 0.0f) {
      stop();
    }
  }
  if (!isPlay()) {
    return;
  }
  frame += streamDelta;
  RchaCam *rcha = current->getRcha();
  if (rcha != nullptr) {
    while (rcha->getFrameCount() <= frame) {
      frame -= rcha->getFrameCount();
    }
    f32 alpha = getAlpha();
    mm::Vec3 pos;
    mm::Vec3 rot;
    rcha->getPos(&pos, frame);
    rcha->getRot(&rot, frame);
    rot *= mm::DEG_TO_RAD;
    updater.reserve(mm::Vec3(alpha * pos.x, alpha * pos.y, alpha * pos.z), mm::Vec3(alpha * rot.x, alpha * rot.y, alpha * rot.z));
  }
  playFrame += streamDelta;
  if (playFrame > PLAY_FRAME_MAX) {
    playFrame = PLAY_FRAME_MAX;
  }
}

void Shaker::stop() { flags = 0; }

f32 Shaker::getAlpha() const {
  if (fadeOut > 0.0f && (flags & FLAG_LIFE) != 0 && life <= fadeOut) {
    return __builtin_fmaxf(life - 1.0f, 0.0f) / fadeOut;
  }
  if (fadeIn > 0.0f && playFrame < fadeIn) {
    return playFrame / fadeIn;
  }
  return 1.0f;
}

void Shaker::tail() { updater.update(); }

u32 Shaker::registerShake(const char *name) {
  u32 index = search(name);
  if (index != 0) {
    return index;
  }
  index = resCount++;
  resList[index].create(name);
  return index;
}

u32 Shaker::search(const char *name) {
  for (u32 i = 1; i < resCount; i++) {
    if (__builtin_strcmp(name, resList[i].getName()) == 0) {
      return i;
    }
  }
  return 0;
}

bool Shaker::play(u32 index, f32 life, f32 fadeIn, f32 fadeOut) {
  if (life > 0.0f) {
    flags |= FLAG_PLAY | FLAG_LIFE;
  } else {
    flags = (flags & ~(FLAG_PLAY | FLAG_LIFE)) | FLAG_PLAY;
  }
  current = &resList[index];
  frame = 0.0f;
  playFrame = 0.0f;
  this->life = life;
  this->fadeIn = fadeIn;
  this->fadeOut = fadeOut;
  return true;
}

} // namespace event
