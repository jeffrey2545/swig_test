// 所有指令
swig -java -c++ CarWrapper.i

g++ -fPIC -c -g -O0 -std=c++17 -pedantic-errors -I. \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux \
    $(python3-config --cflags) CarWrapper_wrap.cxx CarWrapperImpl.cpp

g++ -fno-lto CarWrapper_wrap.o CarWrapperImpl.o -o libCarWrapper.so \
    -shared \
    -I. -I/anaconda/envs/py37_default/include/python3.7m \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux \
    $(python3-config --ldflags)

javac Test.java

java Test

// 文字描述步驟
At the beginning, there are 5 files in the repo, "carClass.py", "CarWrapper.i", "CarWrapper.cpp", "CarWrapperImpl.cpp", "Test.java"

Next, I generate SWIG wrapper by enter
swig -java -c++ CarWrapper.i
Then I got "CarWrapper_wrap.cxx", "CarWrapper.java", "CarWrapperJNI.java", "SWIGTYPE_p_PyObject.java"

Next, I compile C++ code into object files by enter
g++ -fPIC -c -g -O0 -std=c++17 -pedantic-errors -I. \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux \
    $(python3-config --cflags) CarWrapper_wrap.cxx CarWrapperImpl.cpp
Then I got "CarWrapper_wrap.o", "CarWrapperImpl.o"

Next, I link object files to create a shared library by enter
g++ -fno-lto CarWrapper_wrap.o CarWrapperImpl.o -o libCarWrapper.so \
    -shared \
    -I. -I/anaconda/envs/py37_default/include/python3.7m \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include \
    -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux \
    $(python3-config --ldflags)
Then I got "libCarWrapper.so"

Next, I compile Java code by enter
javac Test.java
Then I got "CarWrapper.class", "CarWrapperJNI.class", "SWIGTYPE_p_PyObject.class", "Test.class"

Next, I run the Test by enter
java Test