#include <string.h>

#include "ssd/ssd_buffer.h"
#include "ssd/ssd_debug.h"
#include "types.h"

namespace ssd {

void BufferBase::GetData(u64 size, u64 offset, void *buffer) { memcpy(buffer, unknown00 + offset, size); }

long BufferBase::Read(u64 size, void *buffer) {
  u64 newPosition = unknown10 + size;
  if (newPosition > unknown08) {
    log_message("%s : newPosi > dataSize  newPosi=0x%x\n", __FUNCTION__, static_cast<u32>(newPosition));
    return unknown10;
  }
  memcpy(buffer, unknown00 + unknown10, size);
  unknown10 += size;
  return unknown10;
}

} // namespace ssd
