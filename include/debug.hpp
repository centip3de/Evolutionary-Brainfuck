#ifndef DEBUG_HPP_
#define DEBUG_HPP_

using namespace std;

class Debug
{
    public:
        Debug(bool on);
        ~Debug();
        void print(string text);
        void swap();

    private:
        bool on;
        
};
#endif
