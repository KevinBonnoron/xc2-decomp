#pragma once
#include "types.h"

namespace mm {
namespace mtl {

template <typename Signature> class Delegate;

template <typename R, typename... Args> class Delegate<R(Args...)> {
public:
  typedef R (*Invoker)(const Delegate *delegate, Args... args);

  // No destructor: the game's fw::AnimVolumeFadeModifier D1 and D2 (a Delegate member) are a bare ret, which only happens when
  // the member destructor is implicit; classes whose destructor stores the vtable pointer declare it with the body `{ ; }`.
  Delegate() : m_invoker(nullptr) {}

  bool isValid() const { return m_invoker != nullptr; }
  void clear() { m_invoker = nullptr; }

  R operator()(Args... args) const { return m_invoker(this, args...); }

  template <typename T> static R memberFuncInvoker(const Delegate *delegate, Args... args) {
    typedef R (T::*Function)(Args...);
    T *object = static_cast<T *>(delegate->m_object);
    Function function = *reinterpret_cast<const Function *>(delegate->m_function);
    return (object->*function)(args...);
  }

  static R staticFuncInvoker(const Delegate *delegate, Args... args) {
    R (*function)(Args...) = *reinterpret_cast<R (*const *)(Args...)>(delegate->m_function);
    return function(args...);
  }

  template <typename T> void bind(T *object, R (T::*function)(Args...)) {
    m_object = object;
    *reinterpret_cast<R (T::**)(Args...)>(m_function) = function;
    m_invoker = &memberFuncInvoker<T>;
  }

  void bind(R (*function)(Args...)) {
    *reinterpret_cast<R (**)(Args...)>(m_function) = function;
    m_invoker = &staticFuncInvoker;
  }

  void *m_object;
  Invoker m_invoker;
  u8 m_function[0x10];
};

} // namespace mtl
} // namespace mm
