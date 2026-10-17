#pragma once

namespace arc {

class CArcData {
public:
  CArcData(void *data);
  void *getFileAdr(const char *name) const;

  void *data;
  void *names;
};

static_assert(sizeof(CArcData) == 0x10, "");

} // namespace arc
