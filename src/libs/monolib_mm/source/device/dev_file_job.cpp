#include "ml/dev_file_job.h"

#include "ml/critical_section.h"
#include "ml/file_handle_th.h"
#include "ml/work_root.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"

namespace ml {
class IWorkEvent;

mm::mtl::FixedList<u32, 512> DevFileJob::s_jobs;

CriticalSection &DevFileJob::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

DevFileJob::DevFileJob(const char *name, WorkObj *parent) : WorkObj(name, parent, 0), m_fileHandleTh(nullptr), unknown1f4(0), unknown1f8(false), unknown1f9(false), unknown1fa(false) {
  CS lock(getCriticalSection());
  u32 wid = unknown50;
  s_jobs.push_back(wid);
}

DevFileJob::~DevFileJob() {
  CS lock(getCriticalSection());
  u32 wid = unknown50;
  mm::mtl::FixedList<u32, 512>::iterator it = mm::mtl::find(s_jobs.begin(), s_jobs.end(), wid);
  if (it != s_jobs.end()) {
    s_jobs.erase(it);
  }
}

u32 DevFileJob::getJob(FileHandleTh *handle) {
  CS lock(getCriticalSection());
  for (mm::mtl::FixedList<u32, 512>::iterator it = s_jobs.begin(); it != s_jobs.end(); ++it) {
    DevFileJob *job = static_cast<DevFileJob *>(WorkRootState::getWork(*it));
    if (job != nullptr && job->m_fileHandleTh == handle) {
      return *it;
    }
  }
  return -1;
}

void DevFileJob::clearJob(IWorkEvent *event) {
  if (event == nullptr) {
    wkSetEvent(static_cast<EVT>(0));
  } else if (m_fileHandleTh != nullptr && m_fileHandleTh->m_iWorkEvent == event) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

const char *DevFileJob::getFileName() const { return m_fileHandleTh->unknown98.c_str(); }

f32 DevFileJob::getTransferRatio() const {
  f32 ratio = 0.0f;
  if (m_fileHandleTh != nullptr && m_fileHandleTh->unknown18 != 0) {
    ratio = static_cast<f32>(m_fileHandleTh->m_currentPtr) / static_cast<f32>(static_cast<u32>(m_fileHandleTh->unknown18));
  }
  return ratio;
}

void DevFileJob::shutdownForce() { unknown1fa = true; }

} // namespace ml
