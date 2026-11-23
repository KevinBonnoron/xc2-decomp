#include "dr/dr_pixl_render_cube_map.h"

namespace ml {

DrPixlRenderCubeMap::DrPixlRenderCubeMap(DrMan *man) { m_drMan = man; }

DrPixlRenderCubeMap::~DrPixlRenderCubeMap() { releaseWork(); }

} // namespace ml
