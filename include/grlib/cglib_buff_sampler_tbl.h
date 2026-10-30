#pragma once
#include <stddef.h>

#include "grlib/cglib_link_list.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_sampler_param.h"
#include "types.h"

namespace grlib {

// Layout evidence: constructor 0x71007b083c, create 0x71007b08d0 (params copied to 0x10, sampler param at 0x28, ref
// count at 0x90, table index at 0x92), isCheck 0x71007b08fc and the list updates of CGLibBuffSamplerTbl (previous link
// at 0x0, next link at 0x8, stride 0x98 in setup 0x71007b0af4).
class CGLibBuffResSamObj {
public:
  CGLibBuffResSamObj();
  ~CGLibBuffResSamObj();
  void release();
  void create(const CGLibWkrSamplerParams &params, int index);
  bool isCheck(const CGLibWkrSamplerParams &params);

  CGLibBuffResSamObj *unknown00;   // Inferred role: previous link; original member name unknown.
  CGLibBuffResSamObj *unknown08;   // Inferred role: next link; original member name unknown.
  CGLibWkrSamplerParams unknown10; // Inferred role: sampler params; original member name unknown.
  CGLibSamplerParam unknown28;     // Inferred role: NVN sampler; original member name unknown.
  s16 unknown90;                   // Inferred role: reference count; original member name unknown.
  s16 unknown92;                   // Inferred role: hash table index; original member name unknown.
};

static_assert(offsetof(CGLibBuffResSamObj, unknown10) == 0x10, "");
static_assert(offsetof(CGLibBuffResSamObj, unknown28) == 0x28, "");
static_assert(offsetof(CGLibBuffResSamObj, unknown90) == 0x90, "");
static_assert(offsetof(CGLibBuffResSamObj, unknown92) == 0x92, "");
static_assert(sizeof(CGLibBuffResSamObj) == 0x98, "");

// Layout evidence: constructor 0x71007b098c (0x830 bytes cleared), release 0x71007b09ac (128 hash lists from 0x10, free
// list at 0x810, delayed list at 0x820, buffer at 0x0, 64-bit clear at 0x8), setup 0x71007b0af4 (count at 0x8, num at
// 0xc) and allocSampler 0x71007b0c80.
class CGLibBuffSamplerTbl {
public:
  CGLibBuffSamplerTbl();
  ~CGLibBuffSamplerTbl();
  void release();
  void releaseObj(CGLibLinkList<CGLibBuffResSamObj> &list);
  int setup(void *buffer, u32 num);
  CGLibBuffResSamObj *allocSampler(const CGLibWkrSamplerParams &params);
  void freeSampler(CGLibBuffResSamObj *&sampler);
  void freeDelaySampler(CGLibBuffResSamObj *sampler);

  void *unknown00;                                   // Inferred role: allocated buffer; original member name unknown.
  s32 unknown08;                                     // Inferred role: used sampler num; original member name unknown.
  u32 unknown0c;                                     // Inferred role: sampler num; original member name unknown.
  CGLibLinkList<CGLibBuffResSamObj> unknown10[0x80]; // Inferred role: used samplers by hash; original member name unknown.
  CGLibLinkList<CGLibBuffResSamObj> unknown810;      // Inferred role: free samplers; original member name unknown.
  CGLibLinkList<CGLibBuffResSamObj> unknown820;      // Inferred role: samplers waiting for release; original member name unknown.
};

static_assert(offsetof(CGLibBuffSamplerTbl, unknown08) == 0x08, "");
static_assert(offsetof(CGLibBuffSamplerTbl, unknown10) == 0x10, "");
static_assert(offsetof(CGLibBuffSamplerTbl, unknown810) == 0x810, "");
static_assert(offsetof(CGLibBuffSamplerTbl, unknown820) == 0x820, "");
static_assert(sizeof(CGLibBuffSamplerTbl) == 0x830, "");

} // namespace grlib
