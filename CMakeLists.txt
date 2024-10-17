cmake_minimum_required(VERSION 3.10)
project(Sand)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES "src/*.cpp")

set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(SDL_INCLUDE C:/SDL2/include)
set(SDL_LIB_DIR C:/SDL2/lib)

add_executable(Sand ${SRC_FILES})

if(WIN32)
  target_include_directories(Sand 
    PRIVATE
      include
      ${SDL_INCLUDE}
  )
  target_link_libraries(Sand 
    mingw32
    ${SDL_LIB_DIR}/libSDL2main.a
    ${SDL_LIB_DIR}/libSDL2.a
    winmm
    dinput8
    dxguid
    dxerr8
    ole32
    oleaut32
    imm32
    version
    setupapi
  )
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -mwindows")
elseif(UNIX)
  target_include_directories(Sand PRIVATE include)
  target_link_libraries(Sand SDL2main SDL2)
endif()
