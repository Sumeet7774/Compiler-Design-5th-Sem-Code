#include <bits/stdc++.h>
#include <fstream>
using namespace std;


vector<string> findKeywords(string s,vector<string> arr)
{
    vector<string> keywords;
    istringstream iss(s);
    string word;

    while (iss >> word) 
    {
        for (int i = 0; i < arr.size(); i++) 
        {
            if (word == arr[i]) 
            {
                keywords.push_back(arr[i]);
                break;
            }
        }
    }

    return keywords;
}

vector<string> findVariables(string s, vector<string> arr)
{
    vector<string> variables;
    istringstream iss(s);
    string word;

    while (iss >> word) 
    {
        for (int i = 0; i < arr.size(); i++) 
        {
            if (word == arr[i]) 
            {
                variables.push_back(arr[i]);
                break;
            }
        }
    }

    return variables;
}

vector<char> findOperators(string s, vector<char> arr)
{
    vector<char> operators;

    for(int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i])) 
        {
            continue; // Skip digits
        }
        for(int j = 0; j < arr.size(); j++)
        {
            if(arr[j] == s[i])
            {
                operators.push_back(arr[j]);
            }
        }
    }
    return operators;
}

vector<char> findDigits(string s) 
{
    vector<char> digits;

    for (char c : s) {
        if (isdigit(c)) {
            digits.push_back(c);
        }
    }

    return digits;
}


int main()
{
    ofstream file("practical1_input.txt");
    string input;

    cout << "Enter input: ";
    getline(cin, input);

    file<<input<<endl;
    file.close();

    ifstream inputFile("practical1_input.txt");

    string line;
    string totalline;

    cout<<"Input is: ";
    while(getline(inputFile, line))
    {
        cout<<line;
        totalline = totalline + line + " ";
    }
    cout<<endl;

    if(totalline.empty())
    {
        cout << "Error: Input string is empty!" << endl;
        return 1;
    }

    inputFile.close();

    vector<string> keywordsList = {"int", "float", "double", "string", "char", "break", "catch", "for", "while", "class", "return", "goto"};
    vector<string> variablesList = {"var1", "temp", "arr", "name","a", "b"};
    vector<char> operatorsAndSpecialSymbolsList = {'+', '-', '/', '&', '*', '%', '!', '=', '(', ')' ,'1', '2', '3', '4', '5', '6','7', '8', '9', '0'};

    cout<<endl<<endl;

    vector<string> keywords = findKeywords(totalline, keywordsList);
    vector<string> variables = findVariables(totalline, variablesList);
    vector<char> operators = findOperators(totalline, operatorsAndSpecialSymbolsList);
    vector<char> digits = findDigits(totalline);

    if(keywords.size()!=0)
    {
        cout<<"Keywords are: ";

        for(int i=0; i<keywords.size(); i++)
        {
            cout<<keywords[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        cout<<"Keywords Not Found"<<endl;
    }

    if(variables.size()!=0)
    {
        cout<<"Variables are: ";

        for(int i=0; i<variables.size(); i++)
        {
            cout<<variables[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        cout<<"Variables Not Found"<<endl;
    }

    if(operators.size()!=0)
    {
        cout<<"Operators are: ";

        for(int i=0; i<operators.size(); i++)
        {
            cout<<operators[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        cout<<"Operators Not Found"<<endl;
    }

    if(digits.size()!=0)
    {
        cout<<"Digits are: ";

        for(int i=0; i<digits.size(); i++)
        {
            cout<<digits[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        cout<<"Digits Not Found"<<endl;
    }

    return 0;
}