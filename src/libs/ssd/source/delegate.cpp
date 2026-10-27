#include "ssd/ssd_behavior.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_delegate.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_sound_core.h"

namespace ssd {
enum Result : long;

namespace Delegate {

void MultiCast::Clear() {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr && unknown00.count == 0) {
    return;
  }
  core->unknown708.Lock();
  Handle *it = unknown00.unknown002();
  while (it != unknown00.unknown003()) {
    Handle *next = List<Handle>::unknown004(it);
    unknown00.unknown001(it);
    it = next;
  }
  core->unknown708.Unlock();
}

Result MultiCast::AddDelegate(Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  core->unknown708.Lock();
  Result result;
  if (FindDelegateImpl(handle) == nullptr) {
    unknown00.PushBack(handle);
    result = static_cast<Result>(0);
  } else {
    result = static_cast<Result>(-1);
  }
  core->unknown708.Unlock();
  return result;
}

Handle *MultiCast::FindDelegateImpl(const Handle *handle) {
  Handle *it = unknown00.unknown002();
  while (it != unknown00.unknown003()) {
    if (*handle == it) {
      return it;
    }
    it = List<Handle>::unknown004(it);
  }
  return nullptr;
}

Result MultiCast::RemoveDelegateImpl(Handle *handle) {
  if (FindDelegateImpl(handle) != nullptr) {
    unknown00.unknown001(handle);
    return static_cast<Result>(0);
  }
  return static_cast<Result>(-1);
}

Result MultiCast::RemoveDelegate(Handle *handle) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  core->unknown708.Lock();
  Result result = RemoveDelegateImpl(handle);
  core->unknown708.Unlock();
  return result;
}

Handle *MultiCast::FindDelegate(const Handle *handle) {
  static_cast<SystemCore *>(SoundCore::instance_)->unknown708.Lock();
  Handle *found = FindDelegateImpl(handle);
  static_cast<SystemCore *>(SoundCore::instance_)->unknown708.Unlock();
  return found;
}

} // namespace Delegate

} // namespace ssd
