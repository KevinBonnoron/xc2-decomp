#pragma once
#include <stddef.h>

#include "ml/dev_file_job.h"
#include "ml/wii_filer_common.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class WorkObj;

class DevFileJobSendCom : public DevFileJob {
public:
  DevFileJobSendCom(const char *name, WorkObj *parent);
  ~DevFileJobSendCom() override;
  void setParam(const char *param);
  void callSendOK(const char *text);
  void callSendError(const char *text);
  bool cancel(FileHandleTh *handle) override;
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  u8 _1fb[0x1fc - 0x1fb];
  WiiFilerCommon unknown1fc;       // Inferred role: send packet; original member name unknown.
  mm::mtl::FixStr<256> unknown43c; // Inferred role: parameter text; original member name unknown.
};

static_assert(offsetof(DevFileJobSendCom, unknown1fc) == 0x1fc, "");
static_assert(offsetof(DevFileJobSendCom, unknown43c) == 0x43c, "");

} // namespace ml
