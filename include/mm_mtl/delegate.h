#pragma once
#include "types.h"

namespace mm {
namespace mtl {

template <typename Signature> class Delegate;

template <typename R, typename... Args> class Delegate<R(Args...)> {
public:
  typedef R (*Invoker)(const Delegate *delegate, Args... args);

  Delegate() : m_invoker(nullptr) {}
  ~Delegate() {}

  bool isValid() const { return m_invoker != nullptr; }
  void clear() { m_invoker = nullptr; }

  R operator()(Args... args) const { return m_invoker(this, args...); }

  template <typename T> static R memberFuncInvoker(const Delegate *delegate, Args... args) {
    typedef R (T::*Function)(Args...);
    T *object = static_cast<T *>(delegate->m_object);
    Function function = *reinterpret_cast<const Function *>(delegate->m_function);
    return (object->*function)(args...);
  }

  template <typename T> void bind(T *object, R (T::*function)(Args...)) {
    *reinterpret_cast<R (T::**)(Args...)>(m_function) = function;
    m_object = object;
    m_invoker = &memberFuncInvoker<T>;
  }

  void *m_object;
  Invoker m_invoker;
  u8 m_function[0x10];
};

} // namespace mtl
} // namespace mm
