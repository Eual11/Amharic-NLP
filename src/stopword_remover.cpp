#include "../include/stopword_remover.h"
std::vector<std::wstring> stop_word_list = {
    L"ስለሚሆን", L"እና",     L"ስለዚህ",   L"በመሆኑም", L"ሁሉ",    L"ሆነ",    L"ሌላ",
    L"ልክ",    L"ስለ",     L"በቀር",    L"ብቻ",    L"ና",     L"አንዳች",  L"አንድ",
    L"እንደ",   L"እንጂ",    L"ያህል",    L"ይልቅ",   L"ወደ",    L"እኔ",    L"የእኔ",
    L"ራሴ",    L"እኛ",     L"የእኛ",    L"እራሳችን", L"አንቺ",   L"የእርስዎ", L"ራስህ",
    L"ራሳችሁ",  L"እሱ",     L"እሱን",    L"የእሱ",   L"ራሱ",    L"እርሷ",   L"የእሷ",
    L"ራሷ",    L"እነሱ",    L"እነሱን",   L"የእነሱ",  L"እራሳቸው", L"ምንድን",  L"የትኛው",
    L"ማንን",   L"ይህ",     L"እነዚህ",   L"እነዚያ",  L"ነኝ",    L"ነው",    L"ናቸው",
    L"ነበር",   L"ነበሩ",    L"ሁን",     L"ነበር",   L"መሆን",   L"አለኝ",   L"አለው",
    L"ነበረ",   L"መኖር",    L"ያደርጋል",  L"አደረገው", L"መሥራት",  L"እና",    L"ግን",
    L"ከሆነ",   L"ወይም",    L"ምክንያቱም", L"እንደ",   L"እስከ",   L"ቢሆንም",  L"ጋር",
    L"ላይ",    L"መካከል",   L"በኩል",    L"ወቅት",   L"በኋላ",   L"ከላይ",   L"በርቷል",
    L"ጠፍቷል",  L"በላይ",    L"ስር",     L"እንደገና", L"ተጨማሪ",  L"ከዚያ",   L"አንዴ",
    L"እዚህ",   L"እዚያ",    L"መቼ",     L"የት",    L"እንዴት",  L"ሁሉም",   L"ማናቸውም",
    L"ሁለቱም",  L"እያንዳንዱ", L"ጥቂቶች",   L"ተጨማሪ",  L"በጣም",   L"ሌላ",    L"አንዳንድ",
    L"አይ",    L"ወይም",    L"አይደለም",  L"ብቻ",    L"የራስ",   L"ተመሳሳይ", L"ስለዚህ",
    L"እኔም",   L"በጣም",    L"ይችላል",   L"ይሆናል",  L"በቃ",    L"አሁን",
};
std::wstring stopword_remove(const std::wstring &srcString) {
  std::wstring finalString = srcString;

  for (const auto &stopword : stop_word_list) {
    std::wregex pattern(L"\\b" + stopword + L"\\b");
    finalString = std::regex_replace(finalString, pattern, L"");
  }
  // stripping redundant tabs or spaces
  finalString =
      std::regex_replace(finalString, std::wregex(L"(\\t|\\s){2,}"), L"$1");
  return finalString;
}
