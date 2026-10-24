#include "gf/data/gf_bdat_shop.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbsh {

enum {
  ShopListName,
  ShopListShopIcon,
  ShopListShopType,
  ShopListTableID,
  ShopListDiscount1,
  ShopListDiscount2,
  ShopListDiscount3,
  ShopListDiscount4,
  ShopListDiscount5,
  ShopNormalDefItem1,
  ShopNormalDefItem2,
  ShopNormalDefItem3,
  ShopNormalDefItem4,
  ShopNormalDefItem5,
  ShopNormalDefItem6,
  ShopNormalDefItem7,
  ShopNormalDefItem8,
  ShopNormalDefItem9,
  ShopNormalDefItem10,
  ShopNormalAddtem1,
  ShopNormalAddCondition1,
  ShopNormalPrivilegeCheck1,
  ShopNormalAddtem2,
  ShopNormalAddCondition2,
  ShopNormalPrivilegeCheck2,
  ShopNormalAddtem3,
  ShopNormalAddCondition3,
  ShopNormalPrivilegeCheck3,
  ShopNormalAddtem4,
  ShopNormalAddCondition4,
  ShopNormalPrivilegeCheck4,
  ShopNormalAddtem5,
  ShopNormalAddCondition5,
  ShopNormalPrivilegeCheck5,
  ShopNormalPrivilegeFlag,
  ShopNormalPrivilegeItem,
  ShopInnPrice,
  ShopChangeDefTaskSet1,
  ShopChangeDefTaskSet2,
  ShopChangeDefTaskSet3,
  ShopChangeDefTaskSet4,
  ShopChangeDefTaskSet5,
  ShopChangeDefTaskSet6,
  ShopChangeDefTaskSet7,
  ShopChangeDefTaskSet8,
  ShopChangeAddTaskSet1,
  ShopChangeAddCondition1,
  ShopChangeAddTaskSet2,
  ShopChangeAddCondition2,
  ShopChangeAddTaskSet3,
  ShopChangeAddCondition3,
  ShopChangeAddTaskSet4,
  ShopChangeAddCondition4,
  ShopChangeAddTaskSet5,
  ShopChangeAddCondition5,
  ShopChangeAddTaskSet6,
  ShopChangeAddCondition6,
  ShopChangeAddTaskSet7,
  ShopChangeAddCondition7,
  ShopChangeAddTaskSet8,
  ShopChangeAddCondition8,
  ShopChangeLinkQuestTask,
  ShopChangeLinkQuestTaskID,
  ShopChangeUnitText,
  ShopChangeTaskSetItem1,
  ShopChangeTaskSetNumber1,
  ShopChangeTaskSetItem2,
  ShopChangeTaskSetNumber2,
  ShopChangeTaskSetItem3,
  ShopChangeTaskSetNumber3,
  ShopChangeTaskSetItem4,
  ShopChangeTaskSetNumber4,
  ShopChangeTaskSetItem5,
  ShopChangeTaskSetNumber5,
  ShopChangeTaskHideReward,
  ShopChangeTaskReward,
  ShopChangeTaskAddFlagValue,
  MNU_EventTheatertitle,
  MNU_EventTheaterevent_id,
  MNU_EventTheatercondition,
  MNU_EventTheaterthumbnail,
  MNU_EventTheatercategory,
  MNU_EventTheaterchapter,
  MNU_EventTheatermaincast,
  MNU_EventTheaterblade_id,
  MNU_EventTheaterflag_index,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initShopListName(const CBdatWrapper &wrapper) { s_members[ShopListName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getShopListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListName], id, 2).valueU16;
}

void initShopListShopIcon(const CBdatWrapper &wrapper) { s_members[ShopListShopIcon] = Bdat::getMember(wrapper.unknown00, "ShopIcon"); }

u32 getShopListShopIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListShopIcon] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListShopIcon], id, 2).valueU16;
}

void initShopListShopType(const CBdatWrapper &wrapper) { s_members[ShopListShopType] = Bdat::getMember(wrapper.unknown00, "ShopType"); }

u32 getShopListShopType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListShopType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListShopType], id, 1).valueU8;
}

void initShopListTableID(const CBdatWrapper &wrapper) { s_members[ShopListTableID] = Bdat::getMember(wrapper.unknown00, "TableID"); }

u32 getShopListTableID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListTableID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListTableID], id, 2).valueU16;
}

void initShopListDiscount1(const CBdatWrapper &wrapper) { s_members[ShopListDiscount1] = Bdat::getMember(wrapper.unknown00, "Discount1"); }

u32 getShopListDiscount1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount1], id, 1).valueU8;
}

void initShopListDiscount2(const CBdatWrapper &wrapper) { s_members[ShopListDiscount2] = Bdat::getMember(wrapper.unknown00, "Discount2"); }

u32 getShopListDiscount2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount2], id, 1).valueU8;
}

void initShopListDiscount3(const CBdatWrapper &wrapper) { s_members[ShopListDiscount3] = Bdat::getMember(wrapper.unknown00, "Discount3"); }

u32 getShopListDiscount3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount3], id, 1).valueU8;
}

void initShopListDiscount4(const CBdatWrapper &wrapper) { s_members[ShopListDiscount4] = Bdat::getMember(wrapper.unknown00, "Discount4"); }

