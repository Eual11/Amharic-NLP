#include "../include/stemmer.hpp"
#include <codecvt>
#include <fcntl.h>
#include <iostream>
#include <locale>
#include <windows.h>

int main(void) {
  _setmode(_fileno(stdout), _O_WTEXT);
  _setmode(_fileno(stdin), _O_WTEXT);

  Stemmer stem("./input.txt");

#if 1

  int suffix_level = 1;

  int prefix_level = 1;

  bool recovery = false;
  std::wcout << "Enter Depth for suffix removal(default = 1): ";
  std::wcin >> suffix_level;

  std::wcout << "Enter Depth for prefix_level removal(default = 1): ";
  std::wcin >> prefix_level;

  std::wcout << "Enable Lexical Recovery(1 to enable 0 to disable): ";

  std::wcin >> recovery;
  std::wstring request;
  std::wcout << "Enter Word to be stem: ";
  while (std::wcin >> request) {

    std::wstring corrected =
        stem.wstring_stem(request, suffix_level, prefix_level);

    if (!recovery) {
      std::wcout << L"\033[33m stem: " << corrected << std::endl;
    } else {
      std::wcout << L"\033[33m stem: " << corrected << " Matched Recovery: "
                 << stem.recovery.Correct(corrected, 2, 1) << std::endl;
    }
    std::wcout << L"\033[00m";
    std::wcout << L"Enter Word to stem: ";
  }
#endif
}
