#include "dr/dr_shd_man.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_fetch_man.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_mdo_man.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdMan::DrShdMan(DrMan *drMan) : m_drShdDataList(nullptr), m_drShdMdoMan(nullptr), m_drShdFetchMan(nullptr), m_drShdLgtMan(nullptr), m_drMan(drMan) {
  m_drShdDataList = new (drMan->unknown0c) DrShdDataList(m_drMan);
  m_drShdMdoMan = new (drMan->unknown0c) DrShdMdoMan();
  m_drShdFetchMan = new (drMan->unknown0c) DrShdFetchMan(m_drMan);
  m_drShdLgtMan = new (drMan->unknown0c) DrShdLgtMan(m_drMan);
}

DrShdMan::~DrShdMan() {
  if (m_drShdDataList != nullptr) {
    delete m_drShdDataList;
    m_drShdDataList = nullptr;
  }
  if (m_drShdMdoMan != nullptr) {
    delete m_drShdMdoMan;
    m_drShdMdoMan = nullptr;
  }
  if (m_drShdFetchMan != nullptr) {
    delete m_drShdFetchMan;
    m_drShdFetchMan = nullptr;
  }
  if (m_drShdLgtMan != nullptr) {
    delete m_drShdLgtMan;
    m_drShdLgtMan = nullptr;
  }
}

void DrShdMan::beginUpdate() { m_drShdMdoMan->update(); }

void DrShdMan::debugRender() {}

void DrShdMan::beforeUpdateCate(int cate) { m_drShdLgtMan->beforeUpdateCate(cate); }

void DrShdMan::setupCate(int cate) { m_drShdLgtMan->setupCate(cate); }

void DrShdMan::updateCate(int cate) { m_drShdLgtMan->updateCate(cate); }

void DrShdMan::addViewInfo(int cate) { m_drShdLgtMan->addViewInfo(cate); }

void DrShdMan::delViewInfo(int cate) { m_drShdLgtMan->delViewInfo(cate); }

void DrShdMan::resetColorBuff(int index) {
  if (m_drShdLgtMan != nullptr) {
    m_drShdLgtMan->resetColorBuff(index);
  }
}

} // namespace ml
