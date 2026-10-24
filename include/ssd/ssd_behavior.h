#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

template <typename T> class List {
public:
  class Node {
  public:
    virtual ~Node() {}

    Node *prev;
    Node *next;
  };

  virtual ~List();

  void PushBack(Node *node) {
    node->prev = head.prev;
    node->next = &head;
    head.prev = node;
    node->prev->next = node;
    count++;
  }

  Node head;
  s32 count;
};

class BehaviorControl : public List<BehaviorControl>::Node {
public:
  virtual void ExecBehaviorInstance(f32 value) = 0;

  f32 unknown18; // Inferred role: value; original member name unknown.
  f32 unknown1c; // Inferred role: elapsed; original member name unknown.
  f32 unknown20; // Inferred role: start; original member name unknown.
  f32 unknown24; // Inferred role: end; original member name unknown.
  f32 unknown28; // Inferred role: begin time; original member name unknown.
  f32 unknown2c; // Inferred role: end time; original member name unknown.
};

static_assert(offsetof(BehaviorControl, unknown18) == 0x18, "");

template <typename T> class BehaviorInstance : public BehaviorControl {
public:
  void ExecBehaviorInstance(f32 value) override { (object->*function)(value); }

  void Set(T *object, void (T::*function)(f32), f32 target, f32 time) {
    this->object = object;
    this->function = function;
    unknown1c = 0.0f;
    unknown20 = unknown18;
    unknown24 = target;
    unknown28 = 0.0f;
    unknown2c = time;
  }

  T *object;
  void (T::*function)(f32);
};

} // namespace ssd
