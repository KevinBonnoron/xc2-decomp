#pragma once
#include "event/cmd_variable.h"
#include "mm_math/mm_vec3.h"
#include <stddef.h>

namespace event {

class CmdParam {
public:
  static constexpr size_t VARIABLE_UNKNOWN_11 = 11; // Inferred role: variable count; original name unknown.

  CmdParam();
  virtual ~CmdParam() {}
  void clear();
  CmdVariable &val(size_t index);
  const CmdVariable &val(size_t index) const;
  // Inferred role: stores a vector in three consecutive variables; original name unknown. Used by CamObj::update (moved
  // here from a file-local helper of cam_obj.cpp) and CharaObj::walkPos; the other builders of this kind (CharaObj::linerPos,
  // EffectObj::moveTo...) are written out and also match.
  void unknown001(size_t index, const mm::Vec3 &vec) {
    val(index).setF32(vec.x);
    val(index + 1).setF32(vec.y);
    val(index + 2).setF32(vec.z);
  }

private:
  CmdVariable m_cmdVariable[VARIABLE_UNKNOWN_11]; // Inferred role: variables; original member name unknown.
};

static_assert(sizeof(CmdParam) == 0x110, "");

} // namespace event
