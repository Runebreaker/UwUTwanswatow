/*
The UwUTwanswatow (uwu for UwUTranslator) takes any string and translates it into uwu language.
Copyright (C) 2020  Gino Schulze

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
std::string rulePath = "rules.txt";
std::string copyrightString = "UwUTwanswator  Copyright (C) 2020  Gino Schulze\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `show c' for details.";
std::string warrantyString = "15. Disclaimer of Warranty.\nTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\nAPPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\nHOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\nOF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\nTHE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\nPURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\nIS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\nALL NECESSARY SERVICING, REPAIR OR CORRECTION.";
std::string redistributionString = "4. Conveying Verbatim Copies.\nYou may convey verbatim copies of the Program's source code as you\nreceive it, in any medium, provided that you conspicuously and\nappropriately publish on each copy an appropriate copyright notice;\nkeep intact all notices stating that this License and any\nnon-permissive terms added in accord with section 7 apply to the code;\nkeep intact all notices of the absence of any warranty; and give all\nrecipients a copy of this License along with the Program.\n\nYou may charge any price or no price for each copy that you convey,\nand you may offer support or warranty protection for a fee.\n\n5. Conveying Modified Source Versions.\n\nYou may convey a work based on the Program, or the modifications to\nproduce it from the Program, in the form of source code under the\nterms of section 4, provided that you also meet all of these conditions:\n\na) The work must carry prominent notices stating that you modified\nit, and giving a relevant date.\n\nb) The work must carry prominent notices stating that it is\nreleased under this License and any conditions added under section\n7.  This requirement modifies the requirement in section 4 to\n\"keep intact all notices\".\n\nc) You must license the entire work, as a whole, under this\nLicense to anyone who comes into possession of a copy.  This\nLicense will therefore apply, along with any applicable section 7\nadditional terms, to the whole of the work, and all its parts,\nregardless of how they are packaged.  This License gives no\npermission to license the work in any other way, but it does not\ninvalidate such permission if you have separately received it.\n\nd) If the work has interactive user interfaces, each must display\nAppropriate Legal Notices; however, if the Program has interactive\ninterfaces that do not display Appropriate Legal Notices, your\nwork need not make them do so.\n\nA compilation of a covered work with other separate and independent\nworks, which are not by their nature extensions of the covered work,\nand which are not combined with it such as to form a larger program,\nin or on a volume of a storage or distribution medium, is called an\n\"aggregate\" if the compilation and its resulting copyright are not\nused to limit the access or legal rights of the compilation's users\nbeyond what the individual works permit.  Inclusion of a covered work\nin an aggregate does not cause this License to apply to the other\nparts of the aggregate.\n\n6. Conveying Non-Source Forms.\n\nYou may convey a covered work in object code form under the terms\nof sections 4 and 5, provided that you also convey the\nmachine-readable Corresponding Source under the terms of this License,\nin one of these ways:\n\na) Convey the object code in, or embodied in, a physical product\n(including a physical distribution medium), accompanied by the\nCorresponding Source fixed on a durable physical medium\ncustomarily used for software interchange.\n\nb) Convey the object code in, or embodied in, a physical product\n(including a physical distribution medium), accompanied by a\nwritten offer, valid for at least three years and valid for as\nlong as you offer spare parts or customer support for that product\nmodel, to give anyone who possesses the object code either (1) a\ncopy of the Corresponding Source for all the software in the\nproduct that is covered by this License, on a durable physical\nmedium customarily used for software interchange, for a price no\nmore than your reasonable cost of physically performing this\nconveying of source, or (2) access to copy the\nCorresponding Source from a network server at no charge.\n\nc) Convey individual copies of the object code with a copy of the\nwritten offer to provide the Corresponding Source.  This\nalternative is allowed only occasionally and noncommercially, and\nonly if you received the object code with such an offer, in accord\nwith subsection 6b.\n\nd) Convey the object code by offering access from a designated\nplace (gratis or for a charge), and offer equivalent access to the\nCorresponding Source in the same way through the same place at no\nfurther charge.  You need not require recipients to copy the\nCorresponding Source along with the object code.  If the place to\ncopy the object code is a network server, the Corresponding Source\nmay be on a different server (operated by you or a third party)\nthat supports equivalent copying facilities, provided you maintain\nclear directions next to the object code saying where to find the\nCorresponding Source.  Regardless of what server hosts the\nCorresponding Source, you remain obligated to ensure that it is\navailable for as long as needed to satisfy these requirements.\n\ne) Convey the object code using peer-to-peer transmission, provided\nyou inform other peers where the object code and Corresponding\nSource of the work are being offered to the general public at no\ncharge under subsection 6d.\n\nA separable portion of the object code, whose source code is excluded\nfrom the Corresponding Source as a System Library, need not be\nincluded in conveying the object code work.\n\nA \"User Product\" is either (1) a \"consumer product\", which means any\ntangible personal property which is normally used for personal, family,\nor household purposes, or (2) anything designed or sold for incorporation\ninto a dwelling.  In determining whether a product is a consumer product,\ndoubtful cases shall be resolved in favor of coverage.  For a particular\nproduct received by a particular user, \"normally used\" refers to a\ntypical or common use of that class of product, regardless of the status\nof the particular user or of the way in which the particular user\nactually uses, or expects or is expected to use, the product.  A product\nis a consumer product regardless of whether the product has substantial\ncommercial, industrial or non-consumer uses, unless such uses represent\nthe only significant mode of use of the product.\n\n\"Installation Information\" for a User Product means any methods,\nprocedures, authorization keys, or other information required to install\nand execute modified versions of a covered work in that User Product from\na modified version of its Corresponding Source.  The information must\nsuffice to ensure that the continued functioning of the modified object\ncode is in no case prevented or interfered with solely because\nmodification has been made.\n\nIf you convey an object code work under this section in, or with, or\nspecifically for use in, a User Product, and the conveying occurs as\npart of a transaction in which the right of possession and use of the\nUser Product is transferred to the recipient in perpetuity or for a\nfixed term (regardless of how the transaction is characterized), the\nCorresponding Source conveyed under this section must be accompanied\nby the Installation Information.  But this requirement does not apply\nif neither you nor any third party retains the ability to install\nmodified object code on the User Product (for example, the work has\nbeen installed in ROM).\n\nThe requirement to provide Installation Information does not include a\nrequirement to continue to provide support service, warranty, or updates\nfor a work that has been modified or installed by the recipient, or for\nthe User Product in which it has been modified or installed.  Access to a\nnetwork may be denied when the modification itself materially and\nadversely affects the operation of the network or violates the rules and\nprotocols for communication across the network.\n\nCorresponding Source conveyed, and Installation Information provided,\nin accord with this section must be in a format that is publicly\ndocumented (and with an implementation available to the public in\nsource code form), and must require no special password or key for\nunpacking, reading or copying.";

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

constexpr unsigned int str2int(const char *str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

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
    std::string oldInput = tInput;
    int position = 0;
    int uwuCounter = 0;
    int arraySize = std::count(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>(), '\n') + 1;
    infile.close();

    ruleset = fillArray(ruleset, filePath, arraySize);
    for (int i = 0; i < ruleset.size(); i++)
    {
        Rule currentRule = ruleset.at(i);
        std::regex re(currentRule.regex);
        std::ptrdiff_t const match_count(std::distance(
            std::sregex_iterator(tInput.begin(), tInput.end(), re),
            std::sregex_iterator()));
        uwuCounter += match_count;
        tInput = std::regex_replace(tInput, re, currentRule.replace);
    }

    // tangent hyperbolicus curve to determine the percentage of uwu appendage
    double percent = (-UWU_PERCENT_BARRIER_MAX / 2.0) * tanh((double)tInput.length() / 5.0 - 6.0) + UWU_PERCENT_BARRIER_MAX / 2.0;
    if ((double)uwuCounter / (double)tInput.length() <= percent)
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

    while (wunning)
    {
        system("CLS");
        std::cout << copyrightString << std::endl
                  << std::endl;
        std::getline(std::cin, input);
        if (input == "show w")
        {
            std::cout << warrantyString << std::endl;
            system("pause");
        }
        else if (input == "show c")
        {
            std::cout << redistributionString << std::endl;
            system("pause");
        }
        else
        {
            while (wunning)
            {
                std::cout << "What do you want to twanswate? UwU (type q to quit)" << std::endl
                          << std::endl
                          << "\t";
                std::getline(std::cin, input);
                if (input == (std::string) "q")
                {
                    wunning = 0;
                    break;
                }
                std::cout << std::endl
                          << "Twanswating... UwU" << std::endl
                          << std::endl;
                std::cout << "\t" << translate(input, rulePath) << std::endl
                          << std::endl;
                system("pause");
            }
        }
    }

    std::cout << "Thank you fow using my twanswator OwO" << std::endl
              << std::endl;
    system("pause");
    return 0;
}