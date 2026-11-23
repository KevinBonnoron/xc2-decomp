#include "dr/dr_pixl_post_obj_rain_drop.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

// unknown28 and unknown2c are set in the init list. The game stores 0.0f and 0.1f with one merged 64-bit store (`str x8, [x19, #0x28]` at 0x71008378e4) and 0.2f with a second store at 0x30; render
// loads all three as floats (`ldr s6, [x21, #0x28]` at 0x7100838770, 0x2c at 0x71008387d8, 0x30 at 0x71008387fc).
DrPixlPostObjRainDrop::DrPixlPostObjRainDrop(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), unknown18(0), unknown28(0.0f), unknown2c(0.1f), unknown30(0.2f) {
  m_drPixlRenderTarget = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
}

DrPixlPostObjRainDrop::~DrPixlPostObjRainDrop() {
  DrPixlRenderTarget *renderTarget = m_drPixlRenderTarget;
  if (renderTarget != nullptr) {
    delete renderTarget;
    m_drPixlRenderTarget = nullptr;
  }
}

void DrPixlPostObjRainDrop::resetColorBuff() {}

void DrPixlPostObjRainDrop::releaseColorBuff() {}

void DrPixlPostObjRainDrop::requestRebuildDepth() { unknown18 |= 2; }

void DrPixlPostObjRainDrop::requestUseLoadedDepth() { unknown18 &= ~4; }

void DrPixlPostObjRainDrop::requestSaveDepth(const char *) {}

void DrPixlPostObjRainDrop::update() { m_drMan->unknown120[m_drMan->unknown1c98]->getRainDropOn(); }

} // namespace ml
