project(cpp_d17)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

add_executable(cpp_d17 ../Srcs/main.cpp ../Srcs/Invite/Invite.cpp ../Srcs/Invite/actionner/actionner.cpp ../Srcs/Parser/Parser.cpp ../Srcs/Validator/Validator.cpp )