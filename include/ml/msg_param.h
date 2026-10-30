#pragma once
#include <string.h>

#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace ml {

template <int N> class MsgParam {
public:
  // Inferred role: param type; original type name unknown.
  enum unknown001 {
    unknown001_0 = 0,   // Inferred role: none; original name unknown.
    unknown001_16 = 16, // Inferred role: string; original name unknown.
  };

  struct Param {
    Param(int msg) : msg(msg) {
      data[0] = 0;
      type = unknown001_0;
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
    m_queue[m_index].type = unknown001_16;
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
