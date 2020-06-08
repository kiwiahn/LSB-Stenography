// ImageChecker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LSB.h"
#include "BasicHandling.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
    
    /*Parameter Note
        if 2 parameter, extract text from image
        if 3 parameters, Create Compress image for embed
        if 4 parameters, Embed text to image (compressed)
    */
    switch (argc)
    {
    case 3:
    {
        puts("Creating clone image for embed string....");

        //convert char to wchar
        const WCHAR* pwcsName;
        int nChars = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, NULL, 0);
        pwcsName = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, argv[1], -1, (LPWSTR)pwcsName, nChars);
        CreateMaliciousImage(pwcsName, argv[2]);
        puts("Working done!");
        break;
    }
    case 4:
    {
        //cmd : hasagiiiiii!!!! D:\\Another\\CacKTGT\\btl\\test\\abcd.png  D:\\Another\\CacKTGT\\btl\\test\\encoded_abcd.png
        puts("Embeding string into image....");
        //convert char to wchar
        const WCHAR* pwcsName;
        int nChars = MultiByteToWideChar(CP_ACP, 0, argv[2], -1, NULL, 0);
        pwcsName = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, argv[2], -1, (LPWSTR)pwcsName, nChars);

        //Embed string
        std::string text = argv[1];
        std::string outputImage = argv[3];
        if (!LSB_encode(text, pwcsName, outputImage))
        {
            puts("Please check your input again");
        }
        else puts("Embed string successfully!");
        break;
    }
    case 2:
    {
        //cmd: D:\\Another\\CacKTGT\\btl\\test\\encoded_abcd.png
        puts("Extracting hidden text....");
        const WCHAR* pwcsName;
        int nChars = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, NULL, 0);
        pwcsName = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, argv[1], -1, (LPWSTR)pwcsName, nChars);
        std::string text;
        if ((text = LSB_decode(pwcsName)) == "")
        {
            puts("Fail! Check your input!");
        }
        else
        {
            std::cout << "Hidden string is: " << text;
        }
        break;
    }

    default:
        puts("Out of purpose! Please give correct input!");
        break;
    }
}

