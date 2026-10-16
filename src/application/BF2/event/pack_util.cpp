#include "event/pack_util.h"

namespace event {

u32 PackUtil::conv(u32 value, bool isSwap) { return isSwap ? __builtin_bswap32(value) : value; }

} // namespace event
