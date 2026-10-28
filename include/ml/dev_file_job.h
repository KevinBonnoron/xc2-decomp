#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class FileHandleTh;
class IWorkEvent;
class CriticalSection;

class DevFileJob : public WorkObj {
public:
  DevFileJob(const char *name, WorkObj *parent);
  ~DevFileJob() override;
  static CriticalSection &getCriticalSection();
  static u32 getJob(FileHandleTh *handle);
  virtual bool isRequestFile(const char *path) { return false; }
  virtual bool cancel(FileHandleTh *handle) { return false; }
  void clearJob(IWorkEvent *event);
  const char *getFileName() const;
  f32 getTransferRatio() const;
  void shutdownForce();

  FileHandleTh *unknown1a8;       // Inferred role: file handle; original member name unknown.
  mm::mtl::FixStr<64> unknown1b0; // Inferred role: file name; original member name unknown.
  u32 unknown1f4;                 // Inferred role: unused value; original member name unknown.
  bool unknown1f8;                // Inferred role: flag; original member name unknown.
  bool unknown1f9;                // Inferred role: flag; original member name unknown.
  bool unknown1fa;                // Inferred role: shutdown force; original member name unknown.

  static mm::mtl::FixedList<u32, 512> s_jobs;
};

static_assert(offsetof(DevFileJob, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DevFileJob, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DevFileJob, unknown1f4) == 0x1f4, "");
static_assert(offsetof(DevFileJob, unknown1fa) == 0x1fa, "");

} // namespace ml
