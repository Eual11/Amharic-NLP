#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdint.h>
// isVowel
// checks if the given amharic character is vowel or not
bool isVowel(const char32_t ch);
// checks if the given amharic character is consonant or not
bool isConsonant(const char32_t ch);
// checks
bool isSyllable(const char32_t ch);
bool isAhaz(const char32_t ch);
bool isKuter(const char32_t ch);
bool isAbukuter(const char32_t ch);
bool isCombiningMark(const char32_t ch);
bool isReserved(const char32_t ch); // used for reserverd codepoints in the
                                    // first ethiopic block
bool isPunctuation(const char32_t ch);

std::u32string wstring_to_u32string(const std::wstring &wstr);
int main() {

  _setmode(_fileno(stdout), _O_WTEXT);
  std::wstring ha = L"አኡ፲፳፴፵፪፫፬፭ልሥዖዥ፨እኦ";

  for (const auto &ch : ha) {
    std::wcout << ch << "\n";
    if (isAbukuter(ch)) {
      std::wcout << "Abukuter\n";
    } else
      std::wcout << "Not Abukuter\n";
  }
  return 0;
}

bool isVowel(const char32_t ch) {

  unsigned int codepoint = static_cast<unsigned int>(ch);
  unsigned int character_row = codepoint / 16; // 0xabce -> 0xabc
  unsigned int character_col = codepoint % 16; // 0xabce -> 0xe
  //

  std::wcout << std::hex << codepoint << ", row: " << character_row
             << ", col:" << character_col << "\n";

  if (character_row == 0x12A &&
      (character_col == 7 || (character_col >= 1 && character_col <= 6)))
    return true;

  return false;
}
std::u32string wstring_to_u32string(const std::wstring &wstr) {

  std::u32string u32str;
  u32str.resize(wstr.size());

  for (int i = 0; i < wstr.size(); i++) {
    u32str.insert(u32str.begin() + i, static_cast<uint32_t>(wstr[i]));
  }
  return u32str;
}
bool isAhaz(const char32_t ch) {

  uint32_t codepoint = static_cast<uint32_t>(ch);

  if (codepoint >= 0x1369 && codepoint <= 0x1371)
    return true;
  return false;
}

bool isKuter(const char32_t ch) {

  uint32_t codepoint = static_cast<uint32_t>(ch);

  if (isAhaz(ch) || (codepoint >= 0x1372 && codepoint <= 0x137C))
    return true;
  return false;
}
bool isConsonant(const char32_t ch) {
  if (isVowel(ch))
    return false;
  if (isKuter(ch))
    return false;
  if (isCombiningMark(ch) || isPunctuation(ch))
    return false;
  uint32_t codepoint = static_cast<uint32_t>(ch);

  uint32_t character_col = codepoint % 16;
  if (character_col % 8 == 5)
    return true;

  return false;
}
bool isSyllable(const char32_t ch) {

  if (isKuter(ch) || isCombiningMark(ch) || isPunctuation(ch))
    return false;
  return true;
}
bool isCombiningMark(const char32_t ch) {

  uint32_t codepoint = static_cast<uint32_t>(ch);

  if (codepoint >= 0x135D && codepoint <= 0x135F)
    return true;
  return false;
}

bool isPunctuation(const char32_t ch) {
  uint32_t codepoint = static_cast<uint32_t>(ch);

  if (codepoint >= 0x1360 && codepoint <= 0x1368)
    return true;
  return false;
}
bool isAbukuter(const char32_t ch) { return (isSyllable(ch) || isKuter(ch)); }
