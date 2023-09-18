#include "Sequencer.h"

Sequencer::Sequencer(string fileName){
  //Creates a new sequencer to hold one or more DNA/mRNA strands make of
  //       multiples of three nucleotides
    m_fileName = fileName;
}

Sequencer::~Sequencer(){
  // destructs every Strand in each vector
    cout << "Deleting DNA Strands" << endl;
    for(int i = 0; i <  int(m_DNA.size()); i++){
        delete m_DNA.at(i);
        m_DNA.at(i) = nullptr;
    }
    cout << "Deleting mRNA Strands" << endl;
    for(int i = 0; i < int(m_mRNA.size()); i++){
        delete m_mRNA.at(i);
        m_mRNA.at(i) = nullptr;
    }
}

void Sequencer::StartSequencing(){
  //Calls ReadFile and continually calls mainmenu until the user exits
    int userInput;
    ReadFile();
    do{
        userInput = MainMenu();
        switch(userInput){
            case 1:
                DisplayStrands();
                break;
            case 2:
                ReverseSequence();
                break;
            case 3:
                Transcribe();
                break;
            case 4:
                Translate();
                break;
            default:
                cout << "Exiting Program" << endl;
                break;
        }
    }while(userInput !=5);
}

void Sequencer::DisplayStrands(){
  //goes through each strand and displays the node
    for(int i = 0; i <int(m_DNA.size()); i++){
        cout << "DNA " << i+1 << endl;
        cout << "***" << m_DNA.at(i)->GetName()  << "***" << endl; //print out the name
        cout << *m_DNA.at(i) << endl;
    } 
    for(int i = 0; i <int(m_mRNA.size()); i++){
    cout << "mRNA " << i+1 << endl;
    cout << "***" << m_mRNA.at(i)->GetName()  << "***" << endl;
    cout << *m_mRNA.at(i) << endl;
    } 
}
 
void Sequencer::ReadFile(){
  //Reads in a file of DNA strands that has the name on one line then
  //       the sequence on the next
    string strand, name;
    ifstream myfile(m_fileName);
    if(myfile.is_open()){
        getline(myfile, name, ',');
        while(name != ""){
            getline(myfile, strand);
            Strand *newStrand = new Strand(name);
            for(int i = 0; i < int(strand.length()); i+=2)
                newStrand->InsertEnd(strand[i]);
            m_DNA.push_back(newStrand);
            getline(myfile, name, ',');
            

        };
    }
    else{
        cout << "couldnt open file" << endl;
    }
}

int Sequencer::MainMenu(){
  //Displays the main menu and manages exiting.
  //       Returns 5 if the user chooses to quit
    int input;
    do{
        cout << "What would you like to do:" << endl;
        cout << "1. Display Strands" << endl;
        cout << "2. Reverse Strand" << endl;
        cout << "3. Transcribe DNA to mRNA" << endl; 
        cout << "4. Translate mRNA to Amino Acids" << endl;
        cout << "5. Exit" << endl;
        cin >> input;
    }while(input < 1 || input > 5);
    return input;
}

int Sequencer::ChooseDNA(){
  //Asks the user to choose one strand to use from loaded DNA strands
    int userInput;
    if(int(m_DNA.size()) != 1){
      do{
          cout << "Which strand to work with? " << endl;
          cout << "Choose 1 - " << int(m_DNA.size()) << endl;
          cin >> userInput;
      }while(userInput > int(m_DNA.size()) || userInput < 1);
    }
    else
      userInput = 1;
    return userInput;
}

int Sequencer::ChooseMRNA(){
  //Asks the user to choose one strand to use from loaded MRNA strands
    int userInput;
    if(int(m_mRNA.size()) != 1){
      do{
          cout << "Which strand to work with? " << endl;
          cout << "Choose 1 - " << int(m_mRNA.size()) << endl;
          cin >> userInput;
      }while(userInput > int(m_mRNA.size()) || userInput < 1);
    }
    else
      userInput = 1;
    return userInput;
}

void Sequencer::ReverseSequence(){
  // User chooses to reverse either DNA or mRNA to reverse
  //       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
  //       Calls ReverseStrand on chosen location
    int userInput;
    int secInput;
    do{
        cout << "Which type of strand to reverse? " << endl;
        cout << "1. DNA" << endl;
        cout << "2. mRNA" << endl;
        cin >> userInput;
    }while(userInput < 1 || userInput > 2);
    if(userInput == 1){
        secInput = ChooseDNA() - 1;
        m_DNA.at(secInput)->ReverseSequence(); // ReverseSequence() gets called from a strand in the vector
        cout << "Done reversing DNA " << secInput + 1 << "'s strand." << endl;
    }
    else{
        if(int(m_mRNA.size()) > 0){
          secInput = ChooseMRNA() -1;
          m_mRNA.at(secInput)->ReverseSequence(); // ReverseSequence() gets called from a strand in the vector
          cout << "Done reversing mRNA " << secInput + 1 << "'s strand." << endl;
        }
        else
          cout << "No mRNA strand to reverse" << endl;
    }
}

void Sequencer::Transcribe(){
  //Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
  // A->U, T->A, C->G, G->C (DNA to mRNA)
  // Can be called multiple times (will result in multiple mRNA strands)
  // Puts the transcribed mRNA strand into m_mRNA
    for(int j = 0; j < int(m_DNA.size()); j++){
        Strand *mStrand = new Strand(m_DNA.at(j)->GetName()); //makes a new strand
        for(int i = 0; i < m_DNA.at(j)->GetSize(); i++){ 
            char mData = m_DNA.at(j) -> GetData(i);
            switch(mData){
                case 'A':
                    mData = 'U';
                    break;
                case 'G':
                    mData = 'C';
                    break;
                case 'T':
                    mData = 'A';
                    break;
                case 'C':
                    mData = 'G';
                default:
                    break;
            }
            mStrand->InsertEnd(mData);
        }
        m_mRNA.push_back(mStrand);

    }
    cout << int(m_DNA.size()) << " strands of DNA successfully transcribed into new mRNA strands" << endl;
    
}

string Sequencer::Convert(const string trinucleotide){
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
	  (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
	  (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
	  (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
	  (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
	  (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
	  (trinucleotide=="UCA")||(trinucleotide=="UCG")||
	  (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	  (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

void Sequencer::Translate(){
  // Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class


  string tri = "";
  if(m_mRNA.size() != 0){
    int input = ChooseMRNA();
    input--;
    cout << "***" << m_mRNA.at(input)->GetName()  << "***" << endl;
    for(int i = 0; i < m_mRNA.at(input)->GetSize(); i+=3){ //loops 3 times
      tri = "";
      for(int j = i; j < i+3; j++)
        tri.push_back(m_mRNA.at(input)->GetData(j));
      cout << tri << "->" << Convert(tri) <<endl;
    }
    cout << "Done translating mRNA "<< input +1 <<"'s strand." << endl;
  }
  else
    cout << "No mRNA to translate; transcribe first" << endl;



}