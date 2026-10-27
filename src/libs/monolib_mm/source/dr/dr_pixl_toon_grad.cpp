#include "dr/dr_pixl_toon_grad.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlToonGrad::DrPixlToonGrad(DrMan *drMan) {
  unknown08 = true;
  unknown00 = drMan;
  for (int i = 0; i < 2; i++) {
    m_gradTex[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
    m_gradTex[i]->setTextureInfo(512.0f, 256.0f, GRL_SURFACE_FORMAT_RGBA8, false, 0);
    m_darkGradTex[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
    m_darkGradTex[i]->setTextureInfo(512.0f, 256.0f, GRL_SURFACE_FORMAT_RGBA8, false, 0);
  }
}

DrPixlToonGrad::~DrPixlToonGrad() {
  for (int i = 0; i < 2; i++) {
    if (m_gradTex[i] != nullptr) {
      delete m_gradTex[i];
      m_gradTex[i] = nullptr;
    }
    if (m_darkGradTex[i] != nullptr) {
      delete m_darkGradTex[i];
      m_darkGradTex[i] = nullptr;
    }
  }
}

void DrPixlToonGrad::update() {}

void DrPixlToonGrad::debugRender() {
  m_gradTex[DrMan::s_nDblIdx]->debugRender(5, 5, m_gradTex[DrMan::s_nDblIdx]->unknownbc, m_gradTex[DrMan::s_nDblIdx]->unknownc0 * 2, false, false, 1.0f, true);
  m_darkGradTex[DrMan::s_nDblIdx]->debugRender(
      m_darkGradTex[DrMan::s_nDblIdx]->unknownbc + 6, 5, m_darkGradTex[DrMan::s_nDblIdx]->unknownbc, m_darkGradTex[DrMan::s_nDblIdx]->unknownc0 * 2, false, false, 1.0f, true);
}

const grlib::CGLibTextureBuffer &DrPixlToonGrad::getGradTex() const { return *m_gradTex[DrMan::s_nDblIdx]->unknown70; }

const grlib::CGLibTextureBuffer &DrPixlToonGrad::getDarkGradTex() const { return *m_darkGradTex[DrMan::s_nDblIdx]->unknown70; }

} // namespace ml
