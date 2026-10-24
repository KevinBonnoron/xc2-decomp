#include "event/pack_header.h"

namespace event {

const char *PackHeader::getPath(u32 index) const { return mFiles[index].unknown00; }

u32 PackHeader::getPrio(u32 index) const { return mFiles[index].unknown108; }

u32 PackHeader::getDataOfs(u32 index) const { return mFiles[index].unknown100; }

u32 PackHeader::getDataSize(u32 index) const { return mFiles[index].unknown104; }

u32 PackHeader::getCount() const { return mCount; }

void PackHeader::dump() const {}

} // namespace event
