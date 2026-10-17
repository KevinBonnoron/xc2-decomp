#pragma once
#include <stddef.h>

#include "ml/base_object.h"
#include "ml/work_event.h"
#include "types.h"

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

  FileHandleTh *handle;
  void *buffer;
  int size;
  u8 _d4[0xe0 - 0xd4];
  u64 timeStamp;
  u8 _e8[0xf0 - 0xe8];
  bool isBufferOwner;
  u8 _f1[0xf8 - 0xf1];
  mm::mtl::IAllocator *allocator;
};

static_assert(offsetof(FileResTh, handle) == 0xc0, "");
static_assert(offsetof(FileResTh, size) == 0xd0, "");
static_assert(offsetof(FileResTh, timeStamp) == 0xe0, "");
static_assert(offsetof(FileResTh, isBufferOwner) == 0xf0, "");
static_assert(sizeof(FileResTh) == 0x100, "");

} // namespace ml
