#pragma once
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFieldGimmick {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static int getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int map);
  static u16 getBdatIdOfActiveGmkAntiBladeArea();
};

} // namespace gf
