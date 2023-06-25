#pragma once
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include<cstring>
#include<sstream>
#include<string>

using namespace std;

void print_queue(std::queue<int> q)
{
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void print_array(T array[], const int n)
{
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";
}

int FIFO(int pages[], int n, int capacity)
{
    print_array<int>(pages, n);
    // To represent set of current pages. We use
    // an unordered_set so that we quickly check
    // if a page is present in set or not
    unordered_set<int> s;

    // To store the pages in FIFO manner
    queue<int> indexes;

    // Start from initial page
    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        // Check if the set can hold more pages
        if (s.size() < capacity)
        {
            // Insert it into set if not present
            // already which represents page fault
            if (s.find(pages[i]) == s.end())
            {
                // Insert the current page into the set
                s.insert(pages[i]);

                // increment page fault
                page_faults++;

                // Push the current page into the queue
                indexes.push(pages[i]);
            }
        }

        // If the set is full then need to perform FIFO
        // i.e. remove the first page of the queue from
        // set and queue both and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (s.find(pages[i]) == s.end())
            {
                // Store the first page in the 
                // queue to be used to find and
                // erase the page from the set
                int val = indexes.front();

                // Pop the first page from the queue
                indexes.pop();

                // Remove the indexes page from the set
                s.erase(val);

                // insert the current page in the set
                s.insert(pages[i]);

                // push the current page into
                // the queue
                indexes.push(pages[i]);

                // Increment page faults
                page_faults++;
            }
        }

        cout << "\nPF " << pages[i] << endl;
        print_queue(indexes);
    }

    return page_faults;
}


// Function to find page faults using indexes
int LRU(int pages[], int n, int capacity)
{
    // To represent set of current pages. We use
    // an unordered_set so that we quickly check
    // if a page is present in set or not
    unordered_set<int> s;

    // To store least recently used indexes
    // of pages.
    unordered_map<int, int> indexes;
   

    // Start from initial page
    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        // Check if the set can hold more pages
        if (s.size() < capacity)
        {
            // Insert it into set if not present
            // already which represents page fault
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                

                // increment page fault
                page_faults++;
            }

            // Store the recently used index of
            // each page
            indexes[pages[i]] = i;
        }

        // If the set is full then need to perform lru
        // i.e. remove the least recently used page
        // and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (s.find(pages[i]) == s.end())
            {
                // Find the least recently used pages
                // that is present in the set
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }

                // Remove the indexes page
                s.erase(val);

                // insert the current page
                s.insert(pages[i]);
               
                // Increment page faults
                page_faults++;
            }

            // Update the current page index
            indexes[pages[i]] = i;
        }
        for (auto pg : s) {
            cout << pg << " " << flush;
        }
        cout << endl;
    }

    return page_faults;
}

//  strating with the SecondChance ..
static bool findAndUpdate(int x, int arr[],
    bool second_chance[], int frames)

{
    int i;

    for (i = 0; i < frames; i++)
    {

        if (arr[i] == x)
        {
            // Mark that the page deserves a second chance
            second_chance[i] = true;

            // Return 'true', that is there was a hit
            // and so there's no need to replace any page
            return true;
        }
    }

    // Return 'false' so that a page for replacement is selected
    // as he reuested page doesn't exist in memory
    return false;

}


// Updates the page in memory and returns the pointer
static int replaceAndUpdate(int x, int arr[],
    bool second_chance[], int frames, int pointer)
{
    while (true)
    {

        // We found the page to replace
        if (!second_chance[pointer])
        {
            // Replace with new page
            arr[pointer] = x;

            // Return updated pointer
            return (pointer + 1) % frames;
        }

        // Mark it 'false' as it got one chance
        // and will be replaced next time unless accessed again
        second_chance[pointer] = false;

        //Pointer is updated in round robin manner
        pointer = (pointer + 1) % frames;
    }
}

static void printHitsAndFaults(string reference_string,
    int frames)
{
    int pointer, i, l = 0, x, pf;

    //initially we consider frame 0 is to be replaced
    pointer = 0;

    //number of page faults
    pf = 0;

    // Create a array to hold page numbers
    int* arr = new(int[frames]);

    // No pages initially in frame,
    // which is indicated by -1
    memset(arr, -1, sizeof(arr));

    // Create second chance array.
    // Can also be a byte array for optimizing memory
    bool* second_chance = new(bool[frames]);

    // Split the string into tokens,
    // that is page numbers, based on space

    string str[100];
    string word = "";
    for (auto x : reference_string)
    {
        if (x == ' ')
        {
            str[l] = word;
            word = "";
            l++;
        }
        else
        {
            word = word + x;
        }
    }
    str[l] = word;
    l++;
    // l=the length of array

    for (i = 0; i < l; i++)
    {
        x = stoi(str[i]);

        // Finds if there exists a need to replace
        // any page at all
        if (!findAndUpdate(x, arr, second_chance, frames))
        {
            // Selects and updates a victim page
            pointer = replaceAndUpdate(x, arr,
                second_chance, frames, pointer);
            
            // Update page faults
            pf++;
        }
        if (i >= frames) {
            for (int i = 0; i < frames; i++) {
             cout << arr[i] << " " << flush;
            }
            cout << endl;
        }
        else
        {
            for (int x= 0; x < i; x++) {
                cout << arr[x] << " " << flush;
            }
            cout << endl;

        }
    }
    cout << "Total page faults were " << pf << "\n";
}
//  SecondChance ending..

int LFU(int n, int c, int pages[])
{
    // Initialise count to 0
    int count = 0;

    // To store elements in memory of size c
    vector<int> v(n,-1);
    // To store frequency of pages
    unordered_map<int, int> mp;

    int i;
    for (i = 0; i <= n - 1; i++) {

        // Find if element is present in memory or not
        auto it = find(v.begin(), v.end(), pages[i]);

        // If element is not present
        if (it == v.end()) {

            // If memory is full
            if (v.size() == c) {

                // Decrease the frequency
             
                mp[v[0]]--;

                // Remove the first element as
                // It is least frequently used
                v.erase(v.begin());
            }

            // Add the element at the end of memory
            v.push_back(pages[i]);
            // Increase its frequency
            mp[pages[i]]++;

            // Increment the count
            count++;
        }
        else {

            // If element is present
            // Remove the element
            // And add it at the end
            // Increase its frequency
            mp[pages[i]]++;
            v.erase(it);
            v.push_back(pages[i]);
        }

        // Compare frequency with other pages
        // starting from the 2nd last page                 
        int k = v.size() - 2;

        // Sort the pages based on their frequency 
        // And time at which they arrive
        // if frequency is same
        // then, the page arriving first must be placed first
        while (mp[v[k]] > mp[v[k + 1]] && k > -1) {
            swap(v[k + 1], v[k]);
            k--;
        }
        for (auto pg : v) {
            if(pg!=-1)
            cout << pg << " " << flush;
        }
        cout << endl;
    }

    // Return total page faults
    return count;
}

bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], vector<int>& fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++) {

        // Page found in a frame : HIT
        if (search(pg[i], fr)) {
            hit++;
            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < fn)
            fr.push_back(pg[i]);

        // Find the page to be replaced.
        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
        for (auto pg : fr) {
            cout << pg << " " << flush;
        }
        cout << endl;
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}