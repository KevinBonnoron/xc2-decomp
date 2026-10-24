#pragma once

namespace arc {

class CArcData {
public:
  CArcData(void *data);
  // Reconstructed from symbol arc::CArcData::setData(void*) at 0x7100695320.
  void setData(void *data);
  void *getFileAdr(const char *name) const;

  void *unknown00; // Inferred role: data; original member name unknown.
  void *unknown08; // Inferred role: names; original member name unknown.
};

static_assert(sizeof(CArcData) == 0x10, "");

} // namespace arc
