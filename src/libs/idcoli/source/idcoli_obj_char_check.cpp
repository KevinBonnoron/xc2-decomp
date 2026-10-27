#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"

namespace idcoli {

bool IDColiObjCharCheck::testCheckBox(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallBox[unknownc4](result, input, data);
  }

  return false;
}

} // namespace idcoli
