
# AmharicNLP

This is a lightweight C++17 header-only library for Amharic text pre-processing. The library provides functionalities for text normalization, stop word removal, word stemming, and word suggestion. It is designed to be easy to use, with no external dependencies required.


[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
![C++](https://img.shields.io/badge/-C++-blue?logo=cplusplus)

<div align="center" width="228" height="228">
<a href="https://github.com/othneildrew/Best-README-Template">
      <img src="img/logo.png" alt="Logo" width="80" height="80">
  </a>
</div>

## Features

- **Text normalization**: The library normalizes Amharic text by applying Unicode normalization techniques. This ensures consistent representation of characters and compatibility with other Unicode operations.

- **Stop word removal**: It offers a predefined list of Amharic stop words and efficiently removes them from the given text. This helps in excluding commonly used words that do not contribute significantly to the overall meaning of the text.

- **Word stemming**: The library implements a simple stemming algorithm specifically tailored for the Amharic language. It reduces words to their root form, facilitating better analysis and comparison of text data.

- **Word suggestion**: After removing stop words and stemming the remaining words, the library attempts to provide a suggestion for the possible full word that the stemmed word may represent. This feature helps users with auto-suggestions and improves the usability of the library.
- **Character Composition/Decomposition**: The AmharicNLP library provides a convenient feature for decomposing Amharic characters into their consonant and vowel forms. This functionality allows you to separate the base consonant from any accompanying vowel, enabling a better understanding of the linguistic structure of Amharic text.


## Installation
This library is a single header file, amharic_text_processing.hpp. You can download the header and include it in your C++ project.

in order to enable word suggestion you need to have the dictionary in `asset/` folder and compile your program defining NLP_ENABLE_SUGGESTION
```bash
  g++ -DNLP_ENABLE_SUGGESTION std=c++17 your_program.c -o program
  cd my-project
```
    


<!-- ## Demo -->
<!---->
<!---->


## Usage/Examples

```c++
//stemmer example
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

  std::vector<std::wstring> words = {L"ልጆች",   L"ላይኛው",     L"ይኖሩ",
                                     L"ገርጥቷል", L"እስትንፋስዋም", L"ወጣቷ"};
  std::cout << "[ ";
  for (auto word : words) {
    std::cout << alp.wstring_to_string(word) << ", ";
  }
  std::cout << "]\n";


  std::cout << "[ ";
  for (auto word : words) {
    std::wstring stem_word = alp.wstring_stem(word, 1, 1);
    std::cout << alp.wstring_to_string(stem_word) << ", ";
  }
  std::cout << "]\n";

  return 0;
}

```


```console
$ make example.cpp && ./a
[ ልጆች, ላይኛው, ይኖሩ, ገርጥቷል, እስትንፋስዋም, ወጣቷ, ]
[ ልጅ, ላይ, ኖር, ገርጥቷል, ስትንፋስዋ, ወጣቷ, ]
```
### Decomposing Strings example
```c++
//decomposing_string_example.cpp
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

  std::vector<std::wstring> words = {L"ልጆች",   L"ላይኛው",     L"ይኖሩ",
                                     L"ገርጥቷል", L"እስትንፋስዋም", L"ወጣቷ"};
  std::cout << "[ ";
  for (auto word : words) {
    std::cout << alp.wstring_to_string(word) << ", ";
  }
  std::cout << "]\n";

  std::cout << "[ ";
  for (auto word : words) {
    std::wstring stem_word = alp.decomposeStringSyllables(word);
    std::cout << alp.wstring_to_string(stem_word) << ", ";
  }
  std::cout << "]\n";

  return 0;
}

```
```console
$ make decomposing_example.cpp && ./a
[ ልጆች, ላይኛው, ይኖሩ, ገርጥቷል, እስትንፋስዋም, ወጣቷ, ]
[ ልጅኦች, ልኣይኝኣው, ይንኦርኡ, ግኧርጥትዋል, እስትንፍኣስውኣም, ውኧጥኣትዋ, ]

```
### Composing Strings example
```c++
//composing_string_example.cpp
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
    std::wstring stem_word = alp.decomposeStringSyllables(word);
    std::cout << alp.wstring_to_string(stem_word) << ", ";
  }
  std::cout << "]\n";

  return 0;
}
```
```console
$ make decomposing_example.cpp && ./a
[ ልጅኦች, ልኣይኝኣው, ይንኦርኡ, ግኧርጥትዋል, እስትንፍኣስውኣም, ውኧጥኣትዋ, ]
[ ልጆች, ላይኛው, ይኖሩ, ገርጥቷል, እስትንፋስዋም, ወጣቷ, ]

```

### Stemmer with suggestions example
```c++
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
```


```console
$ g++ -DALP_ENABLE_SUGGESTION
 example.cpp && ./a
Loading Suggestions 
Suggestions Completed
Enter Depth for suffix removal(default = 1): 1
Enter Depth for prefix_level removal(default = 1): 1
Enable Lexical Recovery(1 to enable 0 to disable): 1
Enter Word to be Stem: እስትንፋስዋ
[ ውኣ removed] እስትንፋስ
[ እ removed] ስትንፋስ
 Stem: ስትንፋስ Suggestion : እስትንፋስ

```
> **Note:** The suggestion feature of the AmharicNLP library is currently in an extremely experimental and incomplete state. Please be aware that the suggested word outputs may not always be accurate or comprehensive. We are actively working on improving this feature to enhance its accuracy and coverage. Your [feedback](#Feedback) feedback and contributions are greatly appreciated as we continue to refine and expand the suggestion functionality.
You can find various examples in the `examples/` folder

Additionaly, The AmharicNLP library provides several utility functions for working with the Amharic language and Ethiopic characters:

- `isVowel(const char32_t ch)`: Checks if a character is a vowel.
- `isAhaz(const char32_t ch)`: Checks if a character is a digit.
- `isKuter(const char32_t ch)`: Checks if a character is a number.
- `isConsonant(const char32_t ch)`: Checks if a character is a consonant.
- `isSyllable(const char32_t ch)`: Checks if a character is a syllable.
- `isPunctuation(const char32_t ch)`: Checks if a character is punctuation.

and many more to come!


## Challenges and Special Cases
During the development of this library, some challenges and special cases specific to Amharic text processing were encountered. These include:

**Limited resources**: The availability of comprehensive resources for Amharic language processing, such as stop word lists and linguistic data, is relatively limited. This required careful curation and manual efforts to create a useful implementation.

**Ambiguity in stemming**: Amharic words can have multiple possible stem forms due to complex morphology and context sensitivity. Handling such cases accurately is challenging, and the library aims to provide reasonable suggestions based on common patterns.

**Accuracy of word suggestions**: Generating accurate word suggestions for stemmed words is a complex task, as it often involves analyzing the context and considering various linguistic factors. While the library attempts to provide relevant suggestions, it may not always guarantee perfect matches.
## Contributing

Contributions are always welcome!

See `contributing.md` for ways to get started.

Please adhere to this project's `code of conduct`.


## Feedback

If you have any feedback, please reach out to us at uchihaeual11@gmail.com

