#include "execute/title/title_applet.h"

#include "execute/title/title_main.h"
#include "gf/gf_manager.h"

namespace tl {

TitleApplet::TitleApplet() {}

TitleApplet::~TitleApplet() {}

void TitleApplet::finalize(const fw::Framework &framework) {
  TitleMain::destroy();
  gf::GfManager::destroy();
}

void TitleApplet::update(const fw::UpdateInfo &info) {
  gf::GfManager::update(info);
  TitleMain::update(info);
}

void TitleApplet::postUpdate(const fw::UpdateInfo &info) { gf::GfManager::postUpdate(info); }

} // namespace tl
