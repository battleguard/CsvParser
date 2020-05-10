cmake_minimum_required(VERSION 3.12)

project(CsvParser)

file(GLOB SRCS *.cpp *.hpp)

add_executable(CsvParser ${SRCS})