#pragma once

#include "framework/applet.h"

namespace tl {

// Applet of the title screen. Declared from the vtable _ZTVN2tl11TitleAppletE (0x71011bd3d8) and the symbols of its
// overridden functions.
class TitleApplet : public fw::Applet {
public:
  TitleApplet();
  ~TitleApplet() override;
  void initialize(const fw::Framework &framework) override;
  void finalize(const fw::Framework &framework) override;
  void update(const fw::UpdateInfo &info) override;
  void postUpdate(const fw::UpdateInfo &info) override;
};

} // namespace tl
