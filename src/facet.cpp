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
std::string u32string_to_string(const std::u32string &u32str) {
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

  std::string outstring = converter.to_bytes(u32str);
  return outstring;
}

int main() {

  _setmode(_fileno(stdin), _O_WTEXT);

  std::wcout << L"Type String: ";
  std::wstring inputString;
  std::getline(std::wcin, inputString);

  std::wcout << "size of wchar_t is " << sizeof(wchar_t) << "\n";
  std::wcout << inputString << std::endl;

  std::u32string codepoitns = wstring_to_u32string(inputString);

  constexpr int size = sizeof(codepoitns) / sizeof(char32_t);

  std::string str(codepoitns.begin(), codepoitns.end());
  std::system("chcp 65001");

  for (int i = 0; i < size && codepoitns[i]; i++)
    std::cout << "U+" << std::hex << static_cast<unsigned int>(codepoitns[i])
              << " ";
  std::cout << std::endl;

  str = u32string_to_string(codepoitns);
  std::cout << str << std::endl;
  return 0;
}
