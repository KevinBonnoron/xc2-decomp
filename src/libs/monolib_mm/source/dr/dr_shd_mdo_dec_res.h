#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shader.h"

namespace ml {
class DrShdFetchObj;

class DrShdMdoDecRes : public grlib::CGLibDecShader {
public:
  DrShdFetchObj *m_fetch;
};

static_assert(offsetof(DrShdMdoDecRes, m_fetch) == 0x68, "");

} // namespace ml
