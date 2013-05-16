cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libjaneth-power
  VERSION 1.0
  RELEASE beta
  SUMMARY "A C++ based JanETH car power board interfacing library."
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "https://github.com/jmaye/libjaneth-power"
  LICENSE "GNU Lesser General Public License (LGPL)"
  PREFIX janeth-power-
  INSTALL /usr/
  EXTRA_CXX_FLAGS -std=c++0x
)

remake_doc(
  html
  latex
)

remake_pack_deb(
  DESCRIPTION "Main library"
)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  DEPENDS libjaneth-power
)

remake_pack_deb(
  COMPONENT console-tools
  DESCRIPTION "Console tools"
  DEPENDS libjaneth-power
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  DEPENDS libjaneth-power
)

remake_distribute_deb(
  DISTRIBUTION lucid
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen pkg-config
  PASS CMAKE_BUILD_TYPE LIBJANETH_POWER_GIT_REVISION
)

remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen pkg-config
  PASS CMAKE_BUILD_TYPE LIBJANETH_POWER_GIT_REVISION
)
