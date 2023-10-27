// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class Comp
{
public:
    Comp **bacha = new Comp *[132];
    int uparh;
    int nich;
    vector<Node*> vect;
    Comp()
    {
        uparh=0;
        nich=0;
        for (int i = 0; i < 132; i++)
        {
            bacha[i] = NULL;
        }
    }
    ~Comp()
    {
        for (int i = 0; i < 132; i++)
        {
            delete bacha[i];
            bacha[i]=NULL;
        }
        delete[] bacha;
    }
};
class SearchEngine
{
private:
    Node *head = NULL;
    Comp*root=new Comp();
    Node *abhi = NULL;
    vector<string>mumm={};
    // You can add attributes/helper functions here

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