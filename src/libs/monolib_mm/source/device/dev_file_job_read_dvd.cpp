#include "ml/dev_file_job_read_dvd.h"

#include "ml/work_obj.h"

namespace ml {

DevFileJobReadDvd::DevFileJobReadDvd(const char *name, WorkObj *parent) : DevFileJob(name, parent) {}

DevFileJobReadDvd::~DevFileJobReadDvd() {
  // A body that generates no code still makes the destructor keep its vtable pointer store, which the game's destructors show.
  (void)0;
}

bool DevFileJobReadDvd::wkStandbyLogin() {
  if (!wkIsShutdown() && !unknown1f8) {
    return false;
  }
  return WorkObj::wkStandbyLogin();
}

bool DevFileJobReadDvd::wkStandbyLogout() {
  if (unknown1a8 != nullptr) {
    cancel(unknown1a8);
    return false;
  }
  return WorkObj::wkStandbyLogout();
}

} // namespace ml
