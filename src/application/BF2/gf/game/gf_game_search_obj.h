#pragma once

namespace gf {

struct GF_SEARCH_OBJ;

static GF_SEARCH_OBJ *const INVALID_SEARCH_OBJ = reinterpret_cast<GF_SEARCH_OBJ *>(-1);

class GfGameSearchObj {
public:
  static void destroyObj(GF_SEARCH_OBJ *searchObj);
  static void setEnable(GF_SEARCH_OBJ *searchObj, bool isEnable);
};

} // namespace gf
