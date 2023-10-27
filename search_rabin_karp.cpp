// Do NOT add any other includes
#include "search_rabin_karp.h"

SearchEngine::SearchEngine(){
    baseSize = 0;
}

SearchEngine::~SearchEngine(){
    for(int i = 0;i<baseSize;i++){
        delete base[i].second;
    }
}

void tolower(string &a){
    
    for(int i= 0;i<a.size();i++){
        a[i] = tolower(a[i]);
    }
    
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Node* in = new Node(book_code,page,paragraph,sentence_no,0);
    tolower(sentence);
    base.push_back({sentence,in});
    baseSize++;
}

void insert(Node* &head, Node* &tail, Node* in){
    if(head == nullptr){
        head = in;
        tail = in;
    }
    else{
        tail -> right = in;
        in -> left = tail;
        tail = in;
    }
}


vector<int> searcher(string &sent,string &pattern,long long int &patternka,long long int &madad){
    
    long long int mulwala = 256;
    long long int modwala = 2147483647;
    
    long long int mainka = 0;
    
    int a = pattern.size();
    int b = sent.size();
    vector<int> ans;
    if(a>b){
        return ans;
    }
    
    for(int i = 0;i<a;i++){
        int d = sent[i] - 32;
        mainka = (mainka * mulwala + d)% modwala;
    }
    for(int i = 0;i<b;i++){
        if(mainka == patternka){
            if(pattern == sent.substr(i,a))
            ans.push_back(i);
        }
        if(i+a < b){
            mainka = ((mulwala*(mainka - madad*(sent[i] - 32))) + (sent[i+a] -32))%modwala;
            if(mainka < 0){
                mainka = mainka + modwala;
            }
        }
        else{
            break;
        }
    }
    return ans;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    Node* head = nullptr;
    Node* tail = nullptr;
    tolower(pattern);
    long long int mulwala = 256;
    long long int modwala = 2147483647;
    long long int patternka = 0;
    long long int madad = 1;
    int a = pattern.size();
    for(int i = 0;i<a;i++){
        int c = pattern[i] - 32;
        
        patternka = (patternka * mulwala + c)% modwala;
        
    }
    for(int i = 0;i<a - 1;i++){
        madad = (madad * mulwala)%modwala;
    }
    for(int i = 0;i<baseSize;i++){
           
        vector<int> ans = searcher(base[i].first,pattern,patternka,madad);
        
        for(int j = 0;j<ans.size();j++){
            Node* newa = new Node(base[i].second ->book_code,base[i].second -> page,base[i].second -> paragraph,base[i].second -> sentence_no,ans[j]);
            newa -> left = nullptr;
            newa -> right = nullptr;
            insert(head,tail,newa);
            n_matches++;
        }
    }
    return head;
}

// int main(){
//     string a = "  Cute";
//     //string b = "Namste My meme is great";
//     SearchEngine* s = new SearchEngine();
//     s -> insert_sentence(0,0,0,1,a);
//     //s -> insert_sentence(0,0,0,2,b);
//     int c = 0;
//     //cout<<a[38]<<a[39]<<a[40]<<a[41]<<endl;
//     Node* an = s -> search("cute",c);
//     if(an == NULL){
//         cout<<"nhi mila"<<endl;
//     }
//     while(an != NULL){
//         cout<<an -> offset<<endl;
//         an = an -> right;
//     }
// }