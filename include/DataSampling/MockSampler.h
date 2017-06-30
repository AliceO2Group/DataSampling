///
/// \file    MockSampler.h
/// \author  Barthelemy von Haller
///

#ifndef DATA_SAMPLING_MOCKSAMPLER_H
#define DATA_SAMPLING_MOCKSAMPLER_H

#include <DataFormat/DataBlock.h>
#include <memory>
#include "SamplerInterface.h"
#include "DataBlockProducer.h"

namespace AliceO2 {
namespace DataSampling {

/// \brief Sampler that returns blocks of data with a random payload.
///
/// this data sampler returns blocks of data with a random payload.
/// The size of the payload follows a standard distribution using the default parameters of DataBlockProducer.
///
/// \author Barthelemy von Haller
class MockSampler : public SamplerInterface
{
  public:
    /// Standard Constructor
    MockSampler();
    /// Destructor
    ~MockSampler() override;

    std::vector<std::shared_ptr<DataBlockContainer>>* getData(int timeout = 0) override;
    void releaseData() override;

  private:
    DataBlockProducer *producer;
    std::vector<std::shared_ptr<DataBlockContainer>>* currentBlock;

};

}
}

#endif //DATA_SAMPLING_MOCKSAMPLER_H
