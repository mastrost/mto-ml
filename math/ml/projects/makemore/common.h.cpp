//[mto.import ./common]

//[mto-gen.begin]
#include "./common.h"
namespace mto::math::ml::projects::makemore::common {
namespace common = mto::math::ml::projects::makemore::common;
}
#include "cpp_tools/defines.h"
//[mto-gen.end]
//[mto]
namespace mto::math::ml::projects::makemore::common {//[mto.module-begin]

vector_t<bigram_t>
extract_bigrams(words_t const &words) {
  vector_t<bigram_t> bigrams;
  for (let &w : words.span_of().slice(0, 1000)) {
    for (let i_c : w.foreach_index()) {
      if (i_c == 0) {
        bigrams.push_back({begin, w[i_c]});
      }
      if (i_c == w.size() - 1) {
        bigrams.push_back({w[i_c], end});
      } else {
        bigrams.push_back({w[i_c], w[i_c + 1]});
      }
    }
  }
  return bigrams;
}

char to_char(size_t i) {
  if (i == 26) {
    return begin;
  } else if (i == 27) {
    return end;
  } else {
    REQUIRES(i >= 0 && i <= 25);
    return i + 'a';
  }
}

size_t to_index(char c) {
  if (c == begin) {
    return 26;
  } else if (c == end) {
    return 27;
  } else {
    REQUIRES(c >= 'a' && c <= 'z');
    return size_t(c) - size_t('a');
  }
}

float to_findex(char c) {
  return to_index(c);
}

}//[mto.module-end]
