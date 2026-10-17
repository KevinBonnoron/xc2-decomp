#pragma once
#include "ml/work_event.h"
#include "types.h"

namespace cloud {

class CloudDataMan : public ml::IWorkEvent {
public:
  CloudDataMan();
  ~CloudDataMan() override;
  bool isReadOk() const;
  bool OnFileEvent(ml::EventFileTh *event) override;

  u8 _08[0x70 - 0x08];
};

static_assert(sizeof(CloudDataMan) == 0x70, "");

} // namespace cloud
