#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void solve(
	std::string& curr,
  std::string& floating,
  const std::set<std::string>& dict,
	std::set<std::string>& out,
	size_t ind, size_t empty
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	std::set<std::string> out;
	std::string curr = in;
	std::string fl = floating;

	size_t empty = 0;
	for (size_t i = 0; i < curr.length(); i++) {
		if (curr[i] == '-') {
			empty++;
		}
	}

	solve(curr, fl, dict, out, 0, empty);

	return out;

}

// Define any helper functions here

void solve(
	std::string& curr,
  std::string& floating,
  const std::set<std::string>& dict,
	std::set<std::string>& out,
	size_t ind, size_t empty
) {
	if (ind == curr.length()) {
		if (floating.empty()) {
			if (dict.find(curr) != dict.end()) {
				out.insert(curr);
			}
		}
		return;
	}

	if (curr[ind] != '-') {
		solve(curr, floating, dict, out, ind + 1, empty);
		return;
	}

	for (char c = 'a'; c <= 'z'; c++) {
		size_t found = floating.find(c);
		if (found != std::string::npos) {
			std::string nxt = floating;
			nxt.erase(found, 1);
			curr[ind] = c;
			solve(curr, nxt, dict, out, ind + 1, empty - 1);
			curr[ind] = '-';
		} else {
			if (empty > floating.size()) {
				curr[ind] = c;
				solve(curr, floating, dict, out, ind + 1, empty - 1);
				curr[ind] = '-';
			}
		}
	}
}