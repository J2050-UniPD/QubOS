cmake_minimum_required(VERSION 3.5)
project(J2050_COMMS)
include_directories(include/)
add_executable(
  J2050_COMMS_TESTING 
  libcrypt.c
  libhash.c
  main.c
  protocol.c
  Rope.c
  secrets.c
)
