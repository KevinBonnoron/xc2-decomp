#include "grlib/cglib_pipeline.h"

namespace grlib {

void CGLibPipeline::setDefaults() {
  nvnBlendStateSetDefaults(&m_blendState);
  nvnDepthStencilStateSetDefaults(&m_depthStencilState);
  nvnPolygonStateSetDefaults(&m_cullingOff);
  nvnPolygonStateSetFrontFace(&m_cullingOff, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_cullingFront);
  nvnPolygonStateSetFrontFace(&m_cullingFront, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_cullingBack);
  nvnPolygonStateSetFrontFace(&m_cullingBack, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_cullingDispOff);
  nvnPolygonStateSetFrontFace(&m_cullingDispOff, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_pointMode);
  nvnPolygonStateSetFrontFace(&m_pointMode, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_lineMode);
  nvnPolygonStateSetFrontFace(&m_lineMode, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&m_triangle);
  nvnPolygonStateSetFrontFace(&m_triangle, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetCullFace(&m_cullingOff, NVN_FACE_NONE);
  nvnPolygonStateSetCullFace(&m_cullingFront, NVN_FACE_FRONT);
  nvnPolygonStateSetCullFace(&m_cullingBack, NVN_FACE_BACK);
  nvnPolygonStateSetCullFace(&m_cullingDispOff, NVN_FACE_FRONT_AND_BACK);
  nvnPolygonStateSetPolygonMode(&m_pointMode, NVN_POLYGON_MODE_POINT);
  nvnPolygonStateSetPolygonMode(&m_lineMode, NVN_POLYGON_MODE_LINE);
  nvnPolygonStateSetPolygonMode(&m_triangle, NVN_POLYGON_MODE_FILL);
  nvnChannelMaskStateSetDefaults(&m_channelMaskDefault);
  nvnChannelMaskStateSetDefaults(&m_colorBufferOn);
  nvnChannelMaskStateSetDefaults(&m_colorBufferOff);
  for (int i = 0; i < COLOR_TARGET_NUM; i++) {
    nvnChannelMaskStateSetChannelMask(&m_colorBufferOn, i, true, true, true, true);
    nvnChannelMaskStateSetChannelMask(&m_colorBufferOff, i, false, false, false, false);
  }
  nvnColorStateSetDefaults(&m_colorStateDefault);
  nvnColorStateSetDefaults(&m_blendOn);
  nvnColorStateSetDefaults(&m_blendOff);
  for (int i = 0; i < COLOR_TARGET_NUM; i++) {
    nvnColorStateSetBlendEnable(&m_blendOn, i, true);
    nvnColorStateSetBlendEnable(&m_blendOff, i, false);
  }
  for (int i = 0; i < VERTEX_STREAM_NUM; i++) {
    nvnVertexStreamStateSetDefaults(&m_vertexStreams[i]);
  }
  m_vertexStreamMax = 0;
  m_isVertexStreamDirty = false;
  _98 = 0;
}

void CGLibPipeline::relase() {}

void CGLibPipeline::begin() {
  m_isVertexStreamDirty = false;
  _98 = 0;
  m_vertexStreamMax = 0;
}

void CGLibPipeline::updateVertex() {
  if (m_isVertexStreamDirty) {
    nvnCommandBufferBindVertexStreamState(m_cmdBuf, m_vertexStreamMax + 1, m_vertexStreams);
    m_isVertexStreamDirty = false;
  }
}

CGLibPipeline::CGLibPipeline() {}

CGLibPipeline::~CGLibPipeline() {}

} // namespace grlib
