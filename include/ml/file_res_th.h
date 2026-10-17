#pragma once
#include "ml/base_object.h"
#include "ml/work_event.h"

namespace ml {

class FileResTh : public BaseObjectM, public IWorkEvent {
public:
  FileResTh();
  ~FileResTh() override;
  bool isExist() const;
};

} // namespace ml
