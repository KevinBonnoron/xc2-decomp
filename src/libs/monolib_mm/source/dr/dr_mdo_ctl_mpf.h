#pragma once
#include "dr/dr_mdl_obj.h"

namespace ml {

class DrMdoCtlMpf : public DrMdlObj {
public:
  void callZPrepassRender();
  void callRenderMpf();
};

} // namespace ml
