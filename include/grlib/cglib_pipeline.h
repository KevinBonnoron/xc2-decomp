#pragma once
#include <stddef.h>

#include "nvn/nvn.h"
#include "types.h"

struct NVNcommandBuffer;

namespace grlib {

class CGLibPipeline {
public:
  static const int COLOR_TARGET_NUM = 8;
  static const int VERTEX_STREAM_NUM = 8;

  void setDefaults();
  void relase();
  void begin();
  void updateVertex();
  CGLibPipeline();
  ~CGLibPipeline();

  NVNcommandBuffer *m_cmdBuf;
  NVNblendState m_blendState;
  NVNchannelMaskState m_channelMaskDefault;
  NVNchannelMaskState m_colorBufferOn;
  NVNchannelMaskState m_colorBufferOff;
  NVNcolorState m_colorStateDefault;
  NVNcolorState m_blendOff;
  NVNcolorState m_blendOn;
  NVNdepthStencilState m_depthStencilState;
  NVNpolygonState m_cullingOff;
  NVNpolygonState m_cullingFront;
  NVNpolygonState m_cullingBack;
  NVNpolygonState m_cullingDispOff;
  NVNpolygonState m_pointMode;
  NVNpolygonState m_lineMode;
  NVNpolygonState m_triangle;
  NVNvertexStreamState m_vertexStreams[VERTEX_STREAM_NUM];
  int m_vertexStreamMax;
  bool m_isVertexStreamDirty;
  u64 _98;
};

static_assert(offsetof(CGLibPipeline, m_blendState) == 0x08, "");
static_assert(offsetof(CGLibPipeline, m_colorBufferOn) == 0x14, "");
static_assert(offsetof(CGLibPipeline, m_colorStateDefault) == 0x1c, "");
static_assert(offsetof(CGLibPipeline, m_depthStencilState) == 0x28, "");
static_assert(offsetof(CGLibPipeline, m_cullingOff) == 0x30, "");
static_assert(offsetof(CGLibPipeline, m_vertexStreams) == 0x50, "");
static_assert(offsetof(CGLibPipeline, m_vertexStreamMax) == 0x90, "");
static_assert(offsetof(CGLibPipeline, _98) == 0x98, "");

} // namespace grlib
