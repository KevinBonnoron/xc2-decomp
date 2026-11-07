#pragma once
#include <stddef.h>

#include "anm/anm_job_queue.h"
#include "anm/anm_pose.h"
#include "mm/mm_std_base.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace skd {

class ForceInterface;

void registerApplyDetectJobExecuter(anm::JobQueue *queue);
void registerDetectSphereJobExecuter(anm::JobQueue *queue);
void registerDetectCapsuleJobExecuter(anm::JobQueue *queue);
void registerDetectPlaneJobExecuter(anm::JobQueue *queue);

// Per-pose working buffer shared by the solvers and the detect jobs. Layout evidence: the constructor at 0x710097e1b0
// builds the JobQueue at 0x10 (its allocator at 0x38 and the function table at 0x40), sets the iteration count at
// 0x140, and the destructor at 0x710097e28c destroys the queue and the bind pose. The member name comes from the
// assertion "m_pBindPose == nullptr" in skd_packet.h.
class Packet {
public:
  Packet(mm::mtl::IAllocator *allocator, anm::Pose &pose) : m_pBindPose(nullptr), unknown08(nullptr), unknown10(allocator), unknown140(6) {
    registerApplyDetectJobExecuter(&unknown10);
    registerDetectCapsuleJobExecuter(&unknown10);
    registerDetectPlaneJobExecuter(&unknown10);
    registerDetectSphereJobExecuter(&unknown10);
#line 50
    MM_ASSERT(m_pBindPose == nullptr);
    m_pBindPose = &pose;
    pose.addRef();
  }

  ~Packet();

  anm::Pose *m_pBindPose;
  ForceInterface *unknown08; // Inferred role: force applied to the solvers; original member name unknown.
  anm::JobQueue unknown10;   // Inferred role: detect jobs; original member name unknown.
  u32 unknown140;            // Inferred role: solver iteration count; original member name unknown.
};

static_assert(offsetof(Packet, unknown08) == 0x08, "");
static_assert(offsetof(Packet, unknown10) == 0x10, "");
static_assert(offsetof(Packet, unknown140) == 0x140, "");
static_assert(sizeof(Packet) == 0x148, "");

} // namespace skd
