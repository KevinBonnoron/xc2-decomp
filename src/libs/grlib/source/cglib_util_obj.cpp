#include "grlib/cglib_util_obj.h"

namespace grlib {

CGLibUtilObj::CGLibUtilObj() {}

CGLibUtilObj::~CGLibUtilObj() {}

void CGLibUtilObj::release() {
  unknown00.release();
  unknown68[0].release();
  unknown68[1].release();
  unknown68[2].release();
  unknown98[0].release();
  unknown98[1].release();
  unknownd8.release();
  unknown100.release();
}

} // namespace grlib