u32 getShopListDiscount4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount4], id, 1).valueU8;
}

void initShopListDiscount5(const CBdatWrapper &wrapper) { s_members[ShopListDiscount5] = Bdat::getMember(wrapper.unknown00, "Discount5"); }

u32 getShopListDiscount5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount5], id, 1).valueU8;
}

void initShopNormalDefItem1(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem1] = Bdat::getMember(wrapper.unknown00, "DefItem1"); }

u32 getShopNormalDefItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem1], id, 2).valueU16;
}

void initShopNormalDefItem2(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem2] = Bdat::getMember(wrapper.unknown00, "DefItem2"); }

u32 getShopNormalDefItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem2], id, 2).valueU16;
}

void initShopNormalDefItem3(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem3] = Bdat::getMember(wrapper.unknown00, "DefItem3"); }

u32 getShopNormalDefItem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem3], id, 2).valueU16;
}

void initShopNormalDefItem4(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem4] = Bdat::getMember(wrapper.unknown00, "DefItem4"); }

u32 getShopNormalDefItem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem4], id, 2).valueU16;
}

void initShopNormalDefItem5(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem5] = Bdat::getMember(wrapper.unknown00, "DefItem5"); }

u32 getShopNormalDefItem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem5], id, 2).valueU16;
}

void initShopNormalDefItem6(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem6] = Bdat::getMember(wrapper.unknown00, "DefItem6"); }

u32 getShopNormalDefItem6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem6], id, 2).valueU16;
}

void initShopNormalDefItem7(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem7] = Bdat::getMember(wrapper.unknown00, "DefItem7"); }

u32 getShopNormalDefItem7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem7], id, 2).valueU16;
}

void initShopNormalDefItem8(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem8] = Bdat::getMember(wrapper.unknown00, "DefItem8"); }

u32 getShopNormalDefItem8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem8], id, 2).valueU16;
}

void initShopNormalDefItem9(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem9] = Bdat::getMember(wrapper.unknown00, "DefItem9"); }

u32 getShopNormalDefItem9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem9], id, 2).valueU16;
}

void initShopNormalDefItem10(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem10] = Bdat::getMember(wrapper.unknown00, "DefItem10"); }

u32 getShopNormalDefItem10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem10], id, 2).valueU16;
}

void initShopNormalAddtem1(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem1] = Bdat::getMember(wrapper.unknown00, "Addtem1"); }

u32 getShopNormalAddtem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem1], id, 2).valueU16;
}

void initShopNormalAddCondition1(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition1] = Bdat::getMember(wrapper.unknown00, "AddCondition1"); }

u32 getShopNormalAddCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition1], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck1(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeCheck1] = Bdat::getMember(wrapper.unknown00, "PrivilegeCheck1"); }

u32 getShopNormalPrivilegeCheck1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck1], id, 1).valueU8;
}

void initShopNormalAddtem2(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem2] = Bdat::getMember(wrapper.unknown00, "Addtem2"); }

u32 getShopNormalAddtem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem2], id, 2).valueU16;
}

void initShopNormalAddCondition2(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition2] = Bdat::getMember(wrapper.unknown00, "AddCondition2"); }

u32 getShopNormalAddCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition2], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck2(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeCheck2] = Bdat::getMember(wrapper.unknown00, "PrivilegeCheck2"); }

u32 getShopNormalPrivilegeCheck2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck2], id, 1).valueU8;
}

void initShopNormalAddtem3(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem3] = Bdat::getMember(wrapper.unknown00, "Addtem3"); }

u32 getShopNormalAddtem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem3], id, 2).valueU16;
}

void initShopNormalAddCondition3(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition3] = Bdat::getMember(wrapper.unknown00, "AddCondition3"); }

u32 getShopNormalAddCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition3], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck3(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeCheck3] = Bdat::getMember(wrapper.unknown00, "PrivilegeCheck3"); }

u32 getShopNormalPrivilegeCheck3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck3], id, 1).valueU8;
}

void initShopNormalAddtem4(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem4] = Bdat::getMember(wrapper.unknown00, "Addtem4"); }

u32 getShopNormalAddtem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem4], id, 2).valueU16;
}

void initShopNormalAddCondition4(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition4] = Bdat::getMember(wrapper.unknown00, "AddCondition4"); }

u32 getShopNormalAddCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition4], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck4(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeCheck4] = Bdat::getMember(wrapper.unknown00, "PrivilegeCheck4"); }

u32 getShopNormalPrivilegeCheck4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck4], id, 1).valueU8;
}

void initShopNormalAddtem5(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem5] = Bdat::getMember(wrapper.unknown00, "Addtem5"); }

u32 getShopNormalAddtem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem5], id, 2).valueU16;
}

void initShopNormalAddCondition5(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition5] = Bdat::getMember(wrapper.unknown00, "AddCondition5"); }

u32 getShopNormalAddCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition5], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck5(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeCheck5] = Bdat::getMember(wrapper.unknown00, "PrivilegeCheck5"); }

u32 getShopNormalPrivilegeCheck5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck5], id, 1).valueU8;
}

void initShopNormalPrivilegeFlag(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeFlag] = Bdat::getMember(wrapper.unknown00, "PrivilegeFlag"); }

