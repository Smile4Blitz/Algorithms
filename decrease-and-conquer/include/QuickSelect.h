#include <vector>
#include <iostream>

template <typename T>
void printVector(const std::vector<T> &list)
{
    for (T v : list)
    {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
int LomutoPartitioning(std::vector<T> &list, int low, int high)
{
    int s = low;
    for (int j = low; j < high; j++)
    {
        if(list[j] < list[high]) {
            std::swap(list[s], list[j]);
            s++;
        }
    }
    std::swap(list[s], list[high]);
    return s;
}

template <typename T>
T Quickselect(std::vector<T> &list, int index)
{
    int low = 0;
    int high = list.size() - 1;
    int pivot = LomutoPartitioning(list, low, high);

    while(low <= high) {
        pivot = LomutoPartitioning(list, low, high);
        if(pivot == index) {
            return list[pivot];
        } else if (pivot < (index - 1)) {
            low = pivot + 1;
        } else {
            high = pivot - 1;
        }
    }

    return list[pivot];
}

template <typename T>
T Quickselect_rec(std::vector<T> &list, int list_start, int list_end = 0, int k = -1)
{
    if (k == -1)
    {
        k = list.size() - 1;
    }

    if (list_start == (list_end - 1))
    {
        return list[list_start];
    }
    int s_index = LomutoPartitioning(list, list_start, list_end);

    if (s_index == (k - 1))
    {
        return list[s_index];
    }
    else if (s_index > (list_start + k - 1))
    {
        return Quickselect_rec(list, list_start, list_end, k);
    }
    else
    {
        return Quickselect_rec(list, s_index + 1, list_end, (k - 1 - s_index));
    }
}