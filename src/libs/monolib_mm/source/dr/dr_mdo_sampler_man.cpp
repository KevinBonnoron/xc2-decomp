#include "dr/dr_mdo_sampler_man.h"

#include "dr/dr_res_list.h"
#include "dr/dr_res_mdo_sampler.h"

namespace ml {

DrMdoSamplerMan::DrMdoSamplerMan(DrMan *drMan) : unknown00(nullptr), unknown08(nullptr), unknown10(drMan) {}

DrMdoSamplerMan::~DrMdoSamplerMan() {
  DrResMdoSampler *sampler = unknown00;
  while (sampler != nullptr) {
    DrResMdoSampler *next = sampler->unknown08;
    delete sampler;
    sampler = next;
  }
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void DrMdoSamplerMan::releaseSamplerObj(DrResMdoSampler *sampler) {
  int count = sampler->unknown18 - 1;
  if (sampler->unknown18 < 1) {
    count = 0;
  }
  sampler->unknown18 = count;
  if (count > 0) {
    return;
  }
  unknown001(unknown00, unknown08, sampler);
  delete sampler;
}

void DrMdoSamplerMan::releaseSamplerSeamObj(DrResMdoSampler *sampler) {
  unknown001(unknown00, unknown08, sampler);
  delete sampler;
}

} // namespace ml
