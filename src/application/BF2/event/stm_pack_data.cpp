#include "event/stm_pack_data.h"

#include "ml/dev_file_th.h"

namespace event {

StmPackData::StmPackData() : unknown08(0), unknown90(nullptr) {}

StmPackData::~StmPackData() { destroy(); }

void StmPackData::destroy() {
  close();
  unknown0c = "";
  unknown08 = 0;
}

void StmPackData::create(const char *path) {
  destroy();
  this->unknown0c = path;
}

void StmPackData::close() {
  if (unknown90 != nullptr) {
    ml::DevFileTh::rfIsBusy(unknown90);
    ml::DevFileTh::rfClose(unknown90);
    unknown90 = nullptr;
  }
}

bool StmPackData::open() {
  unknown90 = nullptr;
  ml::DevFileParamTh param;
  param.event = this;
  param.path = unknown0c.c_str();
  unknown90 = ml::DevFileTh::rfOpen(param);
  return unknown90 != nullptr;
}

void StmPackData::read(void *buffer, size_t size, size_t offset) {
  unknown08 |= FLAG_BUSY;
  ml::DevFileParamTh param;
  param.buffer = buffer;
  param.offset = offset;
  param.readSize = size;
  param.size = size;
  param.priority = 1;
  ml::DevFileTh::rfRead(unknown90, param);
}

bool StmPackData::isBusy() const { return (unknown08 & FLAG_BUSY) || ml::DevFileTh::rfIsBusy(unknown90); }

bool StmPackData::isSuccess() const { return unknown90 != nullptr && !isBusy(); }

bool StmPackData::isFailure() const { return unknown90 == nullptr; }

bool StmPackData::OnFileEvent(ml::EventFileTh *event) {
  if (event->type == ml::EventFileTh::TYPE_COMPLETE) {
    unknown08 &= ~FLAG_BUSY;
    return true;
  }
  return false;
}

} // namespace event