u32 getShopNormalPrivilegeFlag(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeFlag], id, 2).valueU16;
}

void initShopNormalPrivilegeItem(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeItem] = Bdat::getMember(wrapper.unknown00, "PrivilegeItem"); }

u32 getShopNormalPrivilegeItem(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeItem] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeItem], id, 2).valueU16;
}

void initShopInnPrice(const CBdatWrapper &wrapper) { s_members[ShopInnPrice] = Bdat::getMember(wrapper.unknown00, "Price"); }

u32 getShopInnPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopInnPrice] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopInnPrice], id, 2).valueU16;
}

void initShopChangeDefTaskSet1(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet1] = Bdat::getMember(wrapper.unknown00, "DefTaskSet1"); }

u32 getShopChangeDefTaskSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet1], id, 2).valueU16;
}

void initShopChangeDefTaskSet2(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet2] = Bdat::getMember(wrapper.unknown00, "DefTaskSet2"); }

u32 getShopChangeDefTaskSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet2], id, 2).valueU16;
}

void initShopChangeDefTaskSet3(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet3] = Bdat::getMember(wrapper.unknown00, "DefTaskSet3"); }

u32 getShopChangeDefTaskSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet3], id, 2).valueU16;
}

void initShopChangeDefTaskSet4(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet4] = Bdat::getMember(wrapper.unknown00, "DefTaskSet4"); }

u32 getShopChangeDefTaskSet4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet4], id, 2).valueU16;
}

void initShopChangeDefTaskSet5(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet5] = Bdat::getMember(wrapper.unknown00, "DefTaskSet5"); }

u32 getShopChangeDefTaskSet5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet5], id, 2).valueU16;
}

void initShopChangeDefTaskSet6(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet6] = Bdat::getMember(wrapper.unknown00, "DefTaskSet6"); }

u32 getShopChangeDefTaskSet6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet6], id, 2).valueU16;
}

void initShopChangeDefTaskSet7(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet7] = Bdat::getMember(wrapper.unknown00, "DefTaskSet7"); }

u32 getShopChangeDefTaskSet7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet7], id, 2).valueU16;
}

void initShopChangeDefTaskSet8(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet8] = Bdat::getMember(wrapper.unknown00, "DefTaskSet8"); }

u32 getShopChangeDefTaskSet8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet8], id, 2).valueU16;
}

void initShopChangeAddTaskSet1(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet1] = Bdat::getMember(wrapper.unknown00, "AddTaskSet1"); }

u32 getShopChangeAddTaskSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet1], id, 2).valueU16;
}

void initShopChangeAddCondition1(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition1] = Bdat::getMember(wrapper.unknown00, "AddCondition1"); }

u32 getShopChangeAddCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition1], id, 2).valueU16;
}

void initShopChangeAddTaskSet2(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet2] = Bdat::getMember(wrapper.unknown00, "AddTaskSet2"); }

u32 getShopChangeAddTaskSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet2], id, 2).valueU16;
}

void initShopChangeAddCondition2(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition2] = Bdat::getMember(wrapper.unknown00, "AddCondition2"); }

u32 getShopChangeAddCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition2], id, 2).valueU16;
}

void initShopChangeAddTaskSet3(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet3] = Bdat::getMember(wrapper.unknown00, "AddTaskSet3"); }

u32 getShopChangeAddTaskSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet3], id, 2).valueU16;
}

void initShopChangeAddCondition3(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition3] = Bdat::getMember(wrapper.unknown00, "AddCondition3"); }

u32 getShopChangeAddCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition3], id, 2).valueU16;
}

void initShopChangeAddTaskSet4(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet4] = Bdat::getMember(wrapper.unknown00, "AddTaskSet4"); }

u32 getShopChangeAddTaskSet4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet4], id, 2).valueU16;
}

void initShopChangeAddCondition4(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition4] = Bdat::getMember(wrapper.unknown00, "AddCondition4"); }

u32 getShopChangeAddCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition4], id, 2).valueU16;
}

void initShopChangeAddTaskSet5(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet5] = Bdat::getMember(wrapper.unknown00, "AddTaskSet5"); }

u32 getShopChangeAddTaskSet5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet5], id, 2).valueU16;
}

void initShopChangeAddCondition5(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition5] = Bdat::getMember(wrapper.unknown00, "AddCondition5"); }

u32 getShopChangeAddCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition5], id, 2).valueU16;
}

void initShopChangeAddTaskSet6(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet6] = Bdat::getMember(wrapper.unknown00, "AddTaskSet6"); }

u32 getShopChangeAddTaskSet6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet6], id, 2).valueU16;
}

void initShopChangeAddCondition6(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition6] = Bdat::getMember(wrapper.unknown00, "AddCondition6"); }

u32 getShopChangeAddCondition6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition6], id, 2).valueU16;
}

void initShopChangeAddTaskSet7(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet7] = Bdat::getMember(wrapper.unknown00, "AddTaskSet7"); }

u32 getShopChangeAddTaskSet7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet7], id, 2).valueU16;
}

void initShopChangeAddCondition7(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition7] = Bdat::getMember(wrapper.unknown00, "AddCondition7"); }

u32 getShopChangeAddCondition7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition7], id, 2).valueU16;
}

