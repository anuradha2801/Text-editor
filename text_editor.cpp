#include <bits/stdc++.h>
using namespace std;

/*------node class or creating storage for the text-----------------------------------*/
class node
{
public:
    string data;
    node *nxt;
    node(string data)
    {
        this->data = data;
        this->nxt = NULL;
    }

    ~node()
    {
        string value = this->data;
        if (this->nxt == NULL)
        {
            delete nxt;
        }
        this->nxt = NULL;
        cout << value << " is is deleted" << endl;
    }
};

/*--------function to display the operations which operation will be performed according to the pressed key-----------------------------------------------------------------------*/
void operations_display()
{
    cout << "**********************************************************" << endl;
    cout << "press 0 to help " << endl;
    cout << "press 1 to  insert new text" << endl;
    cout << "press 2 to delete text" << endl;
    cout << "press 3 to update text" << endl;
    cout << "press 4 to append text" << endl;
    cout << "press 5 to search text" << endl;
    cout << "press 6 to display all the texts" << endl;
    cout << "press 7 to save text permanently" << endl;
    cout << "press 8 to UNDO operation" << endl;
    cout << "press 9 to REDO operation" << endl;
    cout<<"press 11 to show permanently saved data in file"<<endl;
    cout << "press 10 to exit" << endl;
    cout << "==========================================================" << endl;
}

/*----------------inserting node to the copied linked list--------------------------------*/
void insert_Node_Copy(node* &head,string data)
{
    node* newnode=new node(data);
    if(head==NULL){
    head=newnode;
    return;
    }

    node*temp=head;
    while(temp->nxt!=NULL)
    {
        temp=temp->nxt;
    }
    temp->nxt=newnode;
}

/*----------------creating a copy of linked list----------------------------------------*/
node* cpyLL(node* head)
{
   
    node* newhead=NULL;
    node* temp=head;
    while(temp!=NULL)
    {
        string data=temp->data;
        insert_Node_Copy(newhead,data);
        temp=temp->nxt;
    }
    return newhead;
}
/*------------------------add all the operations to stack---------------------------------*/
void AddToStack(node* &head, stack<node*>&undo)
{
node* newhead=cpyLL(head);
undo.push(newhead);
}

/*--------------------undo operation------------------------------*/
void UndoOperation(node* &head, stack<node*> &undo, stack<node*>&redo)
{
    node* newhead=cpyLL(head);
    if(undo.empty())
    {
        cout<<"Cannot perform undo operation."<<endl;
    }else{
        
        redo.push(newhead);
        
        head=undo.top();
        undo.pop();
        cout<<"Undo operation performed successfully!"<<endl;
    }
}

/*-----------------------------redo operation-------------------------*/
void RedoOperation(node* &head,stack<node*>&redo)
{
    if(redo.empty())
    {
        cout<<"Cannot perform redo operation."<<endl;
        return;
    }else{
        head=redo.top();
        redo.pop();
        cout<<"Redo operation performed successfully!!"<<endl;
    }
}

/*---------------------------------insertion function-----------------------------------*/
void insertNode(node *&head, string data,stack<node*>&undo)
{
    
    AddToStack(head,undo);
    node *newnode = new node(data);
    if (head == NULL)
    {
        head = newnode;
        return;
    }
    node *temp = head;
    while (temp->nxt != NULL)
    {
        temp = temp->nxt;
    }
    temp->nxt = newnode;
    newnode->nxt = NULL;
}

/*--------deleting text fromt the text editor-------------------------------------*/
void deleteNode(node* &head, int pos,stack<node*>&undo)
{
    if(pos==1)
    {
        node* current=head;
        head=head->nxt;
        current->nxt=NULL;
        delete current;
    }else{
        node* current=head;
        node* previous=NULL;
        int cnt=1;
        while(cnt<pos)
        {
            previous=current;
            current=current->nxt;
            cnt++;
            if(current==NULL)
            {
                cout<<"Invalid Position"<<endl;
            }
        }
        previous->nxt=current->nxt;
        current->nxt=NULL;
        delete current;
        // AddToStack(head,undo);
    }
      AddToStack(head,undo);
}

/*-----------------Update text function---------------------------------*/
void update(node* &head, int pos, string u_str, stack<node*>&undo)
{
if(head==NULL)
{
   cout<<"No data available to update!"<<endl;
}

node* temp=head;
int cnt=1;
while(cnt<pos )
{
    cnt++;
    if(temp->nxt==NULL)
    {
        cout<<"Invalid position"<<endl;
        break;
    }
temp=temp->nxt;
}
if(temp!=NULL){

temp->data=u_str;
cout<<"Data has been updated sucessfully!"<<endl;
AddToStack(head,undo);
}
 //AddToStack(head,undo);
}

