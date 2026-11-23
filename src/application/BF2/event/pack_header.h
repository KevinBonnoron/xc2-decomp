#pragma once
#include "types.h"

namespace event {

class PackHeader {
public:
  struct File {
    char m_path[0x100]; // Inferred role: path; named after the game accessor event::PackHeader::getPath.
    u32 m_dataOfs;      // Inferred role: data ofs; named after the game accessor event::PackHeader::getDataOfs.
    u32 m_dataSize;     // Inferred role: data size; named after the game accessor event::PackHeader::getDataSize.
    u32 m_prio;         // Inferred role: prio; named after the game accessor event::PackHeader::getPrio.
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
