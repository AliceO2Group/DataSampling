///
/// \file    DataBlockProducer.cxx
/// \author  Barthelemy von Haller
///

#include "Common/DataBlock.h"
#include "DataSampling/DataBlockProducer.h"
#include <fstream>

using namespace std;

namespace AliceO2 {
namespace DataSampling {

DataBlockProducer::DataBlockProducer(bool random, uint32_t payloadSize) : mPayloadSize(payloadSize),
                                                                          mIsRandom(random),
                                                                          mCurrentId(0)
{
}

DataBlockProducer::~DataBlockProducer()
{
}

DataSetReference DataBlockProducer::getDataSet(unsigned int numberBlocks)
{
  DataSet set;
  DataSetReference result = make_shared<DataSet>(set);

  // Add blocks
  for (unsigned int i = 0; i < numberBlocks; i++) {
    result->push_back(getDataBlockContainer());
  }

  return result;
}

DataBlockContainerReference DataBlockProducer::getDataBlockContainer()
{
  DataBlockContainerReference result = make_shared<SelfReleasingBlockContainer>();

  // generate payload size if needed
  uint32_t payloadSize = mPayloadSize;
  if (mIsRandom) {
    std::normal_distribution<float> distribution(mPayloadSize, mPayloadSize/4);
    double temp = distribution(mGenerator);
    temp = (temp < 1) ? 1 : temp; // we don't want to cast a negative number to uint
    payloadSize = (uint32_t) temp;
  }

  // Prepare data
  result->getData()->header.blockType = 0xba; // whatever
  result->getData()->header.headerSize = 0x60; // just the header base -> 96 bits
  result->getData()->header.dataSize = payloadSize;
  result->getData()->header.id = mCurrentId++;
  char *buffer = new char[payloadSize];
  for (unsigned int i = 0; i < payloadSize; i++) {
    buffer[i] = (char) ((i % 26) + 'a');
  }
  result->getData()->data = buffer;

  return result;
}

}
}
