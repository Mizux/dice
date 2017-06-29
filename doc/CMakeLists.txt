# add a target to generate API documentation with Doxygen
include(doxygen)
BUILD_DOC(${PROJECT_NAME} Dice_doc DiceApp_doc)
