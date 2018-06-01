#include<iostream>
#include<cctype>
#include<string>
#include <fstream>
using namespace std;

/* Things to remeber:
hyphenated words are special
put an empty line between output paragraphs #p#
end on an empty line
 */

int wordChecker(char a[], int& start) //This function will check if its a word and how long the word is.
{
    int spaceCounter = 0;
    int wordLength = 0; //We start with word length equal to 0.
    int paragraph = 3;
    for (int k= start; a[k+1] != '\0'; k++) //while there are characters inside of a[].
    {
        if((k != 0 && a[k+4] != '\0' && a[k] == '#' && a[k+1] == 'p' && a[k+2] == '#' && isspace(a[k+3]))) //if it is a paragraph break but it is not at the start or end of the file.
           {
               while (isspace(a[k+3]))
               {
                   spaceCounter++;
                   k++;
               }
               start = spaceCounter + paragraph;
               return -1;
               
           }
        if ((k!=0 && a[k+5] != '\0' && isspace(a[k]) && a[k+1] == '#'&& a[k+2] == 'p' && a[k+3] == '#' && isspace(a[k+4]))) //if it is a paragraph break but it is not at the start or end of the file.
        {
            while (isspace(a[k+4]))
            {
                spaceCounter++;
                k++;
            }
            start = spaceCounter + paragraph;
            return -1;
            
        }
        if((k==0 && a[k+4] != '\0' && a[k] == '#' && a[k+1] == 'p' && a[k+2] == '#' && isspace(a[k+3]))) //if it is a paragraph break but it is  at the start or end of the file.
        {
            while (isspace(a[k+3]))
            {
                spaceCounter++;
                k++;
            }
            start = spaceCounter + paragraph;
            return -2;
            
        }
        if ((k == 0 && a[k+5] != '\0' && isspace(a[k]) && a[k+1] == '#'&& a[k+2] == 'p' && a[k+3] == '#' && isspace(a[k+4]))) //if it is a paragraph break but it is at the start of the file.
        {
            while (isspace(a[k+4]))
            {
                spaceCounter++;
                k++;
            }
            start = spaceCounter + paragraph;
            return -2;
            
        }
        if((a[k] != 0 && a[k+4] == '\0' && a[k] == '#' && a[k+1] == 'p' && a[k+2] == '#' && isspace(a[k+3]))) //if it is a paragraph break but it is  at the end of the file.
        {
            return -3;
        }
        if ((a[k] != 0 && a[k+5] == '\0' && isspace(a[k]) && a[k+1] == '#'&& a[k+2] == 'p' && a[k+3] == '#' && isspace(a[k+4]))) //if it is a paragraph break but it is at the  end of the file.
        {
            return -3;
        }
        if (isalpha(a[k]) || a[k] == '#') //if the first character is a letter
        {
            for (int i = k; (a[i+1] != '\0' && !isspace(a[i]) && a[i] != '.' && a[i] != '?' && a[i] != '-'); i++) // then starting at the first character, while a[i] is not a space, a period, a question mark, or a hyphen, add once int to wordlength to keep track of how long our word is.
            {
                wordLength++; //increase wordlength by one char.
            }
            int j = wordLength;
            while (isspace(a[j]))
            {
                spaceCounter++;
                j++;
            }
            start = spaceCounter + wordLength;
            break;
        }
        if (isspace(a[k]) && (isalpha(a[k+1]) || a[k+1] == '#'))//if it is a space and the second char is a letter or non paragraph #.
        {
            for (int i = k+1; (a[i+1] != '\0' && !isspace(a[i]) && a[i] != '.'  && a[i] != '?' && a[i] != '-'); i++) // then starting at the first letter (spot k+1 in the string), while a[i] is not a space, a period, a question mark, or a hyphen,  add one int to wordlength to keep track of how long our word is.
            {
                wordLength++;//increase wordlength by one char. Punctuation, hyphens, and paragraph breaks won't be counted in the word length.
            }
            int j = wordLength;
            while (isspace(a[j]))
            {
                spaceCounter++;
                j++;
            }
            start = spaceCounter + wordLength;
            break;
        }

    }
return wordLength; //return the size of the word, if it returns 0, then we don't have a word.
}


