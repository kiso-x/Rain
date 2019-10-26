/**
* \file main.cpp
*
* \brief Granular Synth with some extra features running on Rhaspberry PI
*
* \author Henrik von Coler modified by Marquis Fields and Malte Schneider
*
* \date  2019/10/04
*
*/


#include"rain.h"


using std::cout;
using std::endl;

int main(int argc, char *argv[]){

    std::string filename;
    int window_size;

    for (int i = 1; i < argc; i++)
    {
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-f") == 0)
            {
                filename = argv[i + 1];
                i++;
            }

            if (strcmp(argv[i], "-l") == 0)
            {
                window_size = atoi(argv[i + 1]);
                i++;
            }
        }
    }

    Rain * t = new Rain(filename, window_size);

}
