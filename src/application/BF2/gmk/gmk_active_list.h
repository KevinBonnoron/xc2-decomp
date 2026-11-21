#pragma once
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gmk {

template <typename T> class TGmkActiveList : public mm::mtl::PtrSingleton<TGmkActiveList<T>> {
public:
  TGmkActiveList() : unknown20(false) {}
  ~TGmkActiveList() override {}

  // Inferred helper: updates the gimmicks of the list, flagged as being updated meanwhile; GmkManager::seqUpdate (1.0.0: 0x71005dacfc)
  // repeats it for its five lists. Original name unknown.
  static void unknown001(f32 deltaTime) {
    TGmkActiveList *list = TGmkActiveList::get();
    list->unknown20 = true;
    for (typename mm::mtl::IntrusiveList<T>::iterator it = list->unknown08.begin(); it != list->unknown08.end(); ++it) {
      it->updateInActiveList(deltaTime);
    }
    TGmkActiveList::get()->unknown20 = false;
  }

  // Inferred helper: adds a gimmick to the list unless it is already there; the create functions of the precious, event, se, se line and
  // tutorial gimmicks repeat it (GmkPrecious::createGobInst, GmkEvent::createGmkPhantom, GmkSe::createInst, GmkSeLine::createInst,
  // GmkTutorial::createGmkPhantom). Original name unknown.
  static void unknown002(T *gmk) {
    TGmkActiveList *list = TGmkActiveList::get();
    if (list->unknown08.end() == list->unknown08.unknown002(list->unknown08.begin(), list->unknown08.end(), gmk)) {
      TGmkActiveList::get()->unknown08.push_back(gmk);
    }
  }

  mm::mtl::IntrusiveList<T> unknown08; // Inferred role: active gimmicks; original member name unknown.
  bool unknown20;                      // Inferred role: list being updated; original member name unknown.
};

} // namespace gmk
