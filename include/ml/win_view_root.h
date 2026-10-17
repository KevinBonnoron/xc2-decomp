#pragma once

namespace ml {

class WorkObj;

class WinViewRoot {
public:
  static WinViewRoot *create(WorkObj *parent);
};

} // namespace ml
