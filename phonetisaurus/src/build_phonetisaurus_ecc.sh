#/bin/sh

rm *.js
emcc -O3 Phonetisaurus.cpp FstPathFinder.cpp MBRDecoder.cpp LatticePruner.cpp util.cpp phonetisaurus-moz.cpp -o phonetisaurus-moz.html openfst.o -I3rdparty/sparsehash -I3rdparty/utfcpp  -I. -I../../openfst-1.4.1/src/include -lfst -ldl -lm -lrt -v -lstdc++  -std=c++11 -s TOTAL_MEMORY=67108864 -s NO_EXIT_RUNTIME=1 --preload-file asset_dir   
