cmake_minimum_required (VERSION 2.6)
project (mEngine)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Mathematica" ${CMAKE_MODULE_PATH})

find_package(Mathematica)
# find_package(Matlab)
set (MATLAB_INCLUDE_DIRS /Applications/MATLAB_R2010b.app/extern/include .)
set (MATLAB_LIBRARIES /Applications/MATLAB_R2010b.app/bin/maci64)

include_directories(${Mathematica_INCLUDE_DIRS} ${MATLAB_INCLUDE_DIRS})
link_directories(${MATLAB_LIBRARIES})

Mathematica_MathLink_add_executable (mEngineLowLevel template.tm close.c cmd.c get.c isopen.c open.c put.c util.c vis.c Eng.c mlMain.c)
set_target_properties(mEngineLowLevel PROPERTIES FOLDER "MathLink")
list (APPEND _Targets mEngineLowLevel)


# export mprep header and trailer code for the current target platform
#Mathematica_MathLink_MPREP_EXPORT_FRAMES(
    #OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/mprep-frames"
    #SYSTEM_ID ${Mathematica_SYSTEM_ID})

# fix MathLink shared library references under Mac OS X
Mathematica_ABSOLUTIZE_LIBRARY_DEPENDENCIES(mEngineLowLevel)


file (COPY "${CMAKE_CURRENT_SOURCE_DIR}/mEngine.exe" "${CMAKE_CURRENT_SOURCE_DIR}/mEngine.m" "${CMAKE_CURRENT_SOURCE_DIR}/mEngine.nb" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" FILE_PERMISSIONS USE_SOURCE_PERMISSIONS)


file (COPY "${CMAKE_CURRENT_SOURCE_DIR}/mEngine.m" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file (COPY "${CMAKE_CURRENT_SOURCE_DIR}/mEngine.nb" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(mEngineLowLevel mx eng)

install (TARGETS mEngineLowLevel DESTINATION "${Mathematica_USERBASE_DIR}/Applications/")
install (FILES mEngine.exe mEngine.m DESTINATION "${Mathematica_USERBASE_DIR}/Applications/" PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE)