#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shader.h"

namespace ml {
class DrResFetch;
class DrShdFetchMan;
class DrShdFetchObj;
struct MdsMatVertexInfo;

class DrShdMdoDecRes : public grlib::CGLibDecShader {
public:
  DrShdMdoDecRes();
  ~DrShdMdoDecRes();
  void releaseObj();
  void setVertexParam(DrShdFetchMan *fetchMan, int num, const MdsMatVertexInfo *infos);
  DrResFetch *getFetch();

  DrShdFetchObj *m_fetch;
};

static_assert(offsetof(DrShdMdoDecRes, m_fetch) == 0x68, "");

} // namespace ml
