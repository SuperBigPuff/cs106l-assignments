#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);
 
Corpus tokenize(std::string& source) {
  // Step 1
  auto spaces = find_all(source.begin(),source.end(), ::isspace);
  // Step 2
  Corpus corpus;
  // Step 3
  auto combine = [&source](auto it1, auto it2) { return Token(source, it1, it2); };
  std::transform(spaces.begin(), spaces.end() - 1, spaces.begin() + 1, std::inserter(corpus, corpus.end()), combine);
  // Step 4
  auto empty = [](const Token& token) { return token.content.empty(); };
  std::erase_if(corpus, empty);
  return corpus;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  // Step 1
  auto contain = [&dictionary](const Token& token)
  {
    return !dictionary.contains(token.content);
  };
  namespace rv = std::ranges::views;
  // Step 2
  auto suggestion =[&dictionary](const Token& token)
  {
    auto judge = [&token](const std::string& word)
    {
      return levenshtein(token.content, word) == 1;
    };
    auto view = dictionary | rv::filter(judge);
    std::set<std::string> suggestions(view.begin(), view.end());
    return Misspelling{token, suggestions};
  };
  // Step 3
  auto NotEmpty = [](const Misspelling& misspelling)
  {
    return !misspelling.suggestions.empty();
  };
  auto view = source | rv::filter(contain) | rv::transform(suggestion) | rv::filter(NotEmpty);
  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"