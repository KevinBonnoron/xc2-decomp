#include "gf/game/auto_talk/gf_auto_talk.h"

namespace gf {

void GfAutoTalkManager::destroy() { delete get(); }

bool GfAutoTalkManager::isInitialized() { return get() != nullptr; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfAutoTalkManager>::~PtrSingleton();
