#include "event/pack_header.h"

namespace event {

const char *PackHeader::getPath(u32 index) const { return mFiles[index].path; }

u32 PackHeader::getPrio(u32 index) const { return mFiles[index].prio; }

u32 PackHeader::getDataOfs(u32 index) const { return mFiles[index].dataOfs; }

u32 PackHeader::getDataSize(u32 index) const { return mFiles[index].dataSize; }

u32 PackHeader::getCount() const { return mCount; }

void PackHeader::dump() const {}

} // namespace event
