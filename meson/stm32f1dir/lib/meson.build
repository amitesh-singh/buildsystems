foolib = static_library('foo', ['dummy.h', 'dummy.cpp'],
                       cpp_args: stm32f1cargs ,
                       link_args: stm32f1linkargs,
                       include_directories : libocm3_incdir,
                       dependencies: [libocm3lib_dep],
                       pic: false)
include_directories('.')
