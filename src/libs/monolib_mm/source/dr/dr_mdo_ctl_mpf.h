#pragma once
#include "dr/dr_mdl_obj.h"
#include "types.h"

namespace ml {

class DrMan;

class DrMdoCtlMpf : public DrMdlObj {
public:
  DrMdoCtlMpf(const void *data, const char *path, DrMan *drMan, int viewNum);
  ~DrMdoCtlMpf() override;
  void releaseMpf();
  void update() override;
  void resourceInit() override;
  void callZPrepassRender();
  void updateMpf();
  void calcMpfRenderList();
  void callRenderMpf();
  void defMpfZPreRender();
  void defMpfrender();

  u8 _1a8[0x200 - 0x1a8];
};

static_assert(sizeof(DrMdoCtlMpf) == 0x200, "");

} // namespace ml
