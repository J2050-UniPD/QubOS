cmake_minimum_required(VERSION 3.5)
project(J2050_COMMS)
include_directories(include/)
add_executable(
  J2050_COMMS_TESTING 
  sources/main.c
  sources/libcrypt.c
  sources/libhash.c
  #sources/endian-test.c
  #sources/secrets.c
)
