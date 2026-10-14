#pragma once
#include "types.h"

namespace gf {

class GfBdatMsg {
public:
  static u8 *getFpPcWpn();
  static u8 *getFpPcWpnType();
  static u8 *getFpMapInfo();
};

} // namespace gf
