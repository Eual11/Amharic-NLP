#include "../include/amharic_nlp.hpp"
#include <fstream>
#include <ostream>
#include <sstream>
#include <windows.h>
int main(int argc, char **argv) {

  // setting the console output character point to UTF-8 for windows, the
  // default codepoint might be ascii or anything non-unicode which results in a
  // huge mess outputing the amharic character
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [file to remove stop words from]"
              << "\n";
    return 1;
  }

#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  amh_nlp::AmharicNLP alp;
  std::fstream data_file(argv[1], std::ios::in | std::ios::binary);
  std::string data_string;
  std::stringstream buffer;
  buffer << data_file.rdbuf();
  data_string = buffer.str();
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wdata_string = alp.string_to_wstring(data_string);
  std::wstring removed = alp.stopword_remove(wdata_string);
  std::string removedUTF8String = alp.wstring_to_string(removed);

  std::cout << removedUTF8String << "\n";
  return 0;
}
