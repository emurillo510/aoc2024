#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>

/*
--- Part Two ---

Your analysis only confirmed what everyone feared: the two lists of location IDs are indeed very different.

Or are they?

The Historians can't agree on which group made the mistakes or how to read most of the Chief's handwriting, 
but in the commotion you notice an interesting detail: 

a lot of location IDs appear in both lists! 
Maybe the other numbers aren't location IDs at all but rather misinterpreted handwriting.

This time, you'll need to figure out exactly how often each number from the left list appears in the right list. 



Calculate a total similarity score by adding up each number in the left list after multiplying it by the number of times 
that number appears in the right list.

Here are the same example lists again:

3   4
4   3
2   5
1   3
3   9
3   3

For these example lists, here is the process of finding the similarity score:

    The first number in the left list is 3. It appears in the right list three times, so the similarity score increases by 3 * 3 = 9.
    The second number in the left list is 4. It appears in the right list once, so the similarity score increases by 4 * 1 = 4.
    The third number in the left list is 2. It does not appear in the right list, so the similarity score does not increase (2 * 0 = 0).
    The fourth number, 1, also does not appear in the right list.
    The fifth number, 3, appears in the right list three times; the similarity score increases by 9.
    The last number, 3, appears in the right list three times; the similarity score again increases by 9.

So, for these example lists, the similarity score at the end of this process is 31 (9 + 4 + 0 + 0 + 9 + 9).

Once again consider your left and right lists. What is their similarity score?

*/

std::unordered_map<int, int> build_frequency_map(std::vector<int> list) {
    std::unordered_map<int, int> output;

    std::unordered_map<int, int>::iterator it;
    for(auto n : list) {
        it = output.find(n);
        if(it == output.end()) {
            output[n] = 1;
        } else {
            output[n] = output[n] + 1;
        }
    }
    return output;
}
int main() {

    std::ifstream file("input.txt");

    if(file.is_open() == false) {
        std::cout << "can't open file, check if exist or permissions\n";
        return 1;
    }

    std::string line;
    std::vector<int> list1;
    std::vector<int> list2;

    int value1;
    int value2;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> value1 >> value2;
        list1.emplace_back(value1);
        list2.emplace_back(value2);
    }

    file.close();

    std::unordered_map<int, int> frequency_map = build_frequency_map(list2);

    int output = 0;

    std::unordered_map<int, int>::iterator it;
    for(auto n : list1) {
        it = frequency_map.find(n);
        if(it != frequency_map.end()) {
            output += n * frequency_map[n];
        }
    }

    std::cout << "output: " << output << "\n";



    return 0;
}


/*

# part two obsevations:

- they want to me to get each number and multiply the number of occurences from the right list. save that value
and add it to the result

    - I noticed I can reuse the computed output to save work.
    - I can build an occurrence map for the second list straight away.
    - then I would iterate the 1st list and continue applying the requirements.
    - the runtime for this approach would be 2N
    - space complexity would be N + size of hashmap

*/