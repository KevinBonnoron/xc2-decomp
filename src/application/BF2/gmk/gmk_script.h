#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

class GmkScript {
public:
  struct CreateInfo {
    CreateInfo() : startId(-1) {}

    mm::mtl::FixStr<32> name;
    int startId;
  };

  GmkScript(const CreateInfo *info);
  void create(const CreateInfo &info);
  static void vmSetStartId(int id);
  static int vmGetStartId();
  static bool isScriptStart();
  static bool isScriptEnd();
  static bool isScriptExecuting();
  static const char *getExecutingScriptName();
  static void vmBeginScript();
  static void vmEndScript();
  void dispose();
  void endScript();
  void beginScript();
  void seqWaitEndScript(f32 deltaTime);
  void update(f32 deltaTime);

  virtual ~GmkScript() { dispose(); }

  CreateInfo createInfo;
  void (GmkScript::*seq)(f32);
};

static_assert(sizeof(GmkScript::CreateInfo) == 0x28, "");
static_assert(offsetof(GmkScript, createInfo) == 0x08, "");
static_assert(offsetof(GmkScript, seq) == 0x30, "");
static_assert(sizeof(GmkScript) == 0x40, "");

} // namespace gmk
