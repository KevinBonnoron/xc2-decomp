#include "event/pack_endian.h"

namespace event {

u32 PackEndian::conv(u32 value, bool isSwap) { return isSwap ? __builtin_bswap32(value) : value; }

} // namespace event
