// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class DictNode{
    public:
    char key;
    int value;
    DictNode** bacha=new DictNode*[54];

    DictNode(char k){
        key=k;
        value=0;
        for(int i=0 ; i<54 ; i++){
            bacha[i]=NULL;
        }
    }

    ~DictNode(){
        value=0;
        for(int i=0 ; i<54 ; i++){
            delete bacha[i];
        }
        delete[] bacha;
    }

};

class Dict {
private:
    // You can add attributes/helper functions here
    DictNode* root;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};