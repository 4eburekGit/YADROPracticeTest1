#include "Tape.hpp"

int main(int argc, char* argv[]) {
  Tape tape(argv[1],50,50,200);
  Tape outTape(argv[2],50,50,200);
  int rd = 0;
  size_t count = 0;
  bool canForward = true;
  while (canForward) {
    rd = tape.read();
    outTape.write(rd);
    std::cout << std::hex << rd << '\n';
    std::cout.flush();
    outTape.moveForward();
    canForward = tape.moveForward();
    std::cout << '\n';
  }
  outTape.rewind();
  outTape.moveForward();
  outTape.moveForward();
  outTape.write(0xabc,false); // no delimeter because it overwrites;
  std::cout << "written\n = " << std::hex << outTape.read() << "\n\n";
  outTape.rewind();
  bool flag = true;
  while (flag) {
    std::cout << std::hex << outTape.read() << '\n';
    flag = outTape.moveForward();
  }
  std::cout << "second: \n";
  outTape.rewind();
  flag = true;
  while (flag) {
    std::cout << std::hex << outTape.read() << '\n';
    flag = outTape.moveForward();
  } 
}
