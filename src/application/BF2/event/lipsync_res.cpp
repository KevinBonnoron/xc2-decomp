#include "event/lipsync_res.h"

namespace event {

const char *LipsyncRes::getName() const { return name.c_str(); }

bool LipsyncRes::isLoading() const { return (flags & FLAG_LOADING) != 0; }

} // namespace event
