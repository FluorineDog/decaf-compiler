# run this script after "git clone ..."
mkdir -p build
mkdir -p kernel/generated/template
mkdir -p parser/generated/template
mkdir -p lexer/generated/template
cd kernel
python3 visitor_gen.py
cd ..
cd build
cmake ..
cd ..

