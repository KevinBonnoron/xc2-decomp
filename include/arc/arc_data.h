#pragma once
#include "types.h"

namespace arc {

class CArcData {
public:
  CArcData(void *data);
  // Reconstructed from symbol arc::CArcData::setData(void*) at 0x7100695320.
  void setData(void *data);
  void *getFileAdr(const char *name) const;
  // Declared from symbols _ZNK3arc8CArcData8getFilesEv, getFileNameEj, getFileSizeEj and getFileAdrEj (0x6953xx..0x6955xx).
  u32 getFiles() const;
  const char *getFileName(u32 index) const;
  u32 getFileSize(u32 index) const;
  void *getFileAdr(u32 index) const;

  void *unknown00; // Inferred role: data; original member name unknown.
  void *unknown08; // Inferred role: names; original member name unknown.
};

static_assert(sizeof(CArcData) == 0x10, "");

} // namespace arc
