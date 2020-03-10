/*Disk Scheduling Algorithms Bonus Assignment*/
/* 
 *Ali Emad 1610052
 *Aya Hany 1610139
 *Salmeen Essam 1610102
 */
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

#define processes 1000
#define cylinders 5000
#define mm map<int, bool>
using namespace std;

void printKeys(mm m);
int fcfs(mm m, int initialPosition);
int sstf(mm m, int initialPosition);
int scan(mm m, int initialPosition);
int cscan(mm m, int initialPosition);
int look(mm m, int initialPosition);
int clook(mm m, int initialPosition);

int main()
{

    /*
     * We used maps to create a store for the random variables
     *  while simultaneously checking for duplicated in O(1) time
     */
    mm requests;

    int initialPosition;
    cin >> initialPosition;

    /* Use the seed for the rand() function
      *  as the current time to prevent same outputs 
      *  on different code runs
      * 
      * Each pair is {int RequestPosition: bool ServicedOrNot }
      */
    srand((int)time(0));

    int k = 0;
    while (k < processes)
    {
        int random = rand() % cylinders;
        if (requests.find(random) == requests.end())
        {
            requests.insert(pair<int, bool>(random, false));
            k++;
        }
    }

    printKeys(requests);

    cout << "FCFS: " << fcfs(requests, initialPosition) << endl;
    cout << "SSTF: " << sstf(requests, initialPosition) << endl;
    cout << "SCAN: " << scan(requests, initialPosition) << endl;
    cout << "C-SCAN: " << cscan(requests, initialPosition) << endl;
    cout << "LOOK: " << look(requests, initialPosition) << endl;
    cout << "C-LOOK: " << clook(requests, initialPosition) << endl;

    return 0;
}

/*
* First come first served
*/
int fcfs(mm m, int initialPosition)
{
    int distance = 0;
    int pos = initialPosition;
    mm::iterator it = m.begin();
    while (it != m.end())
    {
        int d;
        if (pos > it->first)
        {
            d = pos - it->first;
        }
        else
        {
            d = it->first - pos;
        }
        pos = it->first;

        distance += d;
        it->second = true;
        it++;
    }
    return distance;
}

/*
* Shortest Seek Time First
*/
int sstf(mm m, int initialPosition)
{
    int distance = 0;
    int pos = initialPosition;

    bool done = false;
    while (!done)
    {
        int minD = cylinders;
        int process;
        bool doneFlag = true;

        mm::iterator it = m.begin();
        while (it != m.end())
        {
            int d = 0;
            if (pos < it->first)
            {
                d = it->first - pos;
            }
            else
            {
                d = pos - it->first;
            }

            if (it->second == false && d < minD)
            {
                minD = d;
                process = it->first;
                doneFlag = false;
            }
            it++;
        }

        if (doneFlag)
        {
            done = true;
            break;
        }

        distance += minD;
        pos = process;
        m[process] = true;
    }
    return distance;
}

int scan(mm m, int initialPosition)
{
    mm::iterator it = m.begin();
    int distance = 0;
    int pos = initialPosition;

    int minD = cylinders;
    while (it != m.end())
    {
        if (pos >= it->first)
        {
            distance += pos - it->first;
            pos = it->first;
            it->second = true;
            if (it->first < minD)
            {
                minD = it->first;
            }
        }
        it++;
    }

    distance += minD;
    pos = 0;
    it = m.begin();
    while (it != m.end())
    {
        if (it->second == false)
        {
            distance += it->first - pos;
            pos = it->first;
        }
        it++;
    }
    return distance;
}

int cscan(mm m, int initialPosition)
{
    mm::iterator it = m.begin();
    int distance = 0;
    int pos = initialPosition;
    int maxD = 0;
    while (it != m.end())
    {
        if (pos <= it->first)
        {
            distance += it->first - pos;
            pos = it->first;
            it->second = true;
            if (it->first > maxD)
            {
                maxD = it->first;
            }
        }
        it++;
    }

    distance += (cylinders - 1) - maxD;
    distance += (cylinders - 1);
    pos = 0;
    it = m.begin();
    while (it != m.end())
    {
        if (it->second == false)
        {
            distance += it->first - pos;
            pos = it->first;
        }
        it++;
    }
    return distance;
}

int look(mm m, int initialPosition)
{
    mm::iterator it = m.begin();
    int distance = 0;
    int pos = initialPosition;

    while (it != m.end())
    {
        if (pos >= it->first)
        {
            distance += pos - it->first;
            pos = it->first;
            it->second = true;
        }
        it++;
    }

    it = m.begin();
    while (it != m.end())
    {
        if (it->second == false)
        {
            distance += it->first - pos;
            pos = it->first;
        }
        it++;
    }
    return distance;
}

int clook(mm m, int initialPosition)
{
    mm::iterator it = m.begin();
    int distance = 0;
    int pos = initialPosition;
    int minD = cylinders;
    while (it != m.end())
    {
        if (pos <= it->first)
        {
            distance += it->first - pos;
            pos = it->first;
            it->second = true;
        }
        if (it->first < minD && it->second == false)
        {
            minD = it->first;
        }
        it++;
    }

    distance += pos - minD;
    pos = minD;
    it = m.begin();
    while (it != m.end())
    {
        if (it->second == false)
        {
            distance += it->first - pos;
            pos = it->first;
        }
        it++;
    }
    return distance;
}

void printKeys(mm m)
{
    mm::iterator it = m.begin();
    cout << "{";
    while (it != m.end())
    {
        cout << it->first << ",";
        it++;
    }
    cout << "}" << endl;
}