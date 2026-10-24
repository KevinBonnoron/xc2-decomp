#include "gf/menu/object/gf_menu_obj_mini_game.h"

#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "minigame/tora/minigame_tora.h"
#include "mtl/alloc_handle.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMiniGame::GfMenuObjMiniGame(u32 handle) : GfMenuObject(handle) {}

GfMenuObjMiniGame::~GfMenuObjMiniGame() { ; }

void GfMenuObjMiniGame::initialize() {
  ui::UIObjectAcc *screen = new (getAllocator(ALLOCATOR_DEFAULT)->getMemHandle()) ui::UIObjectAcc(unknown18, "SCR_minigame");
  unknown28 = minigame::tora::factory::create(screen);
  GfMenuObject::initialize();
}

void GfMenuObjMiniGame::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMiniGame::update() {
  if (unknown28 != nullptr && unknown28->isTerminate()) {
    closeFSLayer(unknown18, true, true);
    unknown28 = nullptr;
  }
  GfMenuObject::update();
}

} // namespace gf
