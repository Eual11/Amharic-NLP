// #include <corecrt_wstdio.h>
#include <codecvt>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <regex>
#include <string>

std::u32string wstring_to_u32string(const std::wstring &wstr) {
  std::u32string u32str;
  u32str.resize(wstr.size());
  for (size_t i = 0; i < wstr.size(); ++i) {
    u32str.insert(u32str.begin() + i, static_cast<uint32_t>(wstr[i]));
  }
  return u32str;
}

int main() {

  _setmode(_fileno(stdin), _O_WTEXT);
  _setmode(_fileno(stdout), _O_WTEXT);

  std::wcout << L"Type String: ";
  std::wstring inputString;
  std::getline(std::wcin, inputString);

  std::wcout << "size of wchar_t is " << sizeof(wchar_t) << "\n";
  std::wcout << inputString << std::endl;

  _setmode(_fileno(stdout), _O_TEXT);
  std::cout << "hey" << std::endl;
  std::u32string codepoitns = wstring_to_u32string(inputString);

  std::wregex pattern(L"ሰው");

  if (std::regex_match(inputString, pattern)) {
    std::cout << "man\n";
  }
  constexpr int size = sizeof(codepoitns) / sizeof(char32_t);

  for (int i = 0; i < size && codepoitns[i]; i++)
    std::cout << "U+" << std::hex << static_cast<unsigned int>(codepoitns[i]);

  return 0;
}
