#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "quick_sorting.h"
#include "shell_sorting.h"
#include "one_phase_merge_sorting.h"
#include "two_phase_merge_sorting.h"
#include "natural_merge_sorting.h"

#include <fstream>
#include <vector>
#include <string>
using namespace std;
//Семинар 3



TEST_CASE("Shaker Sort: Already Sorted Array", "[Shaker Sort]") {
    int arr[] = { 1, 2, 3, 4, 5 };
    quick_sort(arr, 0, 4);
    int expected[] = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("Shaker Sort: Reversed Array", "[Shaker Sort]") {
    int arr[] = { 5, 4, 3, 2, 1 };
    quick_sort(arr, 0, 4);
    int expected[] = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("Shaker Sort: Array with Duplicates", "[Shaker Sort]") {
    int arr[] = { 1, 1, 1, 1, };
    quick_sort(arr, 0, 3);
    int expected[] = { 1, 1, 1, 1, };

    for (int i = 0; i < 4; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("Quick Sort: Already Sorted Array", "[Quick Sort]") {
    int arr[] = { 1, 2, 3, 4, 5 };
    shell_sort(arr, 5);
    int expected[] = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("Quick Sort: Reversed Array", "[Quick Sort]") {
    int arr[] = { 5, 4, 3, 2, 1 };
    shell_sort(arr, 5);
    int expected[] = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("Quick Sort: Array with Duplicates", "[Quick Sort]") {
    int arr[] = { 1, 1, 1, 1, };
    shell_sort(arr, 4);
    int expected[] = { 1, 1, 1, 1, };

    for (int i = 0; i < 4; i++) {
        REQUIRE(arr[i] == expected[i]);
    }
}



//Семинар 4

TEST_CASE("One phase: Sorting a file with repeating values") {
    std::ofstream file("file_repeating.txt");
    file << "5 3 8 5 3 9 8 5 2";
    file.close();

    one_phase_merge_sort("file_repeating.txt");

    std::ifstream sorted_file("file_repeating.txt");
    REQUIRE(sorted_file.is_open());

    int prev, curr;
    sorted_file >> prev;
    while (sorted_file >> curr) {
        REQUIRE(prev <= curr);
        prev = curr;
    }
    sorted_file.close();
}

TEST_CASE("One phase: Sorting an empty file") {
    std::ofstream file("empty_file.txt");
    file.close();  

    one_phase_merge_sort("empty_file.txt");

    std::ifstream sorted_file("empty_file.txt");
    REQUIRE(sorted_file.is_open());
    REQUIRE(sorted_file.peek() == std::ifstream::traits_type::eof()); 
    sorted_file.close();
}

TEST_CASE("Two phase: Sorting an already sorted file") {
    string filename = "sorted_file.txt";
    ofstream input(filename);
    input << "1 2 3 4 5 6 7 8 9";
    input.close();

    two_phase_merge_sort(filename);

    ifstream output(filename);
    vector<int> data;
    int value;
    while (output >> value) {
        data.push_back(value);
    }
    output.close();

    vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    REQUIRE(data == expected);  
}

TEST_CASE("Two phase: Sorting a file with negative numbers") {
    string filename = "file_with_negatives.txt";
    ofstream input(filename);
    input << "3 -1 4 -5 2 -3 0 7 -2";
    input.close();

    two_phase_merge_sort(filename);

    ifstream output(filename);
    vector<int> data;
    int value;
    while (output >> value) {
        data.push_back(value);
    }
    output.close();

    vector<int> expected = { -5, -3, -2, -1, 0, 2, 3, 4, 7 };
    REQUIRE(data == expected);  
}

TEST_CASE("Natural merge sort: Sorting a file with mixed numbers") {
    std::ofstream file("mixed_file.txt");
    file << "3 6 1 5 2 8 7 4";
    file.close();

    natural_merge_sort("mixed_file.txt");

    std::ifstream sorted_file("mixed_file.txt");
    REQUIRE(sorted_file.is_open());

    int prev, curr;
    sorted_file >> prev;
    while (sorted_file >> curr) {
        REQUIRE(prev <= curr);
        prev = curr;
    }
    sorted_file.close();
}
