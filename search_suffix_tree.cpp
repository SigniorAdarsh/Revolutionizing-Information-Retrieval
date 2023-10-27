// Do NOT add any other includes
#include "search_suffix_tree.h"
const int limit = 128;
string to_lower(const string &s)
{
    string t = "";
    for (int i = 0; i < s.size(); i++)
    {
        t += tolower(s[i]);
    }
    return t;
}
SearchEngine::SearchEngine()
{
    size = 0;
    max_sentence_length = 0;
}

SearchEngine::~SearchEngine()
{
}
void SearchEngine::build_suffic_array()
{
    if (done)
        return;
    done = true;
    suffices.resize(size);
    int p = 0, q = 0;
    for (int i = 0; i < size; i++)
    {
        suffices[i].index = i;
        suffices[i].sentences_number = p;
        suffices[i].s_index = q;
        suffices[i].position[0] = sentences[p].sentence[q];
        if (q == sentences[p].length - 1)
        {
            suffices[i].position[1] = -1;
            q = 0;
            p++;
        }
        else
        {
            suffices[i].position[1] = sentences[p].sentence[q + 1];
            q++;
        }
    }
    radix_sort(1);
    radix_sort(0);
    vector<int> where(size);
    for (int k = 2; k < max_sentence_length; k <<= 1)
    {
        int position = 0;
        int prev_position = suffices[0].position[0];
        suffices[0].position[0] = position;
        where[suffices[0].index] = 0;
        for (int i = 1; i < size; i++)
        {
            if (!(suffices[i].position[0] == prev_position &&
                  suffices[i].position[1] == suffices[i - 1].position[1]))
            {
                position++;
            }
            prev_position = suffices[i].position[0];
            suffices[i].position[0] = position;
            where[suffices[i].index] = i;
        }
        for (int i = 0; i < size; i++)
        {
            if (suffices[i].s_index + k < sentences[suffices[i].sentences_number].length)
            {
                suffices[i].position[1] = suffices[where[suffices[i].index + k]].position[0];
            }
            else
            {
                suffices[i].position[1] = -1;
            }
        }
        radix_sort(1);
        radix_sort(0);
    }
}
void SearchEngine::radix_sort(int ii)
{
    vector<Suffix> output(size);
    int i = 0;
    vector<int> count(max(limit, size + 1), 0);
    for (i = 0; i < size; i++)
    {
        int k = suffices[i].position[ii];
        count[k + 1]++;
    }
    for (i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (i = size - 1; i >= 0; i--)
    {
        int k = suffices[i].position[ii];
        output[count[k + 1] - 1] = suffices[i];
        count[k + 1]--;
    }
    for (i = 0; i < size; i++)
        suffices[i] = output[i];
}
void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    sentence = to_lower(sentence);
    done = false;
    int p = sentence.length();
    size += p;
    max_sentence_length = max(max_sentence_length, p);
    My_Data dem(book_code, page, paragraph, sentence_no, sentence);
    sentences.push_back(dem);
    return;
}
int SearchEngine::compare(char p, int k, int depth)
{
    const Suffix &s = suffices[k];
    const My_Data &d = sentences[s.sentences_number];
    int w = depth + s.s_index;
    char y = d.sentence[w];
    if (w >= d.length) return -1;
    if (y < p) return -1;
    if (y == p) return 0;
    if (y > p) return 1;
    return 0;
}
int SearchEngine::lower_bound(char p, int start, int end, int depth)
{
    int first = start;
    int last = end;
    while (first != last)
    {
        int mid = (first + last) / 2;

        if (compare(p, mid, depth) == -1)
        {
            first = mid + 1;
        }
        else
        {
            last = mid;
        }
    }
    return first;
}
int SearchEngine::upper_bound(char p, int start, int end, int depth)
{
    int first = start;
    int last = end;
    while (first != last)
    {
        int mid = (first + last) / 2;
        if (compare(p, mid, depth) != 1)
        {
            first = mid + 1;
        }
        else
        {
            last = mid;
        }
    }
    return first;
}
Node *SearchEngine::search(string pattern, int &n_matches)
{
    pattern = to_lower(pattern);
    build_suffic_array();
    vector<Node *> searches;
    int p = 0;
    int q = size;
    for (int j = 0; j < pattern.size(); j++)
    {
        p = lower_bound(pattern[j], p, q, j);
        q = upper_bound(pattern[j], p, q, j);    
    }
    
    
    for (int j = p; j < q; j++)
    {
        const Suffix &s = suffices[j];
        const My_Data &d = sentences[s.sentences_number];
        Node *node = new Node(d.book_code, d.page, d.paragraph, d.sent_no, s.s_index);
        searches.push_back(node);
    }
    n_matches = searches.size();
    if (n_matches == 0)
    {
        return nullptr;
    }
    else if (n_matches == 1)
    {
        return searches[0];
    }
    else
    {
        searches.front()->right = searches[1];
        searches.front()->left = searches.back();
        searches.back()->left = searches[n_matches - 2];
        searches.back()->right = searches.front();
        for (int i = 1; i < n_matches - 1; i++)
        {
            searches[i]->left = searches[i - 1];
            searches[i]->right = searches[i + 1];
        }
        return searches[0];
    }
}
