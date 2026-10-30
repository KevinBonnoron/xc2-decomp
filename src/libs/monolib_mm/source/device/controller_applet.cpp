#include "ml/controller_applet.h"

#include "device/nx/dev_pad_nx.h"
#include "nn/hid.h"
#include "nn/result.h"

namespace ml {

bool ControllerApplet::showApplet() {
  nn::hid::ControllerSupportArg arg;
  arg.unknown001();
  arg.unknown05 = true;
  nn::hid::ControllerSupportResultInfo info;
  nn::Result result = nn::hid::ShowControllerSupport(&info, arg);
  if (result.IsSuccess()) {
    DevPadNx::setUserSelectControllerID(info.unknown04);
  }
  return result.IsSuccess();
}

} // namespace ml
