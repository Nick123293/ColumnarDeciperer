#include <iostream>
#include <vector>
#include<string>
#include <fstream>
#include<math.h>
std::vector<std::vector<int>> RCAG(int, int, std::vector<std::vector<int>>);
void printVector(std::vector<int>);
int main() {
    std::ifstream is("C:\\Users\\Nick\\Desktop\\plain.txt");
    char x;
    std::vector<char> textVector;
    while(is.get(x))
    {
        textVector.push_back(x);
    }
    for(int i = 0; i < textVector.size(); i++) //Prints texts Vector
    {
        std::cout << textVector.at(i) << " ";
    }
    int keyLength;
    std::cout << "Enter Keylength:"<<std::endl;
    std::cin >> keyLength;
    int txtSize = textVector.size();
    int choose = txtSize % keyLength; //num of long columns
    std::cout<<choose<<std::endl;
    int shortColSize = floor(txtSize / keyLength);
    std::vector<std::vector<int>> comboHolder;
    comboHolder = RCAG(keyLength, choose, comboHolder);
    /*for(int i = 0; i < comboHolder.size(); i++) //USED FOR TESTING RCAG
    {
        printVector(comboHolder.at(i));
    }*/
    //std::cout<<"Size: "<<comboHolder.size()<<std::endl; //USED FOR TESTING RCAG
    /*std::vector<int> shortcolVec;
    for(int i = 0; i < keyLength; i++) //Make vector of size keyLength full of the short column size value
    {
        shortcolVec.at(i) = shortColSize;
    }*/
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
    /*for(int i = 0; i<possibleColArrangements.size(); i++) //FOR TESTING POSSIBLECOLARRANGEMENTS
    {
        printVector(possibleColArrangements.at(i));
    }*/
    std::vector<std::vector<std::vector<char>>> possibleTableArrangements;
    for(int i = 0; i<possibleColArrangements.size(); i++) //Create all possible Table Arrangements
    {
        std::vector<std::vector<char>> posTable;
        std::cout << "{"<< std::endl;
        for(int k = 0; k < shortColSize;k++) //Create all short cols
        {
            //std::cout<<k<<std::endl;
            std::vector<char> shortRow;
            int placeInTxt = 0;
            //shortRow.push_back(textVector.at(k)); //First letter in row has value equal to k
            //std::cout<<textVector.at(k)<<' ';
            for(int j = 0; j<keyLength; j++) //Create Row
            {

                //std::cout<<"Making short row"<<std::endl;
                shortRow.push_back(textVector.at(placeInTxt+k));
                std::cout<<(textVector.at(placeInTxt+k))<<' ';
                placeInTxt+=possibleColArrangements.at(i).at(j);


            }
            posTable.push_back(shortRow);
            std::cout<<std::endl;
        }
        int b = shortColSize+1;
        std::vector<char> finRow;
        int placeInTxt = 0;
        char e = 'E';
        /*if(possibleColArrangements.at(i).at(0) == b)
        {
            std::cout<<textVector.at(b-1)<<' ';
        }
        else
        {
            std::cout<<e<<' ';
        }*/

        for(int c = 0; c<keyLength; c++)
        {
            if (possibleColArrangements.at(i).at(c) == b) {
                finRow.push_back(textVector.at( placeInTxt + b-1));
                std::cout<<(textVector.at( placeInTxt + b-1))<<' ';
                placeInTxt += possibleColArrangements.at(i).at(c);


            }
            else
            {
                //finRow.push_back(e);
                std::cout<<e<<' ';
                placeInTxt+=b-1;
            }
        }
        std::cout<<std::endl<<"}";
        posTable.push_back(finRow);
        possibleTableArrangements.push_back(posTable);
    }
    /*for(int i = 0; i<possibleTableArrangements.size(); i++)
    {
        for(int j = 0; j < keyLength; j++)
        {
            for(int k = 0; k<)
        }
    }*/
    std::cout<<possibleTableArrangements.size();
    return 0;
}
std::vector<std::vector<int>> RCAG(int keyLength, int choose, std::vector<std::vector<int>> comboHolder)
{
    if (choose == 0)
    {
        //Remainder is 0, means all columns are the same height so only one choice
    }
    else if (choose == 1)
    {
        std::vector<std::vector<int>> oneVectors;
        for(int i = 0; i<keyLength; i++)
        {
            std::vector<int> combo;
            for(int j = 0; j < keyLength; j++)
            {
                if (j == i)
                {
                    combo.push_back(1);
                }
                else
                {
                    combo.push_back(0);
                }
            }
            oneVectors.push_back(combo);
        }
        return oneVectors;
    }
    else
    {
        std::vector<std::vector<int>> holder;
        std::vector<std::vector<int>> R;
        R = RCAG(keyLength-1, choose-1, comboHolder);
        //std::cout<< "R.size = "<< R.size()<<std::endl; USED FOR TESTING RCAG
        for(int x = 0; x<keyLength; x++)
        {
            for(int a = 0; a < R.size(); a++)
            {
                //std::cout<<"Going"<<std::endl;
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
