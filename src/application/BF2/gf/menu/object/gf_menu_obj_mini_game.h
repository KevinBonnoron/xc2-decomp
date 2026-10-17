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

  fw::UpdatableObject *miniGame;
};

static_assert(offsetof(GfMenuObjMiniGame, miniGame) == 0x28, "");

} // namespace gf
