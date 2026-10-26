#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {

enum ValueType : int {};

class ReflectionValue : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<ReflectionValue> {
public:
  ~ReflectionValue() override {}
  virtual void writeDefault(u8 *data) const;

  u8 _20[0x70 - 0x20];
  s64 unknown70; // Inferred role: member offset in the reflected data; original member name unknown.
};

static_assert(offsetof(ReflectionValue, unknown70) == 0x70, "");

template <typename T, ValueType TYPE> class ReflectionValuePod : public ReflectionValue {
public:
  void writeDefault(u8 *data) const override;

  u8 _78[0x80 - 0x78];
  T unknown80; // Inferred role: default value; original member name unknown.
};

typedef ReflectionValuePod<f32, static_cast<ValueType>(6)> ReflectionValuePodF32;

static_assert(offsetof(ReflectionValuePodF32, unknown80) == 0x80, "");

class ReflectionValueFlag : public ReflectionValue {
public:
  virtual void writeDefaultFlag(u32 &flags) const;

  u32 unknown78;  // Inferred role: flag mask; original member name unknown.
  bool unknown7c; // Inferred role: default value; original member name unknown.
};

static_assert(offsetof(ReflectionValueFlag, unknown78) == 0x78, "");
static_assert(offsetof(ReflectionValueFlag, unknown7c) == 0x7c, "");

class ReflectionValueEnumElem : public ReflectionValue {};

class ReflectionValueStruct : public ReflectionValue {
public:
  mm::mtl::IntrusiveList<ReflectionValue> unknown78; // Inferred role: members; original member name unknown.
};

static_assert(offsetof(ReflectionValueStruct, unknown78) == 0x78, "");

class ReflectionValueBitset32 : public ReflectionValue {
public:
  mm::mtl::IntrusiveList<ReflectionValueFlag> unknown78; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(ReflectionValueBitset32, unknown78) == 0x78, "");

class ReflectionValueEnum : public ReflectionValue {
public:
  mm::mtl::IntrusiveList<ReflectionValueEnumElem> unknown78; // Inferred role: elements; original member name unknown.
  int unknown90;                                             // Inferred role: default value; original member name unknown.
};

static_assert(offsetof(ReflectionValueEnum, unknown90) == 0x90, "");

class Reflection : public mm::mtl::ReferenceObject {
public:
  void setReflectionStruct(u32 index, ReflectionValueStruct *value);

  mm::mtl::Vector<ReflectionValueStruct *> unknown10; // Inferred role: reflected structs; original member name unknown.
};

static_assert(offsetof(Reflection, unknown10) == 0x10, "");

} // namespace fw
