// No game string names this file: named after VwTaskRoot, which it defines.
#include "dir/vw_process.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {
class WinView;
} // namespace ml

namespace dir {

VwTaskRoot::VwTaskRoot() {
  unknown00.Init();
  Reset();
}

void VwTaskRoot::Release() {
  unknown00.Delete();
  unknown00.Term();
  unknown60 = nullptr;
  unknown68 = nullptr;
  unknown50 = nullptr;
  unknown58 = nullptr;
}

void VwTaskRoot::Move() { unknown00.Move(); }

void VwTaskRoot::Draw() { unknown00.Draw(); }

void VwTaskRoot::Tail() {
  unknown00.Tail();
  unknown00.Delete();
}

void VwTaskRoot::DebugDraw(ml::WinView *view) {}

void VwTaskRoot::DebugDrawRecursive(VwProcess *process, ml::WinView *view, int &depth) {}

VwTaskRoot *VwTaskManager::Create() { return new (ml::WorkUtil::getWorkMem()) VwTaskRoot(); }

void VwTaskManager::Release(VwTaskRoot *root) {
  if (root != nullptr) {
    root->Release();
    delete root;
  }
}

} // namespace dir
