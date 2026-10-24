#include "event/shaker.h"

#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "rcha/rcha_cam.h"

namespace event {

static constexpr f32 PLAY_FRAME_MAX = 99999.0f;

Shaker::Shaker() : unknown08(0), unknown310(1), unknown318(nullptr) {}

void Shaker::create() {
  unknown338.clear();
  unknown08 = 0;
  unknown318 = nullptr;
}

void Shaker::destroy() {
  while (unknown310 > 1) {
    unknown10[--unknown310].destroy();
  }
  create();
}

void Shaker::exec(f32 delta, f32 streamDelta) {
  for (u32 i = 1; i < unknown310; i++) {
    unknown10[i].update();
  }
  if (!isPlay()) {
    return;
  }
  if ((unknown08 & FLAG_LIFE) != 0) {
    unknown328 -= delta;
    if (unknown328 < 0.0f) {
      stop();
    }
  }
  if (!isPlay()) {
    return;
  }
  unknown320 += streamDelta;
  RchaCam *rcha = unknown318->getRcha();
  if (rcha != nullptr) {
    while (rcha->getFrameCount() <= unknown320) {
      unknown320 -= rcha->getFrameCount();
    }
    f32 alpha = getAlpha();
    mm::Vec3 pos;
    mm::Vec3 rot;
    rcha->getPos(&pos, unknown320);
    rcha->getRot(&rot, unknown320);
    rot *= mm::DEG_TO_RAD;
    unknown338.reserve(mm::Vec3(alpha * pos.x, alpha * pos.y, alpha * pos.z), mm::Vec3(alpha * rot.x, alpha * rot.y, alpha * rot.z));
  }
  unknown324 += streamDelta;
  if (unknown324 > PLAY_FRAME_MAX) {
    unknown324 = PLAY_FRAME_MAX;
  }
}

void Shaker::stop() { unknown08 = 0; }

f32 Shaker::getAlpha() const {
  if (unknown330 > 0.0f && (unknown08 & FLAG_LIFE) != 0 && unknown328 <= unknown330) {
    return __builtin_fmaxf(unknown328 - 1.0f, 0.0f) / unknown330;
  }
  if (unknown32c > 0.0f && unknown324 < unknown32c) {
    return unknown324 / unknown32c;
  }
  return 1.0f;
}

void Shaker::tail() { unknown338.update(); }

u32 Shaker::registerShake(const char *name) {
  u32 index = search(name);
  if (index != 0) {
    return index;
  }
  index = unknown310++;
  unknown10[index].create(name);
  return index;
}

u32 Shaker::search(const char *name) {
  for (u32 i = 1; i < unknown310; i++) {
    if (__builtin_strcmp(name, unknown10[i].getName()) == 0) {
      return i;
    }
  }
  return 0;
}

bool Shaker::play(u32 index, f32 life, f32 fadeIn, f32 fadeOut) {
  if (life > 0.0f) {
    unknown08 |= FLAG_PLAY | FLAG_LIFE;
  } else {
    unknown08 = (unknown08 & ~(FLAG_PLAY | FLAG_LIFE)) | FLAG_PLAY;
  }
  unknown318 = &unknown10[index];
  unknown320 = 0.0f;
  unknown324 = 0.0f;
  this->unknown328 = life;
  this->unknown32c = fadeIn;
  this->unknown330 = fadeOut;
  return true;
}

} // namespace event
