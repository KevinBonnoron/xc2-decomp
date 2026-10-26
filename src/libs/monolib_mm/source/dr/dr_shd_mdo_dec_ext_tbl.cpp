#include "dr/dr_shd_mdo_dec_ext_tbl.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_shd_fetch_obj.h"
#include "dr/dr_shd_mdo_dec_res.h"

namespace ml {
class DrResFetch;

DrShdMdoDecExtTbl::DrShdMdoDecExtTbl() : CGLibDecShdExtTbl() {}

DrShdMdoDecExtTbl::~DrShdMdoDecExtTbl() {}

void DrShdMdoDecExtTbl::bindShader() {
  DrAPCache *cache = DrAPCache::s_pIns;
  DrResFetch *fetch = &unknown18->m_fetch->unknown20;
  cache->setupShader(this, fetch);
}

u32 DrShdMdoDecExtTbl::getValGlobalParam(int index) { return unknown28[index]; }

void DrShdMdoDecExtTbl::setShaderParamAdd(u32 *param, u32 *globalParam) {
  unknown20 = param;
  unknown28 = globalParam;
}

} // namespace ml
