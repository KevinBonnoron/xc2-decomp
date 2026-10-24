#include "event/cmd_param.h"

namespace event {

CmdParam::CmdParam() {}

void CmdParam::clear() {
  for (size_t i = 0; i < VARIABLE_COUNT; i++) {
    unknown08[i].clear();
  }
}

CmdVariable &CmdParam::val(size_t index) { return unknown08[index]; }

const CmdVariable &CmdParam::val(size_t index) const { return unknown08[index]; }

} // namespace event
