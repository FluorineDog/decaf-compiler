which gcc > /dev/null || { echo "latest gcc is required" ; exit -1 ;};
which clang > /dev/null || { echo "latest clang is required" ; exit -2 ;};
which llc > /dev/null || { echo "latest LLVM toolchain is required" ; exit -3 ;};
which flex > /dev/null || { echo "latest flex is required" ; exit -4 ;};
which bison > /dev/null || { echo "latest bison is required"; exit -5 ;};
which python3 > /dev/null || { echo "latest python3 is required" && exit -6 ;};
mkdir -p build
mkdir -p kernel/generated/template
mkdir -p parser/generated/template
mkdir -p lexer/generated/template
cd kernel > /dev/null
python3 visitor_gen.py > /dev/null || { echo "error with python" && exit -7 ;};
cd ..
cd build 
cmake ..
cd ..
