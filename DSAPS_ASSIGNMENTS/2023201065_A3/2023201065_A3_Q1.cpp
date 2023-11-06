#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_EDIT_DISTANCE = 3;
// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie {
public:
    Trie() {
        root = getNode();
    }

    // Insert a word into the Trie
    void insert(string key) {
        TrieNode* checkPos = root;

        for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';
            if (!checkPos->children[index])
                checkPos->children[index] = getNode();

            checkPos = checkPos->children[index];
        }

        checkPos->isEndOfWord = true;
    }


    bool search(string key) {
        TrieNode* pCrawl = root;

        for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }
        return (pCrawl->isEndOfWord);
    }

    // Autocomplete: Find all words in the Trie that start with a given prefix
    vector<string> autocomplete(string prefix) {
        TrieNode* pCrawl = root;

        for (int i = 0; i < prefix.length(); i++) {
            int index = prefix[i] - 'a';
            if (!pCrawl->children[index]) {
                return {};
            }
            pCrawl = pCrawl->children[index];
        }

        vector<string> words;
        autocompleteHelper(pCrawl, prefix, words);
        return words;
    }

    void autocorrect(const string &query)
    {
        vector<string> words;
        autocorrectHelper(root, query, "", 0, words);
        sort(words.begin(), words.end());
        // cout << words.size() << endl;
        // for (string word : words)
        // {
        //     cout << word << endl;
        // }
    }

private:
    TrieNode* root;

    TrieNode* getNode() {
        TrieNode* pNode = new TrieNode;

        pNode->isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }

        return pNode;
    }

    void autocompleteHelper(TrieNode* node, string current, vector<string>& words) {
        if (node->isEndOfWord) {
            words.push_back(current);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                char ch = 'a' + i;
                autocompleteHelper(node->children[i], current + ch, words);
            }
        }
    }
    void autocorrectHelper(TrieNode *node, const string &query, string current, int errors, vector<string> &words)
    {
        if (errors > MAX_EDIT_DISTANCE)
            return;

        if (node->isEndOfWord && errors <= MAX_EDIT_DISTANCE)
        {
            words.push_back(current);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (node->children[i])
            {
                char ch = 'a' + i;
                if (current.size() < query.size() || (current.size() == query.size() && current[current.size()] == ch))
                {
                    int newErrors = errors + (ch != query[current.size()]);
                    autocorrectHelper(node->children[i], query, current + ch, newErrors, words);
                }
            }
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    Trie trie;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        trie.insert(word);
    }

    for (int i = 0; i < q; i++) {
        int operation;
        string query;
        cin >> operation >> query;

        if (operation == 1) {
            if (trie.search(query)) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (operation == 2) {
            vector<string> completions = trie.autocomplete(query);
            cout << completions.size() << endl;
            sort(completions.begin(), completions.end());
            for (const string& word : completions) {
                cout << word << endl;
            }
        }
        else if (operation == 3)
        {
            trie.autocorrect(query);
        }
    }

    return 0;
}
