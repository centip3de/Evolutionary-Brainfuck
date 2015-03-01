#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "interp.hpp"
#include "debug.hpp"
#include "node.hpp"

using namespace std;

Debug debug(true);

void usage()
{
    cout << "Usage: ./main <initial file>" << endl;
    exit(1);
}

unsigned int interpret_timed(Interp interp)
{

    debug.print("Beginning average time calculation");

    unsigned int accumulator = 0;

    for(int i = 0; i < 100000; i++)
    {
        chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
        interp.execute();
        chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();

        chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time); 
        accumulator += time_span.count();
    }

    debug.print("Stopping timer. Interpretation successful.");

    return accumulator/100000;
}

 

int main(int argc, const char * argv[])
{
    if(argc != 2)
    {
        usage();
    }

    string filename = argv[1];
    ifstream file(filename);
    string line;
    string text;
    unsigned int base_time;
    int base_length;

    cout << "Finding basic stats for a baseline on file, " << filename << "..." << endl;
   
    debug.print("Beginning with initial file, " + filename);


    if(file.is_open())
    {
        /* Reads the file, line-by-line. */
        while(getline(file, line))
        {
            text += line;
        }
        file.close();

        debug.print("File contents read, beginning interpretation of initial file:"); 
        
        /* Attempts to interpret the file. */
        Interp interp(text);
        base_time = interpret_timed(interp);
        debug.print("Baseline time received; " + to_string(base_time) + " nanoseconds");

        base_length = text.length();
        debug.print("Baseline program length received; " + to_string(base_length));

        debug.print("Beginning tree construction with baseline, " + to_string(base_time) + " as root.");
    }
    else
    {
        cerr << "Error: Unable to open file, " << filename << endl;
        return -1;
    } 

    return 0;
}
