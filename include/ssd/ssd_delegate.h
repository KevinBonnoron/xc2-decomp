#pragma once
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_result.h"

namespace ssd {
namespace Delegate {

class Handle : public List<Handle>::Node {
public:
  virtual void ExecuteDelegate(unsigned long long argument1, unsigned long long argument2) = 0;
  virtual bool operator==(const Handle *handle) const = 0;
};

class MultiCast {
public:
  void Clear();
  Result AddDelegate(Handle *handle);
  Result RemoveDelegate(Handle *handle);
  Handle *FindDelegate(const Handle *handle);
  Result RemoveDelegateImpl(Handle *handle);
  Handle *FindDelegateImpl(const Handle *handle);

  List<Handle> unknown00; // Inferred role: registered delegates; original member name unknown.
};

template <typename T, typename Argument1, typename Argument2> class Object : public Handle {
public:
  void ExecuteDelegate(unsigned long long argument1, unsigned long long argument2) override { (object->*function)(this, reinterpret_cast<Argument1>(argument1), static_cast<Argument2>(argument2)); }

  bool operator==(const Handle *handle) const override {
    const Object *other = static_cast<const Object *>(handle);
    return other->object == object && other->function == function;
  }

  T *object;
  void (T::*function)(Handle *, Argument1, Argument2);
};

static_assert(sizeof(MultiCast) == 0x28, "");

} // namespace Delegate
} // namespace ssd
