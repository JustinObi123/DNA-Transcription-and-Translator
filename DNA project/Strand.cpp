#include "Strand.h"


Strand::Strand(){
    //Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Strand::Strand(string name){
    // Used to build a new empty strand with the name passed
  //       with m_head, m_tail = nullptr; size = 0;
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Strand::~Strand(){
    //Strand is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks
  // by iterating through the linked list
    Node *curr = m_head;
    while(curr != nullptr){
        m_head = curr;
        curr = curr ->m_next;
        delete m_head;
    }
    m_head = nullptr;
}

void Strand::InsertEnd(char data){
    //Takes in a char. Creates a new node.
  //       Inserts node at the end of the strand. Increases size.
    Node *temp = new Node(); // dynamically allocated
    Node *curr = m_head;
    temp->m_data = data;
    temp->m_next = nullptr;
    if(m_size == 0){
        m_head = temp;
        m_tail = temp;
        m_size++;
    }
    else{
        while(curr->m_next != nullptr) 
            curr = curr->m_next;
        curr->m_next = temp;
        m_tail = temp;
        m_size++;
        
    }
}

string Strand::GetName(){
    return m_name;
}

int Strand::GetSize(){
    return m_size;
}

void Strand::ReverseSequence(){
    // Returns the data at a specific location in the strand.
  //       Iterates to node and returns char.
    Node *curr = m_head;
    Node *next = m_head;
    Node *prev = nullptr;
    Node *temp = m_tail;
    
    while(curr != nullptr){
        next = curr->m_next;
        curr->m_next = prev;
        prev = curr;
        curr = next;
    }
    m_tail = m_head;
    m_head = temp;
}

char Strand::GetData(int nodeNum){
    //Returns the data at a specific location in the strand.
  //       Iterates to node and returns char.
    Node *curr = m_head;
    int count = 0;
    while(count != nodeNum){
        curr = curr->m_next;
        count++;
    }
    return curr->m_data;

}

ostream &operator<< (ostream &output, Strand &myStrand){
    //Iterates over the entire strand and builds an output stream
    Node *temp = myStrand.m_head; // points at the first node
    while(temp != nullptr){
        output << temp->m_data << "->"; // outputs the char with "->"
        temp = temp -> m_next;
        
    }
    output << "END";
    return output;
}