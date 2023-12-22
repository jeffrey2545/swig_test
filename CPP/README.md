g++ -fPIC -g -O0 -std=c++17 -pedantic-errors -I. \
    Test.cpp ManagementWrapperImpl.cpp \
    $(python3-config --ldflags --embed) \
    $(python3-config --cflags) \
    -o Test