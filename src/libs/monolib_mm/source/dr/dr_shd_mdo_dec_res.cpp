#include "dr/dr_shd_mdo_dec_res.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_fetch_man.h"
#include "dr/dr_shd_fetch_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_shd_list.h"

namespace ml {

void DrShdMdoDecRes::setVertexParam(DrShdFetchMan *fetchMan, int num, const MdsMatVertexInfo *infos) {
  if (m_fetch != nullptr) {
    fetchMan->releaseFetchObj(m_fetch);
  }
  m_fetch = fetchMan->createFetchObj(num, infos);
}

DrShdMdoDecRes::DrShdMdoDecRes() : m_fetch(nullptr) {}

DrShdMdoDecRes::~DrShdMdoDecRes() { releaseObj(); }

void DrShdMdoDecRes::releaseObj() {
  CGLibDecShader::release();
  if (m_fetch != nullptr) {
    DrMan::getIns()->unknown80->unknown10->releaseFetchObj(m_fetch);
    m_fetch = nullptr;
  }
}

DrResFetch *DrShdMdoDecRes::getFetch() { return &m_fetch->unknown20; }

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdMdoDecRes>;
