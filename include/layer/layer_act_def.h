#pragma once
#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {

class LayerActDef : public LayerObjWork {
public:
  u32 calcDefActionWorkSize(const u8 *data);
  void setupDefAction(u8 *work, const u8 *data);
  bool actcmd_iconnum(const u8 *&cmd);
  bool actcmd_animdef(const u8 *&cmd);
  bool actcmd_animfrm(const u8 *&cmd);
};

} // namespace layer
