#include "ml/dev_file_job_read_dvd.h"

#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/work_obj.h"

namespace ml {

DevFileJobReadDvd::DevFileJobReadDvd(const char *name, WorkObj *parent) : DevFileJob(name, parent) {}

DevFileJobReadDvd::~DevFileJobReadDvd() {
  // A body that generates no code still makes the destructor keep its vtable pointer store, which the game's destructors show.
  (void)0;
}

void DevFileJobReadDvd::wkUpdate() {
  if (unknown1fa) {
    if (m_fileHandleTh != nullptr) {
      if (DevFileTh::isLoading(m_fileHandleTh)) {
        return;
      }
      if (m_fileHandleTh->unknown94 & 4) {
        m_fileHandleTh->call(CBM_UNKNOWN_2);
      } else {
        m_fileHandleTh->call(CBM_UNKNOWN_4);
      }
    }
    unknown1fa = false;
  } else if (m_fileHandleTh != nullptr && m_fileHandleTh->m_currentPtr != 0 && m_fileHandleTh->m_currentPtr == m_fileHandleTh->unknown18) {
    // Decision 2026-11-14 #23: a bare accessor call is not original code; the test below gives the same bytes. The game keeps only the
    // singleton null test and the UniquePtr assert of this inlined accessor (0x7100721ae8-0x7100721b14); its result is the constant
    // false, so what the original did with it cannot be seen (`&& !DevFileTh::isSuspend()` at the end of the `else if` condition gives
    // the same 108 instructions). That it is isSuspend is shown by the order of the functions: clang emits the functions of a unit in
    // the order they are first referenced, and the game has, right after wkUpdate (0x7100721a6c), DevFileTh::isLoading (0x7100721c1c),
    // FileHandleTh::call (0x7100721d38) and DevFileTh::isSuspend (0x7100721e0c), then wkStandbyLogin (0x7100721e50); the other accessor
    // with this body, isLapTimeForDebug, stays at 0x7100737500 after enableLapTimeForDebug.
    if (DevFileTh::isSuspend()) {
      return;
    }
    m_fileHandleTh->call(CBM_UNKNOWN_2);
  }
}

bool DevFileJobReadDvd::wkStandbyLogin() {
  if (!wkIsShutdown() && !unknown1f8) {
    return false;
  }
  return WorkObj::wkStandbyLogin();
}

bool DevFileJobReadDvd::wkStandbyLogout() {
  if (m_fileHandleTh != nullptr) {
    cancel(m_fileHandleTh);
    return false;
  }
  return WorkObj::wkStandbyLogout();
}

} // namespace ml
