// Do NOT add any other includes
#include "search_trie.h"
SearchEngine::SearchEngine()
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}
void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    char ch;
    int babloo;
    int index;
    Comp *temp = root;
    int n = sentence.length();
    int cht = temp->uparh;
    // Implement your function here
    for (int i = 0; i < n; i++)
    {
        ch = sentence[i];
        babloo = (int)(ch);
        index = 0;
        if (ch >= '0' && ch <= '9')
        {
            index = ch - '0';
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            index = ch - 'a' + 10;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            index = ch - 'A' + 10;
        }
        else
        {
            index = babloo + 4;
        }
        if (temp->bacha[index] == NULL)
        {
            temp->bacha[index] = new Comp();
            temp = temp->bacha[index];
            temp->uparh = cht + 1;
            temp->nich = n - i;
            temp->vect.push_back(new Node(book_code, page, paragraph, sentence_no, cht));
            cht = temp->uparh;
        }
        else
        {
            temp = temp->bacha[index];
            temp->nich = max(temp->nich, n - i);
            temp->vect.push_back(new Node(book_code, page, paragraph, sentence_no, cht));
            cht = temp->uparh;
        }
    }
}
void dhudhobhaiya(string &pattern, int &n_matches, int matched, Node *&curr, int &n, Comp *&pew, Node *&headd, int j)
{
    if (matched == n)
    {
        Node *tempu;
        for (int i = 0; i < pew->vect.size(); i++)
        {
            if (i == 0 && n_matches == 0)
            {
                tempu = pew->vect[i];
                headd = tempu;
                curr = tempu;
                tempu->offset -= (n - 1);
            }
            else
            {
                tempu = pew->vect[i];
                curr->right = tempu;
                tempu->left = curr;
                curr = tempu;
                tempu->offset -= (n - 1);
            }
        }
        n_matches += pew->vect.size();
        matched = 0;
    }
    if (pew->nich == 1)
    {
        return;
    }
    char ch;
    int babloo;
    int index;
    ch = pattern[matched];
    babloo = (int)(ch);
    index = 0;
    if (ch >= '0' && ch <= '9')
    {
        index = ch - '0';
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        index = ch - 'a' + 10;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        index = ch - 'A' + 10;
    }
    else
    {
        index = babloo + 4;
    }
    for (int i = 0; i < 132; i++)
    {
        if (pew->bacha[i] != NULL && (n - matched) <= pew->bacha[i]->nich)
        {
            if (i == index)
            {
                dhudhobhaiya(pattern, n_matches, matched + 1, curr, n, pew->bacha[i], headd, i);
                if (matched != 0 && pattern[matched] == pattern[0])
                {
                    dhudhobhaiya(pattern, n_matches, 1, curr, n, pew->bacha[i], headd, i);
                }
            }
            else
                dhudhobhaiya(pattern, n_matches, 0, curr, n, pew->bacha[i], headd, i);
        }
    }
}
Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    n_matches = 0;
    int matched = 0;
    int n = pattern.length();
    dhudhobhaiya(pattern, n_matches, matched, abhi, n, root, head, -1);
    return head;
}
// int main()
// {
//     // std::string filename = "mahatma-gandhi-collected-works-volume-1.txt";
//     // SearchEngine *cc = new SearchEngine();
//     // // Open the file
//     // int x=0;
//     // int l=0;
//     // std::ifstream file(filename);

//     // if (file.is_open())
//     // {
//     //     // Read the file contents into a string
//     //     std::string fileContents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
//     //     // Close the file
//     //     file.close();

//     //     // Display the string
//     //     string a="";
//     //     cout<<"pitaji ki size "<<fileContents.size()<<endl;
//     //     for(int i=0;i<fileContents.size();i++)
//     //     {
//     //         if(fileContents[i]=='(')
//     //         {
//     //             l++;
//     //             cc->insert_sentence(1, 1, 1, 1,a, x);
//     //             a="";
//     //         }
//     //         else
//     //         {
//     //             a+=fileContents[i];
//     //         }
//     //     }
//     // }
//     // else
//     // {
//     //     std::cerr << "Failed to open the file: " << filename << std::endl;
//     // }
//     // cout<<"x is "<<x<<endl;
//     // cout<<x/l<<endl;
//     // // int x = 0;
//     // // string s1 = "abcabcaby";
//     // // string s2 = "This is my baba's bacha";
    
    
//     // // cc->insert_sentence(2, 2, 2, 2, s2, x);
//     // // int chikboom = 0;
//     // // Node *ding = cc->search("abcaby", chikboom);
//     // // Node *temp = ding;
//     // // while (temp != NULL)
//     // // {
//     // //     temp->printer();
//     // //     temp = temp->right;
//     // // }
//     // // cout << "x is " << x << endl;
//     // Specify the file name
//     std::string filename = "mahatma-gandhi-collected-works-volume-1.txt";

//     // Open the file
//     std::ifstream file(filename, std::ios::binary);

//     if (file.is_open()) {
//         // Determine the file size
//         file.seekg(0, std::ios::end);
//         std::streampos fileSize = file.tellg();

//         // Close the file
//         file.close();

//         // Display the file size in bytes
//         std::cout << "Total number of characters (bytes) in the file: " << fileSize << std::endl;
//     } else {
//         std::cerr << "Failed to open the file: " << filename << std::endl;
//     }

//     return 0;
// }