void initShopChangeAddTaskSet8(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet8] = Bdat::getMember(wrapper.unknown00, "AddTaskSet8"); }

u32 getShopChangeAddTaskSet8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet8], id, 2).valueU16;
}

void initShopChangeAddCondition8(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition8] = Bdat::getMember(wrapper.unknown00, "AddCondition8"); }

u32 getShopChangeAddCondition8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition8], id, 2).valueU16;
}

void initShopChangeLinkQuestTask(const CBdatWrapper &wrapper) { s_members[ShopChangeLinkQuestTask] = Bdat::getMember(wrapper.unknown00, "LinkQuestTask"); }

u32 getShopChangeLinkQuestTask(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeLinkQuestTask] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeLinkQuestTask], id, 2).valueU16;
}

void initShopChangeLinkQuestTaskID(const CBdatWrapper &wrapper) { s_members[ShopChangeLinkQuestTaskID] = Bdat::getMember(wrapper.unknown00, "LinkQuestTaskID"); }

u32 getShopChangeLinkQuestTaskID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeLinkQuestTaskID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeLinkQuestTaskID], id, 2).valueU16;
}

void initShopChangeUnitText(const CBdatWrapper &wrapper) { s_members[ShopChangeUnitText] = Bdat::getMember(wrapper.unknown00, "UnitText"); }

u32 getShopChangeUnitText(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeUnitText] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeUnitText], id, 2).valueU16;
}

void initShopChangeTaskSetItem1(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem1] = Bdat::getMember(wrapper.unknown00, "SetItem1"); }

u32 getShopChangeTaskSetItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem1], id, 2).valueU16;
}

void initShopChangeTaskSetNumber1(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber1] = Bdat::getMember(wrapper.unknown00, "SetNumber1"); }

u32 getShopChangeTaskSetNumber1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber1], id, 2).valueU16;
}

void initShopChangeTaskSetItem2(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem2] = Bdat::getMember(wrapper.unknown00, "SetItem2"); }

u32 getShopChangeTaskSetItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem2], id, 2).valueU16;
}

void initShopChangeTaskSetNumber2(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber2] = Bdat::getMember(wrapper.unknown00, "SetNumber2"); }

u32 getShopChangeTaskSetNumber2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber2], id, 2).valueU16;
}

void initShopChangeTaskSetItem3(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem3] = Bdat::getMember(wrapper.unknown00, "SetItem3"); }

u32 getShopChangeTaskSetItem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem3], id, 2).valueU16;
}

void initShopChangeTaskSetNumber3(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber3] = Bdat::getMember(wrapper.unknown00, "SetNumber3"); }

u32 getShopChangeTaskSetNumber3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber3], id, 2).valueU16;
}

void initShopChangeTaskSetItem4(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem4] = Bdat::getMember(wrapper.unknown00, "SetItem4"); }

u32 getShopChangeTaskSetItem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem4], id, 2).valueU16;
}

void initShopChangeTaskSetNumber4(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber4] = Bdat::getMember(wrapper.unknown00, "SetNumber4"); }

u32 getShopChangeTaskSetNumber4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber4], id, 2).valueU16;
}

void initShopChangeTaskSetItem5(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem5] = Bdat::getMember(wrapper.unknown00, "SetItem5"); }

u32 getShopChangeTaskSetItem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem5], id, 2).valueU16;
}

void initShopChangeTaskSetNumber5(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber5] = Bdat::getMember(wrapper.unknown00, "SetNumber5"); }

u32 getShopChangeTaskSetNumber5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber5], id, 2).valueU16;
}

void initShopChangeTaskHideReward(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskHideReward] = Bdat::getMember(wrapper.unknown00, "HideReward"); }

u32 getShopChangeTaskHideReward(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskHideReward] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskHideReward], id, 2).valueU16;
}

void initShopChangeTaskReward(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskReward] = Bdat::getMember(wrapper.unknown00, "Reward"); }

u32 getShopChangeTaskReward(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskReward] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskReward], id, 2).valueU16;
}

void initShopChangeTaskAddFlagValue(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskAddFlagValue] = Bdat::getMember(wrapper.unknown00, "AddFlagValue"); }

u32 getShopChangeTaskAddFlagValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskAddFlagValue] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskAddFlagValue], id, 1).valueU8;
}

void initMNU_EventTheatertitle(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatertitle] = Bdat::getMember(wrapper.unknown00, "title"); }

u32 getMNU_EventTheatertitle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatertitle] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatertitle], id, 2).valueU16;
}

void initMNU_EventTheaterevent_id(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterevent_id] = Bdat::getMember(wrapper.unknown00, "event_id"); }

u32 getMNU_EventTheaterevent_id(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterevent_id] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterevent_id], id, 2).valueU16;
}

void initMNU_EventTheatercondition(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatercondition] = Bdat::getMember(wrapper.unknown00, "condition"); }

u32 getMNU_EventTheatercondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatercondition] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatercondition], id, 2).valueU16;
}

void initMNU_EventTheaterthumbnail(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterthumbnail] = Bdat::getMember(wrapper.unknown00, "thumbnail"); }

u32 getMNU_EventTheaterthumbnail(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterthumbnail] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterthumbnail], id, 2).valueU16;
}

