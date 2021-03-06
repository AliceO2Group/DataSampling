///
/// \file   FileSampler.cxx
/// \author Barthelemy von Haller
///

#include "DataSampling/FileSampler.h"

#include <fstream>
#include <memory.h>

using namespace std;

namespace AliceO2 {
namespace DataSampling {

FileSampler::FileSampler()
{
}

FileSampler::~FileSampler()
{
}

std::string FileSampler::getFilePath()
{
  return getLocation().substr(5);
}

DataSetReference FileSampler::getData(int timeout)
{
  // TODO redo
  cout << "DataSampling::getData " << endl;
  string filePath = getFilePath();
  cout << "filePath : " << filePath << endl;
  auto *result = new DataBlock();
  ifstream file(filePath, ios::in | ios::binary);
  file.read((char*) &result->header, sizeof(DataBlockHeaderBase));
  cout << "blockType : " << std::hex << result->header.blockType << endl;
  cout << "headerSize : " << std::hex << result->header.headerSize << endl;
  cout << "payload size : " << std::dec << result->header.dataSize << endl;

  size_t dataSizeBytes = result->header.dataSize / 8;
  cout << "dataSizeBytes : " << dataSizeBytes << endl;
  char buffer[dataSizeBytes];
  file.read(buffer, dataSizeBytes);
  cout << "buffer : " << buffer << endl;
  file.close();
  result->data = new char[dataSizeBytes];
  memcpy (result->data, buffer, dataSizeBytes);
  cout << "data : " << result->data << endl;

  DataSetReference dataSetReference = nullptr;
  return dataSetReference;
}
void FileSampler::releaseData()
{
  cout << "DataSampling::releaseData : " << endl;
}

} /* namespace Utilities */
} /* namespace AliceO2 */
