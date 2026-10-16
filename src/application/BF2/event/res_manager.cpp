#include "event/res_manager.h"

namespace event {

ResManager::ResManager() : flags(0), mLoadingCount(0), mLoadedCount(0) {}

const char *ResManager::filename(const char *path) {
  const char *separator = __builtin_strrchr(path, '\\');
  if (separator != nullptr) {
    return separator + 1;
  }
  separator = __builtin_strrchr(path, '/');
  return separator != nullptr ? separator + 1 : path;
}

bool ResManager::isLoading() { return mLoadingCount > 0; }

void ResManager::setDisp(bool isDisp) {
  if (isDisp) {
    flags |= FLAG_DISP;
  } else {
    flags &= ~FLAG_DISP;
  }
}

bool ResManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

} // namespace event
