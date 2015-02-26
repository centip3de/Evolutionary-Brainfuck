#include <iostream>
#include <string>
#include <fstream>

#include "interp.hpp"
#include "debug.hpp"

using namespace std;

void usage()
{
    cout << "Usage: ./main <initial file>" << endl;
    exit(1);
}

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        usage();
    }

    Debug debug(true);

    string filename = argv[1];
    string line;
    string text;
    debug.print("Beginning with initial file, " + filename);

    ifstream file(filename);

    if(file.is_open())
    {
        /* Reads the file, line-by-line. */
        while(getline(file, line))
        {
            text += line;
        }
        file.close();

        debug.print("File contents read, beginning interpretation:"); 

        /* Attempts to interpret the file. */
        Interp interp(text);
        interp.execute();
    }
    else
    {
        cerr << "Error: Unable to open file, " << filename << endl;
        return -1;
    } 

    return 0;
}