/*---------displaying all the text---------------------------------------*/
void display(node *&head)
{
    if (head == NULL)
    {
        cout << "No text to display" << endl;
    }
    node *temp = head;
   // int count=0;
    while (temp != NULL)
    {
        cout<<temp->data << endl;
        temp = temp->nxt;
    }
    cout << endl;
}

/*--------------function for appending more text to the specified location--------------*/
void appendText(node* &head, int pos, string str, stack<node*>&undo)
{
   if(head==NULL)
   {
    //insertNode(head,str,undo);
    cout<<"No data available"<<endl;
   }
    node* temp=head;
    int cnt=1;
    while(cnt<pos)
    {
    
        cnt++;
        if(temp->nxt==NULL)
        {
            cout<<"Invalid position"<<endl;
            break;
        }
        temp=temp->nxt;
    }
if(temp!=NULL){
temp->data=temp->data+str;
 AddToStack(head,undo);
}
}

/*--------------function for searching the text--------------*/
void searchText(node* &head, string key)
{
    if(head==NULL)
    {
        cout<<"No data is available"<<endl;
    }
    node* temp=head;
   int cnt=1;
   bool flag=true;
    while(temp!=NULL)
    {
       string str=temp->data;
       if(str.find(key)!=-1)
       {
         cout<<key<<" is present in "<< str <<" in line no. "<<cnt<<endl;
         flag=false;
         //break;
       }
     cnt++;
    temp=temp->nxt;
    }
    if(temp==NULL && flag==true)
    cout<<key<<" is not present"<<endl;
}

/*-------------------------------Saving data permanently--------------*/
void saveDataParmanently(node* head)
{
node* temp=head;
ofstream fileInput("text_editor.txt");
while(temp!=NULL)
{
    fileInput<<temp->data<<endl;
    temp=temp->nxt;
}
fileInput.close();
cout<<"Data has been save successfully in text_editor.txt file"<<endl;
}

/*---------------function to show parmanently saves data of file----------*/
void showFileData()
{
    ifstream fileOutput("text_editor.txt");
    string line;
    int i=0;
    while(fileOutput)
    {
        i++;
        getline(fileOutput,line);
        cout<<i<<". "<<line<<endl;
    }
    if(i==0){
        cout<<"No data available in file."<<endl;
    }
}

/*---------MAIN FUNCTION-------------------------------------------------*/
int main()
{
    cout << "**********************************************************" << endl;
    cout << "C++ Text Editor" << endl;
    operations_display();
    node *head = NULL;
    bool exit = 1;
    stack<node*>undo;
    stack<node*>redo;
    while (exit)
    {
        // operations_display();
        cout << "Enter query: ";
        int query;
        cin >> query;
        if(query==10)
        {
            break;
        }
        switch (query)
        {
        case 0:
        {
            operations_display();
            break;
        }
        case 1:
        {
            cout << "Enter text to insert: ";
            string s;
            getline(cin,s);
            getline(cin,s);
            insertNode(head, s,undo);
            cout<<"New text inserted"<<endl;
            break;
        }

        case 2:
        {

            cout << "The the position of Text you want to delete: ";
            int pos;
            cin >> pos;
            deleteNode(head,pos,undo);
            cout<<"data deleted at pos "<<pos<<endl;

            break;
        }
        case 3:
        {
            cout<<"Enter position at which you want to update: ";
            int pos;
            cin>>pos;
            cout<<"Enter the new updated text: ";
            string u_str;
            getline(cin,u_str);
            getline(cin,u_str);
            update(head, pos,u_str,undo);
           // cout<<pos<<" is updated with "<<u_str<<endl;
            break;
        }
        case 4:
        {
            cout<<"Enter the line at which you want to append text: ";
            int pos;
            cin>>pos;
            cout<<"Enter the new text to be appended: ";
            string str;
            getline(cin,str);
            getline(cin,str);
            appendText(head,pos,str,undo);
            cout<<str<<" is appended at "<<pos<<"th line"<<endl;
            break;
        }
           

        case 5:
        {
            cout<<"Enter the text you want to search: ";
            string key;
            cin>>key;
            searchText(head,key);

            break;
        }

        case 6:
        {
            cout<<endl;
            cout << "The texts are:" << endl;
            display(head);
            break;
        }
        case 7:
        {
           if(head==NULL)
           {
           cout<<"No data available to save!"<<endl;
           }
           else{
            saveDataParmanently(head);
           }
            break;
        }

        case 8:
        {
             cout<<"Undo Operation!"<<endl;
             UndoOperation(head,undo,redo);
            break;
        }

        case 9:
        {
            cout<<"Redo Operation!"<<endl;
            RedoOperation(head,redo);
            break;
        }

        case 10:
        {
            exit = false;
            break;
        }

        case 11:
        {
            showFileData();
            break;
        }


        default:
        {
        cout<<"Please Enter Valid Command!!"<<endl;
         //exit = false;
            break;
        }

        }
    }

    return 0;
}