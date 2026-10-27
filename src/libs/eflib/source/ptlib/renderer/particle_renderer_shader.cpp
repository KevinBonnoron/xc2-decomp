#include "ptlib/renderer/particle_renderer_shader.h"

#include "grlib/cglib_dec_shader.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace renderer {

ShaderManager::ShaderManager() : unknown00(nullptr) {}

ShaderManager::~ShaderManager() { unknown08.release(); }

void ShaderManager::init() {
  int size = 0;
  unknown00 = ParticleManager::readFileBlock("/effect/shader/shd_effect.wishp", size);
  unknown08.createPacShader(unknown00, 0x3f3, true);
  for (int i = 0; i < 16; i++) {
    grlib::CGLibDecShader &shader = unknown08.unknown40[i];
    unknown60[i].unknown00 = shader.getDeclarationOfs("VERIATION_MODE");
    unknown60[i].unknown04 = shader.getDeclarationOfs("SOFT_MODE");
    unknown60[i].unknown08 = shader.getDeclarationOfs("SHADOW_MODE");
    unknown60[i].unknown0c = shader.getDeclarationOfs("CLIP_MODE");
    unknown60[i].unknown10 = shader.getDeclarationOfs("USING_TEMPORAL_AA");
  }
}

void ShaderManager::term() {
  unknown08.release();
  if (unknown00 != nullptr) {
    ParticleManager::resFree(unknown00);
    unknown00 = nullptr;
  }
}

void ShaderManager::reload() {
  term();
  init();
}

grlib::CGLibDecShader *ShaderManager::getShaderByIndex(EffShdType type) { return &unknown08.unknown40[type]; }

} // namespace renderer
} // namespace ptlib
