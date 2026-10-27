#include "dr/dr_gpu_check_render.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "grlib/cglib_vtx_instans.h"

namespace ml {

DrGpuCheckRender::DrGpuCheckRender() { unknown18.setup(0x80); }

DrGpuCheckRender::~DrGpuCheckRender() {}

void DrGpuCheckRender::beginUpdate() {
  unknown00 = DrMan::get()->unknown580->unknown10;
  unknown10 = DrMan::get()->unknown88->unknown008->unknown10;
  unknown50 = unknown10->getNextInstansBuff();
  s32 offset = unknown10->unknown08;
  unknown58 = offset;
  unknown5c = offset;
  unknown64 = 1;
}

void DrGpuCheckRender::endUpdate() {
  if (unknown58 != unknown5c) {
    unknown10->unknown08 = unknown58 - unknown5c + unknown10->unknown08;
  }
}

void DrGpuCheckRender::endRender() { DrMan::get()->unknown78->depCheckEnd(); }

} // namespace ml
