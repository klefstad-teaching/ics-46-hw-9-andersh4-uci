#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " with " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1-len2) > d) return false;

    if (len1 > len2) return edit_distance_within(str2, str1, d);

    vector<int> prev(len1 + 1), curr(len1 + 1);

    for (int i = 0; i <= len1; ++i) prev[i] = i;

    for (int j = 1; j <= len2; ++j) {
        curr[0] = j;
        int min_in_row = curr[0];

        for (int i = 1; i <= len1; ++i) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[i] = prev[i - 1];
            } else {
                curr[i] = 1 + min( prev[i - 1], min(prev[i], curr[i - 1]));
            }
            min_in_row = min(min_in_row, curr[i]);
        }

        if (min_in_row > d) return false;

        swap(prev, curr);
    }

    return prev[len1] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    
    for (string word; in >> word;) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder.back();

        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_q.push(new_ladder);
                }
            }
        }
    }

    return {};
}

// void verify_word_ladder() {
    
// }
