// Do NOT add any other includes
#include "search_finite_automata.h"

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
    for (int i = 0; i < sentence.size(); i++)
    {
        sentence[i] = tolower(sentence[i]);
    }
    mumm.push_back(sentence);
    dingdong.push_back(new Node(book_code, page, paragraph, sentence_no, 0));
    return;
}
int getNextState(string pat, int M, int state, int x)
{
    // If the character c is same as next character
    // in pattern,then simply increment state
    if (state < M && x == pat[state])
        return state + 1;

    // ns stores the result which is next state
    int ns, i;

    // ns finally contains the longest prefix
    // which is also suffix in "pat[0..state-1]c"

    // Start from the largest possible value
    // and stop when you find a prefix which
    // is also suffix
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
                if (pat[i] != pat[state - ns + 1 + i])
                    break;
            if (i == ns - 1)
                return ns;
        }
    }

    return 0;
}
void computeTF(string pat, int M, int TF[][128])
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < 128; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}
Node *SearchEngine::search(string pattern, int &n_matches)
{
    for(int i=0;i<pattern.size();i++)
    {
        pattern[i]=tolower(pattern[i]);
    }
    // Implement your function here
    Node *temp;
    int pompom[127];
    for (int i = 0; i < 127; i++)
    {
        pompom[i] = -1;
    }
    int m = pattern.size();
    for (int i = 0; i < m; i++)
    {
        pompom[(int)pattern[i]] = i;
    }
    int n;
    int j;
    string toc;
    Node *cu;
    int M = pattern.size();
    int TF[M + 1][128];
    computeTF(pattern, pattern.size(), TF);

    // Process txt over FA.
    for (int il = 0; il < mumm.size(); il++)
    {
        toc=mumm[il];
        int i, state = 0;
        int N=mumm[il].size();
        cu=dingdong[il];
        for (i = 0; i < N; i++)
        {
            state = TF[state][toc[i]];
            if (state == M)
            {
                temp=new Node(cu->book_code,cu->page,cu->paragraph,cu->sentence_no,i - M + 1);
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
            }
        }
    }
    return sir;
}


