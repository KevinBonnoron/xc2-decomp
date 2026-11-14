#include "gf/object/component/animation/gf_debug_asm_util.h"

#include "anm/anm_animation.h"
#include "anm/anm_asm_blender.h"
#include "anm/anm_asm_state.h"
#include "anm/anm_binding.h"
#include "anm/anm_res_clip_data.h"
#include "anm/anm_state_machine.h"
#include "anm/anm_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "mm_mtl/intrusive_ptr.h"

namespace anm {
class ResASM;
} // namespace anm

namespace gf {
namespace DebugAsmUtil {

u32 getFrameCount(const GfComAsm *comAsm, const char *state) {
  const anm::ResASM *resAsm = comAsm->getResource();
  if (resAsm != nullptr) {
    const anm::Binding *binding = anm::Util::getAsmBinding(*resAsm, state, 0);
    if (binding != nullptr) {
      return binding->m_pAnimation->unknown2c;
    }
  }

  return 0;
}

f32 getCurrentClipFrame(const GfComAsm *comAsm, u32 layer) {
  f32 frame = 0.0f;
  if (comAsm->unknown10 != nullptr) {
    anm::StateMachine *stateMachine = getStateMachine(comAsm->unknown10, static_cast<AnimLayer>(layer));
    if (stateMachine->unknown00.get() != nullptr) {
      const anm::AsmClip *clip = stateMachine->unknown00->getBaseClip();
      const anm::Binding *binding = clip->unknown18->m_pBinding;
      if (binding != nullptr) {
        frame = clip->getLocalTime() * binding->m_pAnimation->unknown24;
      }
    }
  }

  return frame;
}

} // namespace DebugAsmUtil
} // namespace gf
