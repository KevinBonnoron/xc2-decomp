#include "ml/dev_file_job_th.h"

namespace ml {

bool DevFileJobTh::asyncUpdate() { return true; }

int DevFileJobTh::getJobType() const { return 0; }

DevFileReaderTh *DevFileJobTh::getReader() { return nullptr; }

int DevFileReaderTh::getJobType() const { return 1; }

DevFileReaderTh *DevFileReaderTh::getReader() { return this; }

int DevFileWriterTh::getJobType() const { return 2; }

} // namespace ml
