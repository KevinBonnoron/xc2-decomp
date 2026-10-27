#include "dr/dr_res_etc_uniform_obj.h"

#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResEtcUniformObj::DrResEtcUniformObj(DrMan *drMan, int max, int size, int bufferSize) : unknown04(max), unknown08(0), unknown0c(0), unknown10(bufferSize), unknown20(nullptr) {
  int allocSize = unknown04 * 8 + unknown10 * 0x40;
  void *buffer = mtl::MemManager::allocate(drMan->unknown14, allocSize, 0x10, false, "no name", 0);
  unknown18 = static_cast<u8 *>(buffer) + (unknown04 << 3);
  unknown20 = buffer;
  unknown28 = static_cast<unknown001 *>(buffer);
  unknown00 = size;
  unknown30.setup(size);
}

DrResEtcUniformObj::~DrResEtcUniformObj() {
  unknown30.release();
  if (unknown20 != nullptr) {
    mtl::MemManager::deallocate(unknown20, 0, false);
    unknown20 = nullptr;
  }
}

void DrResEtcUniformObj::begin() {
  unknown08 = 0;
  unknown0c = 0;
}

void DrResEtcUniformObj::end() {
  if (unknown0c != 0) {
    unknown30.updateData(0, unknown0c);
  }
}

void DrResEtcUniformObj::setUniformBlock(s16 index, u32 binding) { unknown30.setUniformBlock(binding, unknown28[index].unknown00, unknown28[index].unknown04); }

} // namespace ml
