#pragma once

namespace ml {

class DevFileReaderTh;

class DevFileJobTh {
public:
  virtual bool asyncUpdate();
  virtual int getJobType() const;
  virtual DevFileReaderTh *getReader();
};

class DevFileReaderTh : public DevFileJobTh {
public:
  int getJobType() const override;
  DevFileReaderTh *getReader() override;
};

class DevFileWriterTh : public DevFileJobTh {
public:
  int getJobType() const override;
};

} // namespace ml
