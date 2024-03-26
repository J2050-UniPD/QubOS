cmake_minimum_required(VERSION 3.5)
project(J2050_COMMS)
include_directories(include/)
add_executable(
  J2050_COMMS_TESTING 
  #sources/libcrypt.c
  #sources/libhash.c
  ##sources/hashing_test.c
  #sources/simulation_test.c
  sources/endian-test.c
  #sources/protocol.c
  #sources/Rope.c
  #sources/secrets.c
)
