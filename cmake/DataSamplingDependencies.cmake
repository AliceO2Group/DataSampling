find_package(Boost 1.59 COMPONENTS thread system timer program_options random filesystem chrono exception regex serialization log log_setup unit_test_framework date_time signals REQUIRED)
find_package(Common REQUIRED)
find_package(InfoLogger REQUIRED)

find_package(FairRoot REQUIRED)
find_package(FairMQInFairRoot) # DEPRECATED: This looks for FairMQ embedded in old FairRoot versions,
# before FairMQ and FairLogger have moved to separate repos.
# Remove this line, once we require FairMQ 1.2+.
if(NOT FairMQInFairRoot_FOUND) # DEPRECATED: Remove this condition, once we require FairMQ 1.2+
    find_package(FairMQ REQUIRED)
    find_package(FairLogger REQUIRED)
endif()

# this should go away when fairrot provides a proper Find script or proper config scripts
# See : http://www.cmake.org/cmake/help/v3.0/command/link_directories.html
link_directories(${FAIRROOT_LIBRARY_DIR}     )
ADD_DEFINITIONS(-DWITH_FAIRROOT)

get_target_property(_boost_incdir Boost::boost INTERFACE_INCLUDE_DIRECTORIES)

find_package(Git QUIET)

if(FairMQInFairRoot_FOUND)
    # DEPRECATED: Remove this case, once we require FairMQ 1.2+
    get_target_property(_fairmq_incdir FairRoot::FairMQ INTERFACE_INCLUDE_DIRECTORIES)
    o2_define_bucket(NAME fairmq_bucket
            DEPENDENCIES FairRoot::FairMQ
            INCLUDE_DIRECTORIES ${_boost_incdir} ${_fairmq_incdir}
            )
else()
    get_target_property(_fairmq_incdir FairMQ::FairMQ INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(_fairlogger_incdir FairLogger::FairLogger INTERFACE_INCLUDE_DIRECTORIES)
    o2_define_bucket(NAME fairmq_bucket
            DEPENDENCIES FairMQ::FairMQ
            INCLUDE_DIRECTORIES ${_boost_incdir} ${_fairmq_incdir} ${_fairlogger_incdir}
            )
    set(_fairlogger_incdir)
endif()

o2_define_bucket(
  NAME
  o2_datasampling_bucket

  DEPENDENCIES
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY_DEBUG}
  ${Boost_LOG_LIBRARY_DEBUG}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Common_LIBRARIES}
  ${InfoLogger_LIBRARIES}
  pthread

  SYSTEMINCLUDE_DIRECTORIES
  ${Boost_INCLUDE_DIRS}
  ${Common_INCLUDE_DIRS}
  ${InfoLogger_INCLUDE_DIRS}
)

o2_define_bucket(
  NAME
  o2_datasampling_bucket_with_fair

  DEPENDENCIES
  o2_datasampling_bucket
  fairmq_bucket

  SYSTEMINCLUDE_DIRECTORIES
  ${Boost_INCLUDE_DIR}
  ${FAIRROOT_INCLUDE_DIR}
  ${FAIRROOT_INCLUDE_DIR}/fairmq
)
