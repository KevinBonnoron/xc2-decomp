#include "event/cmd_param.h"

namespace event {

CmdParam::CmdParam() {}

void CmdParam::clear() {
  for (size_t i = 0; i < VARIABLE_UNKNOWN_11; i++) {
    m_cmdVariable[i].clear();
  }
}

CmdVariable &CmdParam::val(size_t index) { return m_cmdVariable[index]; }

const CmdVariable &CmdParam::val(size_t index) const { return m_cmdVariable[index]; }

} // namespace event
