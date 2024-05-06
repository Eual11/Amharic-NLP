// decomposing_string_example.cpp
#include "../include/amharic_nlp.hpp"
#include <fstream>
#include <ostream>
#include <sstream>
#include <windows.h>
int main(int argc, char **argv) {

  amh_nlp::AmharicNLP alp;

  // setting the console output character point to UTF-8 for windows, the
  // default codepoint might be ascii or anything non-unicode which results in a
  // huge mess outputing the amharic character
#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  std::vector<std::wstring> words = {L"ልጅኦች",    L"ልኣይኝኣው",     L"ይንኦርኡ",
                                     L"ግኧርጥትዋል", L"እስትንፍኣስውኣም", L"ውኧጥኣትዋ"};

  std::cout << "[ ";
  for (auto word : words) {
    std::cout << alp.wstring_to_string(word) << ", ";
  }
  std::cout << "]\n";

  std::cout << "[ ";
  for (auto word : words) {
    std::wstring stem_word = alp.composeStringSyllables(word);
    std::cout << alp.wstring_to_string(stem_word) << ", ";
  }
  std::cout << "]\n";

  return 0;
}
