#pragma once
#include "ml/dev_file_job.h"

namespace ml {

class WorkObj;

class DevFileJobReadDvd : public DevFileJob {
public:
  DevFileJobReadDvd(const char *name, WorkObj *parent);
  ~DevFileJobReadDvd() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
};

} // namespace ml
