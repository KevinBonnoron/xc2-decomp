#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DevFileReaderTh;
class FileHandleTh;

class DevFileJobTh {
public:
  virtual bool asyncUpdate();
  virtual int getJobType() const;
  virtual DevFileReaderTh *getReader();

  s32 unknown08; // Inferred role: result; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  FileHandleTh *unknown10; // Inferred role: file handle; original member name unknown.
  bool unknown18;          // Inferred role: cancel requested; original member name unknown.
};

static_assert(offsetof(DevFileJobTh, unknown08) == 0x08, "");
static_assert(offsetof(DevFileJobTh, unknown10) == 0x10, "");
static_assert(offsetof(DevFileJobTh, unknown18) == 0x18, "");

class DevFileReaderTh : public DevFileJobTh {
public:
  int getJobType() const override;
  DevFileReaderTh *getReader() override;
};

class DevFileWriterTh : public DevFileJobTh {
public:
  int getJobType() const override;
};

} // namespace ml
