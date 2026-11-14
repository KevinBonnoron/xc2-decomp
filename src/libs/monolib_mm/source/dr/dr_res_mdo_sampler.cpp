#include "dr/dr_res_mdo_sampler.h"

#include "grlib/cglib_sampler.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSampler::DrResMdoSampler(const u8 *data) : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(1), unknown20(nullptr), unknown28(0) { setupSampler(data); }

DrResMdoSampler::~DrResMdoSampler() { samplerRelease(); }

void DrResMdoSampler::samplerRelease() {
  if (unknown20 != nullptr) {
    for (int i = 0; i < unknown28; i++) {
      unknown30[i].~CGLibSampler();
    }
    if (unknown20 != nullptr) {
      mtl::MemManager::deallocate(unknown20, 0, false);
      unknown20 = nullptr;
    }
  }
}

} // namespace ml
