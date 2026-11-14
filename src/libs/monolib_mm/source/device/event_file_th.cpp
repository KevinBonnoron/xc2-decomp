#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace ml {

EventFileTh::EventFileTh(CBM cbm, FileHandleTh *handle) : type(cbm), unknown08(handle), m_memHandle(), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(0), unknown38(nullptr) {
  if (handle != nullptr) {
    m_memHandle = handle->unknown2c;
    unknown18 = handle->unknown30;
    unknown20 = handle->unknown98.c_str();
    unknown28 = handle->unknown08;
    unknown30 = handle->unknown18;
    unknown38 = handle->unknown68;
  }
}

void EventFileTh::setMemHandle(mtl::ALLOC_HANDLE handle) { m_memHandle = handle; }

void *EventFileTh::moveFileData() {
  if (unknown08 != nullptr) {
    void *data = unknown08->unknown08;
    unknown08->unknown08 = nullptr;
    return data;
  }
  return nullptr;
}

} // namespace ml
