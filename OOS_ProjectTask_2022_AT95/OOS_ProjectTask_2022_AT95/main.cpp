#include "Utility.h"

/*
#include <chrono>
using namespace std::chrono;
auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
 auto duration = duration_cast<microseconds>(stop - start);
*/
int main()
{
    int x = 1;
    int nf, np, * array;    // number of frames, number of pages, storage..
   
        do {
            cout << "***MENU*** \n"
                << "[1] FIFO \n"
                << "[2] LRU \n"
                << "[3] Second Chance (or Clock) \n"
                << "[4] LFU \n"
                << "[5] Optimal Page \n"
                << "[0] Exit" << endl;
            cin >> x;

        

        
        if (x == 1) {

            do
            {
                cout << "Enter the number of frames: ";
                cin >> nf;

                cout << "Enter the number of page references: ";
                cin >> np;
            } while ((nf < 0 || nf > 100) && (np < 0 || np > 1000));

            if (array = new(int[np]))
            {
                for (int i = 0; i < np; i++)
                    do {
                        cout << i + 1 << ".page: ";
                        cin >> array[i]; 
                    } while (array[i] < 0);
            }

            int r = FIFO(array, np, nf);
            cout << "Algorithm Effectiveness: PF = " << r << " => " << r << "/" << np << "*100[%] = " << ((double)r / np) * 100 << "[%]" << endl;
        }


        else if (x == 2) 
        {
            do
            {
                cout << "Enter the number of frames: ";
                cin >> nf;

                cout << "Enter the number of page references: ";
                cin >> np;
            } while ((nf < 0 || nf > 100) && (np < 0 || np > 1000));

            if (array = new(int[np]))
            {
                for (int i = 0; i < np; i++)
                    do {
                        cout << i + 1 << ".page: ";
                        cin >> array[i];
                    } while (array[i] < 0);
            }

            LRU(array, np, nf);
        }


        else if (x == 3)
        {
            string reference_string;
            int frames;
           
            do 
            {
                cout << "Enter the number of frames: ";
                cin >> frames;

            } while (frames < 0);

            cout << "Enter pages: ";
            getline(cin >> ws, reference_string);

            printHitsAndFaults(reference_string, frames);
        }

        
        else if (x == 4)
        {
            do
            {
                cout << "Enter the number of frames: ";
                cin >> nf;

                cout << "Enter the number of page references: ";
                cin >> np;
            } while ((nf < 0 || nf > 100) && (np < 0 || np > 1000));

            if (array = new(int[np]))
            {
                for (int i = 0; i < np; i++)
                    do {
                        cout << i + 1 << ".page: ";
                        cin >> array[i];
                    } while (array[i] < 0);
            }

           LFU(np, nf, array);
        }


        else if (x == 5)
        {
            do
            {
                cout << "Enter the number of frames: ";
                cin >> nf;

                cout << "Enter the number of page references: ";
                cin >> np;
            } while ((nf < 0 || nf > 100) && (np < 0 || np > 1000));

            if (array = new(int[np]))
            {
                for (int i = 0; i < np; i++)
                    do {
                        cout << i + 1 << ".page: ";
                        cin >> array[i];
                    } while (array[i] < 0);
            }

            optimalPage(array, np, nf);
        }

        } while (x != 0);

    return 0;
}