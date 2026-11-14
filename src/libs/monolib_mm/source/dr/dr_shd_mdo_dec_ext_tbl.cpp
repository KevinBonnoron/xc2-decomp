#include "dr/dr_shd_mdo_dec_ext_tbl.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_sampler.h"
#include "dr/dr_shd_fetch_obj.h"
#include "dr/dr_shd_mdo_dec_res.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {
class DrResFetch;

DrShdMdoDecExtTbl::DrShdMdoDecExtTbl() : CGLibDecShdExtTbl() {}

DrShdMdoDecExtTbl::~DrShdMdoDecExtTbl() {}

void DrShdMdoDecExtTbl::setTextureParam(int num) {
  unknown36 = num;
  for (int i = 0; i < num; i++) {
    unknown20[i] = i;
  }
}

void DrShdMdoDecExtTbl::bindShader() {
  DrAPCache *cache = DrAPCache::s_pIns;
  DrResFetch *fetch = &unknown18->m_fetch->unknown20;
  cache->setupShader(this, fetch);
}

u32 DrShdMdoDecExtTbl::getValGlobalParam(int index) { return m_valGlobalParam[index]; }

void DrShdMdoDecExtTbl::setShaderParamAdd(u32 *param, u32 *globalParam) {
  unknown20 = param;
  m_valGlobalParam = globalParam;
}

void DrShdMdoDecExtTbl::setTextureList(const MdsMatTextureInfo *infos, grlib::CGLibTextureBuffer **textures, DrResMdoSampler *sampler) {
  u8 count = unknown36;
  DrAPCache *cache = DrAPCache::s_pIns;
  for (u32 i = 0; i < count; i++) {
    grlib::CGLibTextureBuffer *texture = textures[infos[i].unknown00];
    if (texture->getMipmap() < 2) {
      cache->setTexture(*texture, sampler->unknown30[infos[i].unknown04], unknown20[i]);
    } else {
      cache->setTexture(*texture, sampler->unknown30[infos[i].unknown02], unknown20[i]);
    }
  }
}

} // namespace ml
