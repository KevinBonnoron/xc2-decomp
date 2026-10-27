#include "anm/anm_job.h"
#include "framework/sensor/sensor_manager.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace fw {

const char *SensorUpdateJob::_TYPE_NAME = "SensorUpdateJob";

SensorUpdateJob::SensorUpdateJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(SensorUpdateJob), 0), unknown20(count) {
  unknown10[0] = nullptr;
  unknown10[1] = nullptr;
}

void SensorUpdateJob::exec(anm::Job &job) {
  SensorUpdateJob &updateJob = static_cast<SensorUpdateJob &>(job);
  for (int i = 0; i < updateJob.unknown20; i++) {
    updateJob.unknown10[i]->unknown10();
  }
}

} // namespace fw
