///
/// \file    mockFairInjector.cxx
/// \author  Barthelemy von Haller
///

// std
#include <iostream>
#include <algorithm>
#include <vector>
// boost
#include <boost/program_options.hpp>
// o2
#include "Common/signalUtilities.h"
// datasampling
#include "DataSampling/Version.h"
#include "DataSampling/InjectorFactory.h"
//#include "DataSampling/InjectorDevice.h"
#include "DataSampling/DataBlockProducer.h"
#include "DataSampling/FairInjector.h"

using namespace std;
namespace po = boost::program_options;
using namespace AliceO2::DataSampling;

int main(int argc, char *argv[])
{
  // Arguments parsing
  po::variables_map vm;
  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "Produce help message.")("version,v", "Show program name/version banner and exit.")(
    "rev", "Print the SVN revision number");
  po::store(parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  // help
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return EXIT_SUCCESS;
  }
  // version
  if (vm.count("version")) {
    std::cout << "DataSampling version " << AliceO2::DataSampling::Version::getString() << std::endl;
    return EXIT_SUCCESS;
  }
  // rev
  if (vm.count("rev")) {
    std::cout << "Git revision : " << AliceO2::DataSampling::Version::getRevision() << std::endl;
    return EXIT_SUCCESS;
  }

  unique_ptr<InjectorInterface> dataSamplingInjector = InjectorFactory::create("FairInjector");

  unsigned int i = 0;
  DataBlockProducer producer(true /*random*/, 1024);
  signal(SIGINT, handler_interruption);
  while (keepRunning) {
    DataSetReference dataSetReference = producer.getDataSet();
    dataSamplingInjector->injectSamples(dataSetReference);

    if ((i % 10) == 0) {
      std::cout << "\rNumber of blocks produced so far : " << i;
    }
    i++;
  }
  cout << "\nexiting" << endl;

  return EXIT_SUCCESS;
}
