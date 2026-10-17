#pragma once
#include <stddef.h>

#include "ml/scn_obj.h"
#include "mm_mtl/fixstr.h"

namespace ml {

class Scn;

class ScnObjEnvColi : public ScnObj {
public:
  ScnObjEnvColi(Scn *scn);
  ~ScnObjEnvColi() override;
  const char *getName() const override { return m_name.c_str(); }

  mm::mtl::FixStr<64> m_name;
};

static_assert(offsetof(ScnObjEnvColi, m_name) == 0x14, "");

} // namespace ml
