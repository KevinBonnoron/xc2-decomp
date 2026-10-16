#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace layer {

class LayerBase;

enum LayerFontDisplayArea {};

class LayerAccFontObj : public LayerAccObjBase {
public:
  LayerAccFontObj(LayerBase *layer);
  LayerFontDisplayArea getDisplayArea() const;
  u16 getFontPixelWidth() const;
  u16 getFontPixelHeight() const;
};

} // namespace layer
