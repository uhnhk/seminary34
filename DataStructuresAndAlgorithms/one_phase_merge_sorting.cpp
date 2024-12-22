#include "one_phase_merge_sorting.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void one_phase_merge_sort(const string& filename) {
    int blockSize = 1;

    vector<int> data;
    int value;

    ifstream input(filename);
    while (input >> value) {
        data.push_back(value);
    }
    input.close();

    int totalElements = data.size();

    while (blockSize < totalElements) {
        vector<int> temp(totalElements);
        int leftStart = 0;

        while (leftStart < totalElements) {
            int mid = min(leftStart + blockSize, totalElements);
            int rightEnd = min(leftStart + 2 * blockSize, totalElements);

            int i = leftStart, j = mid, k = leftStart;

            while (i < mid && j < rightEnd) {
                if (data[i] <= data[j]) {
                    temp[k++] = data[i++];
                }
                else {
                    temp[k++] = data[j++];
                }
            }

            while (i < mid) {
                temp[k++] = data[i++];
            }

            while (j < rightEnd) {
                temp[k++] = data[j++];
            }

            leftStart += 2 * blockSize;
        }

        data = temp;
        blockSize *= 2;
    }

    ofstream output(filename);
    for (const auto& val : data) {
        output << val << " ";
    }
    output.close();
}