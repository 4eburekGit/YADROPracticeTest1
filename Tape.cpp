#include "Tape.hpp"

Tape::Tape(std::string fileName, size_t rwDelay, size_t moveDelay, size_t rewindDelay) {
  this->rwDelay = rwDelay;
  this->moveDelay = moveDelay;
  this->rewindDelay = rewindDelay;
  file.open(fileName, file.in | file.out);
  if (!file.is_open()) {
    throw FileAccessError("@Tape::Tape - Unable to open file");
  }
}

Tape::~Tape() {
  file.close();
}

bool Tape::moveForward() {
  std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
  if (file.peek() == EOF) return false;
  char pval = 0;
  while (pval != '\n') {
    pval = file.peek();
    if (pval == '\n') {
      file.seekp(1,std::ios_base::cur); 
      if (file.peek() == '\n') {
        return false;
      }
      return true;
    }
    file.seekp(1,std::ios_base::cur);
  }
  return true;
}

bool Tape::moveBackward() {
  std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
  if (file.tellp() == std::ios::pos_type(0)) return false;
  char pval = 0;
  file.seekp(-2,std::ios_base::cur);
  while (pval != '\n') {
    pval = file.peek();
    if (pval == '\n') {
      file.seekp(1,std::ios_base::cur);
      return true;
    }
    if (file.tellp() == std::ios::pos_type(0)) {
      return false;
    }
    file.seekp(-1,std::ios_base::cur);
  }
  return true;
}

void Tape::rewind() {
  std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay));
  file.seekp(0);
}

int Tape::read() {
  std::this_thread::sleep_for(std::chrono::milliseconds(rwDelay));
  if (file.peek() == EOF) return 0;
  std::string buff = "";
  auto pos = file.tellp();
  char pval = 1;
  while (pval !='\n') {
    pval = file.peek();
    if (pval != '\n') {
      buff.push_back(pval);
      file.seekp(1,std::ios_base::cur);
    }
  }
  file.seekp(pos);
  int res = 0;
  try {
    res = std::stoi(buff,0,16);
  }
  catch (std::invalid_argument e) {
    std::cerr << "Invalid argument in input file at string" << buff << '\n';
  }
  return res;
}

void Tape::write(int thing,bool addDelim) {
  std::this_thread::sleep_for(std::chrono::milliseconds(rwDelay));
  auto pos = file.tellp();
  std::stringstream buf;
  buf << std::hex << thing;
  std::string buff = buf.str();
  while (buff.length()<8) {
    buff.insert(0,1,'0');
  }
  buff.push_back('\n');
  buff.insert(0,"0x",0,2);
  file << buff;
  if (addDelim) file << '\n';
  file.seekp(pos);
}
