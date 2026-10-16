#pragma once
#include "types.h"

enum GrlVtxFormat {
  GRL_VTX_FORMAT_R32F = 10,
  GRL_VTX_FORMAT_R32UI = 11,
  GRL_VTX_FORMAT_RG16F = 17,
  GRL_VTX_FORMAT_RG16SN = 19,
  GRL_VTX_FORMAT_RG16UI = 20,
  GRL_VTX_FORMAT_RG32F = 22,
  GRL_VTX_FORMAT_RGB32F = 34,
  GRL_VTX_FORMAT_RGBA8 = 37,
  GRL_VTX_FORMAT_RGBA8SN = 38,
  GRL_VTX_FORMAT_RGBA8UI = 39,
  GRL_VTX_FORMAT_RGBA16 = 42,
  GRL_VTX_FORMAT_RGBA16SN = 43,
  GRL_VTX_FORMAT_RGBA16I = 45,
  GRL_VTX_FORMAT_RGBA32F = 46,
  GRL_VTX_FORMAT_RGBA32UI = 47,
};

namespace grlib {

struct CGLibVtxAttr {
  GrlVtxFormat format;
  u32 location;
  u32 offset;
  u32 bufferIndex;
};

class CGLibVtxFetch {
public:
  CGLibVtxFetch();
  ~CGLibVtxFetch();
  void release();
  void createFetchObj(CGLibVtxAttr *attributes, int num);

  u8 _00[0x10 - 0x00];
};

} // namespace grlib
