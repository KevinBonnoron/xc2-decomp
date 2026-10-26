#include "gmk/gmk_form_pc.h"

#include "gmk/gmk_set.h"

namespace gmk {

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

} // namespace gmk
