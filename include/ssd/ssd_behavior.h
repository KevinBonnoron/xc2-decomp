#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

template <typename T> class List {
public:
  class Node {
  public:
    Node() : prev(this), next(this) {}
    virtual ~Node() {}

    Node *prev;
    Node *next;
  };

  List() : count(0) {}
  virtual ~List();
  List *Delete();

  void PushBack(Node *node) {
    node->prev = head.prev;
    node->next = &head;
    head.prev = node;
    node->prev->next = node;
    count++;
  }

  void unknown001(Node *node) { // Inferred role: unlink a node; original name unknown.
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = node;
    node->next = node;
    count--;
  }

  T *unknown002() const { return static_cast<T *>(head.next); } // Inferred role: first element; original name unknown.

  const T *unknown003() const { return static_cast<const T *>(&head); } // Inferred role: end sentinel; original name unknown.

  static T *unknown004(T *element) { return static_cast<T *>(element->next); } // Inferred role: next element; original name unknown.

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
