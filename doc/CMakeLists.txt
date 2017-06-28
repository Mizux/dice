# add a target to generate API documentation with Doxygen
include(doxygen)
BUILD_DOXYGEN(${PROJECT_NAME} Dice_doc DiceApp_doc)
