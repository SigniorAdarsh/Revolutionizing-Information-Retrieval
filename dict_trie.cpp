// Do NOT add any other includes
#include "dict_trie.h"

Dict::Dict()
{
    // Implement your function here
    root = new DictNode('@');
}

DictNode *Burn(DictNode *node)
{
    for (int i = 0; i < 54; i++)
    {
        if ((node->bacha[i]))
        {
            node->bacha[i] = Burn(node->bacha[i]);
        }
    }
    delete node;
    return NULL;
}

Dict::~Dict()
{
    // Implement your function here
    root = Burn(root);
}

int asciier(int ind, char ch)
{
    if (ind >= 65 && ind <= 90)
    {
        ind += 32;
    }
    if (ind >= 94 && ind <= 126)
    {
        return ind - 94;
    }
    else if (ind >= 47 && ind <= 57)
    {
        return ch - '/' + 33;
    }
    else if (ind >= 60 && ind <= 62)
    {
        return ch - '<' + 44;
    }
    else if (ind >= 35 && ind <= 38)
    {
        return ch - '#' + 47;
    }
    else if (ind >= 42 && ind <= 43)
    {
        return ch - '*' + 51;
    }
    return 53;
}

//". , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @"
void dalo(DictNode *node, string s)
{
    if (s.length() == 0)
    {
        (node->value)++;
        return;
    }
    char ch = s[0];
    int index = (int)(ch);
    // index=asciier(index,ch);
    DictNode *temp;
    if (index >= 65 && index <= 90)
    {
        index += 32;
        ch = tolower(ch);
    }
    if (index >= 94 && index <= 126)
    {
        index = index - 94;
    }
    else if (index >= 47 && index <= 57)
    {
        index = ch - '/' + 33;
    }
    else if (index >= 60 && index <= 62)
    {
        index = ch - '<' + 44;
    }
    else if (index >= 35 && index <= 38)
    {
        index = ch - '#' + 47;
    }
    else if (index >= 42 && index <= 43)
    {
        index = ch - '*' + 51;
    }
    else
    {
        index = 53;
    }
    if ((node->bacha[index]) != NULL)
    {
        temp = node->bacha[index];
    }
    else
    {
        temp = new DictNode(ch);
        node->bacha[index] = temp;
    }
    dalo(temp, s.substr(1));
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    string s = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        // cout<<i<<"s"<<endl;
        char ch = sentence[i];
        int ind = (int)(sentence[i]);
        if (ch == '.' || ch == ',' || ch == '-' || ch == ':' || ch == '!' || ch == '"' || ch == '(' || ch == ')' || ch == '?' || ch == '[' || ch == ']' || ch == ';' || ch == '@' || ch == ' ')
        {
            if (s.length() > 0)
            {
                dalo(root, s);
            }
            s = "";
        }
        else if ((int)(sentence[i]) == 39)
        {
            if (s.length() > 0)
            {
                dalo(root, s);
            }
            s = "";
        }
        else
        {
            s += sentence[i];
        }
        // cout<<s<<endl;
        // cout<<i<<"e"<<endl;
    }
    if (s.length() != 0)
    {
        dalo(root, s);
        s = "";
    }
    return;
}

int khojo(DictNode *node, string s)
{
    if (s.length() == 0)
    {
        return node->value;
    }
    char ch = s[0];
    int index = (int)(ch);
    // index=asciier(index,ch);
    DictNode *temp;
    if (index >= 65 && index <= 90)
    {
        index += 32;
    }
    if (index >= 94 && index <= 126)
    {
        index = index - 94;
    }
    else if (index >= 47 && index <= 57)
    {
        index = ch - '/' + 33;
    }
    else if (index >= 60 && index <= 62)
    {
        index = ch - '<' + 44;
    }
    else if (index >= 35 && index <= 38)
    {
        index = ch - '#' + 47;
    }
    else if (index >= 42 && index <= 43)
    {
        index = ch - '*' + 51;
    }
    else
    {
        index = 53;
    }
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = tolower(ch);
    }
    if (node->bacha[index] != NULL)
    {
        temp = node->bacha[index];
    }
    else
    {
        return 0;
    }
    return khojo(temp, s.substr(1));
}

int Dict::get_word_count(string word)
{
    // Implement your function here
    return khojo(root, word);
}

void khatm(DictNode *temp, string s, ofstream &abhishek)
{
    if (temp->value > 0)
    {
        abhishek << s << ","
                 << " " << temp->value << endl;
    }
    for (int i = 0; i < 54; i++)
    {
        if (temp->bacha[i])
        {
            khatm(temp->bacha[i], s + temp->bacha[i]->key, abhishek);
        }
    }
}

void Dict::dump_dictionary(string filename)
{
    // Implement your function here
    ofstream abhishek;
    string adarsh = filename;
    abhishek.open(adarsh);
    khatm(root, "", abhishek);
    abhishek.close();
    return;
}
// 6 Hair cutting 2 Soap 1 Tooth powder 1 Coal 12 Margin 3 ______ Total 4 s 0 d With 7s for the room rent and 4s for extras we have 9s remaining for food.
// int main(){
//     cout<<"Hii"<<endl;
//     Dict* d=new Dict();
//     cout<<"Hii2"<<endl;
//     d->insert_sentence(0, 0, 0, 0, "An Autobiography, Pt. 1/2lb, Ch. VIII");
//     cout<<"Hii3"<<endl;
//     d->insert_sentence(1, 1, 1, 1, "Sandi mandi andi sandi-(andi)andi 1/2lb");
//     int a=d->get_word_count("andi");
//     int b=d->get_word_count("sandi");
//     int c=d->get_word_count("1/2lb");
//     cout<<a<<' '<<b<<' '<<c<<endl;
//     d->dump_dictionary("out.txt");
//     return 0;
// }

