#include "layer/layer_obj_draw.h"

#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_vertex_obj.h"

namespace layer {

void LayerObjDraw::renderMesh(grlib::CGLibDblUniformBlock *uniform, const LyrMeshData *mesh) {
  u32 count = mesh->unknown1a;
  if (count != 0) {
    const LyrDrawData *draw = reinterpret_cast<const LyrDrawData *>(unknown298->unknown10) + mesh->unknown18;
    for (u32 i = 0; i < count; i++) {
      (this->*s_pCallDraw[draw[i].unknown0d])(uniform, &draw[i]);
    }
  }
}

void LayerObjDraw::draw_call_onm_def(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(static_cast<LayerDefVertType>(0));
  shader->unknown4f0 = 0;
  shader->setupShader(uniform);
  shader->renderQuadsIndex();
}

void LayerObjDraw::draw_call_onm_tex(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 1;
  shader->setupShader(uniform);
  u8 count = draw->unknown0c;
  if (count != 0) {
    const u16 *textures = reinterpret_cast<const u16 *>(unknown298->unknown08 + static_cast<size_t>(draw->unknown08) * 6 + 2);
    for (u32 i = 0; i != count; i++) {
      shader->setupTexture(*unknown280[*textures], static_cast<LayerSamplerType>(unknownc6), i);
      textures += 3;
    }
  }
  shader->renderQuadsIndex();
}

void LayerObjDraw::draw_call_res_def(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(unknown270, draw->unknown04);
  shader->unknown4f0 = 0;
  shader->setupShader(uniform);
  unknown270->render(draw->unknown06);
}

void LayerObjDraw::draw_call_res_tex(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(unknown270, draw->unknown04);
  shader->unknown4f0 = 1;
  shader->setupShader(uniform);
  shader->setupTexture(*unknown280[*reinterpret_cast<const u16 *>(unknown298->unknown08 + static_cast<size_t>(draw->unknown08) * 6 + 2)], static_cast<LayerSamplerType>(unknownc6), 0);
  unknown270->render(draw->unknown06);
}

void LayerObjDraw::draw_call_icon(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(static_cast<LayerDefVertType>(2));
  shader->unknown4f0 = 4;
  shader->setupShader(uniform);
  u8 count = draw->unknown0c;
  if (count != 0) {
    const u16 *textures = reinterpret_cast<const u16 *>(unknown298->unknown08 + static_cast<size_t>(draw->unknown08) * 6 + 2);
    for (u32 i = 0; i != count; i++) {
      shader->setupTexture(*unknown280[*textures], static_cast<LayerSamplerType>(unknownc6), i);
      textures += 3;
    }
  }
  shader->renderQuadsIndex();
}

void LayerObjDraw::draw_call_number(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(static_cast<LayerDefVertType>(2));
  shader->unknown4f0 = 5;
  shader->setupShader(uniform);
  shader->setupInstaceVertex(*unknown298->unknown78->unknown00, 0x24, 0);
  u8 count = draw->unknown0c;
  if (count != 0) {
    const u16 *textures = reinterpret_cast<const u16 *>(unknown298->unknown08 + static_cast<size_t>(draw->unknown08) * 6 + 2);
    for (u32 i = 0; i != count; i++) {
      shader->setupTexture(*unknown280[*textures], static_cast<LayerSamplerType>(unknownc6), i);
      textures += 3;
    }
  }
  shader->renderInstaceQuadsIndex(unknown298->unknown78->unknown08);
}

void LayerObjDraw::draw_call_hdr(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw) {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 10;
  shader->setupShader(uniform);
  shader->setupTexture(*unknown280[*reinterpret_cast<const u16 *>(unknown298->unknown08 + static_cast<size_t>(draw->unknown08) * 6 + 2)], static_cast<LayerSamplerType>(unknownc6), 0);
  shader->setupTexture(shader->unknown368, static_cast<LayerSamplerType>(unknownc6), 1);
  shader->renderQuadsIndex();
}

} // namespace layer
