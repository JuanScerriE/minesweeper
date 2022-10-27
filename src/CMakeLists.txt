# src CMakeLists.txt

add_executable(minesweeper
    Main.cpp
)

target_link_libraries(minesweeper
    minesweeper1
)


# if(UNIX)
#   if (NOT APPLE)
#     # target_compile_options(editor PRIVATE "-ldl;-lpthread;-lX11;-lXxf86vm;-lXrandr;-lXi")
#   endif()
# endif()
