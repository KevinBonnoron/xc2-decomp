#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace layer {

class LayerBase;

enum LAYER_GAUGE {
  LAYER_GAUGE_NONE = 0,
};

class LayerAccDefObj : public LayerAccObjBase {
public:
  LayerAccDefObj(LayerBase *layer);
  void setParm(f32 parm);
  f32 getParm() const;
  void setIconNum(u16 num);
  u16 getIconNum() const;
  u16 getIconMax() const;
  void setGauge(LAYER_GAUGE gauge);
  LAYER_GAUGE getGauge() const;
};

} // namespace layer
