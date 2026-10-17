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
  ui::UIObjectAcc *screen = new (getAllocator(ALLOCATOR_DEFAULT)->getMemHandle()) ui::UIObjectAcc(handle, "SCR_minigame");
  miniGame = minigame::tora::factory::create(screen);
  GfMenuObject::initialize();
}

void GfMenuObjMiniGame::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMiniGame::update() {
  if (miniGame != nullptr && miniGame->isTerminate()) {
    closeFSLayer(handle, true, true);
    miniGame = nullptr;
  }
  GfMenuObject::update();
}

} // namespace gf
