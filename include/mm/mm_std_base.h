#pragma once

#define MM_ASSERT(cond)                                                                                                                              \
  do {                                                                                                                                               \
    if (!(cond)) {                                                                                                                                   \
      mm::MMStdBase::mmAssert(#cond, __FILE__, __LINE__);                                                                                            \
    }                                                                                                                                                \
  } while (0)

namespace mm {

class MMStdBase {
public:
  static void mmAssert(const char *cond, const char *file, unsigned int line);
};

} // namespace mm
