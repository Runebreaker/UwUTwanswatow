#include <iostream>
#include <fstream>
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <regex>
#include <vector>

struct Rule
{
    std::string regex;
    std::string replace;

    Rule(std::string a, std::string b)
    {
        regex = a;
        replace = b;
    }
    Rule() : Rule("", "") {}
};

bool wunning = 1;
const double UWU_PERCENT_BARRIER_MAX = 0.3;

char *token;
std::vector<Rule> ruleset;
std::string rulePath = "../src/rules.txt";

std::string h = " ";
std::string last = " ";

/*std::string getText()
{
    // Try opening the clipboard
    if (!OpenClipboard(nullptr))
        std::cout << GetLastError() << std::endl; // error

    // Get handle of clipboard object for ANSI text
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        std::cout << GetLastError() << std::endl; // error

    // Lock the handle to get the actual text pointer
    char *pszText = static_cast<char *>(GlobalLock(hData));
    if (pszText == nullptr)
        std::cout << GetLastError() << std::endl; // error

    // Save text in a string class instance
    std::string text(pszText);

    // Release the lock
    GlobalUnlock(hData);

    // Release the clipboard
    CloseClipboard();

    last = h;
    h = text;
    return text;
}

void setText(std::string in)
{
    const size_t len = in.length() + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), &in, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}*/

std::vector<Rule> fillArray(std::vector<Rule> array, std::string filePath, int arraySize)
{
    std::ifstream file(filePath);
    std::regex re("[ \t\n]+$"); //For removing trailing newlines and whitespaces

    std::string temp;
    for (int i = 0; i < arraySize; i++)
    {
        std::getline(file, temp);
        std::regex_replace(temp, re, "");
        int delimPos = temp.find(',');

        if (delimPos >= 0)
        {
            std::string a = temp.substr(0, delimPos);
            std::string b = temp.substr(delimPos + 1, temp.length() - delimPos);
            array.push_back(Rule(a, b));
        }
    }
    file.close();

    return array;
}

std::string translate(std::string tInput, std::string filePath) //Mainly for rules implementation
{
    std::ifstream infile(filePath);
    int position = 0;
    int uwuCounter = 0;
    int arraySize = std::count(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>(), '\n') + 1;
    infile.close();

    ruleset = fillArray(ruleset, filePath, arraySize);
    for(int i = 0; i < ruleset.size(); i++)
    {
        Rule currentRule = ruleset.at(i);
        std::regex re(currentRule.regex);
        tInput = std::regex_replace(tInput, re, currentRule.replace);
    }

    // tangent hyperbolicus curve to determine the percentage of uwu appendage
    if ((double)uwuCounter / (double)tInput.length() <= -UWU_PERCENT_BARRIER_MAX / 2 * tanh(tInput.length() / 5 - 6) + UWU_PERCENT_BARRIER_MAX / 2)
        tInput.append(" uwu");

    return tInput;
}

/*void run()
{
    while (wunning)
    {
        getText();
        if (h != last)
        {
            setText(translate(h));
        }
    }
}*/

int main()
{
    //run();

    std::string input;
    std::cout << "What do you want to twanswate? UwU" << std::endl
              << std::endl
              << "\t";
    std::getline(std::cin, input);
    std::cout << std::endl
              << "Twanswating... UwU" << std::endl
              << std::endl;
    std::cout << "\t" << translate(input, rulePath) << std::endl
              << std::endl
              << "Thank you fow using my twanswator OwO" << std::endl
              << std::endl;
    system("pause");
    return 0;
}