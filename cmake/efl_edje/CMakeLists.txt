project("Edje")
find_program(EDJE_CC edje_cc)

if (NOT EDJE_CC)
   message(FATAL_ERROR "edje_cc is missing.")
endif()

add_custom_command(OUTPUT "mytheme.edj"
   COMMAND "edje_cc" mytheme.edc)
add_custom_target(mytheme ALL DEPENDS "mytheme.edj")

