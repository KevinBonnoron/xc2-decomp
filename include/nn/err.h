#pragma once
#include "types.h"

// Error applet of the SDK, reconstructed from the imports of the game (nn::err::ShowError,
// nn::err::ShowApplicationError and the nn::err::ApplicationErrorArg methods) and the stack
// layout of ml::ErrorApplet::showApplet.

namespace nn {
class Result;
namespace settings {
struct LanguageCode;
} // namespace settings

namespace err {

class ApplicationErrorArg {
public:
  ApplicationErrorArg();
  void SetApplicationErrorCodeNumber(u32 number);
  void SetDialogMessage(const char *message);
  void SetFullScreenMessage(const char *message);
  void SetLanguageCode(const settings::LanguageCode &languageCode);

private:
  u8 unknown0000[0x1014]; // Inferred role: argument storage; original member name unknown.
};

void ShowError(Result result);
void ShowApplicationError(const ApplicationErrorArg &arg);

} // namespace err
} // namespace nn
