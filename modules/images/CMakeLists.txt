unnecessary_module(
        images
        "include/unnecessary/graphics/image.h"
)

unnecessary_module_libraries(
        images
        lodepng
)
add_executable(
        images_test
        tests/loadtest.cpp
)
target_link_libraries(
        images_test
        unnecessary_images_s
)