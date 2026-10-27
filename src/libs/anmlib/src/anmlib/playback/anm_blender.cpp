#include "anm/anm_blender.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"

namespace anm {

bool Blender::addControl(Control *pControl) {
  MM_ASSERT(pControl);
  if (pControl->m_pBinding->m_indexTable.size() == unknown40->unknown30.size()) {
    pControl->addRef();
    unknown18.push_back(pControl);
    return true;
  }
  return false;
}

bool Blender::removeControl(Control *pControl) {
  Control **it = mm::mtl::find(unknown18.begin(), unknown18.end(), pControl);
  if (it == unknown18.end()) {
    return false;
  }
  unknown18.erase(it);
  pControl->release();
  return true;
}

void Blender::update(f32 deltaTime) {
  Control **it = unknown18.begin();
  Control **last = unknown18.end();
  for (; it != last; ++it) {
    (*it)->update(deltaTime);
  }
}

} // namespace anm
