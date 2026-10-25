#include "dr/dr_shd_mdo_dec_ext_tbl.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_shd_fetch_obj.h"
#include "dr/dr_shd_mdo_dec_res.h"

namespace ml {
class DrResFetch;

void DrShdMdoDecExtTbl::bindShader() {
  DrAPCache *cache = DrAPCache::s_pIns;
  DrResFetch *fetch = &unknown18->m_fetch->unknown20;
  cache->setupShader(this, fetch);
}

u32 DrShdMdoDecExtTbl::getValGlobalParam(int index) { return unknown28[index]; }

} // namespace ml
