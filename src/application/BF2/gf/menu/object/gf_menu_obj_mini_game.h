#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace fw {
class UpdatableObject;
} // namespace fw

namespace gf {

class GfMenuObjMiniGame : public GfMenuObject {
public:
  GfMenuObjMiniGame(u32 handle);
  ~GfMenuObjMiniGame() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  fw::UpdatableObject *unknown28; // Inferred role: mini game; original member name unknown.
};

static_assert(offsetof(GfMenuObjMiniGame, unknown28) == 0x28, "");

} // namespace gf
