#pragma once
#include <stddef.h>

#include "event/cmd_item.h"
#include "event/i_cmd.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {
class CmdParam;

template <size_t N, int Type> class CmdQueue {
public:
  virtual ~CmdQueue() {}
  void clear() { mItems.clear(); }
  bool isEmpty() const { return mItems.size() == 0; }
  void update();
  void erase(const ICmd *cmd);
  void push_back(ICmd *cmd, const CmdParam &param);
  void eraseAll() {
    while (mItems.size() != 0) {
      erase(mItems.front().mCmd);
    }
  }
  bool isExist(const ICmd *cmd) const {
    for (u32 i = 0; i < mItems.size(); i++) {
      if (mItems.at(i)->mCmd == cmd) {
        return true;
      }
    }
    return false;
  }

private:
  mm::mtl::FixedVector<CmdItem, N> mItems;
};

template <size_t N, int Type> void CmdQueue<N, Type>::update() {
  u32 nextCount = 0;
  u32 index = 0;
  CmdItem *it = mItems.begin();
  while (true) {
    if (nextCount > index) {
      if (it == mItems.end() || it->mWaitFrame > 0) {
        break;
      }
      ++it;
      ++index;
      continue;
    }
    if (it == mItems.end() || it->mWaitFrame > 0) {
      break;
    }
    ICmd::RESULT result = it->mCmd->update(ICmd::Param(it->mParam, it->frame));
    if (it->frame != 0x7fffffff) {
      it->frame++;
    }
    switch (result) {
    case ICmd::RESULT_WAIT:
      goto end;
    case ICmd::RESULT_END:
      it->mCmd->term();
      mItems.erase(it);
      it = mItems.begin();
      index = 0;
      break;
    case ICmd::RESULT_NEXT:
      ++it;
      nextCount++;
      ++index;
      break;
    default:
      break;
    }
  }
end:
  for (u32 i = 0; i < mItems.size(); i++) {
    if (mItems[i].mWaitFrame > 0) {
      mItems[i].mWaitFrame--;
    }
  }
}

template <size_t N, int Type> void CmdQueue<N, Type>::erase(const ICmd *cmd) {
  for (CmdItem *it = mItems.begin(); it != mItems.end(); ++it) {
    if (it->mCmd == cmd) {
      it->mCmd->term();
      mItems.erase(it);
      return;
    }
  }
}

template <size_t N, int Type> void CmdQueue<N, Type>::push_back(ICmd *cmd, const CmdParam &param) {
  while (mItems.size() >= mItems.capacity()) {
    mItems.erase(mItems.begin());
  }
  cmd->init();
  mItems.push_back(CmdItem(cmd, param));
}

} // namespace event
