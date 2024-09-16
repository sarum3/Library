// Siri Arumilli - UIN: 664104217
// CS 251 Project 1 - Prof Koehler
// The Library Management System program allows the user to perform a variety of tasks
// used to simulate a functioning library
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition

void addItem(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void clearLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void coutStats(vector<string>& bookTitles, vector<int>& checkOutStatus);

string cleanIsbn(string isbnStr);

void displayLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void deleteItem(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void invalid(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void loadLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

void outputLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

string printCheckout(vector<int>& checkOutStatus, int index);

void printMenu();

void searchFunction(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus);

bool validateTitle(string title);


int main()
{
    string command;

    // the following vectors are the data structures used to hold each element of a book
    // which inludes the book titles, isbn codes, and checkout status of each book
    // the 3 vectors together make up the "library"
    vector<string> bookTitles(0);
    vector<string> isbnCodes(0);
    vector<int> checkOutStatus;


    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        // commands for non-exit calls
        if(command == "a" || command == "A"){
            addItem(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "d" || command == "D"){
            displayLibrary(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "c" || command == "C"){
            clearLibrary(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "l" || command == "L"){
            loadLibrary(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "p" || command == "P"){
            coutStats(bookTitles, checkOutStatus);
        }else if(command == "o" || command == "O"){
            outputLibrary(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "s" || command == "S"){
            searchFunction(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "r" || command == "R"){
            deleteItem(bookTitles, isbnCodes, checkOutStatus);
        }else if(command == "i" || command == "I"){
            invalid(bookTitles, isbnCodes, checkOutStatus);
        }
        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

// Function definitions for all the glorious function decomposition

// adds a book to the library using the title and isbn
// parameters are the 3 vector data types holding the book titles, isbn codes, and checkout status
// vectors are passed by reference to be modified
void addItem(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus)
{
    cout << "What is the book title? " << endl;
    string title;
    getline(cin >> ws, title);
    if(validateTitle(title))
    { 
      cout << "What is the 13-digit ISBN (with hyphens)? " << endl;
      string isbn;
      getline(cin >> ws, isbn);
      bookTitles.push_back(title);
      isbnCodes.push_back(isbn);
      checkOutStatus.push_back(0);
      cout << "The Following Entry Was Added\n-----------------------------\n";
      cout << title << " --- " << isbn << " --- In Library\n";
    }else{
      cout << "The book title cannot contain commas.\n";
    }
}

// validates the isbn calculations
// parameter is a string that consists of the isbn cleaned up (no hyphens)
// returns true of the isbn is valid, false if not
bool checkIsbn(string isbn){
  int sum = 0;
  if(isbn.size() == 13)
  {
    for(int i = 0; i < 12; i++){
      int numVal = stoi(isbn.substr(i,1));
      if(i % 2 == 0){
        sum += numVal;
      }else{
        sum += numVal * 3;
      }
    }
    int checkVal = sum % 10;
    checkVal = 10 - checkVal;    
    if(checkVal == stoi(isbn.substr(12)))
    {
      return true;
    }
  }
  return false;
}

// clears the current library by clearing all the data structures that make up the contents of the library
// parameters: the 3 vectors that hold the library contents, passed by reference to be modified
void clearLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus)
{
    bookTitles.clear();
    isbnCodes.clear();
    checkOutStatus.clear();
    cout << "Your library is now empty.\n";
}

// prints stats on the checkout status of all the library's book
// parameters: vector of book titles, and vector of checkout status' 
void coutStats(vector<string>& bookTitles, vector<int>& checkOutStatus){
    cout << "Your Current Library's Stats\n----------------------------\n";
    cout << "Total Books: " << bookTitles.size() << endl;
    int zero = 0;
    int one = 0;
    int two = 0;
    int three = 0;
    int other = 0;
    for(int i = 0; i < checkOutStatus.size(); i++){
      if(checkOutStatus.at(i) == 0)
      {
        zero++;
      }else if(checkOutStatus.at(i) == 1){
        one++;
      }else if(checkOutStatus.at(i) == 2){
        two++;
      }else if(checkOutStatus.at(i) == 3){
        three++;
      }else{
        other++;
      }
    }
    cout << "   In Library: " << zero << endl;
    cout << "   Checked Out: " << one << endl;
    cout << "   On Loan: " << two << endl;
    cout << "   Unknown: " << three << endl;
    cout << "   Other: " << other << endl;
}

// cleans up the isbn string by removing hyphens
// parameter: isbn string that has hyphens separating the numbers
// returns a string of the isbn code without any hyphens
string cleanIsbn(string isbnStr){
  string isbn;
  for(int i = 0; i < isbnStr.size(); i++){
    if(isbnStr[i] != '-')
    {
      isbn += isbnStr[i];
    }
  }
  return isbn;
}

// prints out the current library, containing book title, isbn, & checkout status of each item
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void displayLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus)
{
    cout << "Your Current Library\n--------------------\n";
    for(int i = 0; i < bookTitles.size(); i++){
        cout << bookTitles.at(i) << " --- " << isbnCodes.at(i) << " --- " << printCheckout(checkOutStatus, i);
    }
    if(bookTitles.size() == 0)
    {
        cout << "The library has no books.\n";
    }
}

// searches for an item in the library and deletes it
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void deleteItem(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus){
  cout << "Would you like remove by (1) name or (2) ISBN.\nEnter the numeric choice: \n";
  string choice;
  getline(cin, choice);
  int option = stoi(choice);
  int index = -1;
  if(option == 1)
  {
    cout << "Enter the book name: \n";
    string name;
    getline(cin >> ws, name);
    for(int i = 0; i < bookTitles.size(); i++){
      if(bookTitles.at(i) == name)
      {
        index = i; //gets the last occurance of the title to be deleted
      }
    }
  }else if(option == 2){
    cout << "Enter the book 13-digit ISBN (with dashes): \n";
    string isbn;
    getline(cin >> ws, isbn);
    for(int i = 0; i < isbnCodes.size(); i++){
      if(isbnCodes.at(i) == isbn)
      {
        index = i;
      }
    }
  }
  if(option < 1 || option > 2)
  {
    cout << "Invalid remove by choice option.\n";
  }else{
    cout << "The Following Entry Was Removed From The Library\n------------------------------------------------\n";
    if(index >= 0)
    {
      cout << bookTitles.at(index) << " --- " << isbnCodes.at(index) << " --- " << printCheckout(checkOutStatus, index);
      bookTitles.erase(bookTitles.begin() + index);
      isbnCodes.erase(isbnCodes.begin() + index);
      checkOutStatus.erase(checkOutStatus.begin() + index);
      
    }else{
      cout << "No matching entry found in the library.\n";
    }
  }
}

// checks and prints entries of the library that have invalid data:
// incorrect isbn or out-of-bounds checkout status
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void invalid(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus){
  cout << "The Following Library Entries Have Invalid Data\n-----------------------------------------------\n";

  vector<int> invalidIndex;

  for(int i = 0; i < isbnCodes.size(); i++){
    string isbnStr = cleanIsbn(isbnCodes.at(i));
    if(checkIsbn(isbnStr) == false || checkOutStatus.at(i) < 0 || checkOutStatus.at(i) > 3) //checks for invalid isbn, or out of bound checkout status
    {
      invalidIndex.push_back(i); //populates vector with location (indeces) of invalid entries
    }
  }
  if(bookTitles.size() == 0)
  {
    cout << "The library has no books.\n";
  }else if(invalidIndex.size() > 0){
    for(int i = 0; i < invalidIndex.size(); i++){
      cout << bookTitles.at(invalidIndex.at(i)) << " --- " << isbnCodes.at(invalidIndex.at(i)) << " --- " << printCheckout(checkOutStatus, invalidIndex.at(i));
    }
  }else{
    cout << "The library has no invalid entries.";
  }
}

// iterates through a file line by line and extracts book titles, isbn's, and checkout status
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void loadLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus)
{
  cout << "What database to read from? \n";
  string fileName;
  getline(cin >> ws, fileName);
  fstream f(fileName, ios::in);
  string line;
  int count = 0;

  if(f.is_open())
  {
    getline(f, line);
    while(f){
      if(line.find(',', 0) != string::npos) //checks if a comma is present, used to get isbn
      {
        int firstComma = line.find(',', 0);
        string title = line.substr(0, firstComma);
        bookTitles.push_back(title);
        if(line.find(',', firstComma+1) != string::npos) //checks if a second comma is present, used to get checkout status
        {
          int secondComma = line.find(',', firstComma+1);
          string isbn = line.substr(firstComma + 2, secondComma - (firstComma + 2));
          isbnCodes.push_back(isbn);
          string stat = line.substr(secondComma+2);
          int statusNum = stoi(stat);
          checkOutStatus.push_back(statusNum);
          
        }else{
          string isbn = line.substr(firstComma + 2);
          isbnCodes.push_back(isbn);
          checkOutStatus.push_back(0);
        }
      }else{
        bookTitles.push_back(line); 
        isbnCodes.push_back("000-0-00-000000-0"); //if no data available, default values
        checkOutStatus.push_back(0);
      }
      getline(f, line);
      count++;
    }
    cout << "Read in " << count << " lines from the file.\n";
    f.close();
  }else{
    cout << "Could not find the database file." << endl;
  }
}

// creates and writes the contents of the library to a file
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void outputLibrary(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus){
  cout << "What file to write to? \n";
  string fileName;
  getline(cin >> ws, fileName);
  ofstream file(fileName);
  for(int i = 0; i < bookTitles.size(); i++){
    file << bookTitles.at(i) << ", " << isbnCodes.at(i) << ", " << checkOutStatus.at(i) << endl;
  }
  file.close();
}

// prints the various checkout locations based on its numeric value
// parameters: checkoutStatus vector and an index int used to check the status at a certain index
string printCheckout(vector<int>& checkOutStatus, int index){
  if(checkOutStatus.at(index) == 0)
  {
    return "In Library\n";
  }else if(checkOutStatus.at(index) == 1){
    return "Checked Out\n";
  }else if(checkOutStatus.at(index) == 2){
    return "On Loan\n";
  }else if(checkOutStatus.at(index) == 3){
    return "Unknown State\n";
  }else{
    return "Invalid State\n";
  }
}

/// @brief print out the main menu of the management system
void printMenu()
{
  cout << "Library Management Menu" << endl;
  cout << "-----------------------" << endl;
  cout << "A - Add Item To Library" << endl;
  cout << "C - Clear The Library Of All Entries" << endl;
  cout << "D - Display Library Entries" << endl;    
  cout << "I - List Invalid Library Entries" << endl;
  cout << "L - Load Library From File" << endl;    
  cout << "O - Output Library To File" << endl;
  cout << "P - Print Out Checkout Stats" << endl;
  cout << "R - Remove A Library Entry" << endl;      
  cout << "S - Search For A Library Entry" << endl;    
  cout << "X - Exit Program" << endl;
}

// performs a search using a name or isbn, through the library and prints the latest match
// parameters: 3 vectors -> represent the 3 elements of a book in the library
void searchFunction(vector<string>& bookTitles, vector<string>& isbnCodes, vector<int>& checkOutStatus)
{
  cout << "Would you like to search by (1) name or (2) ISBN.\nEnter the numeric choice: \n";
  string choice;
  getline(cin, choice);
  int option = stoi(choice);
  int index = -1;
  if(option == 1)
  {
    cout << "Enter the book name: \n";
    string name;
    getline(cin >> ws, name);
    for(int i = 0; i < bookTitles.size(); i++){
      if(bookTitles.at(i) == name)
      {
        index = i;
      }
    }
  }else if(option == 2){
    cout << "Enter the book 13-digit ISBN (with dashes): \n";
    string isbn;
    getline(cin >> ws, isbn);
    for(int i = 0; i < isbnCodes.size(); i++){
      if(isbnCodes.at(i) == isbn)
      {
        index = i;
      }
    }
  }
  if(option < 1 || option > 2)
  {
    cout << "Invalid search by choice option.\n";
  }else{
    cout << "The Following Are Your Search Results\n-------------------------------------\n";
    if(index >= 0)
    {
      cout << bookTitles.at(index) << " --- " << isbnCodes.at(index) << " --- " << printCheckout(checkOutStatus, index);
    }else{
      cout << "No matching entry found in the library.\n";
    }
  }
}

// checks that the title doesn't have a comma
// returns true if there is no comma, false if there is a comma in the title
bool validateTitle(string title)
{
  size_t found = title.find(",");
  if(found != string::npos)
  {
    return false;
  }
  return true;
}