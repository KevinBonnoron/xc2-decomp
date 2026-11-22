#include "layer/layer_font_information.h"

#include "layer/layer_manager.h"
#include "layer/layer_mem_handle_allocator.h"

namespace layer {

LayerFontInformation::LayerFontInformation(u32 num) {
  unknown00.setAllocator(&LayerManager::get()->m_layerMemHandleAllocator);
  unknown00.reserve(num);
}

LayerFontInformation::~LayerFontInformation() { unknown00.destroy(); }

} // namespace layer