// // Do NOT add any other includes
// #include "dict.h"

// Dict::Dict(){
//     // Implement your function here
//     root=new DictNode('@');
// }

// DictNode* Burn(DictNode* node){
//     for(int i=0 ; i<54 ; i++){
//         if((node->bacha[i])){
//             node->bacha[i]=Burn(node->bacha[i]);
//         }
//     }
//     delete node;
//     return NULL;
// }

// Dict::~Dict(){
//     // Implement your function here
//     root=Burn(root);
// }

// //". , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @"
// void dalo(DictNode* node,string s){
//     if(s.length()==0){
//         (node->value) ++;
//         return;
//     }
//     char ch=s[0];
//     int index=(int)(ch);
//     DictNode* temp;
//     if(ch>='0' && ch<='9'){
//         index=ch-'0';
//     }
//     else if(ch>='a' && ch<='z'){
//         index=ch-'a'+10;
//     }
//     else if(ch>='A' && ch<='Z'){
//         index=ch-'A'+10;
//         ch=tolower(ch);
//     }
//     else if(index>=35 && index<=38){
//         index=ch-'#'+36;
//     }
//     else if(index>=42 && index<=43){
//         index=ch-'*'+40;
//     }
//     else if(index==47){
//         index=ch-'/'+42;
//     }
//     else if(index>=60 && index<=62){
//         index=ch-'<'+43;
//     }
//     else if(index==92){
//         index=46;
//     }
//     else if(index==94){
//         index=47;
//     }
//     else if(index==96){
//         index=48;
//     }
//     else if(index>=123 && index<=126){
//         index=ch-'{'+49;
//     }
//     else if(index==95){
//         index=53;
//     }
//     if((node->bacha[index])!=NULL){
//         temp=node->bacha[index];
//     }
//     else{
//         temp=new DictNode(ch);
//         node->bacha[index]=temp;
//     }
//     s=s.substr(1);
//     dalo(temp,s);
// }

// void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
//     // Implement your function here
//     string s="";
//     for(int i=0 ; i<sentence.length() ; i++){
//         char ch=sentence[i];
//         if(ch=='.' || ch==',' || ch=='-' || ch==':' || ch=='!' || ch=='"'  || ch=='(' || ch==')' || ch=='?' || ch=='[' || ch==']' || ch==';' || ch=='@' || ch==' '){
//             dalo(root,s);
//             s="";
//         }
//         else if((int)(sentence[i])==39){
//             dalo(root,s);
//             s="";
//         }
//         else{
//             s+=sentence[i];
//         }
//     }
//     if(s.length()!=0){
//         dalo(root,s);
//         s="";
//     }
//     return;
// }

// int khojo(DictNode* node,string s){
//     if(s.length()==0){
//         return node->value;
//     }
//     char ch=s[0];
//     int index=(int)(ch);
//     DictNode* temp;
//     if(ch>='0' && ch<='9'){
//         index=ch-'0';
//     }
//     else if(ch>='a' && ch<='z'){
//         index=ch-'a'+10;
//     }
//     else if(ch>='A' && ch<='Z'){
//         index=ch-'A'+10;
//         ch=tolower(ch);
//     }
//     else if(index>=35 && index<=38){
//         index=ch-'#'+36;
//     }
//     else if(index>=42 && index<=43){
//         index=ch-'*'+40;
//     }
//     else if(index==47){
//         index=ch-'/'+42;
//     }
//     else if(index>=60 && index<=62){
//         index=ch-'<'+43;
//     }
//     else if(index==92){
//         index=46;
//     }
//     else if(index==94){
//         index=47;
//     }
//     else if(index==96){
//         index=48;
//     }
//     else if(index>=123 && index<=126){
//         index=ch-'{'+49;
//     }
//     else if(index==95){
//         index=53;
//     }
//     if(node->bacha[index]!=NULL){
//         temp=node->bacha[index];
//     }
//     else{
//         return 0;
//     }
//     s=s.substr(1);
//     return khojo(temp,s);
// }

// int Dict::get_word_count(string word){
//     // Implement your function here
//     return khojo(root,word);
// }

// void khatm(DictNode* temp , string s, ofstream &abhishek){
//     if(temp->value>0){
//         abhishek<<s<<","<<" "<<temp->value<<endl;
//     }
//     for(int i=0 ; i<54 ; i++){
//       if(temp->bacha[i]){
//         khatm(temp->bacha[i] , s+temp->bacha[i]->key,abhishek);
//       }
//     }
// }

// void Dict::dump_dictionary(string filename){
//     // Implement your function here
//     ofstream abhishek;
//     string adarsh=filename;
//     abhishek.open(adarsh);
//     khatm(root,"",abhishek);
//     abhishek.close();
//     return;
// }

// // int main(){
// //     cout<<"Hii"<<endl;
// //     Dict* d=new Dict();
// //     cout<<"Hii2"<<endl;
// //     d->insert_sentence(0, 0, 0, 0, "An Autobiography, Pt. 1/2lb, Ch. VIII");
// //     cout<<"Hii3"<<endl;
// //     d->insert_sentence(1, 1, 1, 1, "Sandi mandi andi sandi-(andi)andi 1/2lb");
// //     int a=d->get_word_count("andi");
// //     int b=d->get_word_count("sandi");
// //     int c=d->get_word_count("1/2lb");
// //     cout<<a<<' '<<b<<' '<<c<<endl;
// //     d->dump_dictionary("out.txt");
// //     return 0;
// // }