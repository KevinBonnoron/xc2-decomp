#include "anm/anm_job.h"
#include "framework/dynamics/dynamics_manager.h"
#include "types.h"

namespace fw {

const char *DynamicsUpdateJob::_TYPE_NAME = "DynamicsUpdateJob";

DynamicsUpdateJob::DynamicsUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(DynamicsUpdateJob), 1), unknown18(count), unknown20(nullptr) {}

void DynamicsUpdateJob::exec(anm::Job &job) {
  DynamicsUpdateJob &updateJob = static_cast<DynamicsUpdateJob &>(job);
  for (int i = 0; i < updateJob.unknown18; i++) {
    updateJob.unknown10[i]->update(*updateJob.unknown20);
  }
}

} // namespace fw
