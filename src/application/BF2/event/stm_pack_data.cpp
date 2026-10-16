#include "event/stm_pack_data.h"

#include "ml/dev_file_th.h"

namespace event {

StmPackData::StmPackData() : flags(0), handle(nullptr) {}

StmPackData::~StmPackData() { destroy(); }

void StmPackData::destroy() {
  close();
  path = "";
  flags = 0;
}

void StmPackData::create(const char *path) {
  destroy();
  this->path = path;
}

void StmPackData::close() {
  if (handle != nullptr) {
    ml::DevFileTh::rfIsBusy(handle);
    ml::DevFileTh::rfClose(handle);
    handle = nullptr;
  }
}

bool StmPackData::open() {
  handle = nullptr;
  ml::DevFileParamTh param;
  param.event = this;
  param.path = path.c_str();
  handle = ml::DevFileTh::rfOpen(param);
  return handle != nullptr;
}

void StmPackData::read(void *buffer, size_t size, size_t offset) {
  flags |= FLAG_BUSY;
  ml::DevFileParamTh param;
  param.buffer = buffer;
  param.offset = offset;
  param.readSize = size;
  param.size = size;
  param.priority = 1;
  ml::DevFileTh::rfRead(handle, param);
}

bool StmPackData::isBusy() const { return (flags & FLAG_BUSY) || ml::DevFileTh::rfIsBusy(handle); }

bool StmPackData::isSuccess() const { return handle != nullptr && !isBusy(); }

bool StmPackData::isFailure() const { return handle == nullptr; }

bool StmPackData::OnFileEvent(ml::EventFileTh *event) {
  if (event->type == ml::EventFileTh::TYPE_COMPLETE) {
    flags &= ~FLAG_BUSY;
    return true;
  }
  return false;
}

} // namespace event
