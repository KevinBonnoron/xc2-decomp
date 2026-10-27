#include "ml/dev_file_th.h"

#include "device/nx/dev_file_nx_th.h"
#include "mm_mtl/fixstr.h"
#include "nn/fs.h"

namespace ml {

void DevFileTh::flushSave() {
  if (DevFileNxTh::m_mountSave) {
    nn::fs::CommitSaveData("save");
  }
}

FileHandleTh *DevFileTh::checkValidFile(const char *path, IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->checkValidFile(path, event);
}

bool DevFileTh::writeFileBlock(const char *path, const void *data, u32 size, int priority) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->writeFileBlock(path, data, size, priority);
}

FileHandleTh *DevFileTh::readFile(const DevFileParamTh &param) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->readFile(param);
}

FileHandleTh *DevFileTh::rfOpen(const DevFileParamTh &param) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->rfOpen(param);
}

bool DevFileTh::rfClose(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->rfClose(handle);
  }
  return false;
}

bool DevFileTh::rfIsBusy() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->rfIsBusy();
}

void DevFileTh::cancel(FileHandleTh *handle, bool isForce) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->cancelRequest(handle);
  }
}

bool DevFileTh::isValidHandle(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isValidHandle(handle);
  }
  return false;
}

void DevFileTh::Impl::registAccessor(MEDIA media, DevFileAccessor *accessor) { unknown588b0[media] = accessor; }

void DevFileTh::Impl::removeAccessor(MEDIA media) { unknown588b0[media] = nullptr; }

void DevFileTh::Impl::registArchiveAccessor(MEDIA media, DevFileAccessor *accessor) { unknown588f0[media] = accessor; }

void DevFileTh::Impl::removeArchiveAccessor(MEDIA media) { unknown588f0[media] = nullptr; }

void DevFileTh::Impl::suspendThread() {}

bool DevFileTh::Impl::isSuspendThread() { return false; }

void DevFileTh::Impl::resumeThread() {}

void DevFileTh::Impl::setSuspend(bool suspend) {}

bool DevFileTh::Impl::isSuspend() const { return false; }

bool DevFileTh::Impl::isInitialized() { return m_initialized; }

bool DevFileTh::isSuspend() {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isSuspend();
  }
  return false;
}

bool DevFileTh::setSuspend(bool suspend) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->setSuspend(suspend);
  return true;
}

void DevFileTh::registAccessor(MEDIA media, DevFileAccessor *accessor) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->registAccessor(media, accessor);
  }
}

void DevFileTh::removeAccessor(MEDIA media) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->removeAccessor(media);
  }
}

void DevFileTh::registArchiveAccessor(MEDIA media, DevFileAccessor *accessor) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->registArchiveAccessor(media, accessor);
  }
}

void DevFileTh::removeArchiveAccessor(MEDIA media) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->removeArchiveAccessor(media);
  }
}

bool DevFileTh::initialize() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->initialize();
}

bool DevFileTh::finalize() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return true;
  }
  return file->unknown1c0->finalize();
}

void DevFileTh::initializeEnv(const char *path) {
  char buffer[1024] = {};
  initializePath(buffer, false);
}

void DevFileTh::addMediaPath(MEDIA media, const char *path, int priority) {
  if (path != nullptr && path[0] != '\0') {
    dvfl_detail::addMediaPath(media, path, priority);
  }
}

bool DevFileTh::removeFileJob(DevFileJob *job) { return true; }

bool DevFileTh::getReadingInfo(mm::mtl::FixStr<256> &name, f32 &ratio) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->getReadingInfo(name, ratio);
  }
  return false;
}

bool DevFileTh::getWritingInfo(mm::mtl::FixStr<256> &name, f32 &ratio) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->getWritingInfo(name, ratio);
  }
  return false;
}

void DevFileTh::enableLapTimeForDebug(bool enable) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->enableLapTimeForDebug(enable);
  }
}

bool DevFileTh::isLapTimeForDebug() {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isLapTimeForDebug();
  }
  return false;
}

bool DevFileTh::entryCb(IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->unknown5a348 = event;
  return true;
}

bool DevFileTh::removeCb(IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->unknown5a348 = nullptr;
  return true;
}

bool DevFileTh::isNowSaving() {
  DevFileTh *file = get();
  if (file != nullptr) {
    return file->unknown1c9;
  }
  return false;
}

void DevFileTh::setNowSaving(bool isSaving) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c9 = isSaving;
  }
}

bool DevFileTh::checkValidFileBlock(const char *path) { return getFileSize(path, nullptr) >= 0; }

void DevFileTh::sendCommand(const char *command, const char *argument) {}

void DevFileTh::wkUpdate() {}

bool DevFileTh::icbError(CERR_STRUCT *error) { return true; }

void DevFileTh::icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) {}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileTh>::~PtrSingleton();
