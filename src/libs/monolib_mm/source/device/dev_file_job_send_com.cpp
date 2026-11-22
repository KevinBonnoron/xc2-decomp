#include "ml/dev_file_job_send_com.h"

#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/work_obj.h"

namespace ml {

DevFileJobSendCom::DevFileJobSendCom(const char *name, WorkObj *parent) : DevFileJob(name, parent) { unknown1f9 = true; }

DevFileJobSendCom::~DevFileJobSendCom() {}

void DevFileJobSendCom::setParam(const char *param) { unknown43c = param; }

void DevFileJobSendCom::callSendOK(const char *text) {
  if (m_fileHandleTh != nullptr) {
    DevFileTh::cancel(m_fileHandleTh, false);
    m_fileHandleTh = nullptr;
  }
}

void DevFileJobSendCom::callSendError(const char *text) {
  if (m_fileHandleTh != nullptr) {
    DevFileTh::cancel(m_fileHandleTh, false);
    m_fileHandleTh = nullptr;
  }
}

bool DevFileJobSendCom::cancel(FileHandleTh *handle) {
  if (m_fileHandleTh == handle) {
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
    m_wiiFilerCommon.clear();
    m_wiiFilerCommon.setLocation(m_fileHandleTh->unknown98.c_str());
    m_wiiFilerCommon.setTimeStamp(unknown43c.c_str());
  }
  return WorkObj::wkStandbyLogin();
}

bool DevFileJobSendCom::wkStandbyLogout() {
  if (m_fileHandleTh != nullptr) {
    unknown1b0 = "error send data";
  }
  return WorkObj::wkStandbyLogout();
}

} // namespace ml
