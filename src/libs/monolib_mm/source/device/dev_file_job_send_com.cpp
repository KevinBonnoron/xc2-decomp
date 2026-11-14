#include "ml/dev_file_job_send_com.h"

#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/work_obj.h"

namespace ml {

DevFileJobSendCom::DevFileJobSendCom(const char *name, WorkObj *parent) : DevFileJob(name, parent) { unknown1f9 = true; }

DevFileJobSendCom::~DevFileJobSendCom() {}

void DevFileJobSendCom::setParam(const char *param) { unknown43c = param; }

void DevFileJobSendCom::callSendOK(const char *text) {
  if (unknown1a8 != nullptr) {
    DevFileTh::cancel(unknown1a8, false);
    unknown1a8 = nullptr;
  }
}

void DevFileJobSendCom::callSendError(const char *text) {
  if (unknown1a8 != nullptr) {
    DevFileTh::cancel(unknown1a8, false);
    unknown1a8 = nullptr;
  }
}

bool DevFileJobSendCom::cancel(FileHandleTh *handle) {
  if (unknown1a8 == handle) {
    wkIsCurrent();
  }
  return true;
}

void DevFileJobSendCom::wkUpdate() {}

bool DevFileJobSendCom::wkStandbyLogin() {
  if (!wkIsShutdown()) {
    if (!wkIsCurrent()) {
      return false;
    }
    unknown1fc.clear();
    unknown1fc.setLocation(unknown1a8->unknown98.c_str());
    unknown1fc.setTimeStamp(unknown43c.c_str());
  }
  return WorkObj::wkStandbyLogin();
}

bool DevFileJobSendCom::wkStandbyLogout() {
  if (unknown1a8 != nullptr) {
    unknown1b0 = "error send data";
  }
  return WorkObj::wkStandbyLogout();
}

} // namespace ml
