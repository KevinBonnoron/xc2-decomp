// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/execute/title/title_main.cpp.
#include "execute/title/title_menu.h"
#include "gf/menu/gf_menu_manager.h"
#include "mm_mtl/delegate.h"  // IWYU pragma: keep
#include "mm_mtl/singleton.h" // IWYU pragma: keep

namespace tl {

class TitleMain; // IWYU pragma: keep

} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleMain>::~PtrSingleton();
template void mm::mtl::Delegate<void(tl::TitleMain *)>::staticFuncInvoker(const mm::mtl::Delegate<void(tl::TitleMain *)> *, tl::TitleMain *);

namespace tl {

void TitleMenu::openTitle(bool isFadeOut) { gf::GfMenuManager::openFullScreen(3, isFadeOut, true); }

void TitleMenu::openOption() { gf::GfMenuManager::openFullScreen(7, false, true); }

bool TitleMenu::isOpenTitle() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

bool TitleMenu::isOpenOption() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

bool TitleMenu::isOpenEventTheater() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

} // namespace tl
