#include "ml/edian_util.h"

namespace ml {

int EdianUtil::read(const int &value) { return __builtin_bswap32(value); }

u32 EdianUtil::read(const u32 &value) { return __builtin_bswap32(value); }

u64 EdianUtil::read(const u64 &value) { return __builtin_bswap64(value); }

f32 EdianUtil::read(const f32 &value) {
  union {
    u32 bits;
    f32 value;
  } swapped;
  swapped.bits = __builtin_bswap32(*reinterpret_cast<const u32 *>(&value));
  return swapped.value;
}

s16 EdianUtil::read(const s16 &value) { return __builtin_bswap16(value); }

u16 EdianUtil::read(const u16 &value) { return __builtin_bswap16(value); }

void EdianUtil::write(s16 &destination, s16 value) {
  u8 *bytes = reinterpret_cast<u8 *>(&destination);
  bytes[0] = value >> 8;
  bytes[1] = value;
}

void EdianUtil::write(u16 &destination, u16 value) {
  u8 *bytes = reinterpret_cast<u8 *>(&destination);
  bytes[0] = value >> 8;
  bytes[1] = value;
}

} // namespace ml
