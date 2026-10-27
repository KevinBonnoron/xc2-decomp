#include "ml/language_info.h"

#include "ml/ml_mem.h"
#include "mtl/mem_manager.h"

namespace ml {

LanguageInfo::LanguageInfo() {
  unknown28 = nullptr;
  unknown30 = 0;
  unknown20 = mtl::ALLOC_HANDLE();
  unknown10 = nullptr;
  unknown18 = 0;
  unknown1c = 0;
  unknown08 = 0;
  unknown0c = 0;
}

LanguageInfo::~LanguageInfo() {
  unknown18 = 0;
  if (unknown20.isValid() && unknown10 != nullptr) {
    mtl::MemManager::deallocate(unknown10, 0, false);
    unknown10 = nullptr;
  }
  unknown10 = nullptr;
  unknown1c = 0;
  unknown20 = mtl::ALLOC_HANDLE();
}

void LanguageInfo::initialize(mtl::ALLOC_HANDLE) {
  LanguageInfo *info = get();
  info->unknown10 = static_cast<LanguageInfoParam *>(mtl::MemManager::allocate(info->unknown20 = MlMem::getProductMem(), 0x1a00, 0x10, false, "no name", 0));
  info->unknown18 = 0;
  info->unknown1c = 0x40;
}

const char *LanguageInfo::getText(MLLANG_STRUCT *text) {
  LanguageInfo *info = get();
  const LanguageInfoParam &entry = info->unknown10[reinterpret_cast<size_t>(text) & 0xffff];
  return entry.unknown00[info->unknown0c];
}

} // namespace ml