void initMNU_EventTheatercategory(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatercategory] = Bdat::getMember(wrapper.unknown00, "category"); }

u32 getMNU_EventTheatercategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatercategory] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatercategory], id, 1).valueU8;
}

void initMNU_EventTheaterchapter(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterchapter] = Bdat::getMember(wrapper.unknown00, "chapter"); }

u32 getMNU_EventTheaterchapter(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterchapter] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterchapter], id, 1).valueU8;
}

void initMNU_EventTheatermaincast(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatermaincast] = Bdat::getMember(wrapper.unknown00, "maincast"); }

u32 getMNU_EventTheatermaincast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatermaincast] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatermaincast], id, 1).valueU8;
}

void initMNU_EventTheaterblade_id(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterblade_id] = Bdat::getMember(wrapper.unknown00, "blade_id"); }

u32 getMNU_EventTheaterblade_id(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterblade_id] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterblade_id], id, 2).valueU16;
}

void initMNU_EventTheaterflag_index(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterflag_index] = Bdat::getMember(wrapper.unknown00, "flag_index"); }

u32 getMNU_EventTheaterflag_index(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterflag_index] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterflag_index], id, 2).valueU16;
}

} // namespace _gfbsh

GfBdatShop::GfBdatShop() : m_shopList(nullptr), m_shopNormal(nullptr), m_shopInn(nullptr), m_shopChange(nullptr), m_shopChangeTask(nullptr), m_shopCategoryName(nullptr), m_MNU_EventTheater(nullptr) {
  bdatRefresh();
}

GfBdatShop::~GfBdatShop() { destroyFP(); }

void GfBdatShop::destroyFP() {
  if (m_shopList != nullptr) {
    delete m_shopList;
    m_shopList = nullptr;
  }

  if (m_shopNormal != nullptr) {
    delete m_shopNormal;
    m_shopNormal = nullptr;
  }

  if (m_shopInn != nullptr) {
    delete m_shopInn;
    m_shopInn = nullptr;
  }

  if (m_shopChange != nullptr) {
    delete m_shopChange;
    m_shopChange = nullptr;
  }

  if (m_shopChangeTask != nullptr) {
    delete m_shopChangeTask;
    m_shopChangeTask = nullptr;
  }

  if (m_shopCategoryName != nullptr) {
    delete m_shopCategoryName;
    m_shopCategoryName = nullptr;
  }

  if (m_MNU_EventTheater != nullptr) {
    delete m_MNU_EventTheater;
    m_MNU_EventTheater = nullptr;
  }
}

void GfBdatShop::createFP() {
  // __LINE__ of the game: it is the line argument of the operator new.
#line 1112
  m_shopList = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_LIST)};
  m_shopNormal = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_NORMAL)};
  m_shopInn = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_INN)};
  m_shopChange = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE)};
  m_shopChangeTask = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK)};
  m_shopCategoryName = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_SHOP_CATEGORY_NAME)};
  m_MNU_EventTheater = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_MNU_EVENT_THEATER)};
}

