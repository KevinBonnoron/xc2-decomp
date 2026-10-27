#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "types.h"

namespace ml {

class FileHandleTh;
class IWorkEvent;

class DevFileJob : public WorkObj {
public:
  void clearJob(IWorkEvent *event);
  const char *getFileName() const;
  f32 getTransferRatio() const;
  void shutdownForce();

  FileHandleTh *unknown1a8; // Inferred role: file handle; original member name unknown.
  u8 _1b0[0x1fa - 0x1b0];
  bool unknown1fa; // Inferred role: shutdown force; original member name unknown.
};

static_assert(offsetof(DevFileJob, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DevFileJob, unknown1fa) == 0x1fa, "");

} // namespace ml
