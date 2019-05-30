

boostrap.bat

MINGW:

.\b2 toolset=gcc --build-type=complete stage cxxflags="-std=c++17" -mt --with-coroutine

MSVC:

da Command Prompt di Visual Studio:

in msvc.jam sostituire VS150COMNTOOLS con VS160COMNTOOLS
.\b2 -j8 toolset=msvc --variant=release --link=static --runtime-link=static --build-type=complete stage cxxflags="/std:c++17" -mt --with-coroutine

