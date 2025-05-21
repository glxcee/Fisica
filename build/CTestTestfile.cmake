# CMake generated Testfile for 
# Source directory: /home/rugs/desk/Fisica
# Build directory: /home/rugs/desk/Fisica/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[project.t]=] "/home/rugs/desk/Fisica/build/Debug/project.t")
  set_tests_properties([=[project.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/rugs/desk/Fisica/CMakeLists.txt;36;add_test;/home/rugs/desk/Fisica/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[project.t]=] "/home/rugs/desk/Fisica/build/Release/project.t")
  set_tests_properties([=[project.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/rugs/desk/Fisica/CMakeLists.txt;36;add_test;/home/rugs/desk/Fisica/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[project.t]=] "/home/rugs/desk/Fisica/build/RelWithDebInfo/project.t")
  set_tests_properties([=[project.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/rugs/desk/Fisica/CMakeLists.txt;36;add_test;/home/rugs/desk/Fisica/CMakeLists.txt;0;")
else()
  add_test([=[project.t]=] NOT_AVAILABLE)
endif()
