#include "ml/rand.h"
#include "mm_mtl/mt_rand.h"
#include "nn/os.h"
#include "types.h"

namespace ml {

static mm::mtl::MTRand s_rand(nn::os::GetSystemTick().GetInt64Value());

void mtInit(u32 seed) { s_rand.init(seed); }

int mtRand() { return s_rand.generate() >> 1; }

int mtRand(int max) {
  if (max == 0) {
    return 0;
  }
  return mtRand() % max;
}

int mtRand(int min, int max) {
  int range = max - min;
  if (range <= 0) {
    return min;
  }
  return mtRand() % range + min;
}

f32 mtRandf1() { return s_rand.generate() * (1.0 / 4294967295.0); }

f32 mtRandf1(f32 max) {
  if (max > 0.0f) {
    return mtRandf1() * max;
  }
  return 0.0f;
}

f32 mtRandf1(f32 min, f32 max) {
  f32 range = max - min;
  if (range > 0.0f) {
    return range * mtRandf1() + min;
  }
  return min;
}

f32 mtRandf2() { return s_rand.generate() * (0.999999 / 4294967295.0); }

f32 mtRandf2(f32 max) {
  if (max > 0.0f) {
    return mtRandf2() * max;
  }
  return 0.0f;
}

f32 mtRandf2(f32 min, f32 max) {
  f32 range = max - min;
  if (range > 0.0f) {
    return range * mtRandf2() + min;
  }
  return min;
}

f32 mtRandf3() { return (s_rand.generate() | 1) * (0.999999 / 4294967295.0); }

f32 mtRandf3(f32 max) {
  if (max > 0.0f) {
    return mtRandf3() * max;
  }
  return 0.0f;
}

f32 mtRandf3(f32 min, f32 max) {
  f32 range = max - min;
  if (range > 0.0f) {
    return range * mtRandf3() + min;
  }
  return min;
}

} // namespace ml
