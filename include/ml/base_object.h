#pragma once

namespace ml {

class BaseObjectM {
public:
  virtual ~BaseObjectM();
  virtual int AddRef();
  virtual int Release();
  virtual void SetName(const char *name);
};

} // namespace ml
