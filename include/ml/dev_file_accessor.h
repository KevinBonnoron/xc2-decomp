#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
union VAL64;
} // namespace mm

namespace ml {
class DevFileJobTh;
class FileHandleTh;
struct DevFileParamTh;

enum DevFileResult {};

class DevFileAccessor {
public:
  virtual ~DevFileAccessor() {}
  virtual bool initialize();
  virtual bool finalize();
  virtual void tail();
  virtual u32 addressAlignment();
  virtual bool isValid() const;
  virtual bool readBlock(FileHandleTh *handle, const char *path);
  virtual bool readBlockSlice(FileHandleTh *handle, const char *path, void *buffer, u32 size);
  virtual int getFileSize(const char *path, mm::VAL64 *size, const char *archive);
  virtual bool writeBlock(FileHandleTh *handle, DevFileResult &result);
  virtual DevFileJobTh *createLoader(mtl::ALLOC_HANDLE handle);
  virtual DevFileJobTh *createWriter(mtl::ALLOC_HANDLE handle);
  virtual DevFileJobTh *createFileValid(mtl::ALLOC_HANDLE handle);
  virtual bool rfOpen(FileHandleTh *handle, const char *path);
  virtual bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
  virtual bool rfIsBusy(FileHandleTh *handle);
  virtual bool rfClose(FileHandleTh *handle);
  virtual bool rfIsUsedChannel(u32 channel);
  virtual bool getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension);
  virtual bool deleteFileBlock(const char *path);
  virtual const char *getMediaRootPath() const;
};

} // namespace ml
