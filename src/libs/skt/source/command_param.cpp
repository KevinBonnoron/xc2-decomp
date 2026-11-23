#include <stdlib.h>

#include "mm_mtl/fixstr.h"
#include "skt/command_manager.h"
#include "skt/fixed_vector.h"
#include "types.h"

namespace skt {

bool CommandParam::isValid(int index) const { return static_cast<size_t>(index) < unknown800.size(); }

const char *CommandParam::getArg(int index) const {
  const char *arg = "";
  if (isValid(index) && unknown800[index].unknown00 != nullptr) {
    arg = unknown800[index].unknown00;
  }
  return arg;
}

mm::mtl::FixStr<128> CommandParam::getStr(int index) const { return mm::mtl::FixStr<128>(getArg(index)); }

bool CommandParam::getS32(int index, int &value) const {
  const char *arg = getArg(index);
  if (*arg != '\0') {
    char *end;
    value = strtol(arg, &end, 0);
    if (end != arg) {
      return true;
    }
  }

  return false;
}

bool CommandParam::getF32(int index, f32 &value) const {
  const char *arg = getArg(index);
  if (*arg != '\0') {
    char *end;
    value = strtod(arg, &end);
    if (end != arg) {
      return true;
    }
  }

  return false;
}

} // namespace skt
