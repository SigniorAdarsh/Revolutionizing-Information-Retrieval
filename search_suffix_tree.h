// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

struct My_Data
{
    int book_code;
    int page;
    int paragraph;
    int sent_no;
    string sentence;
    vector<int> indices;
    int length;
    My_Data(){}
    My_Data(int bc, int pg, int para, int sn, string senece){
        book_code = bc;
        page = pg;
        paragraph = para;
        sent_no = sn;
        sentence = senece;
        length = sentence.length();
        indices.resize(length);
    }
    ~My_Data(){}
};
struct Suffix{
    int sentences_number;
    int s_index;
    int index;
    int position[2];
};

class SearchEngine
{
public:
    // You can add attributes/helper functions here
    vector<My_Data> sentences;
    int max_sentence_length;
    vector<Suffix> suffices;
    void build_suffic_array();
    int size;
    void radix_sort(int i);
    bool done = false;
    int upper_bound(char p, int a, int b, int c);
    int lower_bound(char p, int a, int b, int c);
    int compare(char p, int k, int j);

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
};