#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/script/gf_script_manager.h"
#include "mm_mtl/fixstr.h"
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
  bool isEnd() const override { return m_end; }
  bool cancel() override {
    dispose();
    return true;
  }
  virtual ~AFieldSeq() {
    m_end = false;
    unknown21 = false;
    unknown10 = nullptr;
    unknown08 = INVALID_HANDLE;
  }
  virtual void onFsSucceeded() = 0;
  virtual void onFsFailed() {}

  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  Sequence unknown10;       // Inferred role: sequence; original member name unknown.
  bool m_end;
  bool unknown21; // Inferred role: fs succeeded; original member name unknown.
};

static_assert(offsetof(AFieldSeq, unknown08) == 0x08, "");
static_assert(offsetof(AFieldSeq, unknown10) == 0x10, "");
static_assert(offsetof(AFieldSeq, m_end) == 0x20, "");
static_assert(offsetof(AFieldSeq, unknown21) == 0x21, "");
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
  typedef void (GfFieldGrave::*Sequence)(f32 deltaTime);

  GfFieldGrave(const GfSetupParam &param);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void create(GF_OBJ_HANDLE *handle) override;
  void seqWaitToSelect(f32 deltaTime);
  void dispose() override;
  void update(f32 deltaTime);

  const char *getIdStr() const override {
    static const char s_classId[] = "GfFieldGrave";
    return s_classId;
  }

  bool isEnd() const override { return m_end; }

  bool cancel() override {
    dispose();
    return true;
  }

  virtual ~GfFieldGrave() {}

  // __LINE__ must be 312 as in the original header: its value changes the instruction order.
#line 312
  static void build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldGrave(param); }

  static void destroy() {
    get()->dispose();
    delete get();
  }

  GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  bool m_end;
  Sequence unknown20; // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(GfFieldGrave, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldGrave, m_end) == 0x18, "");
static_assert(offsetof(GfFieldGrave, unknown20) == 0x20, "");
static_assert(sizeof(GfFieldGrave) == 0x30, "");

class GfFieldJump : public AFieldSeq, public mm::mtl::PtrSingleton<GfFieldJump> {
public:
  GfFieldJump(const GfSetupParam &param) : AFieldSeq(param) {}
  void onFsSucceeded() override;

  const char *getIdStr() const override {
    static const char s_classId[] = "GfFieldJump";
    return s_classId;
  }

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
  void onFsSucceeded() override;

  const char *getIdStr() const override {
    static const char s_classId[] = "GfFieldWarp";
    return s_classId;
  }

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
  GfFieldGmkTutorial() : unknown08(SCRIPT_SLOT_GMK_TUTORIAL), unknown50(0) {}
  ~GfFieldGmkTutorial() { dispose(); }
  static void build(const GfSetupParam &param);
  static void destroy();
  void dispose();
  void create(const char *name, u32 tutorial);
  bool isEnd() const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);

  int unknown08;                 // Inferred role: script slot; original member name unknown.
  mm::mtl::FixStr<64> unknown0c; // Inferred role: script name; original member name unknown.
  u32 unknown50;                 // Inferred role: tutorial; original member name unknown.
};

static_assert(offsetof(GfFieldGmkTutorial, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldGmkTutorial, unknown0c) == 0x0c, "");
static_assert(offsetof(GfFieldGmkTutorial, unknown50) == 0x50, "");
static_assert(sizeof(GfFieldGmkTutorial) == 0x58, "");

} // namespace gf