void GfBdatShop::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbsh::initShopListName(*m_shopList);
  _gfbsh::initShopListShopIcon(*m_shopList);
  _gfbsh::initShopListShopType(*m_shopList);
  _gfbsh::initShopListTableID(*m_shopList);
  _gfbsh::initShopListDiscount1(*m_shopList);
  _gfbsh::initShopListDiscount2(*m_shopList);
  _gfbsh::initShopListDiscount3(*m_shopList);
  _gfbsh::initShopListDiscount4(*m_shopList);
  _gfbsh::initShopListDiscount5(*m_shopList);
  _gfbsh::initShopNormalDefItem1(*m_shopNormal);
  _gfbsh::initShopNormalDefItem2(*m_shopNormal);
  _gfbsh::initShopNormalDefItem3(*m_shopNormal);
  _gfbsh::initShopNormalDefItem4(*m_shopNormal);
  _gfbsh::initShopNormalDefItem5(*m_shopNormal);
  _gfbsh::initShopNormalDefItem6(*m_shopNormal);
  _gfbsh::initShopNormalDefItem7(*m_shopNormal);
  _gfbsh::initShopNormalDefItem8(*m_shopNormal);
  _gfbsh::initShopNormalDefItem9(*m_shopNormal);
  _gfbsh::initShopNormalDefItem10(*m_shopNormal);
  _gfbsh::initShopNormalAddtem1(*m_shopNormal);
  _gfbsh::initShopNormalAddCondition1(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeCheck1(*m_shopNormal);
  _gfbsh::initShopNormalAddtem2(*m_shopNormal);
  _gfbsh::initShopNormalAddCondition2(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeCheck2(*m_shopNormal);
  _gfbsh::initShopNormalAddtem3(*m_shopNormal);
  _gfbsh::initShopNormalAddCondition3(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeCheck3(*m_shopNormal);
  _gfbsh::initShopNormalAddtem4(*m_shopNormal);
  _gfbsh::initShopNormalAddCondition4(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeCheck4(*m_shopNormal);
  _gfbsh::initShopNormalAddtem5(*m_shopNormal);
  _gfbsh::initShopNormalAddCondition5(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeCheck5(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeFlag(*m_shopNormal);
  _gfbsh::initShopNormalPrivilegeItem(*m_shopNormal);
  _gfbsh::initShopInnPrice(*m_shopInn);
  _gfbsh::initShopChangeDefTaskSet1(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet2(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet3(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet4(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet5(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet6(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet7(*m_shopChange);
  _gfbsh::initShopChangeDefTaskSet8(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet1(*m_shopChange);
  _gfbsh::initShopChangeAddCondition1(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet2(*m_shopChange);
  _gfbsh::initShopChangeAddCondition2(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet3(*m_shopChange);
  _gfbsh::initShopChangeAddCondition3(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet4(*m_shopChange);
  _gfbsh::initShopChangeAddCondition4(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet5(*m_shopChange);
  _gfbsh::initShopChangeAddCondition5(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet6(*m_shopChange);
  _gfbsh::initShopChangeAddCondition6(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet7(*m_shopChange);
  _gfbsh::initShopChangeAddCondition7(*m_shopChange);
  _gfbsh::initShopChangeAddTaskSet8(*m_shopChange);
  _gfbsh::initShopChangeAddCondition8(*m_shopChange);
  _gfbsh::initShopChangeLinkQuestTask(*m_shopChange);
  _gfbsh::initShopChangeLinkQuestTaskID(*m_shopChange);
  _gfbsh::initShopChangeUnitText(*m_shopChange);
  _gfbsh::initShopChangeTaskSetItem1(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetNumber1(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetItem2(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetNumber2(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetItem3(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetNumber3(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetItem4(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetNumber4(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetItem5(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskSetNumber5(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskHideReward(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskReward(*m_shopChangeTask);
  _gfbsh::initShopChangeTaskAddFlagValue(*m_shopChangeTask);
  _gfbsh::initMNU_EventTheatertitle(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheaterevent_id(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheatercondition(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheaterthumbnail(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheatercategory(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheaterchapter(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheatermaincast(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheaterblade_id(*m_MNU_EventTheater);
  _gfbsh::initMNU_EventTheaterflag_index(*m_MNU_EventTheater);
}

u32 GfBdatShop::getShopListStart() const { return Bdat::getIdTop(m_shopList->unknown00); }

u32 GfBdatShop::getShopListEnd() const { return Bdat::getIdTop(m_shopList->unknown00) + Bdat::getIdCount(m_shopList->unknown00); }

u32 GfBdatShop::getShopListName(u32 id) const { return _gfbsh::getShopListName(*m_shopList, id); }

u32 GfBdatShop::getShopListShopIcon(u32 id) const { return _gfbsh::getShopListShopIcon(*m_shopList, id); }

u32 GfBdatShop::getShopListShopType(u32 id) const { return _gfbsh::getShopListShopType(*m_shopList, id); }

u32 GfBdatShop::getShopListTableID(u32 id) const { return _gfbsh::getShopListTableID(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount1(u32 id) const { return _gfbsh::getShopListDiscount1(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount2(u32 id) const { return _gfbsh::getShopListDiscount2(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount3(u32 id) const { return _gfbsh::getShopListDiscount3(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount4(u32 id) const { return _gfbsh::getShopListDiscount4(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount5(u32 id) const { return _gfbsh::getShopListDiscount5(*m_shopList, id); }

u32 GfBdatShop::getShopListDiscount(u32 shop, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbsh::getShopListDiscount1, _gfbsh::getShopListDiscount2, _gfbsh::getShopListDiscount3, _gfbsh::getShopListDiscount4, _gfbsh::getShopListDiscount5};
  return getters[index](*m_shopList, shop);
}

u32 GfBdatShop::getShopNormalStart() const { return Bdat::getIdTop(m_shopNormal->unknown00); }

u32 GfBdatShop::getShopNormalEnd() const { return Bdat::getIdTop(m_shopNormal->unknown00) + Bdat::getIdCount(m_shopNormal->unknown00); }

u32 GfBdatShop::getShopNormalDefItem1(u32 id) const { return _gfbsh::getShopNormalDefItem1(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem2(u32 id) const { return _gfbsh::getShopNormalDefItem2(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem3(u32 id) const { return _gfbsh::getShopNormalDefItem3(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem4(u32 id) const { return _gfbsh::getShopNormalDefItem4(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem5(u32 id) const { return _gfbsh::getShopNormalDefItem5(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem6(u32 id) const { return _gfbsh::getShopNormalDefItem6(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem7(u32 id) const { return _gfbsh::getShopNormalDefItem7(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem8(u32 id) const { return _gfbsh::getShopNormalDefItem8(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem9(u32 id) const { return _gfbsh::getShopNormalDefItem9(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem10(u32 id) const { return _gfbsh::getShopNormalDefItem10(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem1(u32 id) const { return _gfbsh::getShopNormalAddtem1(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition1(u32 id) const { return _gfbsh::getShopNormalAddCondition1(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck1(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck1(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem2(u32 id) const { return _gfbsh::getShopNormalAddtem2(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition2(u32 id) const { return _gfbsh::getShopNormalAddCondition2(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck2(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck2(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem3(u32 id) const { return _gfbsh::getShopNormalAddtem3(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition3(u32 id) const { return _gfbsh::getShopNormalAddCondition3(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck3(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck3(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem4(u32 id) const { return _gfbsh::getShopNormalAddtem4(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition4(u32 id) const { return _gfbsh::getShopNormalAddCondition4(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck4(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck4(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem5(u32 id) const { return _gfbsh::getShopNormalAddtem5(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition5(u32 id) const { return _gfbsh::getShopNormalAddCondition5(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck5(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck5(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeFlag(u32 id) const { return _gfbsh::getShopNormalPrivilegeFlag(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeItem(u32 id) const { return _gfbsh::getShopNormalPrivilegeItem(*m_shopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbsh::getShopNormalDefItem1,
                                                              _gfbsh::getShopNormalDefItem2,
                                                              _gfbsh::getShopNormalDefItem3,
                                                              _gfbsh::getShopNormalDefItem4,
                                                              _gfbsh::getShopNormalDefItem5,
                                                              _gfbsh::getShopNormalDefItem6,
                                                              _gfbsh::getShopNormalDefItem7,
                                                              _gfbsh::getShopNormalDefItem8,
                                                              _gfbsh::getShopNormalDefItem9,
                                                              _gfbsh::getShopNormalDefItem10};
  return getters[index](*m_shopNormal, table);
}

u32 GfBdatShop::getShopNormalAddItem(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbsh::getShopNormalAddtem1, _gfbsh::getShopNormalAddtem2, _gfbsh::getShopNormalAddtem3, _gfbsh::getShopNormalAddtem4, _gfbsh::getShopNormalAddtem5};
  return getters[index](*m_shopNormal, table);
}

u32 GfBdatShop::getShopNormalAddCondition(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbsh::getShopNormalAddCondition1, _gfbsh::getShopNormalAddCondition2, _gfbsh::getShopNormalAddCondition3, _gfbsh::getShopNormalAddCondition4, _gfbsh::getShopNormalAddCondition5};
  return getters[index](*m_shopNormal, table);
}

u32 GfBdatShop::getShopNormalPrivilegeCheck(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbsh::getShopNormalPrivilegeCheck1, _gfbsh::getShopNormalPrivilegeCheck2, _gfbsh::getShopNormalPrivilegeCheck3, _gfbsh::getShopNormalPrivilegeCheck4, _gfbsh::getShopNormalPrivilegeCheck5};
  return getters[index](*m_shopNormal, table);
}

u32 GfBdatShop::getShopInnStart() const { return Bdat::getIdTop(m_shopInn->unknown00); }

u32 GfBdatShop::getShopInnEnd() const { return Bdat::getIdTop(m_shopInn->unknown00) + Bdat::getIdCount(m_shopInn->unknown00); }

u32 GfBdatShop::getShopInnPrice(u32 id) const { return _gfbsh::getShopInnPrice(*m_shopInn, id); }

u32 GfBdatShop::getShopChangeStart() const { return Bdat::getIdTop(m_shopChange->unknown00); }

u32 GfBdatShop::getShopChangeEnd() const { return Bdat::getIdTop(m_shopChange->unknown00) + Bdat::getIdCount(m_shopChange->unknown00); }

u32 GfBdatShop::getShopChangeDefTaskSet1(u32 id) const { return _gfbsh::getShopChangeDefTaskSet1(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet2(u32 id) const { return _gfbsh::getShopChangeDefTaskSet2(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet3(u32 id) const { return _gfbsh::getShopChangeDefTaskSet3(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet4(u32 id) const { return _gfbsh::getShopChangeDefTaskSet4(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet5(u32 id) const { return _gfbsh::getShopChangeDefTaskSet5(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet6(u32 id) const { return _gfbsh::getShopChangeDefTaskSet6(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet7(u32 id) const { return _gfbsh::getShopChangeDefTaskSet7(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet8(u32 id) const { return _gfbsh::getShopChangeDefTaskSet8(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet1(u32 id) const { return _gfbsh::getShopChangeAddTaskSet1(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition1(u32 id) const { return _gfbsh::getShopChangeAddCondition1(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet2(u32 id) const { return _gfbsh::getShopChangeAddTaskSet2(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition2(u32 id) const { return _gfbsh::getShopChangeAddCondition2(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet3(u32 id) const { return _gfbsh::getShopChangeAddTaskSet3(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition3(u32 id) const { return _gfbsh::getShopChangeAddCondition3(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet4(u32 id) const { return _gfbsh::getShopChangeAddTaskSet4(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition4(u32 id) const { return _gfbsh::getShopChangeAddCondition4(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet5(u32 id) const { return _gfbsh::getShopChangeAddTaskSet5(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition5(u32 id) const { return _gfbsh::getShopChangeAddCondition5(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet6(u32 id) const { return _gfbsh::getShopChangeAddTaskSet6(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition6(u32 id) const { return _gfbsh::getShopChangeAddCondition6(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet7(u32 id) const { return _gfbsh::getShopChangeAddTaskSet7(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition7(u32 id) const { return _gfbsh::getShopChangeAddCondition7(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet8(u32 id) const { return _gfbsh::getShopChangeAddTaskSet8(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition8(u32 id) const { return _gfbsh::getShopChangeAddCondition8(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeLinkQuestTask(u32 id) const { return _gfbsh::getShopChangeLinkQuestTask(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeLinkQuestTaskID(u32 id) const { return _gfbsh::getShopChangeLinkQuestTaskID(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeUnitText(u32 id) const { return _gfbsh::getShopChangeUnitText(*m_shopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbsh::getShopChangeDefTaskSet1,
                                                              _gfbsh::getShopChangeDefTaskSet2,
                                                              _gfbsh::getShopChangeDefTaskSet3,
                                                              _gfbsh::getShopChangeDefTaskSet4,
                                                              _gfbsh::getShopChangeDefTaskSet5,
                                                              _gfbsh::getShopChangeDefTaskSet6,
                                                              _gfbsh::getShopChangeDefTaskSet7,
                                                              _gfbsh::getShopChangeDefTaskSet8};
  return getters[index](*m_shopChange, table);
}

u32 GfBdatShop::getShopChangeAddTaskSet(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbsh::getShopChangeAddTaskSet1,
                                                              _gfbsh::getShopChangeAddTaskSet2,
                                                              _gfbsh::getShopChangeAddTaskSet3,
                                                              _gfbsh::getShopChangeAddTaskSet4,
                                                              _gfbsh::getShopChangeAddTaskSet5,
                                                              _gfbsh::getShopChangeAddTaskSet6,
                                                              _gfbsh::getShopChangeAddTaskSet7,
                                                              _gfbsh::getShopChangeAddTaskSet8};
  return getters[index](*m_shopChange, table);
}

u32 GfBdatShop::getShopChangeAddCondition(u32 table, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbsh::getShopChangeAddCondition1,
                                                              _gfbsh::getShopChangeAddCondition2,
                                                              _gfbsh::getShopChangeAddCondition3,
                                                              _gfbsh::getShopChangeAddCondition4,
                                                              _gfbsh::getShopChangeAddCondition5,
                                                              _gfbsh::getShopChangeAddCondition6,
                                                              _gfbsh::getShopChangeAddCondition7,
                                                              _gfbsh::getShopChangeAddCondition8};
  return getters[index](*m_shopChange, table);
}

u32 GfBdatShop::getShopChangeTaskStart() const { return Bdat::getIdTop(m_shopChangeTask->unknown00); }

u32 GfBdatShop::getShopChangeTaskEnd() const { return Bdat::getIdTop(m_shopChangeTask->unknown00) + Bdat::getIdCount(m_shopChangeTask->unknown00); }

u32 GfBdatShop::getShopChangeTaskSetItem1(u32 id) const { return _gfbsh::getShopChangeTaskSetItem1(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber1(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber1(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem2(u32 id) const { return _gfbsh::getShopChangeTaskSetItem2(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber2(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber2(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem3(u32 id) const { return _gfbsh::getShopChangeTaskSetItem3(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber3(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber3(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem4(u32 id) const { return _gfbsh::getShopChangeTaskSetItem4(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber4(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber4(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem5(u32 id) const { return _gfbsh::getShopChangeTaskSetItem5(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber5(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber5(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskHideReward(u32 id) const { return _gfbsh::getShopChangeTaskHideReward(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskReward(u32 id) const { return _gfbsh::getShopChangeTaskReward(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskAddFlagValue(u32 id) const { return _gfbsh::getShopChangeTaskAddFlagValue(*m_shopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem(u32 task, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbsh::getShopChangeTaskSetItem1, _gfbsh::getShopChangeTaskSetItem2, _gfbsh::getShopChangeTaskSetItem3, _gfbsh::getShopChangeTaskSetItem4, _gfbsh::getShopChangeTaskSetItem5};
  return getters[index](*m_shopChangeTask, task);
}

u32 GfBdatShop::getShopChangeTaskSetNumber(u32 task, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbsh::getShopChangeTaskSetNumber1, _gfbsh::getShopChangeTaskSetNumber2, _gfbsh::getShopChangeTaskSetNumber3, _gfbsh::getShopChangeTaskSetNumber4, _gfbsh::getShopChangeTaskSetNumber5};
  return getters[index](*m_shopChangeTask, task);
}

u32 GfBdatShop::getMNU_EventTheaterStart() const { return Bdat::getIdTop(m_MNU_EventTheater->unknown00); }

u32 GfBdatShop::getMNU_EventTheaterEnd() const { return Bdat::getIdTop(m_MNU_EventTheater->unknown00) + Bdat::getIdCount(m_MNU_EventTheater->unknown00); }

u32 GfBdatShop::getMNU_EventTheatertitle(u32 id) const { return _gfbsh::getMNU_EventTheatertitle(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterevent_id(u32 id) const { return _gfbsh::getMNU_EventTheaterevent_id(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatercondition(u32 id) const { return _gfbsh::getMNU_EventTheatercondition(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterthumbnail(u32 id) const { return _gfbsh::getMNU_EventTheaterthumbnail(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatercategory(u32 id) const { return _gfbsh::getMNU_EventTheatercategory(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterchapter(u32 id) const { return _gfbsh::getMNU_EventTheaterchapter(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatermaincast(u32 id) const { return _gfbsh::getMNU_EventTheatermaincast(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterblade_id(u32 id) const { return _gfbsh::getMNU_EventTheaterblade_id(*m_MNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterflag_index(u32 id) const { return _gfbsh::getMNU_EventTheaterflag_index(*m_MNU_EventTheater, id); }

} // namespace gf
