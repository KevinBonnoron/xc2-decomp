#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

class GmkScript {
public:
  struct CreateInfo {
    CreateInfo() : unknown24(-1) {}

    mm::mtl::FixStr<32> unknown00; // Inferred role: name; original member name unknown.
    int unknown24;                 // Inferred role: start id; original member name unknown.
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

  CreateInfo unknown08;              // Inferred role: create info; original member name unknown.
  void (GmkScript::*unknown30)(f32); // Inferred role: seq; original member name unknown.
};

static_assert(sizeof(GmkScript::CreateInfo) == 0x28, "");
static_assert(offsetof(GmkScript, unknown08) == 0x08, "");
static_assert(offsetof(GmkScript, unknown30) == 0x30, "");
static_assert(sizeof(GmkScript) == 0x40, "");

} // namespace gmk
