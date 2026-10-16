#pragma once

namespace fw {
struct PadData;
}

namespace ui {

class UIPadRead {
public:
  virtual ~UIPadRead() {}
  virtual const fw::PadData *getPadData() const = 0;
};

} // namespace ui
