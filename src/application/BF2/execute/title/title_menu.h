#pragma once

namespace tl {

class TitleMenu {
public:
  void openTitle(bool isFadeOut);
  void openOption();
  bool isOpenTitle() const;
  bool isOpenOption() const;
  bool isOpenEventTheater() const;
};

} // namespace tl
