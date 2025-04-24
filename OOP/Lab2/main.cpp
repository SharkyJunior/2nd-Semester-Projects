#include "Source/set.hpp"
#include <initializer_list>
#include <vector>
#include <iostream>

int main() {
    Set<int> s1 {};

    int arr1[5] {1, 2, 2, 3, 4};
    Set<int> s2 = Set<int>(arr1, 5);
    int arr2[3] {3, 4, 5};
    Set<int> s3 = Set<int>(arr2, 3);

    Set<int> s4 {2, 5, 6, 7, 8, 9};

    vector< Set<int> > vec {s1, s2, s3, s4};

    cout << "Sets:\n";
    for (int i = 0; i < 4; i++)
        cout << "s" << i+1 << ": " << vec[i] << endl;

    cout << endl << "lengths: \n";
    for (int i = 0; i < 4; i++)
        cout << vec[i].getLength() << ", ";

    int elem = 2;
    cout << endl << "\"" << elem << "\" included: ";
    for (int i = 0; i < 4; i++)
        cout << vec[i].contains(elem) << " ";

    vec[0].add(100);
    cout << endl << "Added 100 to s1: " << vec[0] << endl;

    vec[3].remove(9);
    cout << "Removed 9 from s4: " << vec[3] << endl;

    cout << "Sets:\n";
    for (int i = 0; i < 4; i++)
        cout << "s" << i+1 << ": " << vec[i] << endl;

    cout << "Union of s1 and s2: " << vec[0].sunion(vec[1]) << endl;

    cout << "Intersection of s2 and s3: " << vec[1].intersection(vec[2]) << endl;

    cout << "Difference of s2 and s3: " << vec[1].difference(vec[2]) << endl;

    Set<int> s5 = s4;
    cout << "Copied s4 to s5: " << s5 << endl;


    
    return 0;
}