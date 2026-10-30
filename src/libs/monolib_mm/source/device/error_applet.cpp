#include "ml/error_applet.h"

#include "ml/dev_setting.h"
#include "nn/err.h"
#include "nn/result.h"
#include "nn/settings.h"

namespace ml {

bool ErrorApplet::showApplet(const Config &config) {
  nn::err::ApplicationErrorArg arg;
  arg.SetApplicationErrorCodeNumber(config.unknown00);
  if (config.unknown08 != nullptr) {
    arg.SetDialogMessage(config.unknown08);
  }
  if (config.unknown10 != nullptr) {
    arg.SetFullScreenMessage(config.unknown10);
  }
  LangType lang = config.unknown18;
  if (lang == DEV_LANG_INVALID) {
    lang = DevSetting::getLang();
  }
  nn::settings::LanguageCode languageCode = nn::settings::LanguageCode::Make(static_cast<nn::settings::Language>(lang));
  arg.SetLanguageCode(languageCode);
  nn::err::ShowApplicationError(arg);
  return true;
}

bool SystemErrorApplet::showApplet(nn::Result &result) {
  if (!result.IsSuccess()) {
    nn::err::ShowError(result);
  }
  return true;
}

} // namespace ml
