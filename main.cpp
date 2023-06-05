#include <iostream>
#include <vector>
#include<string>
#include <fstream>
#include<math.h>
std::vector<std::vector<int>> RCAG(int, int, std::vector<std::vector<int>>);
void printVector(std::vector<int>);
std::vector<int> RatioCalculator(int);
int main() {
    std::ifstream is("C:\\Users\\Nick\\Desktop\\plain.txt"); //Reads file from my desktop MUST BE SET SO PATH MATCHES WHERE THE PLAINTEXT IS
    char x; //Placeholder character to read from the file one char at a time
    std::vector<char> textVector; //Initialization of vector which will hold the plaintext
    while(is.get(x)) //Puts the plaintext into a vector of characters
    {
        textVector.push_back(x); //Inserts character into vector
    }
    for(int i = 0; i < textVector.size(); i++) //Prints texts Vector for testing
    {
        std::cout << textVector.at(i) << " ";
    }
    std::cout << textVector.size() <<std::endl; //Prints vector size for testing
    int keyLength;
    std::cout << "Enter Keylength:"<<std::endl; //Asking the user to enter the keylength
    std::cin >> keyLength; //Taking input
    int txtSize = textVector.size(); //txtSize = the size of the vector = num of letters in plaintext
    int numLongCols = txtSize % keyLength; //num of long columns = the remainder of the division of txtsize by keylength
    std::cout<<numLongCols<<std::endl; //print num of long cols for testing
    int shortColSize = floor(txtSize / keyLength); //length of short column = txtsize/keylength truncated
    std::vector<std::vector<int>> comboHolder; //Creates a vector which holds vectors holding integers (Essentially a 2D array)
    comboHolder = RCAG(keyLength, numLongCols, comboHolder);
    std::vector<std::vector<int>> possibleColArrangements;
    for(int i = 0; i < comboHolder.size(); i++) //Create all possible Column Arrangements
    {
        std::vector<int> posColArr;
        for(int j = 0; j < keyLength; j++)
        {
            posColArr.push_back(comboHolder.at(i).at(j) + shortColSize);

        }

        possibleColArrangements.push_back(posColArr);
    }
    std::vector<std::vector<std::vector<char>>> possibleTableArrangements;
    int ColsWithCorrectVowelNum = 0;
    for(int i = 0; i<possibleColArrangements.size(); i++) //Create all possible Table Arrangements
    {
        std::vector<std::vector<char>> posTable;
        std::cout << "{"<< std::endl;
        for(int k = 0; k < shortColSize;k++) //Create all short cols
        {
            std::vector<char> shortRow;
            int placeInTxt = 0;
            int numOfVowel = 0;
            for(int j = 0; j<keyLength; j++) //Create Row
            {
                shortRow.push_back(textVector.at(placeInTxt+k));
                if(textVector.at(placeInTxt+k) == 'A' ||textVector.at(placeInTxt+k) == 'E' ||textVector.at(placeInTxt+k) == 'I' ||textVector.at(placeInTxt+k) == 'O' ||textVector.at(placeInTxt+k) == 'U')
                {
                    numOfVowel++;
                }
                std::cout<<(textVector.at(placeInTxt+k))<<' ';
                placeInTxt+=possibleColArrangements.at(i).at(j);
            }
            std::vector<int> convertedRatio = RatioCalculator(keyLength); //gets the number of vowels that should be in the average english text of length keyLength
            if(convertedRatio.size() == 1) //True if keyLength * .4 and keyLength *.36 both rounded are the same, meaning there is only one accepted value for the number of vowels in a row
            {
                if(numOfVowel == convertedRatio.at(0))
                {
                    ColsWithCorrectVowelNum++;
                    std::cout<<"ColsWithCorr... iterated";
                }
            }
            else if(convertedRatio.size() == 2) //True if there are two accepted values for the number of vowels in a row
            {
                if(numOfVowel == convertedRatio.at(0) || numOfVowel == convertedRatio.at(1))
                {
                    ColsWithCorrectVowelNum++;
                    std::cout<<"ColsWithCorr... iterated";
                }
            }
            posTable.push_back(shortRow); // add the row to the table
            std::cout<<std::endl;
        }
        int b = shortColSize+1;
        std::vector<char> finRow;
        int placeInTxt = 0;
        char e = '%'; //NULL CHARACTER
        for(int c = 0; c<keyLength; c++)
        {
            if (possibleColArrangements.at(i).at(c) == b) {
                finRow.push_back(textVector.at( placeInTxt + b-1));
                std::cout<<(textVector.at( placeInTxt + b-1))<<' ';
                placeInTxt += possibleColArrangements.at(i).at(c);


            }
            else
            {
                std::cout<<e<<' ';
                placeInTxt+=b-1;
            }
        }
        std::cout<<std::endl<<"}";
        posTable.push_back(finRow);
        possibleTableArrangements.push_back(posTable);
    }
    std::cout<<comboHolder.size()<<std::endl;
    std::cout<<"Number of Columns with the correct vowel count = "<<ColsWithCorrectVowelNum<<std::endl<<"Number of Cols with correct vowel count / Col count = "<<ColsWithCorrectVowelNum/(comboHolder.size()*floor(textVector.size()/float(keyLength)))<<std::endl;
    std::cout<<possibleTableArrangements.size();
    return 0;
}
std::vector<std::vector<int>> RCAG(int keyLength, int numLongCols, std::vector<std::vector<int>> comboHolder)
{
    if (numLongCols == 0)
    {
        //Remainder is 0, means all columns are the same height so only one choice. In this case there is no point in using this software because the solution could be figured out trivially
    }
    else if (numLongCols == 1) //If there is one long column, which models a key length choose 1 combination
    {
        std::vector<std::vector<int>> oneVectors; //Create a 2D vector
        for(int i = 0; i<keyLength; i++) //Iterate keyLength times
        {
            std::vector<int> combo; //Initialize integer vector
            for(int j = 0; j < keyLength; j++) //Iterate keyLength times
            {
                //if both iterators hold the same integer put a 1 in instead of a 0, this 1 represents the long column, since this is a choose 1 combination everything else will be a zero
                //Creates a 2d vector where every row has a 1 in the next column starting from the first ex. { {100}, {010}, {001} }
                if (j == i)
                {
                    combo.push_back(1);
                }
                else
                {
                    combo.push_back(0);
                }
            }
            oneVectors.push_back(combo); //put the integer vector into the 2d vector
        }
        return oneVectors;
    }
    else //If there is more than one long column, which models a key length choose n combination
    {
        std::vector<std::vector<int>> holder; //Create a 2D vector
        std::vector<std::vector<int>> R;  //Create another 2D vector
        R = RCAG(keyLength-1, numLongCols - 1, comboHolder);  //R gets set to the solution of this function with a key length with one less size and 1 less long column
        for(int x = 0; x<keyLength; x++) //Iterate key length times
        {
            for(int a = 0; a < R.size(); a++)
            {
                std::vector<int> RatA = R.at(a);
                std::vector<int> extendedVector;
                int y = 0;
                for(int x1 = 0; x1< keyLength; x1++)
                {
                    if(extendedVector.size() == x)
                    {
                        extendedVector.push_back(1);
                    }
                    else
                    {
                        extendedVector.push_back(RatA.at(y));
                        y++;
                    }
                }
                int u = 0;
                for(int s = 0; s < holder.size(); s++)
                {
                    if(holder.at(s) == extendedVector)
                    {
                        u++;
                    }
                }
                if (u == 0)
                {
                    holder.push_back(extendedVector);
                }
            }
        }
        return holder;
    }
}
void printVector(std::vector<int> vector) { //PRINTS VECTOR
    std::cout << "{";
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout<< vector.at(i);
        if(i == vector.size()-1){}
        else {std::cout << ", ";};
    }
    std::cout << "} ";
}
std::vector<int> RatioCalculator(int keylength)
{
    float a = keylength*.4;
    float b = keylength*.36;
    a = round(a); b = round(b);
    std::vector<int> output;
    if (a == b)
    {
        output.push_back(a);
    }
    else
    {
        output.push_back(b);
        output.push_back(a);
    }
    return output;
}