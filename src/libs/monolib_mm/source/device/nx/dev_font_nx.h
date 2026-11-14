#pragma once
#include "ml/dev_font.h"

namespace ml {
class WorkObj;

// Layout evidence: WorkUtil::createWork<DevFontNx> (0x710072946c, instantiated in dev_font_nx.cpp) allocates 0x208 bytes, the size of DevFont, and inlines this constructor (the DevFont constructor,
// then the vtable stores); the game has no constructor symbol. releaseFont and the destructor sit with the unit's inline functions (0x710073a6cc, 0x710073a6a8), createFont and wkUpdate in the file
// (0x71007222d8, 0x71007222e0).
class DevFontNx : public DevFont {
public:
  DevFontNx(const char *name, WorkObj *parent) : DevFont(name, parent) {}
  bool createFont() override;
  bool releaseFont() override { return true; }
  void wkUpdate() override;
};

static_assert(sizeof(DevFontNx) == 0x208, "");

} // namespace ml
