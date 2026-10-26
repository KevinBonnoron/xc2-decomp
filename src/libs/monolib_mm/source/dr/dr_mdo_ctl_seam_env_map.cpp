#include "dr/dr_mdo_ctl_seam_env_map.h"

#include "dr/dr_res_mdo_seam_wrk_env.h"

namespace ml {

void DrMdoCtlSeamEnvMap::createEnvDisplayList(DrResMdoSeamWrkEnv *wrk) { wrk->setDispState(); }

} // namespace ml
