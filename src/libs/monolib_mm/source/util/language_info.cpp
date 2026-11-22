#include "ml/language_info.h"

#include "ml/ml_mem.h"
#include "mtl/mem_manager.h"

namespace ml {

LanguageInfo::LanguageInfo() {
  unknown28 = nullptr;
  unknown30 = 0;
  m_ALLOC_HANDLE = mtl::ALLOC_HANDLE();
  m_languageInfoParam = nullptr;
  unknown18 = 0;
  unknown1c = 0;
  unknown08 = 0;
  unknown0c = 0;
}

LanguageInfo::~LanguageInfo() {
  unknown18 = 0;
  if (m_ALLOC_HANDLE.isValid() && m_languageInfoParam != nullptr) {
    mtl::MemManager::deallocate(m_languageInfoParam, 0, false);
    m_languageInfoParam = nullptr;
  }
  m_languageInfoParam = nullptr;
  unknown1c = 0;
  m_ALLOC_HANDLE = mtl::ALLOC_HANDLE();
}

void LanguageInfo::initialize(mtl::ALLOC_HANDLE) {
  LanguageInfo *info = get();
  info->m_languageInfoParam = static_cast<LanguageInfoParam *>(mtl::MemManager::allocate(info->m_ALLOC_HANDLE = MlMem::getProductMem(), 0x1a00, 0x10, false, "no name", 0));
  info->unknown18 = 0;
  info->unknown1c = 0x40;
}

const char *LanguageInfo::getText(MLLANG_STRUCT *text) {
  LanguageInfo *info = get();
  const LanguageInfoParam &entry = info->m_languageInfoParam[reinterpret_cast<size_t>(text) & 0xffff];
  return entry.unknown00[info->unknown0c];
}

} // namespace ml
