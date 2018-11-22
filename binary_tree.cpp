/*
Course: Data Structures
Lab project
Read a file with words,create a list of nodes,find the length of every word,print,delete,search and create a new file with every detail
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct node{
	char word[15];
	int line[20];
	int nline;
	struct node *left;
	struct node *right;
};

int read_line (struct node *&);// CASE 1
void insert (struct node *,struct node *&,int ,int ); //CASE 1,3
void print (struct node *& ); //CASE 2
void search (struct node *&,char []); //CASE 4
void delete2(struct node*&); //CASE 5
void delete1 (struct node *&,char []); //CASE 5
void write_file(struct node *&); //CASE 6
void menu();

int k=0;
int m=0;
int s=0;
char rest1[100];

clock_t start, end;
double elapsed;


int main(){
int epil;
string arxeio;
char word1[20];
struct node *n;
n=NULL;

do{

    menu();
    cin>>epil;

    if(epil==1){
        start = clock();
        read_line(n);
        end=clock();
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;}


    else if(epil==2){
        print(n);
        cout<<"Number of words: "<<k<<endl;
        cout<<"Words: "<<m<<endl;
        cout<<"Time to create: "<<elapsed<<endl;
        cout<<endl;}


    else if(epil==3){
        struct node *newnode=new node;
         cout<<"Word to insert: "<<endl;
         cin>>newnode->word;

        insert(newnode,n,0,1);}

    else if(epil==4){
        cout<<"Word to search: "<<endl;
        cin>>word1;
        search(n,word1);}

    else if(epil==5){
        cout<<"Word to delete: "<<endl;
        cin>>word1;

        delete1(n,word1);}

    else if(epil==6){
        write_file(n);
        cout<<endl;
        cout<<"File is Ready: Checked!"<<endl;}

}while(epil!=7&&epil<7);
}


void menu(){
cout<<"1. Insert words in the binary tree"<<endl;
cout<<"2. Show every word of the tree"<<endl;
cout<<"3. Insert a new word"<<endl;
cout<<"4. Search a word"<<endl;
cout<<"5. Delete a word"<<endl;
cout<<"6. Create new file for the tree"<<endl;
}


int read_line(struct node *&n){
	char sentence[250];

	ifstream file; ///open file
    file.open("test.txt");

	if (file.is_open()) ///check
		cout << "File Open: Checked" << endl;
	else
		cout << "File Open: Error" << endl;

    char *rest;
    char *word;

	while (file.getline(sentence, 249) != NULL){  //read a line

        word = strtok(sentence," "); //split
        s=s+1;

        while(word!=NULL){
            struct node *newnode=new node;
            strcpy(newnode->word,word);
            insert(newnode,n,s,0);  //calling insert, 0 means that the word
            word = strtok(NULL," ");
            k=k+1;}}

    return s;}


void insert(struct node *newnode,struct node *&n,int s,int p){ //insert node to the tree

if((n)==NULL){ //if is null,inserting

    if(p==0){
    newnode->nline=0;
    newnode->line[newnode->nline]=s;
    }
    n=newnode;
    n->left=NULL;
    n->right=NULL;
    m=m+1;}

else if(strcmp(newnode->word,n->word)<0){ //if is bigger I call again insert for the right side child
    if(p==0){
    insert(newnode,n->right,s,0);}

    else{
    insert(newnode,n->right,s,1); }}

else if(strcmp(newnode->word,n->word)>0){ //if is smaller i call insert for the left side child
    if(p==0){
    insert(newnode,n->left,s,0);}

    else{
    insert(newnode,n->left,s,1); }}

else if(strcmp(newnode->word,n->word)==0){ //if is equal, i am not inserting anything just change the row of elements
            int k;
   if(p==0){
    for(int i=0;i<=n->nline;i++){

        if(n->line[i]==s){
           k=1;}

        else{
            k=0;}}

    if(k!=1){
    n->nline=n->nline+1;
    n->line[n->nline]=s;}}

    else{
        cout<<"Word already exist.Insert of the word is not acceptable."<<endl;}
        }
    }



void print(struct node *& n){ //show tree elements

if(n==NULL){
    return;}

print(n->left); //IN ORDER-from left to right
cout<<n->word<<" ";

for(int i=0; i<=n->nline; i++){

    cout<<n->line[i]<<" ";}

cout<<endl;

print(n->right);}


void search(struct node *&n,char word1[20]){

  if(n==NULL)
     cout<<"There is no tree."<<endl;

  else{
    if(strcmp(n->word,word1)>0){
        search(n->right,word1);}

    else if (strcmp(n->word,word1)<0){
        search(n->left,word1);}

    else{
        cout<<"Word: "<<word1;   //if the word is there, it will printed with its details
        for(int i=0;i<=n->nline;i++){

            if ( n->line[i] != n->line[i+1])
                cout<<" "<<n->line[i];}

        cout<<" VRETHIKE"<<endl;}}

}

void delete1(struct node *&n,char word1[]){ //Delete of element

if (n== NULL)
	return;

   if (strcmp(n->word,word1)<0)
     delete1 (n->left,word1);

   else if (strcmp(n->word,word1)>0)
     delete1(n->right,word1);

   else
     delete2(n);} //if i found the element,i am calling delete2 to do the process


void delete2(struct node *&n){ //Delete process

  node *temp;

  temp = n;

  if (n->left == NULL){  //if n hasn't a left child.
	n= n->right;
	delete temp;}

  else if (n->right == NULL){ //if n hasn't a right child.
      	n=n->left;
	delete temp;}

  else{ //if is there both left and right childs, i am calling again delete1 for the left child
     temp=n->left;
     while (temp->right != NULL)
       temp = temp->right;
       n->word[20]= temp->word[20];
       delete1(n->left, temp->word); }
}


void write_file(struct node *&n){  //insert to file and print of elements

    ofstream file ("output.txt",std::ios_base::app | std::ios_base::out);

    if (n==NULL)
        return;

      write_file(n->left);

      file<<n->word<<" ";

    for (int i=0;i<= n->nline;i++){
        if ( n->line[i] != n->line[i+1])
            file<<n->line[i] << " ";}

            file<<"\n";
            write_file(n->right);


}
