#include "../include/amharic_nlp.hpp"
#include <fstream>
#include <ostream>
#include <sstream>
int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [file to remove stop words from]"
              << "\n";
    return 1;
  }
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
