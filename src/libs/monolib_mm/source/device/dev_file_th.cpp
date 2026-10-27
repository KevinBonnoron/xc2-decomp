#include "ml/dev_file_th.h"

namespace ml {

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
