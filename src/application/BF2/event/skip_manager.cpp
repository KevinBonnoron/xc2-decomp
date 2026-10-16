#include "event/skip_manager.h"

namespace event {

SkipManager::SkipManager() : flags(0), mSkipState(0), mSkipFrame(-1.0f) {}

SkipManager::~SkipManager() {}

} // namespace event
