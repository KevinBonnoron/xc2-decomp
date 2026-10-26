#include "dr/dr_environment_tex.h"

#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrEnvironmentTex::DrEnvironmentTex() : unknown00(nullptr), unknown08(0) {}

int DrEnvironmentTex::getTextureWork(int count) { return count * sizeof(grlib::CGLibTextureBuffer); }

grlib::CGLibTextureBuffer *DrEnvironmentTex::getTexture(int index) { return &unknown00[index]; }

void DrEnvironmentTex::releaseTexture() {
  if (unknown08 != 0) {
    for (int i = 0; i < unknown08; i++) {
      unknown00[i].release();
    }
    unknown08 = 0;
    unknown00 = nullptr;
  }
}

} // namespace ml
