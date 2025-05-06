#include "TapeSort.hpp"

TapeSorter::TapeSorter(std::string inp, std::string outp, size_t rwDelay, size_t moveDelay, size_t rewindDelay):
  in{inp,rwDelay,moveDelay,rewindDelay},
  out{outp,rwDelay,moveDelay,rewindDelay},
  binMain{std::string("tmp/binMain.txt"),rwDelay,moveDelay,rewindDelay},
  binOnes{std::string("tmp/binOnes.txt"),rwDelay,moveDelay,rewindDelay},
  binZero{std::string("tmp/binZero.txt"),rwDelay,moveDelay,rewindDelay}
{}

TapeSorter::~TapeSorter() {}

void TapeSorter::sort() {
  bool flag = true;
  int temp = 0;
  binMain.rewind();
  in.rewind();
  while (flag) {
    temp = in.read();
    binMain.write(temp);
    binOnes.write(0);
    binZero.write(0);
    flag = in.moveForward();
    binMain.moveForward();
    binZero.moveForward();
    binOnes.moveForward();
  }
  size_t countOnes = 0;
  size_t countZero = 0;
  for (size_t radix = 0; radix<32; radix++) {
    binMain.rewind();
    binOnes.rewind();
    binZero.rewind();
    flag = true;
    countOnes = 0;
    countZero = 0;
    while(flag) { // initial fill binMain <- in, binZero <- 0, binOnes <- 0
      temp = binMain.read();
      int sign = (temp & int(std::pow(2,radix))); // sign check (if specific radix != 1it should be zero)
      if (sign != 0) {
        countOnes++;
        binOnes.write(temp,false);
        binOnes.moveForward();
      }
      else {
        countZero++;
        binZero.write(temp,false);
        binZero.moveForward();
      }
      flag = binMain.moveForward();
    }
    // in increasing order so:
    binMain.rewind();
    binZero.rewind();
    binOnes.rewind();
    // std::cout << radix << '\n';
    for (size_t i = countZero; i>0 ; i--) {
      temp = binZero.read();
      binZero.write(0,false);
      binZero.moveForward();
      // std::cout << "zeros " << int(temp) << '\n'; // temp output for debugging/non "black box" mode
      binMain.write(temp,false);
      binMain.moveForward();
    }
    for (size_t i = countOnes; i>0 ; i--) {
      temp = binOnes.read();
      binOnes.write(0,false);
      binOnes.moveForward();
      // std::cout << "ones " << int(temp) << '\n'; // likewise
      binMain.write(temp,false);
      binMain.moveForward();
    }
    // std::cout << '\n';
  }
  flag = true;
  binMain.rewind();
  while(flag) { // final output
    out.write(binMain.read());
    flag = binMain.moveForward();
    out.moveForward();
  }
}
