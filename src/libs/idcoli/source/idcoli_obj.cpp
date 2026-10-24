#include "idcoli/idcoli.h"

namespace idcoli {

IDColiObj::IDColiObj() {
  unknown10 = nullptr;
  unknown1c = 0;
  unknown20 = 9;
  unknown18 = 3;
  _40 = 0;
  unknown48 = nullptr;
  unknown08 = nullptr;
  _30 = 0;
  _38 = 0;
  unknown28 = 0;
  unknown2c = 0;
}

void IDColiObj::release() {
  unknown48 = nullptr;
  unknown1c |= 1 << IDColiManager::s_nStkIdx;
}

void IDColiObj::setDeleteCall() { unknown1c |= 1 << IDColiManager::s_nStkIdx; }

bool IDColiObj::isDeleteAll() const { return (unknown1c & 3) != 0; }

} // namespace idcoli
