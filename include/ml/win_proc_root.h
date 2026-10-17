#pragma once

namespace ml {

class WorkObj;

class WinProcRoot {
public:
  static WinProcRoot *create(WorkObj *parent);
};

} // namespace ml
