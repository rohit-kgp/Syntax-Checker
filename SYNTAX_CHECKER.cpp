#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <iomanip>
#include <fstream>

using namespace std;

bool checkSyntax(fstream &myFile, string fileName)
{
    myFile.open(fileName);
    stack<char> s;
    stack<int> line;
    int lineCount = 1;
    char ch;

    while (myFile.get(ch))
    {
        if (ch == '\n')
            lineCount++;

        if (ch == '/')
        {
            // IF A COMMENT IS PRESENT, WE NEED TO SKIP THE WHOLE LINE
            if (myFile.peek() == '/')
            {
                while (ch != '\n')
                    myFile.get(ch);
                lineCount++;
            }
        }
        // IF WE ENCOUNTER SINGLE QUOTE - '
        if (ch == '\'')
        {
            // Push it to the stack
            s.push(ch);
            // We need to skip the next character, since a single character must be present in single quotes
            myFile.get(ch);

            myFile.get(ch);
            while (ch != '\'')
            {
                if (!myFile.get(ch)) // This means some different character is present, which does not match
                {
                    cout << "Unbalanced single quote \' is present on line number " << lineCount << "\n";
                    return false;
                }
            }

            char prev = s.top();
            s.pop();

            if (ch != '\'' || prev != '\'')
            {
                cout << "Match not found for single quote \' on line number " << lineCount << "\n";
                return false;
            }
        }

        if (ch == '\"')
        {
            // Push it to the stack
            s.push(ch);
            // We need to skip atleast next character, since a single character must be present in single quotes
            myFile.get(ch);
            while (ch != '\"')
            {
                myFile.get(ch);
                if (myFile.peek(), myFile.eof()) // This means some different character is present, which does not match
                {
                    cout << "Unbalanced \" is present on line number " << lineCount << "\n";
                    return false;
                }
            }

            char prev = s.top();
            s.pop();

            if (ch != '\"' || prev != '\"')
            {
                cout << "Match not found for \" on line number " << lineCount << "\n";
                return false;
            }
        }
        // If comment using - /* is present
        if (ch == '/' && myFile.peek() == '*')
        {
            s.push(ch);
            myFile.get(ch);
            s.push(ch);

            while (ch != '*' && myFile.peek() != '/')
            {
                myFile.get(ch);

                if (myFile.peek(), myFile.eof())
                {
                    cout << "Match not found for /* on line number " << lineCount << "\n";
                    return false;
                }
            }
        }

        if (ch == '*' && myFile.peek() == '/')
        {
            if (s.empty())
            {
                cout << "Match not found for */ on line number " << lineCount << "\n";
                return false;
            }

            char prev1, prev2;
            prev1 = s.top(); //*
            s.pop();
            prev2 = s.top(); // /
            s.pop();

            if (prev1 != ch || prev2 != myFile.peek())
            {
                cout << "Match not found for */ on line number " << lineCount << "\n";
                return false;
            }
        }
        // Checking validation for parenthesis
        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
            line.push(lineCount);
        }

        if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.empty())
            {
                cout << "Match not found for " << ch << " on line number " << lineCount << "\n";
                return false;
            }

            char prev = s.top();
            s.pop();
            if (ch == ')' && prev != '(')
            {
                cout << "Match not found for " << prev << " on line number " << line.top() << "\n";
                return false;
            }
            if (ch == '}' && prev != '{')
            {
                cout << "Match not found for " << prev << " on line number " << line.top() << "\n";
                return false;
            }
            if (ch == ']' && prev != '[')
            {
                cout << "Match not found for " << prev << " on line number " << line.top() << "\n";
                return false;
            }

            line.pop();
        }
    }
    // If stack is not empty, it means somewhere we didn't find a match
    if (!s.empty())
    {
        cout << "Match not found for " << s.top() << " on line number " << line.top() << "\n";
        return false;
    }
    return true;
}

int main()
{
    fstream myFile;
    string fileName;
    cout << "\n";
    cout << "Please Enter File Name: \n";
    cin >> fileName;
    cout << "FILENAME - " << fileName << "\nResult: ";
    bool flag = checkSyntax(myFile, fileName);
    if (flag)
    {
        cout << "All paranthesis, block comments, single and double quotes are balanced\n";
    }
    cout << "\n";
    return 0;
}