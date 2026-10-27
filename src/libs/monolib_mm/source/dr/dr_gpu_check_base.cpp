#include "dr/dr_gpu_check_base.h"

#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"

namespace ml {

bool DrGpuCheckBase::isClip(const mm::Vec3 &position, f32 radius) { return DrMan::get()->unknown580->unknown10->unknown4e0.clipTest(position, radius); }

DrGpuCheckBase *DrGpuCheckBase::createGpuCheckObj(int type) { return DrMan::get()->unknown88->createGpuCheckObj(type); }

DrGpuCheckBase *DrGpuCheckBase::createEffGpuCheckObj(int type) { return DrMan::get()->unknown88->createEffGpuCheckObj(type); }

} // namespace ml
