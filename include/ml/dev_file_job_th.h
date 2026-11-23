#pragma once
#include <stddef.h>

#include "ml/dev_file_th.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ml {

class DevFileAccessor;
class DevFileReaderTh;
class FileHandleTh;

class DevFileJobTh {
public:
  DevFileJobTh() : unknown08(0), m_fileHandleTh(nullptr), unknown18(false) {}
  virtual ~DevFileJobTh() {}
  virtual bool asyncUpdate();
  virtual int getJobType() const;
  virtual DevFileReaderTh *getReader();

  s32 unknown08; // Inferred role: result; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  FileHandleTh *m_fileHandleTh; // Inferred role: file handle; original member name unknown.
  bool unknown18;               // Inferred role: cancel requested; original member name unknown.
};

static_assert(offsetof(DevFileJobTh, unknown08) == 0x08, "");
static_assert(offsetof(DevFileJobTh, m_fileHandleTh) == 0x10, "");
static_assert(offsetof(DevFileJobTh, unknown18) == 0x18, "");

class DevFileReaderTh : public DevFileJobTh {
public:
  // Inferred role: one accessor to try for the file, filled by DevFileTh::Impl::readFile; original name unknown.
  struct unknown001 {
    MEDIA unknown00;                    // Inferred role: media; original member name unknown.
    const char *unknown08;              // Inferred role: media root path; original member name unknown.
    DevFileAccessor *m_devFileAccessor; // Inferred role: accessor; original member name unknown.
  };

  bool asyncUpdate() override;
  int getJobType() const override;
  DevFileReaderTh *getReader() override;

  mm::mtl::FixedVector<unknown001, 8> unknown20; // Inferred role: accessors to try in order; original member name unknown.
};

static_assert(sizeof(DevFileReaderTh::unknown001) == 0x18, "");
static_assert(offsetof(DevFileReaderTh, unknown20) == 0x20, "");
static_assert(sizeof(DevFileReaderTh) == 0xe8, "");

class DevFileWriterTh : public DevFileJobTh {
public:
  int getJobType() const override;
};

} // namespace ml
