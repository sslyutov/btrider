cmake -B "binary" -G "Visual Studio 16 2019"

cd "binary"

devenv "btrider.vcxproj" /Rebuild "Release|x64"

devenv "btrider.vcxproj" /Rebuild "Debug|x64"

cd ..
