#pragma once

namespace ml {

class IWorkBackground {
public:
  virtual ~IWorkBackground() {}
  virtual void bkgHomeMenu(bool isEnter);
  virtual void bkgHomeMenuDenied();
};

} // namespace ml
