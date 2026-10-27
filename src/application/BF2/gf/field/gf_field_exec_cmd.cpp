#include "gf/field/gf_field_exec_cmd.h"

#include <string.h>

#include "gf/object/component/animation/gf_com_asm.h"

namespace gf {

template <typename T> void TFieldExecCmd<T>::create(const CreateInfo &info) {
  dispose();
  unknown00 = info.unknown00;
  unknown08 = info.unknown08;
  unknown2c = info.unknown2c;
}

template <typename T> bool TFieldExecCmd<T>::execCmd(T &comAsm, const char *command) const {
  const char *stateName = comAsm.getStateName(ANIM_LAYER_BASE);
  if (stateName == nullptr) {
    return false;
  }

  mm::mtl::FixStr<32> state = comAsm.getStateName(ANIM_LAYER_BASE);
  if (strcmp(command + 1, state.c_str() + 1) == 0) {
    return true;
  }

  return comAsm.execCmd(command, ANIM_LAYER_BASE);
}

template class TFieldExecCmd<GfComAsm>;

} // namespace gf
