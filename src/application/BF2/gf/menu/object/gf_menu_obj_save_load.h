#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjSaveLoad : public GfMenuObject {
public:
  GfMenuObjSaveLoad(u32 handle);
  ~GfMenuObjSaveLoad() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24; // Role and original member name unknown, zeroed by the constructor.
};

static_assert(offsetof(GfMenuObjSaveLoad, unknown24) == 0x24, "");

} // namespace gf
