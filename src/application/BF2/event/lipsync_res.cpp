#include "event/lipsync_res.h"

#include "arc/arc_data.h"

namespace event {

const char *LipsyncRes::getName() const { return name.c_str(); }

bool LipsyncRes::isLoading() const { return (flags & FLAG_LOADING) != 0; }

void LipsyncRes::OnResEvent(const PARAM &param) {
  if (param.result == RES_RESULT_TYPE_SUCCESS) {
    // The call at 0x71000e4d74 uses this + 0x50 as CArcData storage.
    reinterpret_cast<arc::CArcData *>(_50)->setData(param.adr);
    flags |= FLAG_LOADED;
  } else {
    flags &= ~FLAG_LOADED;
  }
  flags &= ~FLAG_LOADING;
}

} // namespace event
