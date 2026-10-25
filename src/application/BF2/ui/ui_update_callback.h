#pragma once

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIUpdateCallback {
public:
  void endUpdate(const fw::UpdateInfo &info);
  void beginApply();
  void endApply();
};

} // namespace ui
