#pragma once
#include <string.h>

#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace ml {

template <int N> class MsgParam {
public:
  enum ParamType {
    PARAM_TYPE_NONE = 0,
    PARAM_TYPE_STRING = 16,
  };

  struct Param {
    Param(int msg) : msg(msg) {
      data[0] = 0;
      type = PARAM_TYPE_NONE;
    }

    int msg;
    char data[16];
    u8 type;
  };

  MsgParam() : m_index(0) {}
  virtual ~MsgParam() {}

  void add(int msg) {
    m_queue.push(Param(msg));
    m_index = m_queue.size();
    m_index--;
  }

  void set(const char *string) {
    m_queue[m_index].type = PARAM_TYPE_STRING;
    strcpy(m_queue[m_index].data, string);
  }

  int size() const { return m_queue.size(); }
  Param &get(u32 index) { return m_queue[index]; }
  void pop() { m_queue.pop_front(); }

  int find(int msg) const {
    for (u32 i = 0; i < m_queue.size(); i++) {
      if (m_queue[i].msg == msg) {
        return i;
      }
    }

    return -1;
  }

  mm::mtl::FixedQueue<Param, N> m_queue;
  u32 m_index;
};

} // namespace ml
