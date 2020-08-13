#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <string>
#include <algorithm>

bool wunning = 1;

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

std::string translate(std::string tInput)
{
    int *toBeRemoved = new int[tInput.size()];
    int position = 0;
    int uwuCounter = 0;
    for (int i = 0; i < tInput.size(); i++)
    {
        if (tInput[i] == 'L' || tInput[i] == 'R') //Basics
        {
            tInput[i] = 'W';
            uwuCounter++;
        }
        else if (tInput[i] == 'l' || tInput[i] == 'r') //Basics
        {
            tInput[i] = 'w';
            uwuCounter++;
        }
        else if ((tInput[i] == 'T' || tInput[i] == 't')) //Replace the -> te, this -> tis
        {
            if ((i + 2) <= tInput.size() && (tInput[i + 1] == 'h' || tInput[i + 1] == 'H') && (tInput[i + 2] == 'e' || tInput[i + 2] == 'E'))
            {
                tInput[i + 1] = 'e';
                tInput[i + 2] = ' ';
                toBeRemoved[position] = (i + 2);
                position++;
            }
            if ((i + 3) <= tInput.size() && (tInput[i + 1] == 'h' || tInput[i + 1] == 'H') && (tInput[i + 2] == 'i' || tInput[i + 2] == 'I') && (tInput[i + 3] == 's' || tInput[i + 3] == 'S'))
            {
                tInput[i] = 'D';
                tInput[i + 1] = 'i';
                tInput[i + 2] = 's';
                tInput[i + 3] = ' ';
                toBeRemoved[position] = (i + 3);
                position++;
            }
        }
    }

    for (int i = 0; i < position; i++)
    {
        tInput.erase(toBeRemoved[i], 1);
    }

    delete toBeRemoved;

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

std::string textBasedTranslation(std::string in)
{
    std::string out = "";
    out = translate(in);
    return out;
}

int main()
{
    //run();
    std::string input;
    std::cout << "What do you want to twanswate? UwU" << std::endl << std::endl << "\t";
    std::getline(std::cin, input);
    std::cout << std::endl << "Twanswating... UwU" << std::endl << std::endl
    << "\t" << textBasedTranslation(input) << std::endl << std::endl
    << "Thank you fow using my twanswator OwO" << std::endl << std::endl;
    system("pause");
    return 0;
}