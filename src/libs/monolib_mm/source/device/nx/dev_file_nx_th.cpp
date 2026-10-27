#include "device/nx/dev_file_nx_th.h"

namespace ml {

u32 DevFileNxTh::addressAlignment() { return 16; }

bool DevFileNxTh::rfIsUsedChannel(u32 channel) { return (&*unknown20 + channel)->unknown10c; }

} // namespace ml
