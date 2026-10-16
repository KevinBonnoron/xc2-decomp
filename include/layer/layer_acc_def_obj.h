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

class LayerAccDefAnmObj : public LayerAccObjBase {
public:
  LayerAccDefAnmObj(LayerBase *layer);
  f32 getMaxSecond() const;
  f32 getSecond() const;
  void setSecond(f32 second);
  void setLoop(bool loop);
  bool isLoop() const;
  void setPause(bool pause);
  bool isPause() const;
  u32 getDataType() const;
};

} // namespace layer
