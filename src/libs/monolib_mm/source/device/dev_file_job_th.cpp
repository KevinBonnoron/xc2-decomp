#include "ml/dev_file_job_th.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ml {

bool DevFileJobTh::asyncUpdate() { return true; }

int DevFileJobTh::getJobType() const { return 0; }

DevFileReaderTh *DevFileJobTh::getReader() { return nullptr; }

int DevFileReaderTh::getJobType() const { return 1; }

DevFileReaderTh *DevFileReaderTh::getReader() { return this; }

int DevFileWriterTh::getJobType() const { return 2; }

} // namespace ml

template mm::mtl::FixedList<ml::DevFileJobTh *, 640>::iterator mm::mtl::FixedList<ml::DevFileJobTh *, 640>::erase(mm::mtl::FixedList<ml::DevFileJobTh *, 640>::iterator);
