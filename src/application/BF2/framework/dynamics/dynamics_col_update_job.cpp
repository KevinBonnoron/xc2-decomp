#include "anm/anm_job.h"
#include "framework/dynamics/dynamics_manager.h"
#include "types.h"

namespace fw {

const char *DynamicsColUpdateJob::_TYPE_NAME = "DynamicsColUpdateJob";

DynamicsColUpdateJob::DynamicsColUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(DynamicsColUpdateJob), 0), unknown18(count) {}

void DynamicsColUpdateJob::exec(anm::Job &job) {
  DynamicsColUpdateJob &colUpdateJob = static_cast<DynamicsColUpdateJob &>(job);
  for (int i = 0; i < colUpdateJob.unknown18; i++) {
    colUpdateJob.unknown10[i]->update();
  }
}

} // namespace fw
