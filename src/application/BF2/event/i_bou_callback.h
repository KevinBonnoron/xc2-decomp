#pragma once
#include "mm_math/mm_col4.h"

namespace event {

class BouRect;

class IBouCallback {
public:
  struct SelectParam {
    SelectParam(const BouRect *rect) : rect(rect) {}

    const BouRect *rect;
  };

  struct RenderParam {
    RenderParam(const mm::Col4 &color) : color(color) {}

    mm::Col4 color;
  };

  virtual ~IBouCallback() {}
  virtual bool OnBouRectSelect(const SelectParam &param) { return false; }
  virtual void OnBouRender(const RenderParam &param) {}
};

} // namespace event
