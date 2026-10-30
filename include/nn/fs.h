#pragma once
#include <stddef.h>

#include "nn/result.h"

// Reconstructed from the symbols imported by the game executable (_ZN2nn2fs14CommitSaveDataEPKc,
// _ZN2nn2fs8OpenFileEPNS0_10FileHandleEPKci, _ZN2nn2fs11GetFileSizeEPlNS0_10FileHandleE,
// _ZN2nn2fs9CloseFileENS0_10FileHandleE, _ZN2nn2fs8ReadFileEPmNS0_10FileHandleElPvm) and from how the game calls
// them; the parameter names, the return types and the layout of FileHandle are inferred (the game opens files with
// mode 1), no SDK header was used.
namespace nn {
namespace fs {

struct FileHandle {
  void *handle;
};

Result CommitSaveData(const char *mountName);
Result OpenFile(FileHandle *outHandle, const char *path, int mode);
Result GetFileSize(long *outSize, FileHandle handle);
void CloseFile(FileHandle handle);
Result ReadFile(size_t *outSize, FileHandle handle, long offset, void *buffer, size_t size);

} // namespace fs
} // namespace nn
