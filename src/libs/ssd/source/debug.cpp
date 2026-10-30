#include "ssd/ssd_debug.h"
#include "ssd/ssd_mutex.h"
#include "types.h"

namespace ssd {
enum Result : long;

namespace Debug {

unknown002 log_;

void Init() {
  log_.m_logTimeStampType = LogTimeStamp::TYPE_UNKNOWN_3;
  log_.m_errorLogFlag = 0x10000015;
  log_.m_warningLogFlag = 0x10000015;
  log_.unknown0c = 0x10000015;
  log_.unknown10 = LogMethodT;
}

Result LogMethodT(LogMessage::Type type, const char16_t *text) { return static_cast<Result>(0); }

void SetMessageMethod(unknown001 method) { log_.unknown10 = method != nullptr ? method : LogMethodT; }

void SetTimeStampType(LogTimeStamp::Type type) { log_.m_logTimeStampType = type; }

void OnWarningFlag(u32 flag) { log_.m_warningLogFlag |= flag; }

void OnErrorFlag(u32 flag) { log_.m_errorLogFlag |= flag; }

} // namespace Debug

Mutex OutStreamLock;

void InitDebug() { OutStreamLock.unknown001(); }

void QuitDebug() { OutStreamLock.unknown002(); }

} // namespace ssd
