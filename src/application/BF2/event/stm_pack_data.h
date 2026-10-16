#pragma once
#include <stddef.h>

#include "ml/work_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class FileHandleTh;
} // namespace ml

namespace event {

class StmPackData : public ml::IWorkEvent {
public:
  enum {
    FLAG_BUSY = 1 << 0,
  };

  StmPackData();
  virtual ~StmPackData();
  void destroy();
  void create(const char *path);
  void close();
  bool open();
  void read(void *buffer, size_t size, size_t offset);
  bool isBusy() const;
  bool isSuccess() const;
  bool isFailure() const;
  virtual bool OnFileEvent(ml::EventFileTh *event);

private:
  u32 flags;
  mm::mtl::FixStr<128> path;
  ml::FileHandleTh *handle;
};

static_assert(sizeof(StmPackData) == 0x98, "");

} // namespace event
