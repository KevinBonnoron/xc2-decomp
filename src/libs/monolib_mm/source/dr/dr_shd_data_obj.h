#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shader.h"
#include "types.h"

namespace ml {

class DrResFetch;
class DrShdDataList;

class DrShdDataObj : public grlib::CGLibDecShader {
public:
  void createShader(DrShdDataList *list, int type, int index);
  DrShdDataObj();
  ~DrShdDataObj();
  void release();
  void setupShader(u32 index);
  void setupShader(DrResFetch *fetch);
  void setupComputeShader();

  DrResFetch *unknown68[2]; // Inferred role: fetches; original member name unknown.
};

static_assert(offsetof(DrShdDataObj, unknown68) == 0x68, "");
static_assert(sizeof(DrShdDataObj) == 0x78, "");

} // namespace ml
