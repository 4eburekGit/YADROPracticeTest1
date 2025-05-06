#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include "TapeExcept.hpp"

#ifndef TAPE
#define TAPE

// Wrapper around opened file stream that emulates magnetic tapes containing 32-bit integers
// writen in hexadecimal

/* For simplicity and better performance it requiress input file to be:
 * 1) 1 hexadecimal 32-bit integer per line
 * 2) No other symbols except 0..9,A..F
 * 3) File ends with \n
 * Preferably all the hexadecimals are to be written with ALL the preceding zeros (e.g. 0x00ABCDEF)
 * as this is how the output file will look like
 */

class Tape {
  public:
  // Constructors
  // Construct a Tape instance from input file 
  Tape(std::string fileName, size_t rwDelay, size_t moveDelay, size_t rewindDelay);
  ~Tape();
  // Move methods return whether it is possible to move any further in that direction
  bool moveForward();         // move 1 space forward
  bool moveBackward();        // move 1 space backward
  void rewind();              // return to the start
  int read();             // read from current position
  void write(int thing,bool addDelim = true);  // write on current position
  private:
  // Read/Write and Move commands delays given in:
  size_t rwDelay;       // read/write,ms
  size_t moveDelay;     // move,ms
  size_t rewindDelay;   // rewind,ms
  // fstream for file manipulations
  std::fstream file;
};
#endif
