#include "../include/amharic_nlp.hpp"
#include <codecvt>
#include <fcntl.h>
#include <iostream>
#include <locale>
#include <windows.h>

int main(void) {
  _setmode(_fileno(stdout), _O_WTEXT);
  _setmode(_fileno(stdin), _O_WTEXT);

  amh_nlp::AmharicNLP alp;

#if 1

  int suffix_level = 1;

  int prefix_level = 1;
  bool recovery = false;
  std::wcout << "Enter Depth for suffix removal(default = 1): ";
  std::wcin >> suffix_level;

  std::wcout << "Enter Depth for prefix_level removal(default = 1): ";
  std::wcin >> prefix_level;

#ifdef ALP_ENABLE_SUGGESTION
  std::wcout << "Enable Lexical Recovery(1 to enable 0 to disable): ";
  std::wcin >> recovery
#endif
      ;
  std::wstring request;
  std::wcout << "Enter Word to be Stem: ";
  while (std::wcin >> request) {

    std::wstring corrected =
        alp.wstring_stem(request, suffix_level, prefix_level);

    if (!recovery) {
      std::wcout << L"\033[33m Stem: " << corrected << std::endl;
    } else {
      std::wcout << L"\033[33m Stem: " << corrected << "\033[32m Suggestion : "
                 << alp.suggest.Correct(corrected, 2, 1) << std::endl;
    }
    std::wcout << L"\033[00m";
    std::wcout << L"Enter Word to Stem: ";
  }
#endif
}
