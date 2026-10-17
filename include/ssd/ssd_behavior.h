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

  f32 value;
  f32 elapsed;
  f32 start;
  f32 end;
  f32 beginTime;
  f32 endTime;
};

static_assert(offsetof(BehaviorControl, value) == 0x18, "");

template <typename T> class BehaviorInstance : public BehaviorControl {
public:
  void ExecBehaviorInstance(f32 value) override { (object->*function)(value); }

  void Set(T *object, void (T::*function)(f32), f32 target, f32 time) {
    this->object = object;
    this->function = function;
    elapsed = 0.0f;
    start = value;
    end = target;
    beginTime = 0.0f;
    endTime = time;
  }

  T *object;
  void (T::*function)(f32);
};

} // namespace ssd
