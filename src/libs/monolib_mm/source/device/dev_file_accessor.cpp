#include "ml/dev_file_accessor.h"

#include "mtl/alloc_handle.h"

namespace ml {

bool DevFileAccessor::isValid() const { return true; }

bool DevFileAccessor::readBlock(FileHandleTh *handle, const char *path) { return false; }

bool DevFileAccessor::writeBlock(FileHandleTh *handle, DevFileResult &result) {
  result = static_cast<DevFileResult>(0);
  return false;
}

bool DevFileAccessor::deleteFileBlock(const char *path) { return false; }

bool DevFileAccessor::initialize() { return true; }

bool DevFileAccessor::finalize() { return true; }

void DevFileAccessor::tail() {}

u32 DevFileAccessor::addressAlignment() { return 16; }

bool DevFileAccessor::readBlockSlice(FileHandleTh *handle, const char *path, void *buffer, u32 size) { return false; }

int DevFileAccessor::getFileSize(const char *path, mm::VAL64 *size, const char *archive) { return -1; }

DevFileJobTh *DevFileAccessor::createLoader(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileAccessor::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileAccessor::createFileValid(mtl::ALLOC_HANDLE handle) { return nullptr; }

bool DevFileAccessor::rfOpen(FileHandleTh *handle, const char *path) { return false; }

bool DevFileAccessor::rfRead(FileHandleTh *handle, const DevFileParamTh &param) { return false; }

bool DevFileAccessor::rfIsBusy(FileHandleTh *handle) { return false; }

bool DevFileAccessor::rfClose(FileHandleTh *handle) { return false; }

bool DevFileAccessor::rfIsUsedChannel(u32 channel) { return false; }

bool DevFileAccessor::getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) { return false; }

const char *DevFileAccessor::getMediaRootPath() const { return ""; }

} // namespace ml
