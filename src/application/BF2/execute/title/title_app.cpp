#include "execute/title/title_app.h"

#include "ml/proc_desktop.h"
#include "ml/win_view.h"
#include "ml/work_util.h"
#include "mm_math/mm_col4.h"

namespace tl {

// Inferred role: creates the title work under the desktop and gives it the wid of the application view; original name unknown. The game holds this body in each
// of the four execute functions (1.0.0: 0x71001427b8, 0x7100142910, 0x7100142994, 0x7100142a18), none of which calls a helper.
static void unknown001(const char *title) {
  TitleApp *app = ml::WorkUtil::createWork<TitleApp>(title, ml::ProcDesktop::get(), false);
  ml::WinView *view = ml::ProcDesktop::get()->pssGetApplicationView() != nullptr ? ml::ProcDesktop::get()->pssGetApplicationView() : ml::ProcDesktop::getView();
  app->unknown1e8 = view->unknown50;
}

const char *TitleApp::m_szTitle = "Title";
const char *TitleAppEN::m_szTitle = "Title_english";
const char *TitleAppCN::m_szTitle = "Title_cn_simple";
const char *TitleAppTW::m_szTitle = "Title_cn_original";

bool TitleApp::wkStandbyLogout() {
  if (LauncherApp::wkStandbyLogout()) {
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    return true;
  }
  return false;
}

void TitleApp::execute() {
  if (get() == nullptr) {
    unknown001(m_szTitle);
  }
}

void TitleAppEN::execute() {
  if (TitleApp::get() == nullptr) {
    unknown001(m_szTitle);
    TitleApp::get()->unknown768 = 12;
  }
}

void TitleAppCN::execute() {
  if (TitleApp::get() == nullptr) {
    unknown001(m_szTitle);
    TitleApp::get()->unknown768 = 6;
  }
}

void TitleAppTW::execute() {
  if (TitleApp::get() == nullptr) {
    unknown001(m_szTitle);
    TitleApp::get()->unknown768 = 11;
  }
}

} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleApp>::~PtrSingleton();
