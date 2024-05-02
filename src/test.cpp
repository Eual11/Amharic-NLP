#include <iostream>
#include <string>

int main(void) {

  constexpr char32_t codepoitns[] = U"ኆ";

  constexpr int size = sizeof(codepoitns) / sizeof(char32_t);

  if (*codepoitns % 16 == 0) {
    std::cout << "YESSS\n";
  }
  for (int i = 0; i < size && codepoitns[i]; i++)
    std::cout << "U+" << std::hex << static_cast<unsigned int>(codepoitns[i]);
  return 0;
}
