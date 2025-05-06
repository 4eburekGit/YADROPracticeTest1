#include "Tape.hpp"
#include <cmath>
/* Tape sorting class that sorts input tape via binary radix sort and
 * returns the result to the output tape */

#ifndef SORT
#define SORT

class TapeSorter {
  public:
  TapeSorter(std::string inp, std::string outp,size_t rwDelay, size_t moveDelay, size_t rewindDelay);
  ~TapeSorter();
  void sort(); // sorts the tape via radix sort
  private:
    // I/O tapes
  Tape in;
  Tape out;
    // temp tapes
  Tape binMain; // Main tape used to store temp result
  Tape binOnes; // Tape that stores elements that have 1 in current radix
  Tape binZero; // Tape that stores elements that have 0 in current radix
};

#endif
