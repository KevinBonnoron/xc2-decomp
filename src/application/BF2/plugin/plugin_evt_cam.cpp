#include "event/memory_manager.h"
#include "event/script_cam_cut.h"
#include "event/script_cam_follow_pos.h"
#include "event/script_cam_follow_tar.h"
#include "event/script_cam_fov.h"
#include "event/script_cam_motion.h"
#include "event/script_cam_move_fov.h"
#include "event/script_cam_move_pos.h"
#include "event/script_cam_move_rot_z.h"
#include "event/script_cam_move_tar.h"
#include "event/script_cam_nearfar.h"
#include "event/script_cam_pos.h"
#include "event/script_cam_rot_z.h"
#include "event/script_cam_tar.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ITodo;

ITodo *ScriptCamMotion::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamMotion; }

ITodo *ScriptCamPos::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamPos; }

ITodo *ScriptCamMovePos::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamMovePos; }

ITodo *ScriptCamTar::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamTar; }

ITodo *ScriptCamMoveTar::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamMoveTar; }

ITodo *ScriptCamFov::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamFov; }

ITodo *ScriptCamMoveFov::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamMoveFov; }

ITodo *ScriptCamRotZ::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamRotZ; }

ITodo *ScriptCamMoveRotZ::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamMoveRotZ; }

ITodo *ScriptCamNearfar::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamNearfar; }

ITodo *ScriptCamCut::exec() { return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamCut; }

ITodo *ScriptCamFollowPos::exec() {
  return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamFollowPos;
}

ITodo *ScriptCamFollowTar::exec() {
  return new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ScriptCamFollowTar;
}

} // namespace event
