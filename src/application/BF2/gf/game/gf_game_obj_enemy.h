#pragma once

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameObjEnemy {
public:
  void enterEnemyObj(GF_OBJ_HANDLE *handle);
  void leaveEnemyObj(GF_OBJ_HANDLE *handle);
};

} // namespace gf
