#pragma once
#include "types.h"

namespace event {

class PackHeader {
public:
  struct File {
    char path[0x100];
    u32 dataOfs;
    u32 dataSize;
    u32 prio;
    u8 _10c[0x120 - 0x10c];
  };

  const char *getPath(u32 index) const;
  u32 getPrio(u32 index) const;
  u32 getDataOfs(u32 index) const;
  u32 getDataSize(u32 index) const;
  u32 getCount() const;
  void dump() const;

private:
  u8 _0[0x4 - 0x0];
  u32 mCount;
  u8 _8[0x10 - 0x8];
  File mFiles[1];
};

} // namespace event
