#include <codecvt>
#include <fcntl.h>
#include <float.h>
#include <fstream>
#include <io.h>
#include <ios>
#include <iostream>
#include <istream>
#include <locale>
#include <regex>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>
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
bool isDerivateSyllable(const char32_t ch);
char32_t getSyllableConsonant(const char32_t ch);
char32_t getSyllableVowel(const char32_t ch);
std::wstring decomposeSyllable(const char32_t ch);

std::wstring wstring_stem(const std::wstring &wstr);
std::u32string wstring_to_u32string(const std::wstring &wstr);
std::wstring decomposeStringSyllables(const std::wstring &str);
std::wstring composeStringSyllables(const std::wstring &str);

// test for composing and decomposing
//

std::vector<std::wstring> splitWString(const std::wstring &str,
                                       wchar_t delimiter);
std::vector<std::string> splitString(const std::string &str, char delmit);
void testDecompose() {
  std::fstream file("input.txt", std::ios::in | std::ios::binary);

  if (!file.is_open()) {
    std::cerr << "Couldn't open file\n";
    return;
  }

  std::stringstream buffer;
  std::string data_string;
  buffer << file.rdbuf();
  data_string = buffer.str();

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

  std::wstring wstr = converter.from_bytes(data_string);

  std::vector<std::wstring> words = splitWString(wstr, ' ');

  int testsPassed = 0;
  int testsFailed = 0;
  for (const auto &word : words) {
    std::wstring decomposed = decomposeStringSyllables(word);
    std::wstring composed = composeStringSyllables(decomposed);

    if (composed == word) {
      std::wcout << " Test Passed " << word << " = " << composed << "\n";
      testsPassed++;
    } else {
      std::wcout << " Test Failed " << word << " != " << composed
                 << " was decomposed to [" << decomposed << "]\n";
      testsFailed++;
    }
  }
  std::wcout << testsPassed << " Tests Passed \n"
             << testsFailed << " Tests Failed";
}
int main() {

  _setmode(_fileno(stdout), _O_WTEXT);

  std::wcout << "Input Word to detach: ";
  std::wstring inputWord = L"ልጅቷ";

  std::wcout << "Stem String: " << wstring_stem(inputWord)
             << " was decomposed to " << decomposeStringSyllables(inputWord)
             << std::endl;
  return 0;
}

