/* System includes */
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>

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

string mutate(string text)
{
    // Random number for the location in the origin string to mutate
    int random_location = rand()%text.length();

    // Random number for the character to mutate to
    int random_char = rand()%5;

    // Random number for multiple mutations
    int mutate_again = rand()%100; 

    int insert_remove = rand()%3;

    srand(time(NULL));

    while(mutate_again >= 50)
    {
        char new_char;
        int loc = random_location;

        /* Currently, let's not mutate to [, ], or user input (,). */
        switch(random_char)
        {
            case 0:
                new_char = '>';
                break;

            case 1:
                new_char = '<';
                break;

            case 2:
                new_char = '+';
                break;

            case 3:
                new_char = '-';
                break;

            case 4:
                new_char = '.';
                break;
        }

        if(text[loc] != ']' || text[loc] != '[')
        {

            if(insert_remove == 0)
            {
                debug.print("Mutating string at " + to_string(loc) + " to " + new_char);
                text[loc] = new_char; 
            }
            else if(insert_remove == 1)
            {
                debug.print("Mutating string by appending " + to_string(new_char));
                text += new_char;
            }
            else if(insert_remove == 2)
            {
                debug.print("Removing character at location, " + to_string(loc));
                text.erase(text.begin()+loc);
            }
        }

       random_char      = rand()%4;
       random_location  = rand()%text.length();
       mutate_again     = rand()%100;

    } 

    return text;
}

bool survived(Interp a)
{
    if(a.getStatus() == 0)
    {
        return true;
    }
    return false;
}

bool outputs_equal(Interp a, Interp b)
{
    if(a.getOutput() == b.getOutput())
    {
        return true;
    }
    return false;
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
    int number_of_mutations = 1;

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

        debug.print("File contents read, beginning interpretation of initial string:"); 
        
        /* Attempts to interpret the file. */
        Interp interp(text);
        interp.execute();
        
        debug.print("Gathering time information for initial string...");
        base_time = interpret_timed(interp);
        debug.print("Baseline time received; " + to_string(base_time) + " nanoseconds");

        base_length = text.length();
        debug.print("Baseline program length received; " + to_string(base_length));

        debug.print("Beginning tree construction with baseline, " + to_string(base_time) + " as root.");
        tree.insert(base_time, base_length);

        for(int i = 0; i < number_of_mutations; i++)
        {
            debug.print("Beginning mutations.");
            string mutated = mutate(text);

            debug.print("Text mutated to, " + mutated);
            debug.print("Interpreting new mutation.");
            Interp mutation(mutated);
            mutation.execute();

            debug.print("Gathering time information on mutation...");
            unsigned int mutate_time = interpret_timed(mutation);
            debug.print("Mutation time received; " + to_string(mutate_time) + " nanoseconds.");

            int mutate_length = mutated.length();
            debug.print("Mutation length received; " + to_string(mutate_length));

            bool survival = survived(mutation);
            debug.print("Checking it's survival... ");
            
            if(survival)
            {
                debug.print("Mutation survived.");

                bool match_output = outputs_equal(interp, mutation);
                debug.print("Checking it's output...");

                if(match_output)
                {
                    debug.print("Mutation matched output. Inserting into tree.");
                    tree.insert(mutate_time, mutate_length);
                    debug.print("Tree insertion successful.");
                }
                else
                {
                    debug.print("Mutation failed to match output.");
                }
            }
            else
            {
                debug.print("Mutation failed.");
            }
       }
    }
    else
    {
        cerr << "Error: Unable to open file, " << filename << endl;
        return -1;
    } 

    return 0;
}
