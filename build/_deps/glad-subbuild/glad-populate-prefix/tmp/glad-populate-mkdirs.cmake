# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ray/projects/c/RONG/build/_deps/glad-src"
  "/home/ray/projects/c/RONG/build/_deps/glad-build"
  "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix"
  "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/tmp"
  "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp"
  "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/src"
  "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ray/projects/c/RONG/build/_deps/glad-subbuild/glad-populate-prefix/src/glad-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