bool isVowel(const char32_t ch) {

  unsigned int codepoint = static_cast<unsigned int>(ch);
  unsigned int character_row = codepoint / 16; // 0xabce -> 0xabc
  unsigned int character_col = codepoint % 16; // 0xabce -> 0xe
  //

  if (character_col == 5)
    return false;
  if (character_row == 0x12A &&
      (character_col == 7 || (character_col >= 1 && character_col <= 6)))
    return true;

  return false;
}
std::u32string wstring_to_u32string(const std::wstring &wstr) {

  std::u32string u32str;
  u32str.resize(wstr.size());

  for (size_t i = 0; i < wstr.size(); i++) {
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

char32_t getSyllableConsonant(const char32_t ch) {

  // TODO: needs to handle derivate letters
  if (!isSyllable(ch))
    return ch;
  if (isConsonant(ch))
    return ch;
  if (isVowel(ch))
    return ch;

  else {
    uint32_t codepoint = static_cast<uint32_t>(ch);
    uint32_t character_col = codepoint % 16;
    if (character_col > 7) {
      codepoint -= character_col;
      codepoint += 0xD;
    } else {
      codepoint -= character_col;
      codepoint += 0x5;
    }

    return static_cast<char32_t>(codepoint);
  }
}

std::wstring decomposeSyllable(const char32_t ch) {
  if (!isSyllable(ch)) {
    std::wstring decomposed{static_cast<wchar_t>(ch)};
    return decomposed;
  }
  if (isDerivateSyllable(ch)) {
    // the consonant and vowel form for derivate syllabel is different from the
    // regular ones the consonant remains the sadis letter but the vowel is the
    // letter ዋ
    char32_t consonant = getSyllableConsonant(ch);
    char32_t vowel = U'ዋ';
    std::wstring decomposed{static_cast<wchar_t>(consonant),
                            static_cast<wchar_t>(vowel)};
    return decomposed;
  }

  // han
  char32_t consonant = getSyllableConsonant(ch);
  char32_t vowel = getSyllableVowel(ch);
  if (consonant != vowel) {
    std::wstring decomposed{static_cast<wchar_t>(consonant),
                            static_cast<wchar_t>(vowel)};
    return decomposed;
  }
  std::wstring decomposed{static_cast<wchar_t>(consonant)};

  return decomposed;
}
char32_t getSyllableVowel(const char32_t ch) {
  if (!isSyllable(ch))
    return ch;
  if (isVowel(ch))
    return ch;
  if (isConsonant(ch))
    return ch;
  //
  char32_t amharic_vowels[] = {U'ኧ', U'ኡ', U'ኢ', U'ኣ', U'ኤ', U'እ', U'ኦ'};
  uint32_t codepoint = static_cast<uint32_t>(ch);
  uint32_t character_col = codepoint % 16;

  if (character_col % 8 < (sizeof(amharic_vowels) / sizeof(char32_t))) {
    int vowel_index = character_col % 8;
    return amharic_vowels[vowel_index];
  }
  return ch;
}
std::wstring decomposeStringSyllables(const std::wstring &str) {
  std::u32string u32str = wstring_to_u32string(str);

  std::wstring decomposedString;

  for (size_t i = 0; i < str.length(); i++) {
    char32_t ch = u32str[i];
    decomposedString += decomposeSyllable(ch);
  }
  return decomposedString;
}

std::wstring composeStringSyllables(const std::wstring &str) {
  std::u32string u32str = wstring_to_u32string(str);

  std::wstring composedString;
  for (size_t i = 0; i < str.length(); i++) {

    if (i >= str.length())
      break;
    char32_t ch = u32str[i];

    if (isConsonant(ch)) {

      if (i + 1 < str.length()) {
        uint32_t nextch = u32str[i + 1];
        if (isVowel(nextch)) {

          auto getVowelIndex = [](char32_t ch) {
            char32_t amharic_vowels[] = {U'ኧ', U'ኡ', U'ኢ', U'ኣ',
                                         U'ኤ', U'እ', U'ኦ'};

            int size = sizeof(amharic_vowels) / sizeof(char32_t);
            for (int i = 0; i < size; i++) {
              if (ch == amharic_vowels[i])
                return i;
            }
            return 0;
          };

          int vowelIndex = getVowelIndex(nextch);

          uint32_t intialCodepoint = static_cast<uint32_t>(ch) - 5;

          wchar_t syllabel =
              static_cast<uint32_t>((intialCodepoint + vowelIndex));
          composedString += syllabel;
          i++;
          // contniue processig
        } else if (nextch == U'ዋ') {
          // handing derivate sounds like ሟ
          uint32_t codepoint = static_cast<uint32_t>(ch);
          uint32_t character_col = codepoint % 16;

          if (character_col > 8) {
            codepoint -= character_col;
            codepoint += 0xF;
            composedString += static_cast<wchar_t>(codepoint);
          } else {
            codepoint -= character_col;
            codepoint += 0x7;
            composedString += static_cast<wchar_t>(codepoint);
          }

          i++;
        } else {
          composedString += static_cast<wchar_t>(ch);
        }
      } else {
        composedString += static_cast<wchar_t>(ch);
      }
      //
    } else if (isVowel(ch)) {
      composedString += static_cast<wchar_t>(ch);

      //
    } else {
      composedString += static_cast<wchar_t>(ch);
      //
    }
  }
  return composedString;
}

std::vector<std::wstring> splitWString(const std::wstring &str,
                                       wchar_t delimiter) {
  std::wstringstream stream(str);
  std::wstring token;
  std::vector<std::wstring> words;

  while (std::getline(stream, token, delimiter)) {

    words.push_back(token);
  }
  return words;
}

bool isDerivateSyllable(const char32_t ch) {
  if (!isSyllable(ch))
    return false;
  if (isVowel(ch))
    return false;
  if (isConsonant(ch))
    return false;
  uint32_t codepoint = static_cast<uint32_t>(ch);

  uint32_t character_col = codepoint % 16;
  if (character_col % 8 == 7)
    return true;
  return false;
}
std::wstring wstring_stem(const std::wstring &wstr) {

  const std::vector<std::wstring> suffix_list = {
      L"ኦችኣችኧውንንኣ", L"ኦችኣችህኡ", L"ኦችኣችኧውን", L"ኣችኧውንንኣ", L"ኦችኣችኧው", L"ኢዕኧልኧሽ",
      L"ኦችኣችን",     L"ኣውኢው",   L"ኣችኧውኣል",  L"ችኣት",     L"ችኣችህኡ",  L"ችኣችኧው",
      L"ኣልኧህኡ",     L"ኣውኦች",   L"ኣልኧህ",    L"ኣልኧሽ",    L"ኣልችህኡ",  L"ኣልኣልኧች",
      L"ብኣችኧውስ",    L"ብኣችኧው",  L"ኣችኧውን",   L"ኣልኧች",    L"ኣልኧን",   L"ኣልኣችህኡ",
      L"ኣችህኡን",     L"ኣችህኡ",   L"ኣችህኡት",   L"ውኦችንንኣ",  L"ውኦችን",   L"ኣችኧው",
      L"ውኦችኡን",     L"ውኦችኡ",   L"ውንኣ",     L"ኦችኡን",    L"ውኦች",    L"ኝኣንኧትም",
      L"ኝኣንኣ",      L"ኝኣንኧት",  L"ኝኣን",     L"ኝኣውም",    L"ኝኣው",    L"ኣውኣ",
      L"ብኧትን",      L"ኣችህኡም",  L"ችኣችን",    L"ኦችህ",     L"ኦችሽ",    L"ኦችኡ",
      L"ኦችኤ",       L"ኦውኣ",    L"ኦቿ",      L"ችው",      L"ችኡ",     L"ኤችኡ",
      L"ንኧው",       L"ንኧት",    L"ኣልኡ",     L"ኣችን",     L"ክኡም",    L"ክኡት",
      L"ክኧው",       L"ችን",     L"ችም",      L"ችህ",      L"ችሽ",     L"ችን",
      L"ችው",        L"ይኡሽን",   L"ይኡሽ",     L"ውኢ",      L"ኦችንንኣ",  L"ኣውኢ",
      L"ብኧት",       L"ኦች",     L"ኦችኡ",     L"ውኦን",     L"ኝኣ",     L"ኝኣውን",
      L"ኝኣው",       L"ኦችን",    L"ኣል",      L"ም",       L"ሽው",     L"ክም",
      L"ኧው",        L"ውኣ",     L"ትም",      L"ውኦ",      L"ውም",     L"ውን",
      L"ንም",        L"ሽን",     L"ኣች",      L"ኡት",      L"ኢት",     L"ክኡ",
      L"ኤ",         L"ህ",      L"ሽ",       L"ኡ",       L"ሽ",      L"ክ",
      L"ች",         L"ኡን",     L"ን",       L"ም",       L"ንኣ",     L"ዋ"};

  const std::vector<std::wstring> prefix_list = {
      L"ስልኧምኣይ", L"ይኧምኣት", L"ዕንድኧ", L"ይኧትኧ", L"ብኧምኣ", L"ብኧትኧ", L"ዕኧል", L"ስልኧ",
      L"ምኧስ",    L"ዕይኧ",   L"ይኣል",  L"ስኣት",  L"ስኣን",  L"ስኣይ",  L"ስኣል", L"ይኣስ",
      L"ይኧ",     L"ልኧ",    L"ብኧ",   L"ክኧ",   L"እን",   L"አል",   L"አስ",  L"ትኧ",
      L"አት",     L"አን",    L"አይ",   L"ይ",    L"አ",    L"እ"};

  std::wstring wsteam = decomposeStringSyllables(wstr);

  std::wcout << wsteam << "\n";
  // removing suffixes
  std::wcout << "////// removing suffixes \n" << std::endl;
  for (const auto &suffix : suffix_list) {
    std::wregex pattern(decomposeStringSyllables(suffix) + L"$");

    std::wstring pre_removal_string =
        wsteam; // holding a copy of wstem before it gets eviscirated

    wsteam = std::regex_replace(wsteam, pattern, L"");

    if (wsteam != pre_removal_string) {
      std::wcout << "[ " << suffix << " removed"
                 << "] " << wsteam << std::endl;
    }
    if (wsteam.length() <= 1)
      wsteam = pre_removal_string;
  }

  std::wcout << "////// removing prefix \n" << std::endl;
  for (const auto &prefix : prefix_list) {
    std::wregex pattern(L"^" + decomposeStringSyllables(prefix));
    std::wstring pre_removal_string =
        wsteam; // holding a copy of wstem before it gets eviscirated

    wsteam = std::regex_replace(wsteam, pattern, L"");

    if (wsteam != pre_removal_string) {
      std::wcout << "[ " << prefix << " removed"
                 << "] " << wsteam << std::endl;
    }
    if (wsteam.length() <= 1)
      wsteam = pre_removal_string;
  }

  return composeStringSyllables(wsteam);
}
