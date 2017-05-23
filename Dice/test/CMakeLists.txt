set(NAME Dice_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
target_link_libraries(${NAME} Catch Dice)
add_test(NAME ${NAME} COMMAND ${NAME})
add_test(NAME Dice::Stat COMMAND ${NAME} \[Stat\])
add_test(NAME Dice::Face COMMAND ${NAME} \[Face\])
add_test(NAME Dice::Die COMMAND ${NAME} \[Die\])
add_test(NAME Dice::Dice COMMAND ${NAME} \[Dice\])
add_test(NAME Dice::Roll COMMAND ${NAME} \[Roll\])
