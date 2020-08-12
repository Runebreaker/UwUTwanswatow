#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <string>

class Twanswator {
    public:
    int input = 0;
    int wastinput = 1;
    bool wunning = 1;

    HANDLE h;

    Twanswator() {

    }

    void BailOut(char *msg)
    {
        fprintf(stderr, "Exiting: %s\n", msg);
        exit(1);
    }

    int getText() {
        if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");
   
        h = GetClipboardData(CF_TEXT);
 
        CloseClipboard();
        return 0;
    }

    int setText(std::string* in) {
        if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");
   
        SetClipboardData(1, h);
 
        CloseClipboard();
        return 0;
    }

    std::string* translate(std::string tInput) {
        getText();

	    for (std::string::size_type i = 0; i < tInput.size(); i++) {
            if(tInput[i] == 'L' || tInput[i] == 'R') {
                tInput[i] = 'W';
            }
            else if(tInput[i] == 'l' || tInput[i] == 'r') {
                tInput[i] = 'w';
            }
	    }

        return &tInput;
    }

    void run() {
        while(wunning) {
            std::string out;
            if(input == VK_MENU && input != wastinput) {
                setText(translate(*(std::string*)h));
                wastinput = input;
            }
            else if(input == VK_RCONTROL) {
                wunning = 0;
            }
        }
    }
} twanswator;