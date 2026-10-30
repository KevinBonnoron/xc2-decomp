#include "ptlib/math/particle_keyframe_ip.h"

#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "ptlib/particle_math.h"

namespace ptlib {
namespace math {

namespace {

// Inferred role: value of a key with the random range applied; original name unknown.
inline f32 unknown002(const f32 *key, u32 &seed) { return key[0] + key[1] * unknown001(seed); }

// Inferred role: value of a three component key with the random ranges applied; original name unknown.
inline void unknown003(mm::Vec3 &result, const Vec3r *key, u32 &seed) {
  result.x = key->unknown00 + key->unknown0c * unknown001(seed);
  result.y = key->unknown04 + key->unknown10 * unknown001(seed);
  result.z = key->unknown08 + key->unknown14 * unknown001(seed);
}

// Inferred role: three component value interpolated between the start and end keys, shared by both get_ip3 overloads; original name unknown.
template <typename T> inline void unknown004(KeyFrameIP &keyFrame, T &result, int index) {
  mm::Vec3 start;
  mm::Vec3 end;
  unknown003(start, reinterpret_cast<const Vec3r *>(keyFrame.unknown00 + index), keyFrame.unknown14);
  unknown003(end, reinterpret_cast<const Vec3r *>(keyFrame.unknown08 + index), keyFrame.unknown18);
  f32 rate = keyFrame.unknown10;
  result.x = start.x * (1.0f - rate) + end.x * rate;
  result.y = start.y * (1.0f - rate) + end.y * rate;
  result.z = start.z * (1.0f - rate) + end.z * rate;
}

// Inferred role: value of a two component key with the random ranges applied; original name unknown.
inline void unknown005(vec2f &result, const f32 *key, u32 &seed) {
  result.unknown00 = key[0] + key[2] * unknown001(seed);
  result.unknown04 = key[1] + key[3] * unknown001(seed);
}

} // namespace

f32 KeyFrameIP::get_ip1(int index) {
  f32 start = unknown002(unknown00 + index, unknown14);
  f32 end = unknown002(unknown08 + index, unknown18);
  return unknown10 * end + (1.0f - unknown10) * start;
}

void KeyFrameIP::get_ip2(vec2f *result, int index) {
  vec2f start;
  vec2f end;
  unknown005(start, unknown00 + index, unknown14);
  unknown005(end, unknown08 + index, unknown18);
  f32 rate = unknown10;
  result->unknown00 = start.unknown00 * (1.0f - rate) + end.unknown00 * rate;
  result->unknown04 = start.unknown04 * (1.0f - rate) + end.unknown04 * rate;
}

void KeyFrameIP::get_ip3(mm::Vec3NA *result, int index) { unknown004(*this, *result, index); }

void KeyFrameIP::get_ip3(mm::Vec3 *result, int index) { unknown004(*this, *result, index); }

void KeyFrameIP::mul_ip3(mm::Vec3NA *result, int index) {
  mm::Vec3NA value;
  get_ip3(&value, index);
  result->x *= value.x;
  result->y *= value.y;
  result->z *= value.z;
}

void KeyFrameIP::mul_ip3(mm::Vec3 *result, int index) {
  mm::Vec3 value;
  get_ip3(&value, index);
  result->x *= value.x;
  result->y *= value.y;
  result->z *= value.z;
}

void KeyFrameIP::setup_keyrand(EPkey *epkey, int count, u32 &rand) {
  u16 startId = static_cast<int>(unknown00[-1]);
  u16 endId = static_cast<int>(unknown08[-1]);
  if (epkey->unknown00 != startId) {
    u16 previousEndId = epkey->unknown02;
    epkey->unknown00 = startId;
    if (previousEndId == startId) {
      epkey->unknown04 = epkey->unknown08;
    } else {
      rand = rand * 0x41c64e6d + 0x3039;
      epkey->unknown04 = rand;
      for (int i = 1; i < count; i++) {
        rand = rand * 0x41c64e6d + 0x3039;
      }
    }
  }
  if (epkey->unknown02 != endId) {
    epkey->unknown02 = endId;
    rand = rand * 0x41c64e6d + 0x3039;
    epkey->unknown08 = rand;
    for (int i = 1; i < count; i++) {
      rand = rand * 0x41c64e6d + 0x3039;
    }
  }
  unknown14 = epkey->unknown04;
  unknown18 = epkey->unknown08;
}

f32 KeyFrameIP::keyrand_get_ip1(EPkey *epkey, u32 &rand) {
  setup_keyrand(epkey, 1, rand);
  return get_ip1(0);
}

void KeyFrameIP::keyrand_get_ip3(mm::Vec3NA *result, EPkey *epkey, u32 &rand) {
  setup_keyrand(epkey, 3, rand);
  get_ip3(result, 0);
}

void KeyFrameIP::keyrand_get_ip3(mm::Vec3 *result, EPkey *epkey, u32 &rand) {
  setup_keyrand(epkey, 3, rand);
  get_ip3(result, 0);
}

void KeyFrameIP::keyrand_mul_ip3(mm::Vec3NA *result, EPkey *epkey, u32 &rand) {
  mm::Vec3NA value;
  keyrand_get_ip3(&value, epkey, rand);
  result->x *= value.x;
  result->y *= value.y;
  result->z *= value.z;
}

void KeyFrameIP::keyrand_mul_ip3(mm::Vec3 *result, EPkey *epkey, u32 &rand) {
  mm::Vec3 value;
  keyrand_get_ip3(&value, epkey, rand);
  result->x *= value.x;
  result->y *= value.y;
  result->z *= value.z;
}

} // namespace math
} // namespace ptlib