int stuff(int lineLength, istream& inf, ostream& outf)
{
    const int MAX = 141;
    int nonErrorVal = 0;
    if (lineLength < 1)
    {
        return 2; //If the maximum allowed lineLength is less than 1, then we return 2 and dont have any other output.
    }
    char inputText[MAX]; //where I want to put the input so that I can process it
    inf.getline(inputText, MAX); //this while loop will import characters from my input file/cin and will put them into the Cstring inoutText.
    int remainingLength = lineLength;
    int wordBeingChecked = 0;
    for (int k = 0; k<MAX-1; k+= wordBeingChecked ) //this for loop will look at all the characters that have now been inputted into the Cstring.
    {
        int wordLength = wordChecker(inputText, wordBeingChecked);
        if (wordLength!= 0) //if the characters in my string are a word:
        {
            if (inputText[wordLength+1] !=  '.' || inputText[wordLength+1] !=  '?' || inputText[wordLength+1] !=  '-' || inputText[k] == '#') // if the word does not end with punctuation or start with a number sign
            {
                if(wordLength < lineLength && wordLength <= remainingLength) //if the word is less than the line and there is enough space for it to comepltely fit
                {
                        if( remainingLength != lineLength ) //if its not the first word in the line
                        {
                            outf << ' '; //output a space before the word
                            for( int j = k; j < wordLength+k; j++) //then for the length of the word
                            {
                                outf << inputText[j]; //print the word
                            }
                            remainingLength -= (wordLength+1); //remianing length is the size of the word plus the one space in front of it.
                        }
                        else //if it is the first word of a new line.
                        {
                            for( int j = k; j < wordLength+k; j++) //then for the length of the word
                            {
                                outf << inputText[j]; //print the word
                            }
                            remainingLength -= wordLength; //reminaing length is lineLength - the size of the word without a space in front of it
                        }
                }
                if(wordLength < lineLength && wordLength > remainingLength) //if the word is less than the line and there is not enough space for it to comepltely fit
                {
                    outf << endl; //Go to the next line.
                    if( remainingLength != lineLength ) //if its not the first word in the line
                    {
                            outf << ' '; //output a space before the word
                            for( int j = k; j < wordLength+k; j++) //then for the length of the word
                            {
                                outf << inputText[j]; //print the word
                            }
                            remainingLength -= (wordLength+1); //remianing length is the size of the word plus the one space in front of it.
                    }
                    else //if it is the first word of a new line.
                    {
                        for( int j = k; j < wordLength+k; j++) //then for the length of the word
                        {
                            outf << inputText[j]; //print the word
                        }
                        remainingLength -= wordLength; //reminaing length is lineLength - the size of the word without a space in front of it
                    }
                }
                if( wordLength > lineLength) //if the word we are looking at is longer than the lineLinegth
                {
                    nonErrorVal = 1; //we change our return line to equal 1
                    int lettersPlaced=0;
                    for( int j = lettersPlaced; j < wordLength+k; j++) //for the word starting at lettersplaced = 0 , until the word is over
                    {
                        for( int j = lettersPlaced; j < lineLength ; j++) //then starting at lettersplaced = 0
                        {
                            outf << inputText[j]; //we print the word until we run out of room on the lune
                            lettersPlaced++; //then we add one to the number of letters placed to keep track of what letter we are on
                        }
                        outf << endl; //once the line finishes we go to a new one and repeat starting at j = letters placed so that we pick up where we left off. Once the word runs out of characters, we exit the loop and go to the next word.
                    }
                }
            }
            if (inputText[wordLength+1] ==  '.' || inputText[wordLength+1] ==  '?')//if it is still a word but it ends with a period or ? mark.
            {
                if(wordLength +1 < lineLength && wordLength +1 <= remainingLength  ) //if the word is less than the line and there is enough space for it to comepltely fit
                {
                    if( remainingLength - wordLength > 1 ) //if its not the last word in the line
                    {
                        for( int j = k; j < wordLength+1+k; j++) //then for the length of the word
                        {
                            outf << inputText[j]; //print the word and the period/question mark
                        }
                        outf << ' '; //put a space after the period so that there will be two spaces between punctuation and the word.
                        remainingLength -= (wordLength+2); //remianing length is the size of the word plus the punctuation and the extra space after it.
                    }
                    if ((remainingLength - wordLength) == 1) //if it is the last word of a new line, since there is only one spot left after the size of the word is taken from remaining length.
                    {
                        for( int j = k; j < wordLength+1+k; j++) //then for the length of the word plus the punctuation
                        {
                            outf << inputText[j]; //print the word and the punctuation
                        }
                        outf << endl; //go to a new line
                    }
                }
                if(wordLength +1 < lineLength && wordLength+ 1 > remainingLength) //if the word with a period is less than the line and there is not enough space for it to comepltely fit
                {
                    outf << endl; //Go to the next line.
                    if( remainingLength - wordLength > 1 ) //if its not the last word in the line
                    {
                        for( int j = k; j < wordLength+1+k; j++) //then for the length of the word
                        {
                            outf << inputText[j]; //print the word and the period/question mark
                        }
                        outf << ' '; //put a space after the period so that there will be two spaces between punctuation and the word.
                        remainingLength -= (wordLength+2); //remianing length is the size of the word plus the punctuationa and the extra space after it.
                    }
                    if ((remainingLength - wordLength) == 1) //if it is the last word of a new line, since there is only one spot left after the size of the word is taken from remaining length.
                    {
                        for( int j = k; j < wordLength+1+k; j++) //then for the length of the word plus the punctuation
                        {
                            outf << inputText[j]; //print the word and the punctuation
                        }
                        outf << endl;   //reminaing length is equal to 0, that way we will go to a new line.
                    }
                }
                if( wordLength+1 > lineLength) //if the word we are looking at is longer than the lineLinegth
                {
                    nonErrorVal = 1; //we change our return line to equal 1
                    int lettersPlaced=0;
                    for( int j = lettersPlaced; j < wordLength +1; j++) //for the word with punctuation starting at lettersplaced = 0 , until the word with punctuation is over
                    {
                        for( int j = lettersPlaced; j < lineLength ; j++) //then starting at lettersplaced = 0
                        {
                            outf << inputText[j]; //we print the word with the period until we run out of room on the line
                            lettersPlaced++; //then we add one to the number of letters placed to keep track of what letter we are on
                        }
                        outf << endl; //once the line finishes we go to a new one and repeat starting at j = letters placed so that we pick up where we left off. Once the word runs out of characters, we exit the loop and go to the next word.
                    }
                }
            }
            if (wordLength == -1 ) //if it is a paragraph break in the middle of two words then it will leave an empty line.
            {
                outf << endl << endl;
            }
            if (wordLength == -2 ) //if it is a paragraph break at the start then it will only go to a new line.
            {
                outf << endl;
            }
            if (wordLength == -3 ) //if it is a paragraph break at the very end it will only go to a new line. ;
            {
                outf << endl;
            }
            
                
//if s[wordchecker +1] is a hyphen and remaining length =1. put the hyphen and go to new line . if its a hyphen and we can fit the second word. add no space between the hyphen and the word.
            
        } // end of if it is a word
    }//end of big loop
    outf << endl;
    return nonErrorVal; //return 0 if function stuffed without any problems and return 1 if the word was longer than the line length. Both returns will produce output.
}




int main()
{

    cout << "write words here:" << endl;
    int j = stuff(10, cin, cout);
    cout << j << endl;

    
}







