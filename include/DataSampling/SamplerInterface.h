///
/// \file   SamplerInterface.h
/// \author Barthelemy von Haller
///

#ifndef DATASAMPLING_LIBS_DATASAMPLING_SAMPLERINTERFACE_H_
#define DATASAMPLING_LIBS_DATASAMPLING_SAMPLERINTERFACE_H_

#include <string>
#include <iostream>

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#include <memory>
#include <vector>
#include <Common/DataSet.h>

namespace AliceO2 {
namespace DataSampling {

/// \brief Outputs the value of an enum class in c++11.
///
/// Usage :
/// \code
/// enum class A {
///   a = 1,
///   b = 69,
///   c= 666
/// };
/// int main () {
///   A a = A::c;
///   cout << a << endl;
/// }
/// \endcode
///
/// \param stream
/// \param e
/// \return
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

enum class Policy {Must, Percent, Most};
enum class DataFormat {Raw, STF, TF, CTF, AOD, ESD};

/// \brief  Interface for all data sampler classes.
///
/// Data sampler are used to get a data blocks from various sources and following a number of filters and policies.
///
/// \author Barthelemy von Haller
class SamplerInterface
{
  public:
    /// Default constructor
    SamplerInterface();
    /// Standard constructor
    SamplerInterface(std::string Uri);
    /// Destructor
    virtual ~SamplerInterface();

    virtual DataSetReference getData(int timeout) = 0; // TODO add specific types ? what do we get back ?

    virtual void releaseData() = 0;
    void setLocation(std::string Uri);
    std::string getLocation() const;
    void setPolicy(Policy policy);
    Policy getPolicy() const;
    void setDataFormat(DataFormat format);
    void setDataFormat(std::string format);
    DataFormat getDataFormat() const;
//    void setFilter();

  private:
    std::string mLocation;
    Policy mPolicy;
    DataFormat mFormat;
};

} /* namespace DataSampling */
} /* namespace AliceO2 */

#endif /* DATASAMPLING_LIBS_DATASAMPLING_SAMPLERINTERFACE_H_ */
