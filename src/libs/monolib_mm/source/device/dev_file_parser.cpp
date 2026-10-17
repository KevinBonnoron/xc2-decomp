#include "ml/dev_file_parser.h"

#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_system.h"

namespace ml {

bool DevFileParser::isInitialized() {
  DevFileParser *parser = get();
  if (parser->wkIsWaitException()) {
    return false;
  }

  return parser->wkIsActive();
}

bool DevFileParser::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool DevFileParser::wkStandbyLogout() {
  if (m_children.size() == 0 && WorkSystem::get() == nullptr && LibMain::get() == nullptr) {
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

} // namespace ml
