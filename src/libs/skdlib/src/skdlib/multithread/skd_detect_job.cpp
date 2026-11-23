// Original file name inferred from the job type strings and the skd_detect_info.h assertion file path.
#include <float.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_job.h"
#include "anm/anm_job_queue.h"
#include "anm/anm_pose.h"
#include "anm/anm_reference_object.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "skd/skd_collision_object.h" // IWYU pragma: keep
#include "skd/skd_detect_info.h"      // IWYU pragma: keep
#include "skd/skd_dynamics.h"
#include "skd/skd_packet.h"
#include "types.h"

namespace skd {

Packet::~Packet() { anm::unknown001(m_pBindPose); }

const char *ApplyDetectJob::_TYPE_NAME = "ApplyDetectJob";
const char *DetectCapsuleJob::_TYPE_NAME = "DetectCapsuleJob";
const char *DetectPlaneJob::_TYPE_NAME = "DetectPlaneJob";
const char *DetectSphereJob::_TYPE_NAME = "DetectSphereJob";

ApplyDetectJob::ApplyDetectJob(u16 index, NodeArray *nodes) : anm::Job(_TYPE_NAME, sizeof(ApplyDetectJob), 3), unknown10(index), unknown118(0), unknown120(nodes) {}

DetectSphereJob::DetectSphereJob(const ShpereCollObj *object, const ResNodeCollision *nodeCollision, const mm::Vec3 &position, DetectInfo *unknown30, DetectInfo *unknown38)
    : anm::Job(_TYPE_NAME, sizeof(DetectSphereJob), 0), unknown10(object), unknown18(nodeCollision), unknown20(position), unknown30(unknown30), unknown38(unknown38) {}

DetectCapsuleJob::DetectCapsuleJob(const CapsuleCollObj *object, const ResNodeCollision *nodeCollision, const mm::Vec3 &position, DetectInfo *unknown30, DetectInfo *unknown38)
    : anm::Job(_TYPE_NAME, sizeof(DetectCapsuleJob), 1), unknown10(object), unknown18(nodeCollision), unknown20(position), unknown30(unknown30), unknown38(unknown38) {}

DetectPlaneJob::DetectPlaneJob(const PlaneCollObj *object, const ResNodeCollision *nodeCollision, const mm::Vec3 &position, DetectInfo *unknown30, DetectInfo *unknown38)
    : anm::Job(_TYPE_NAME, sizeof(DetectPlaneJob), 2), unknown10(object), unknown18(nodeCollision), unknown20(position), unknown30(unknown30), unknown38(unknown38) {}

namespace {

// Inferred helper: the game has three separate 176-byte detect-job functions with this common shape; the original helper name is unknown.
template <typename Job> void unknown002(anm::Job &job) {
  Job &detectJob = static_cast<Job &>(job);
  const ResNodeCollision *nodeCollision = detectJob.unknown18;
  mm::Vec3 normal;
  if (!detectJob.unknown10->detect(nodeCollision->unknown08, detectJob.unknown20, &normal)) {
    return;
  }
  if (detectJob.unknown30 != nullptr) {
    detectJob.unknown30->unknown10 = normal * (1.0f - nodeCollision->unknown04);
    detectJob.unknown30->unknown20 = true;
  }
  if (detectJob.unknown38 != nullptr) {
    detectJob.unknown38->unknown10 = normal * nodeCollision->unknown04;
    detectJob.unknown38->unknown20 = true;
  }
}

// Inferred helper: appends the hit entry of a node unless the node has flag bit 0 set, else returns nullptr; the
// original name is unknown. The index is a reference: the game reloads it after the append (0x7100982f9c).
DetectInfo *unknown003(const NodeArray *nodes, const u16 &index, DetectInfoBuffer *buffer) {
  if (((*nodes->unknown00)[index].unknown24 & 1) != 0) {
    return nullptr;
  }
  DetectInfo *info = buffer->unknown001();
  info->unknown00 = index;
  return info;
}

} // namespace

// addDetectSphereJob, addDetectCapsuleJob and addDetectPlaneJob stay written out. A template helper for them was tried,
// but it gives addDetect*Job a 0x160 frame against the game's 0x1a0.
void addDetectCapsuleJob(const CapsuleCollObj *object, const ResNodeCollision *nodeCollision, const NodeArray *nodes, const mm::Vec3 &position, DetectInfoBuffer *buffer, anm::JobQueue *queue) {
  if ((nodeCollision->unknown0c & (1u << object->unknown00->unknown18)) == 0) {
    return;
  }
  DetectCapsuleJob job(object, nodeCollision, position, unknown003(nodes, nodeCollision->unknown00, buffer), unknown003(nodes, nodeCollision->unknown02, buffer));
  queue->unknown001(job);
}

void addDetectPlaneJob(const PlaneCollObj *object, const ResNodeCollision *nodeCollision, const NodeArray *nodes, const mm::Vec3 &position, DetectInfoBuffer *buffer, anm::JobQueue *queue) {
  if ((nodeCollision->unknown0c & (1u << object->unknown00->unknown18)) == 0) {
    return;
  }
  DetectPlaneJob job(object, nodeCollision, position, unknown003(nodes, nodeCollision->unknown00, buffer), unknown003(nodes, nodeCollision->unknown02, buffer));
  queue->unknown001(job);
}

void addDetectSphereJob(const ShpereCollObj *object, const ResNodeCollision *nodeCollision, const NodeArray *nodes, const mm::Vec3 &position, DetectInfoBuffer *buffer, anm::JobQueue *queue) {
  if ((nodeCollision->unknown0c & (1u << object->unknown00->unknown18)) == 0) {
    return;
  }
  DetectSphereJob job(object, nodeCollision, position, unknown003(nodes, nodeCollision->unknown00, buffer), unknown003(nodes, nodeCollision->unknown02, buffer));
  queue->unknown001(job);
}

void executeApplyDetectJob(anm::Job &job) {
  ApplyDetectJob &applyJob = static_cast<ApplyDetectJob &>(job);
  mm::Vec3 offset = mm::Vec3::zero;
  f32 count = 0.0f;
  const DetectInfo *const *hit = applyJob.unknown18;
  const DetectInfo *const *end = hit + applyJob.unknown118;
  for (; hit != end; hit++) {
    const DetectInfo *info = *hit;
    offset += info->unknown10;
    count += 1.0f;
  }
  if (count > FLT_EPSILON) {
    offset *= 1.0f / count;
    applyJob.unknown120->unknown10[applyJob.unknown10].unknown50 += offset;
  }
}

void executeDetectSphereJob(anm::Job &job) { unknown002<DetectSphereJob>(job); }

void executeDetectCapsuleJob(anm::Job &job) { unknown002<DetectCapsuleJob>(job); }

void executeDetectPlaneJob(anm::Job &job) { unknown002<DetectPlaneJob>(job); }

void registerApplyDetectJobExecuter(anm::JobQueue *queue) { queue->registerJobExecuter(3, executeApplyDetectJob); }
void registerDetectSphereJobExecuter(anm::JobQueue *queue) { queue->registerJobExecuter(0, executeDetectSphereJob); }
void registerDetectCapsuleJobExecuter(anm::JobQueue *queue) { queue->registerJobExecuter(1, executeDetectCapsuleJob); }
void registerDetectPlaneJobExecuter(anm::JobQueue *queue) { queue->registerJobExecuter(2, executeDetectPlaneJob); }

} // namespace skd
