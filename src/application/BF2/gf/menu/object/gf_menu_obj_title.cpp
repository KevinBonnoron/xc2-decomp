#include "gf/menu/object/gf_menu_obj_title.h"

namespace gf {

bool GfMenuObjTitle::s_NoSaveData;

void GfMenuObjTitle::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjTitle::isEnableNewGame() { return true; }

bool GfMenuObjTitle::isEnableNewGameAdv() { return false; }

bool GfMenuObjTitle::isEnableContinue() { return !s_NoSaveData; }

bool GfMenuObjTitle::isEnableOption() { return true; }

} // namespace gf
