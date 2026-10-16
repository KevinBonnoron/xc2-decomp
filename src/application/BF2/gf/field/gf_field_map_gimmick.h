#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class IFieldSeq {
public:
  virtual const char *getIdStr() const = 0;
  virtual void create(GF_OBJ_HANDLE *handle) = 0;
  virtual void dispose() = 0;
  virtual bool isEnd() const = 0;
  virtual bool cancel() = 0;
};

class AFieldSeq : public IFieldSeq {
public:
  typedef void (AFieldSeq::*Sequence)(f32 deltaTime);

  AFieldSeq(const GfSetupParam &param);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  gmk::AGmkBase *findBindedGmk() const;
  void create(GF_OBJ_HANDLE *handle) override;
  void seqCheckFs(f32 deltaTime);
  void dispose() override;
  void update(f32 deltaTime);
  void setTargetable(bool isTargetable);
  bool isTargetable() const;
  void seqWaitUIEnd(f32 deltaTime);
  bool isEnd() const override { return isEndSeq; }
  bool cancel() override {
    dispose();
    return true;
  }
  virtual ~AFieldSeq() { dispose(); }
  virtual void onFsSucceeded() = 0;
  virtual void onFsFailed() {}

  GF_OBJ_HANDLE *handle;
  Sequence sequence;
  bool isEndSeq;
  bool isFsSucceeded;
};

static_assert(offsetof(AFieldSeq, handle) == 0x08, "");
static_assert(offsetof(AFieldSeq, sequence) == 0x10, "");
static_assert(offsetof(AFieldSeq, isEndSeq) == 0x20, "");
static_assert(offsetof(AFieldSeq, isFsSucceeded) == 0x21, "");
static_assert(sizeof(AFieldSeq) == 0x28, "");

class GfFieldMapGimmick : public AFieldSeq, public mm::mtl::PtrSingleton<GfFieldMapGimmick> {
public:
  GfFieldMapGimmick(const GfSetupParam &param);
  void create(GF_OBJ_HANDLE *handle) override;
  void dispose() override;
  void update(f32 deltaTime);
  void onFsSucceeded() override;
  void onFsFailed() override;
  const char *getIdStr() const override;
  bool isEnd() const override;
  ~GfFieldMapGimmick();

  // __LINE__ must be 208 as in the original header: its value changes the instruction order.
#line 208
  static void build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldMapGimmick(param); }

  static void destroy() {
    get()->dispose();
    delete get();
  }

  u8 _30[0x4e0 - 0x30];
};

static_assert(sizeof(GfFieldMapGimmick) == 0x4e0, "");

class GfFieldGrave : public IFieldSeq, public mm::mtl::PtrSingleton<GfFieldGrave> {
public:
  GfFieldGrave(const GfSetupParam &param);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void create(GF_OBJ_HANDLE *handle) override;
  void dispose() override;
  void update(f32 deltaTime);
  const char *getIdStr() const override;
  bool isEnd() const override;
  bool cancel() override;
  virtual ~GfFieldGrave();

  // __LINE__ must be 312 as in the original header: its value changes the instruction order.
#line 312
  static void build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldGrave(param); }

  static void destroy() {
    get()->dispose();
    delete get();
  }

  u8 _10[0x30 - 0x10];
};

static_assert(sizeof(GfFieldGrave) == 0x30, "");

class GfFieldJump : public AFieldSeq, public mm::mtl::PtrSingleton<GfFieldJump> {
public:
  GfFieldJump(const GfSetupParam &param) : AFieldSeq(param) {}
  const char *getIdStr() const override;
  void onFsSucceeded() override;

  // __LINE__ must be 383 as in the original header: its value changes the instruction order.
#line 383
  static void build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldJump(param); }

  static void destroy() {
    get()->dispose();
    delete get();
  }
};

static_assert(sizeof(GfFieldJump) == 0x30, "");

class GfFieldWarp : public AFieldSeq, public mm::mtl::PtrSingleton<GfFieldWarp> {
public:
  GfFieldWarp(const GfSetupParam &param) : AFieldSeq(param) {}
  const char *getIdStr() const override;
  void onFsSucceeded() override;

  // __LINE__ must be 438 as in the original header: its value changes the instruction order.
#line 438
  static void build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldWarp(param); }

  static void destroy() {
    get()->dispose();
    delete get();
  }
};

static_assert(sizeof(GfFieldWarp) == 0x30, "");

class GfFieldGmkTutorial : public mm::mtl::PtrSingleton<GfFieldGmkTutorial> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
};

} // namespace gf
