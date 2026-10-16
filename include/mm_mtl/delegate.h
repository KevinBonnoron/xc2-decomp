#pragma once
#include "types.h"

namespace mm {
namespace mtl {

template <typename Signature> class Delegate;

template <typename R, typename... Args> class Delegate<R(Args...)> {
public:
  typedef R (*Invoker)(const Delegate *delegate, Args... args);

  Delegate() : m_invoker(nullptr) {}

  bool isValid() const { return m_invoker != nullptr; }

  R operator()(Args... args) const { return m_invoker(this, args...); }

  void *m_object;
  Invoker m_invoker;
  u8 m_function[0x10];
};

} // namespace mtl
} // namespace mm
