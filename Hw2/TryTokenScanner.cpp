#include "TryTokenScanner.h"

#include "tokenscanner.h"

using namespace std;

// Part I
Vector<string> TryTokenScanner::allTokens(string text) {
  Vector<string> tokens;
  
    TokenScanner token(text);
    while (token.hasMoreTokens()) {
        tokens.push_back(token.nextToken());
    }
    

  return tokens;
}

// Part II
Vector<string> TryTokenScanner::noWhitespaces(string text) {
  Vector<string> tokens;
    TokenScanner token(text);
    token.ignoreWhitespace();
    while (token.hasMoreTokens()) {
        tokens.push_back(token.nextToken());
    }
    

  return tokens;
}

// Part III
Vector<string> TryTokenScanner::noComments(string text) {
  Vector<string> tokens;
    TokenScanner token(text);
    token.ignoreComments();
    while (token.hasMoreTokens()) {
        tokens.push_back(token.nextToken());
    }
    

  return tokens;
}
