#include "event/cmd_param.h"

namespace event {

CmdParam::CmdParam() {}

void CmdParam::clear() {
  for (size_t i = 0; i < VARIABLE_COUNT; i++) {
    mVariables[i].clear();
  }
}

CmdVariable &CmdParam::val(size_t index) { return mVariables[index]; }

const CmdVariable &CmdParam::val(size_t index) const { return mVariables[index]; }

} // namespace event
