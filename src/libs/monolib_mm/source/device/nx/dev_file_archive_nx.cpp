#include "device/nx/dev_file_archive_nx.h"

namespace ml {

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

bool DevFileArchiveNx::rfIsUsedChannel(u32 channel) { return (&*unknown20 + channel)->unknown10c; }

} // namespace ml
