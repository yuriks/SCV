#include "stdafx.h"
#include "TextFilter.h"

namespace scv {

TextFilter::TextFilter(void) {
   memset(_filter, true, s_printableCharacters + 1);
}

void TextFilter::denyAll(void) {
   memset(_filter, false, s_printableCharacters + 1);
}

void TextFilter::denyNumbers(void) {
   //in ASCII numbers are from 48 to 57
   //+1 cause including the first one
   memset(&_filter[48 - s_vectorDisplacement], false, 57 - 48 + 1);
}

void TextFilter::denyLetters(void) {
   //in ASCII letters are from 65 to 90
   //+1 cause including the first one
   memset(&_filter[65 - s_vectorDisplacement], false, 90 - 65 + 1);

   //in ASCII letters are from 97 to 122
   memset(&_filter[97 - s_vectorDisplacement], false, 122 - 97 + 1);
}

void TextFilter::denyThese(const std::string &filter) {
   for (int i = 0; i < filter.size(); i++) {
      if (filter[i] >= s_vectorDisplacement && filter[i] <= s_vectorDisplacement + s_printableCharacters)
         _filter[filter[i] - s_vectorDisplacement] = false;
   }
}

void TextFilter::allowAll(void) {
   memset(_filter, true, s_printableCharacters + 1);
}

void TextFilter::allowNumbers(void) {
   //in ASCII numbers are from 48 to 57
   //+1 cause including the first one
   memset(&_filter[48 - s_vectorDisplacement],true, 57 - 48 + 1);
}

void TextFilter::allowLetters(void) {
   //in ASCII letters are from 65 to 122
   //+1 cause including the first one
   memset(&_filter[65 - s_vectorDisplacement],true, 90 - 65 + 1);

   //in ASCII letters are from 97 to 122
   memset(&_filter[97 - s_vectorDisplacement],true, 122 - 97 + 1);
   // ENABLE SPACE
}

void TextFilter::allowThese(const std::string &filter) {
   for (int i = 0; i < filter.size(); i++) {
      if (filter[i] >= s_vectorDisplacement && filter[i] <= s_vectorDisplacement + s_printableCharacters)
         _filter[filter[i] - s_vectorDisplacement] = true;
   }
}

bool TextFilter::checkFilter(char character) {
   if (character >= s_vectorDisplacement && character <= s_vectorDisplacement + s_printableCharacters)
      return _filter[character - s_vectorDisplacement];
   return true;
}

} // namespace scv
