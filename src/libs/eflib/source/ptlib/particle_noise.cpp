#include "ptlib/particle_noise.h"

#include <math.h>

#include "mm_math/mm_vec3.h"

namespace ptlib {

namespace {
// Inferred role: permutation table of improved Perlin noise; original name unknown.
int unknown001[256] = {151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190, 6,   148,
                       247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175,
                       74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,  245, 40,  244, 102, 143, 54,
                       65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,
                       52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189, 28,  42,  223, 183, 170, 213,
                       119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104,
                       218, 246, 97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
                       184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180};
// Inferred role: gradient vectors of improved Perlin noise; original name unknown.
mm::Vec3 unknown002[16] = {
    mm::Vec3(1.0f, 1.0f, 0.0f),
    mm::Vec3(-1.0f, 1.0f, 0.0f),
    mm::Vec3(1.0f, -1.0f, 0.0f),
    mm::Vec3(-1.0f, -1.0f, 0.0f),
    mm::Vec3(1.0f, 0.0f, 1.0f),
    mm::Vec3(-1.0f, 0.0f, 1.0f),
    mm::Vec3(1.0f, 0.0f, -1.0f),
    mm::Vec3(-1.0f, 0.0f, -1.0f),
    mm::Vec3(0.0f, 1.0f, 1.0f),
    mm::Vec3(0.0f, -1.0f, 1.0f),
    mm::Vec3(0.0f, 1.0f, -1.0f),
    mm::Vec3(0.0f, -1.0f, -1.0f),
    mm::Vec3(1.0f, 1.0f, 0.0f),
    mm::Vec3(0.0f, -1.0f, 1.0f),
    mm::Vec3(-1.0f, 1.0f, 0.0f),
    mm::Vec3(0.0f, -1.0f, -1.0f),
};

// Inferred role: smoothstep curve of improved Perlin noise; original name unknown.
f32 unknown003(f32 t) { return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f); }

// Inferred role: linear interpolation of improved Perlin noise; original name unknown.
f32 unknown004(f32 t, f32 a, f32 b) { return a + t * (b - a); }

// Inferred role: gradient dot product of improved Perlin noise; original name unknown.
f32 unknown005(int hash, f32 x, f32 y, f32 z) {
  const mm::Vec3 &gradient = unknown002[hash & 0xf];
  return x * gradient.x + y * gradient.y + z * gradient.z;
}
} // namespace

f32 TurbulenceN::s_fTotalTime;
ImprovedNoise TurbulenceN::s_noise;

ImprovedNoise::ImprovedNoise() {
  for (int i = 0; i < 256; i++) {
    unknown000[i] = unknown001[i];
    unknown000[256 + i] = unknown001[i];
  }
}

ImprovedNoise::~ImprovedNoise() {}

f32 ImprovedNoise::noise(f32 x, f32 y, f32 z) {
  int cellX = static_cast<int>(floorf(x)) & 0xff;
  int cellY = static_cast<int>(floorf(y)) & 0xff;
  int cellZ = static_cast<int>(floorf(z)) & 0xff;
  x -= floorf(x);
  y -= floorf(y);
  z -= floorf(z);
  f32 u = unknown003(x);
  f32 v = unknown003(y);
  f32 w = unknown003(z);
  int a = unknown000[cellX] + cellY;
  int aa = unknown000[a] + cellZ;
  int ab = unknown000[a + 1] + cellZ;
  int b = unknown000[cellX + 1] + cellY;
  int ba = unknown000[b] + cellZ;
  int bb = unknown000[b + 1] + cellZ;
  return unknown004(w,
                    unknown004(v,
                               unknown004(u, unknown005(unknown000[aa], x, y, z), unknown005(unknown000[ba], x - 1.0f, y, z)),
                               unknown004(u, unknown005(unknown000[ab], x, y - 1.0f, z), unknown005(unknown000[bb], x - 1.0f, y - 1.0f, z))),
                    unknown004(v,
                               unknown004(u, unknown005(unknown000[aa + 1], x, y, z - 1.0f), unknown005(unknown000[ba + 1], x - 1.0f, y, z - 1.0f)),
                               unknown004(u, unknown005(unknown000[ab + 1], x, y - 1.0f, z - 1.0f), unknown005(unknown000[bb + 1], x - 1.0f, y - 1.0f, z - 1.0f))));
}

void TurbulenceN::init() { s_fTotalTime = 0.0f; }

f32 TurbulenceN::getTotalTime() { return s_fTotalTime; }

void TurbulenceN::updateTime(f32 deltaTime) { s_fTotalTime += deltaTime; }

} // namespace ptlib
