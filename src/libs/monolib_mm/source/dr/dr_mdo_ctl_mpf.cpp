#include "dr/dr_mdo_ctl_mpf.h"

namespace ml {

void DrMdoCtlMpf::callZPrepassRender() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  defMpfZPreRender();
}

} // namespace ml
