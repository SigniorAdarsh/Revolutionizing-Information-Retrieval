// Do NOT add any other includes
#include "search_boyer_moore.h"

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
    // Implement your function here
    for(int i=0;i<sentence.size();i++)
    {
        sentence[i]=tolower(sentence[i]);
    }
    mumm.push_back(sentence);
    dingdong.push_back(new Node(book_code,page,paragraph,sentence_no,0));
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    sir=NULL;
    abhi=NULL;
    for(int i=0;i<pattern.size();i++)
    {
        pattern[i]=tolower(pattern[i]);
    }
    Node*temp;
    int pompom[127];
    for(int i=0;i<127;i++)
    {
        pompom[i]=-1;
    }
    int m=pattern.size();
    for(int i=0;i<m;i++)
    {
        pompom[(int)pattern[i]]=i;
    }
    int n;
    int j;
    string toc;
    Node*cu;
    for(int i=0;i<mumm.size();i++)
    {
        cu=dingdong[i];
        n=mumm[i].size();
        int s=0;
        toc=mumm[i];
        while(s<=(n-m))
        {
            j=m-1;
            while(j>=0&&pattern[j]==toc[s+j])
            {
                j--;
            }
            if(j<0)
            {
                temp=new Node(cu->book_code,cu->page,cu->paragraph,cu->sentence_no,s);
                if(sir==NULL)
                {
                    sir=temp;
                    abhi=temp;
                }
                else
                {
                    abhi->right=temp;
                    temp->left=abhi;
                    abhi=temp;
                }
                n_matches++;
                s+=(s+m<n)?m-pompom[toc[s+m]]:1;
            }
            else
            {
                s+=max(1,j-pompom[toc[s+j]]);
            }
        }
    }
    return sir;
}
// int main()
// {
//     int x=0;
//     SearchEngine *puke=new SearchEngine();
//     puke->insert_sentence(1,1,1,1,"This is my name");
//     puke->search("nam",x)
// }
