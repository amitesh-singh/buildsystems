project("Edje")
find_program(EDJE_CC edje_cc)

if (NOT EDJE_CC)
   message(FATAL_ERROR "edje_cc is missing.")
endif()

add_custom_target(OUTPUT mytheme.edj
   COMMAND ${EDJE_CC} -v mytheme.edc mytheme.edj
   VERBATIM)

