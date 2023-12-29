#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <time.h>
using namespace std;
string ref_string()
{
    string s;
    int range = 57 - 48 + 1;
    srand(time(NULL));
    while (s.length() < 50)
    {
        int num = rand() % range + 48;
        s += char(num);
    }
    return s;
}
int main()
{
    string ref = ref_string();
    std::list<char> l1;
    list<char>::iterator it;
    int page_fault = 0, page_hit = 0;
    bool hit = 0;
    cout << ref << endl;
    for (int i = 0; i < ref.length(); i++)
    {
        cout << "T" << i << "\t";
        it = find(l1.begin(), l1.end(), ref[i]);
        if (it != l1.end())
        {
            hit = 1;
            page_hit++;
            l1.erase(it);
            l1.push_front(ref[i]);
        }
        else
        {
            hit = 0;
            l1.push_front(ref[i]);
            page_fault++;
        }
        for (auto const &v : l1)
            std::cout << v << " ";
        cout << "\t" << (hit ? "Page Hit" : "Page Fault") << "\n";
    }
    cout << "\nPage Hits: " << page_hit << "\nPage Faults: " << page_fault << endl;
    return 0;
}