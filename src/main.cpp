/* System includes */
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

/* User defined includes */
#include "interp.hpp"
#include "debug.hpp"
#include "bst.hpp"

using namespace std;

// Made global to use in all functions. Probably not the best idea, though. 
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

    // Run 100,000 times for a fair average
    for(int i = 0; i < 100000; i++)
    {
        // Get the time before execution, execute the code, then get the time after execution
        chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
        interp.execute();
        chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();

        // Calculate the time during execution, and add it to the accumulator
        chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time); 
        accumulator += time_span.count();
    }

    debug.print("Stopping timer. Interpretation successful.");

    // Return the average
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
    BinaryTree tree;

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
        tree.insert(base_time, base_length);

    }
    else
    {
        cerr << "Error: Unable to open file, " << filename << endl;
        return -1;
    } 

    return 0;
}
