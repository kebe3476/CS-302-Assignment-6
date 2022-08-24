/*
CS 302 Assignment 6

Name: Keith Beauvais, 5005338658, CS 302 Assignment 6
*/

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

//Struct for category for hash map 
struct words{
    int T, C, W, P, duplicate;
    std::string N, A;
    //contructor that initalizes everything
    words(){
        N="";
        A="";
        T = C = W = P = duplicate = 0;

    }
    //contructor that is overloaded
    words(std::string name, std::string actual, int test, int categories, int amountOfWords, int differentWords){
        N = name;
        T = test;
        C = categories;
        W = amountOfWords;
        P = differentWords;
        A = actual;
        duplicate = 0;
    }
};
//Struct for categoryNum for hash map 
struct wordNum{
    int diffWords, duplicatePrint,printCategory;
    std::string diffWordsString;

    //contructor that initalizes everything
    wordNum(){
        diffWords = duplicatePrint = 0;
        diffWordsString = "";
    }
    //contructor that is overloaded
    wordNum(int diff, std::string nameOfDiff, int printC){
        diffWords = diff;
        duplicatePrint = 0;
        diffWordsString = nameOfDiff;
        printCategory = printC;

    }
};

std::string lowerCase(std::string);

int main(){
    std::ifstream infile;
    std::string n, a, loweringString, filename, wordInCategory, sentence = "", wordInSentence = "";
    int counter, t, c, w, p, printCounter = 1 , pc = 0;
    std::vector<std::string> comparisonVector;
    bool flag = true;

    /*
    T = T that denotes the amount of test cases
    C = Each test case starts with a positive number C for the amount of categories
    N = For each category, a line that contains N that denotes the category name
    W = W (the amount of words in the category)
    P = P (the amount of different words that should appear in the description so the problem fits the category)
    */
    
    counter = 1; // used to count how many tests cases it has gone through

    std:: unordered_map<std::string, words> category; // hashmap for all word info to include some category info
    std:: unordered_map<std::string, wordNum> categoryNum; // hashmap for all category info 
  
    //reads in file
    std::cout << "Enter filename: ";
    std::cin >> filename;
    
    infile.open(filename);
    
    infile >> t; // reads in amount of test cases
    do{
        infile >> c; // reads in amount of categories
    
        
        for(int i = 0; i < c; i++){
            
            infile >> n >> w >> p; // reads in category name, amount of words in the category, and 
            //amount of different words that should appear in the description
            categoryNum[n] = wordNum(p, n, counter); // loads all info into the category hashmap
            comparisonVector.push_back(n); // vector to store in category name as it is read in for ordering later


            for(int j = 0; j< w; j++){
                
                infile >> wordInCategory; // reads in the word in a specfic category
                a = lowerCase(wordInCategory); // makes it lower case
                category[a] = words(n,a,t,c,w,p); // loads all info into the word hashmap

            }
            
        }

        infile.ignore(50,'\n');
        while(std::getline(infile, sentence)){ // getline to read until blank line
            
            std::stringstream ss(sentence); // parses the sentence string to word string to compare

            while(ss>>wordInSentence){
                wordInSentence = lowerCase(wordInSentence); // makes it lower case to compare
                if(wordInSentence == category[wordInSentence].A){ // if the comparison is true
            
                    category[wordInSentence].duplicate++;// if the comparison is true then adds 1 to duplicate num 
                    if(category[wordInSentence].duplicate <= 1){ // checks to make sure not duplicate
                        loweringString = category[wordInSentence].N; 
                        categoryNum[loweringString].diffWords--; // lowers the category count by 1 once it is 0 then all words were found
                    }
                }
            }
            infile.clear();
            //infile.ignore('\n');
            if(sentence.length()==0){
                break;
            }
        }
        flag = true; // flag used to see if the 
        printCounter=1; // used to see if at end of vector
        
        // used for printing out results
        std::cout<< "Test case "<< counter << std::endl;
        for(int i = 0; i<comparisonVector.size();i++){ // goes through the vector with category names 
            // if the amount of different words = 0 and duplicants dont get printed
            if(categoryNum[comparisonVector[i]].diffWords == 0 && categoryNum[comparisonVector[i]].duplicatePrint == 0){
                std::cout<< categoryNum[comparisonVector[i]].diffWordsString<<std::endl;
                categoryNum[comparisonVector[i]].duplicatePrint++;
                flag = false; // changes to false so it wont print SQF 
            }
            // if at the end and has not printed out any other values and the counter is equal to the C
            if(printCounter == c && flag && counter == categoryNum[comparisonVector[i]].printCategory){
                std::cout<< "SQF Problem"<<std::endl;
            }
            printCounter++; // increase by 1 
        }
        
        counter++;
        comparisonVector.clear(); // clears vector after an interation of T

    }while(counter!=t+1);

    infile.close();

    return 0;
}
/* 
std::string lowerCase(std::string fromSentence)- takes in a string and makes all characters lower case

return value - returns a string that is all lower case
*/
std::string lowerCase(std::string fromSentence){
    std::string newString;

    for(int i = 0; i< fromSentence.length(); i++){
        fromSentence[i] = tolower(fromSentence[i]);
    }

    return fromSentence;
}