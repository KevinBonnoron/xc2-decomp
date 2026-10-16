#pragma once
#include "types.h"

namespace layer {

struct LayerResParmInfo;

class LayerAnimeObj {
public:
  ~LayerAnimeObj();
  bool update(LayerResParmInfo &parm, f32 frame);
  static LayerAnimeObj *createAnimObj(int id);
};

} // namespace layer
