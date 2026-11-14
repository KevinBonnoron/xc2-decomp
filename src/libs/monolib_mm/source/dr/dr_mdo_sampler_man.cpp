#include "dr/dr_mdo_sampler_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_mdl_sampler.h"
#include "dr/dr_res_list.h"
#include "dr/dr_res_mdo_sampler.h"
#include "mtl/alloc_handle.h"

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

void DrMdoSamplerMan::begin() {
  if (DrMan::get()->unknown188->update()) {
    for (DrResMdoSampler *sampler = unknown00; sampler != nullptr; sampler = sampler->unknown08) {
      sampler->setup();
    }
  }
}

DrResMdoSampler *DrMdoSamplerMan::createSamplerObj(const u8 *data) {
  DrResMdoSampler *sampler = unknown003(unknown00, data);
  if (sampler != nullptr) {
    return sampler;
  }
  sampler = new (unknown10->unknown10) DrResMdoSampler(data);
  if (sampler != nullptr) {
    unknown101(unknown00, unknown08, sampler);
  }
  return sampler;
}

DrResMdoSampler *DrMdoSamplerMan::createSamplerSeamObj(const u8 *data) {
  DrResMdoSampler *sampler = new (unknown10->unknown10) DrResMdoSampler(data);
  if (sampler != nullptr) {
    unknown101(unknown00, unknown08, sampler);
  }
  return sampler;
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
