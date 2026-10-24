#include "event/copydata_manager.h"

#include <stdarg.h>

namespace event {

CopydataManager::CopydataManager() : unknown10(0), unknown14("evtEditor"), _58() {}

void CopydataManager::clear() {}

void CopydataManager::init() {}

void CopydataManager::OnEventProc(MSG_TYPE type) {}

void CopydataManager::pause(bool isPause) {}

void CopydataManager::send(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_end(args);
}

} // namespace event
