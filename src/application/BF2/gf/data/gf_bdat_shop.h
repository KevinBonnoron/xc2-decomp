#pragma once
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

class GfBdatShop : public mm::mtl::PtrSingleton<GfBdatShop>, public IDataBdat {
public:
  GfBdatShop();
  virtual ~GfBdatShop();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getShopListStart() const;
  u32 getShopListEnd() const;
  u32 getShopListName(u32 id) const;
  u32 getShopListShopIcon(u32 id) const;
  u32 getShopListShopType(u32 id) const;
  u32 getShopListTableID(u32 id) const;
  u32 getShopListDiscount1(u32 id) const;
  u32 getShopListDiscount2(u32 id) const;
  u32 getShopListDiscount3(u32 id) const;
  u32 getShopListDiscount4(u32 id) const;
  u32 getShopListDiscount5(u32 id) const;
  u32 getShopListDiscount(u32 shop, u32 index) const;
  u32 getShopNormalStart() const;
  u32 getShopNormalEnd() const;
  u32 getShopNormalDefItem1(u32 id) const;
  u32 getShopNormalDefItem2(u32 id) const;
  u32 getShopNormalDefItem3(u32 id) const;
  u32 getShopNormalDefItem4(u32 id) const;
  u32 getShopNormalDefItem5(u32 id) const;
  u32 getShopNormalDefItem6(u32 id) const;
  u32 getShopNormalDefItem7(u32 id) const;
  u32 getShopNormalDefItem8(u32 id) const;
  u32 getShopNormalDefItem9(u32 id) const;
  u32 getShopNormalDefItem10(u32 id) const;
  u32 getShopNormalAddtem1(u32 id) const;
  u32 getShopNormalAddCondition1(u32 id) const;
  u32 getShopNormalPrivilegeCheck1(u32 id) const;
  u32 getShopNormalAddtem2(u32 id) const;
  u32 getShopNormalAddCondition2(u32 id) const;
  u32 getShopNormalPrivilegeCheck2(u32 id) const;
  u32 getShopNormalAddtem3(u32 id) const;
  u32 getShopNormalAddCondition3(u32 id) const;
  u32 getShopNormalPrivilegeCheck3(u32 id) const;
  u32 getShopNormalAddtem4(u32 id) const;
  u32 getShopNormalAddCondition4(u32 id) const;
  u32 getShopNormalPrivilegeCheck4(u32 id) const;
  u32 getShopNormalAddtem5(u32 id) const;
  u32 getShopNormalAddCondition5(u32 id) const;
  u32 getShopNormalPrivilegeCheck5(u32 id) const;
  u32 getShopNormalPrivilegeFlag(u32 id) const;
  u32 getShopNormalPrivilegeItem(u32 id) const;
  u32 getShopNormalDefItem(u32 table, u32 index) const;
  u32 getShopNormalAddItem(u32 table, u32 index) const;
  u32 getShopNormalAddCondition(u32 table, u32 index) const;
  u32 getShopNormalPrivilegeCheck(u32 table, u32 index) const;
  u32 getShopInnStart() const;
  u32 getShopInnEnd() const;
  u32 getShopInnPrice(u32 id) const;
  u32 getShopChangeStart() const;
  u32 getShopChangeEnd() const;
  u32 getShopChangeDefTaskSet1(u32 id) const;
  u32 getShopChangeDefTaskSet2(u32 id) const;
  u32 getShopChangeDefTaskSet3(u32 id) const;
  u32 getShopChangeDefTaskSet4(u32 id) const;
  u32 getShopChangeDefTaskSet5(u32 id) const;
  u32 getShopChangeDefTaskSet6(u32 id) const;
  u32 getShopChangeDefTaskSet7(u32 id) const;
  u32 getShopChangeDefTaskSet8(u32 id) const;
  u32 getShopChangeAddTaskSet1(u32 id) const;
  u32 getShopChangeAddCondition1(u32 id) const;
  u32 getShopChangeAddTaskSet2(u32 id) const;
  u32 getShopChangeAddCondition2(u32 id) const;
  u32 getShopChangeAddTaskSet3(u32 id) const;
  u32 getShopChangeAddCondition3(u32 id) const;
  u32 getShopChangeAddTaskSet4(u32 id) const;
  u32 getShopChangeAddCondition4(u32 id) const;
  u32 getShopChangeAddTaskSet5(u32 id) const;
  u32 getShopChangeAddCondition5(u32 id) const;
  u32 getShopChangeAddTaskSet6(u32 id) const;
  u32 getShopChangeAddCondition6(u32 id) const;
  u32 getShopChangeAddTaskSet7(u32 id) const;
  u32 getShopChangeAddCondition7(u32 id) const;
  u32 getShopChangeAddTaskSet8(u32 id) const;
  u32 getShopChangeAddCondition8(u32 id) const;
  u32 getShopChangeLinkQuestTask(u32 id) const;
  u32 getShopChangeLinkQuestTaskID(u32 id) const;
  u32 getShopChangeUnitText(u32 id) const;
  u32 getShopChangeDefTaskSet(u32 table, u32 index) const;
  u32 getShopChangeAddTaskSet(u32 table, u32 index) const;
  u32 getShopChangeAddCondition(u32 table, u32 index) const;
  u32 getShopChangeTaskStart() const;
  u32 getShopChangeTaskEnd() const;
  u32 getShopChangeTaskSetItem1(u32 id) const;
  u32 getShopChangeTaskSetNumber1(u32 id) const;
  u32 getShopChangeTaskSetItem2(u32 id) const;
  u32 getShopChangeTaskSetNumber2(u32 id) const;
  u32 getShopChangeTaskSetItem3(u32 id) const;
  u32 getShopChangeTaskSetNumber3(u32 id) const;
  u32 getShopChangeTaskSetItem4(u32 id) const;
  u32 getShopChangeTaskSetNumber4(u32 id) const;
  u32 getShopChangeTaskSetItem5(u32 id) const;
  u32 getShopChangeTaskSetNumber5(u32 id) const;
  u32 getShopChangeTaskHideReward(u32 id) const;
  u32 getShopChangeTaskReward(u32 id) const;
  u32 getShopChangeTaskAddFlagValue(u32 id) const;
  u32 getShopChangeTaskSetItem(u32 task, u32 index) const;
  u32 getShopChangeTaskSetNumber(u32 task, u32 index) const;
  u32 getMNU_EventTheaterStart() const;
  u32 getMNU_EventTheaterEnd() const;
  u32 getMNU_EventTheatertitle(u32 id) const;
  u32 getMNU_EventTheaterevent_id(u32 id) const;
  u32 getMNU_EventTheatercondition(u32 id) const;
  u32 getMNU_EventTheaterthumbnail(u32 id) const;
  u32 getMNU_EventTheatercategory(u32 id) const;
  u32 getMNU_EventTheaterchapter(u32 id) const;
  u32 getMNU_EventTheatermaincast(u32 id) const;
  u32 getMNU_EventTheaterblade_id(u32 id) const;
  u32 getMNU_EventTheaterflag_index(u32 id) const;

private:
  CBdatWrapper *m_shopList;
  CBdatWrapper *m_shopNormal;
  CBdatWrapper *m_shopInn;
  CBdatWrapper *m_shopChange;
  CBdatWrapper *m_shopChangeTask;
  CBdatWrapper *m_shopCategoryName;
  CBdatWrapper *m_MNU_EventTheater;
};

} // namespace gf
