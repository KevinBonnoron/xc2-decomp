#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "ml/base_object.h"
#include "ml/work_event.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {

class FileHandleTh;

class FileResTh : public BaseObjectM, public IWorkEvent {
public:
  FileResTh();
  ~FileResTh() override;
  bool isExist() const;
  virtual void setMem(void *buffer, int size, const char *name, bool isBufferOwner);
  virtual bool loadBlock(mtl::ALLOC_HANDLE handle, const char *path, u32 option, u32 priority);
  virtual bool loadBlock(mm::mtl::IAllocator *allocator, const char *path, u32 option);
  virtual bool load(mtl::ALLOC_HANDLE handle, const char *path, u32 option, FILE_PRIO priority);
  virtual bool load(mm::mtl::IAllocator *allocator, const char *path, u32 option, FILE_PRIO priority);
  virtual void release();
  bool OnFileEvent(EventFileTh *event) override;

  FileHandleTh *fileHandle;
  void *buffer;
  int size;
  u8 _d4[0xe0 - 0xd4];
  u64 timeStamp;
  u8 _e8[0xf0 - 0xe8];
  bool isBufferOwner;
  u8 _f1[0xf8 - 0xf1];
  mm::mtl::IAllocator *allocator;
};

static_assert(offsetof(FileResTh, fileHandle) == 0xc0, "");
static_assert(offsetof(FileResTh, size) == 0xd0, "");
static_assert(offsetof(FileResTh, timeStamp) == 0xe0, "");
static_assert(offsetof(FileResTh, isBufferOwner) == 0xf0, "");
static_assert(sizeof(FileResTh) == 0x100, "");

} // namespace ml
