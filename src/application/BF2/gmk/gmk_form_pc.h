#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkFormPcGob;
class GmkFormPcnpcGob;

template <GmkType TYPE> class TGmkFormPcnpc : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = TYPE;

  ~TGmkFormPcnpc() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugUpdateMmf() override;

  u8 _48[0x50 - 0x48];
};

template <GmkType TYPE, typename FORM_PCNPC> class TGmkFormPc : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = TYPE;

  ~TGmkFormPc() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void debugUpdateMmf() override;
  const IGmkList *getBindedFormPcnpcList() const;

  u8 _48[0x50 - 0x48];
};

template <typename T, typename BASE> class TGmkFormPcList : public BASE {
public:
  explicit TGmkFormPcList(u32 updateGmkNumPerFrame) : BASE(updateGmkNumPerFrame) {}
  ~TGmkFormPcList() override { this->dispose(); }

  void create(const IGmkList::CreateInfo &info) override { BASE::create(info); }

protected:
  void createGmk(void *data) override;
};

template <typename T, typename BASE> class TGmkFormPcnpcList : public BASE {
public:
  explicit TGmkFormPcnpcList(u32 updateGmkNumPerFrame) : BASE(updateGmkNumPerFrame) {}

protected:
  void createGmk(void *data) override;
};

template <typename T, u32 MAGIC, u32 VERSION, typename GOB> using TGmkFormList = TGmkList<T, typename T::BdatInfo, MAGIC, VERSION, GOB>;

typedef TGmkFormPc<GMK_TYPE_FORM_PC, TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC>> GmkFormPc;
typedef TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC> GmkFormPcnpc;
typedef TGmkFormPc<GMK_TYPE_FORM_PC_EV, TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC_EV>> GmkFormPcEv;
typedef TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC_EV> GmkFormPcnpcEv;

typedef TGmkFormPcList<GmkFormPc, TGmkFormList<GmkFormPc, 0x43505246, 3, GmkFormPcGob>> GmkFormPcList;
typedef TGmkFormPcnpcList<GmkFormPcnpc, TGmkFormList<GmkFormPcnpc, 0x504e5246, 2, GmkFormPcnpcGob>> GmkFormPcnpcList;
typedef TGmkFormPcList<GmkFormPcEv, TGmkFormList<GmkFormPcEv, 0x43505246, 3, GmkFormPcGob>> GmkFormPcEvList;
typedef TGmkFormPcnpcList<GmkFormPcnpcEv, TGmkFormList<GmkFormPcnpcEv, 0x504e5246, 2, GmkFormPcnpcGob>> GmkFormPcnpcEvList;

static_assert(sizeof(GmkFormPcnpc) == 0x50, "");
static_assert(sizeof(GmkFormPc) == 0x50, "");

} // namespace gmk
