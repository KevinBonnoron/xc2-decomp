#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_form_impl.h" // IWYU pragma: keep

#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"

namespace gmk {

template bool TGmkList<GmkFormPc, GmkFormPc::BdatInfo, 0x43505246, 3, GmkFormPcGob>::initGmkBdatInfo(GmkFormPc::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkFormPcnpc, GmkFormPcnpc::BdatInfo, 0x504e5246, 2, GmkFormPcnpcGob>::initGmkBdatInfo(GmkFormPcnpc::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkFormPcEv, GmkFormPcEv::BdatInfo, 0x43505246, 3, GmkFormPcGob>::initGmkBdatInfo(GmkFormPcEv::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkFormPcnpcEv, GmkFormPcnpcEv::BdatInfo, 0x504e5246, 2, GmkFormPcnpcGob>::initGmkBdatInfo(GmkFormPcnpcEv::BdatInfo &, int &, const AGmkBase &);

template <GmkType TYPE> TGmkFormPcnpc<TYPE>::~TGmkFormPcnpc() { dispose(); }

template <GmkType TYPE> GmkType TGmkFormPcnpc<TYPE>::getGmkType() const { return GMK_TYPE; }

template <GmkType TYPE> bool TGmkFormPcnpc<TYPE>::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

template <GmkType TYPE> void TGmkFormPcnpc<TYPE>::create(const CreateInfo &info) { AGmkBase::create(info); }

template <GmkType TYPE> void TGmkFormPcnpc<TYPE>::dispose() { AGmkBase::dispose(); }

template <GmkType TYPE> void TGmkFormPcnpc<TYPE>::debugUpdateMmf() {}

template <GmkType TYPE, typename FORM_PCNPC> TGmkFormPc<TYPE, FORM_PCNPC>::~TGmkFormPc() { dispose(); }

template <GmkType TYPE, typename FORM_PCNPC> GmkType TGmkFormPc<TYPE, FORM_PCNPC>::getGmkType() const { return GMK_TYPE; }

template <GmkType TYPE, typename FORM_PCNPC> bool TGmkFormPc<TYPE, FORM_PCNPC>::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

template <GmkType TYPE, typename FORM_PCNPC> void TGmkFormPc<TYPE, FORM_PCNPC>::create(const CreateInfo &info) { AGmkBase::create(info); }

template <GmkType TYPE, typename FORM_PCNPC> void TGmkFormPc<TYPE, FORM_PCNPC>::dispose() { AGmkBase::dispose(); }

template <GmkType TYPE, typename FORM_PCNPC> void TGmkFormPc<TYPE, FORM_PCNPC>::debugUpdateMmf() {}

template <GmkType TYPE, typename FORM_PCNPC> const IGmkList *TGmkFormPc<TYPE, FORM_PCNPC>::getBindedFormPcnpcList() const {
  return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[FORM_PCNPC::GMK_TYPE];
}

template class TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC>;
template class TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC_EV>;
template class TGmkFormPc<GMK_TYPE_FORM_PC, TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC>>;
template class TGmkFormPc<GMK_TYPE_FORM_PC_EV, TGmkFormPcnpc<GMK_TYPE_FORM_PCNPC_EV>>;

template bool GmkForm::create<GmkFormPc, GmkFormPcnpc>(const GmkFormPc &);

} // namespace gmk
