#pragma once

#define MM_ASSERT(cond)                                                                                                                                                                                \
  do {                                                                                                                                                                                                 \
    if (!(cond)) {                                                                                                                                                                                     \
      mm::MMStdBase::mmAssert(#cond, __FILE__, __LINE__);                                                                                                                                              \
    }                                                                                                                                                                                                  \
  } while (0)

namespace mm {

class MMStdBase {
public:
  MMStdBase();
  virtual ~MMStdBase() {}

  static void mmPrint(const char *format, ...);
  static void mmAssert(const char *cond, const char *file, unsigned int line);
  static void mmAssertMsg(const char *cond, const char *file, unsigned int line, const char *format, ...);

  virtual void customOutput(const char *text) = 0;
  virtual void customAssert(const char *cond, const char *file, unsigned int line) = 0;
  virtual void customAssertMsg(const char *cond, const char *file, unsigned int line, const char *message) = 0;

  static MMStdBase *s_pCurrentStd;
};

class MMStd : public MMStdBase {
public:
  void customOutput(const char *text) override;
  void customAssert(const char *cond, const char *file, unsigned int line) override;
  void customAssertMsg(const char *cond, const char *file, unsigned int line, const char *message) override;
};

} // namespace mm
