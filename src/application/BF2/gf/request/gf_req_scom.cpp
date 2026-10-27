#include "gf/request/gf_req_scom.h"

namespace gf {

bool GfReqSmallCom::isExistCommand() {
  GfReqSmallCom *smallCom = get();
  if (smallCom->unknown4820 != 0) {
    return true;
  }

  return smallCom->unknown9040 != 0;
}

} // namespace gf
