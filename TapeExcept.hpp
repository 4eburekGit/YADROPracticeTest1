#include <exception>

#ifndef TAPE_EXCEPT
#define TAPE_EXCEPT

// Exception for "move" methods, if trying to move beyond any end of the tape
class OutOfTapeRangeError : public std::exception {
  public:
  OutOfTapeRangeError(): reason_("Tape end reached") {};
  OutOfTapeRangeError(const char* reason): reason_(reason) {};
  const char* what() const noexcept{ return reason_; }
  private:
  const char* reason_;
};
// Exception for constructor in case of unaccessible files
class FileAccessError : public std::exception {
  public:
  FileAccessError(): reason_("File is unable to be accessed") {};
  FileAccessError(const char* reason): reason_(reason) {};
  const char* what() const noexcept{ return reason_; }
  private:
  const char* reason_;
};
#endif
