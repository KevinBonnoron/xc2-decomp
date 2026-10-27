#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {
namespace math {

struct EPkey {
  u16 unknown00; // Inferred role: key id of the start key; original member name unknown.
  u16 unknown02; // Inferred role: key id of the end key; original member name unknown.
  u32 unknown04; // Inferred role: random seed of the start key; original member name unknown.
  u32 unknown08; // Inferred role: random seed of the end key; original member name unknown.
};

static_assert(offsetof(EPkey, unknown04) == 0x04, "");
static_assert(sizeof(EPkey) == 0x0c, "");

class KeyFrameIP {
public:
  f32 get_ip1(int index);
  void setup_keyrand(EPkey *epkey, int count, u32 &rand);
  f32 keyrand_get_ip1(EPkey *epkey, u32 &rand);

  const f32 *unknown00; // Inferred role: start key; original member name unknown.
  const f32 *unknown08; // Inferred role: end key; original member name unknown.
  f32 unknown10;        // Inferred role: blend rate; original member name unknown.
  u32 unknown14;        // Inferred role: random seed of the start key; original member name unknown.
  u32 unknown18;        // Inferred role: random seed of the end key; original member name unknown.
};

static_assert(offsetof(KeyFrameIP, unknown08) == 0x08, "");
static_assert(offsetof(KeyFrameIP, unknown10) == 0x10, "");
static_assert(offsetof(KeyFrameIP, unknown18) == 0x18, "");

} // namespace math
} // namespace ptlib
