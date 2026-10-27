#include "framework/reflection.h"

namespace fw {

void ReflectionValue::writeDefault(u8 *data) const {}

template <typename T, ValueType TYPE> void ReflectionValuePod<T, TYPE>::writeDefault(u8 *data) const {
  T *destination = reinterpret_cast<T *>(data + unknown70);
  *destination = unknown80;
}

template class ReflectionValuePod<f32, static_cast<ValueType>(6)>;
template class ReflectionValuePod<int, static_cast<ValueType>(5)>;
template class ReflectionValuePod<u32, static_cast<ValueType>(2)>;

void ReflectionValueStruct::writeDefault(u8 *data) const {
  for (mm::mtl::IntrusiveList<ReflectionValue>::iterator it = unknown78.begin(); it != unknown78.end(); ++it) {
    it.get()->writeDefault(data);
  }
}

void ReflectionValueFlag::writeDefaultFlag(u32 &flags) const {
  if (unknown7c) {
    flags |= unknown78;
  } else {
    flags &= ~unknown78;
  }
}

void Reflection::setReflectionStruct(u32 index, ReflectionValueStruct *value) {
  if (unknown10[index] != nullptr) {
    unknown10[index]->release();
    unknown10[index] = nullptr;
  }

  unknown10[index] = value;
  value->addRef();
}

} // namespace fw
