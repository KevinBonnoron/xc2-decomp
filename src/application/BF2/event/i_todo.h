#pragma once

namespace event {

class Param;

class ITodo {
public:
  virtual ~ITodo() {}
  virtual const char *cmdName() const = 0;
  virtual void doit(const Param &param) = 0;
  virtual void undo(const Param &param) {}
  virtual void redo(const Param &param) {}
};

} // namespace event
