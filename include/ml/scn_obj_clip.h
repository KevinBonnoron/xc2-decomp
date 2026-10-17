#pragma once
#include <stddef.h>

#include "ml/scn_obj.h"
#include "mm_mtl/fixstr.h"

namespace ml {

class Scn;

class ScnObjClip : public ScnObj {
public:
  ScnObjClip(Scn *scn);
  ~ScnObjClip() override;
  const char *getName() const override { return m_name.c_str(); }

  mm::mtl::FixStr<64> m_name;
};

static_assert(offsetof(ScnObjClip, m_name) == 0x14, "");

} // namespace ml
