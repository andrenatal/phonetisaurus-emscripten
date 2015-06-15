#/bin/sh

#reset && g++ Phonetisaurus.o FstPathFinder.o MBRDecoder.o LatticePruner.o util.o  phonetisaurus-moz.cpp -o phonetisaurus-moz -std=c++11 -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src/3rdparty/sparsehash -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src/3rdparty/utfcpp -I/usr/local/include -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src -lfst -ldl -lm -lrt


reset && g++ Phonetisaurus.cpp FstPathFinder.cpp MBRDecoder.cpp LatticePruner.cpp util.cpp  phonetisaurus-moz.cpp -o phonetisaurus-moz -std=c++11 -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src/3rdparty/sparsehash -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src/3rdparty/utfcpp -I/usr/local/include -I/home/andre/projetos/phonetisaurus-0.8a/phonetisaurus/src -lfst -ldl -lm -lrt
