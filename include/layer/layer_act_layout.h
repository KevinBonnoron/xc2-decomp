#pragma once
#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {

class LayerActLayout : public LayerObjWork {
public:
  u32 calcLayoutActionWorkSize(const u8 *data);
  void setupLayoutAction(u8 *work, const u8 *data);
  bool actcmd_notcmd01(const u8 *&cmd);
  bool actcmd_notcmd02(const u8 *&cmd);
  bool actcmd_notcmd03(const u8 *&cmd);
};

} // namespace layer
