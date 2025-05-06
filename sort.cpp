#include "TapeSort.hpp"
#include <limits>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "invalid number of args\n"; 
    return 1;
  }
  size_t rwDelay,moveDelay, rewindDelay;
  std::ifstream config;
  config.open("config.txt");
  if (!config.is_open()) {
    std::cerr << "Unable to locate config.txt file, using default settings instead\n";
    rwDelay = 50;
    moveDelay = 200;
    rewindDelay = 1000;
  }
  else {
    std::string line;
    size_t n = 0;
    std::getline(config, line, '\n');
    n = line.find("rwDelay = ");
    if (n == std::string::npos) {
      std::cerr << "Config file missing rwDelay, defaulting to 50 ms\n";
      rwDelay = 50;
    }
    else rwDelay = std::stoll(line.substr(n+10));
    std::getline(config, line, '\n');
    n = line.find("moveDelay = ");
    if (n == std::string::npos) {
      std::cerr << "Config file missing moveDelay, defaulting to 100 ms\n";
      rwDelay = 100;
    }
    else moveDelay = std::stoll(line.substr(n+12));
    std::getline(config, line, '\n');
    n = line.find("rewindDelay = ");
    if (n == std::string::npos) {
      std::cerr << "Config file missing rewindDelay, defaulting to 1s\n";
      rewindDelay = 1000;
    }
    else rewindDelay = std::stoll(line.substr(n+14));
  }
  std::cout << rwDelay << ' ' << moveDelay << ' ' << rewindDelay << '\n';
  // Tests for file existence
  try {
    Tape input = Tape(argv[1],rwDelay,moveDelay,rewindDelay);  // input wrapper for input tape
    Tape output = Tape(argv[2],rwDelay,moveDelay,rewindDelay); // outside wraper for output tape
    // TapeSorter object
    TapeSorter ts = TapeSorter(argv[1],argv[2],rwDelay,moveDelay,rewindDelay);
    // imbuing hexadecimal output for integers
    std::cout << std::hex;
    // Initial tape
    bool flag = true;
    std::cout << "Initial array:\n";
    input.rewind();
    while (flag) {
      std::cout << input.read() << '\n';
      flag = input.moveForward();
    }
    ts.sort();
    flag = true;
    output.rewind();
    while (flag) {
      std::cout << output.read() << '\n';
      flag = output.moveForward();
    }
  }
  catch (FileAccessError e) {
    std::cout << e.what() << ' ' << "Input or Output does not exist\n";
  }
}
