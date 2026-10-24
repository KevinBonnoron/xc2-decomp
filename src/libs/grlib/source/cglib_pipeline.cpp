#include "grlib/cglib_pipeline.h"

namespace grlib {

void CGLibPipeline::setDefaults() {
  nvnBlendStateSetDefaults(&unknown08);
  nvnDepthStencilStateSetDefaults(&unknown28);
  nvnPolygonStateSetDefaults(&unknown30);
  nvnPolygonStateSetFrontFace(&unknown30, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown34);
  nvnPolygonStateSetFrontFace(&unknown34, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown38);
  nvnPolygonStateSetFrontFace(&unknown38, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown3c);
  nvnPolygonStateSetFrontFace(&unknown3c, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown40);
  nvnPolygonStateSetFrontFace(&unknown40, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown44);
  nvnPolygonStateSetFrontFace(&unknown44, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetDefaults(&unknown48);
  nvnPolygonStateSetFrontFace(&unknown48, NVN_FRONT_FACE_CW);
  nvnPolygonStateSetCullFace(&unknown30, NVN_FACE_NONE);
  nvnPolygonStateSetCullFace(&unknown34, NVN_FACE_FRONT);
  nvnPolygonStateSetCullFace(&unknown38, NVN_FACE_BACK);
  nvnPolygonStateSetCullFace(&unknown3c, NVN_FACE_FRONT_AND_BACK);
  nvnPolygonStateSetPolygonMode(&unknown40, NVN_POLYGON_MODE_POINT);
  nvnPolygonStateSetPolygonMode(&unknown44, NVN_POLYGON_MODE_LINE);
  nvnPolygonStateSetPolygonMode(&unknown48, NVN_POLYGON_MODE_FILL);
  nvnChannelMaskStateSetDefaults(&unknown10);
  nvnChannelMaskStateSetDefaults(&unknown14);
  nvnChannelMaskStateSetDefaults(&unknown18);
  for (int i = 0; i < COLOR_TARGET_NUM; i++) {
    nvnChannelMaskStateSetChannelMask(&unknown14, i, true, true, true, true);
    nvnChannelMaskStateSetChannelMask(&unknown18, i, false, false, false, false);
  }
  nvnColorStateSetDefaults(&unknown1c);
  nvnColorStateSetDefaults(&unknown24);
  nvnColorStateSetDefaults(&unknown20);
  for (int i = 0; i < COLOR_TARGET_NUM; i++) {
    nvnColorStateSetBlendEnable(&unknown24, i, true);
    nvnColorStateSetBlendEnable(&unknown20, i, false);
  }
  for (int i = 0; i < VERTEX_STREAM_NUM; i++) {
    nvnVertexStreamStateSetDefaults(&unknown50[i]);
  }
  unknown90 = 0;
  unknown94 = false;
  _98 = 0;
}

void CGLibPipeline::relase() {}

void CGLibPipeline::begin() {
  unknown94 = false;
  _98 = 0;
  unknown90 = 0;
}

void CGLibPipeline::updateVertex() {
  if (unknown94) {
    nvnCommandBufferBindVertexStreamState(unknown00, unknown90 + 1, unknown50);
    unknown94 = false;
  }
}

CGLibPipeline::CGLibPipeline() {}

CGLibPipeline::~CGLibPipeline() {}

} // namespace grlib
