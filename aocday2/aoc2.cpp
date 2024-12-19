#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {

  // Open the input file
  std::ifstream file("input.txt");
  if(!file.is_open()) {
    std::cerr << "Error: Unable to open input.txt\n"; // Enhanced error message
    return 1;
  }

  std::string line;
  int num;

  // Read and parse each line into a vector of integers
  std::vector<std::vector<int>> reports;
  while(std::getline(file, line)) {
    std::stringstream ss(line);
    std::vector<int> report;
    while(ss >> num) {
      report.emplace_back(num);
    }
    reports.emplace_back(report);
  }

  file.close(); // Close the file after reading

  int num_of_safe_reports = 0; // Counter for safe reports

  // Iterate through each report to analyze safety
  for(int i = 0; i < reports.size(); i++) {
    const std::vector<int>& report = reports[i];

    // Handle single-element reports
    if(report.size() < 2) {
      std::cout << "Report " << i+1 << " is a safe report (single-element).\n";
      num_of_safe_reports += 1;
      continue;
 
    }

    bool is_entirely_increasing = true;
    bool is_entirely_decreasing = true;

    // Analyze each pair of adjacent numbers
    for(int j = 0; j < report.size() - 1; j++) {
      int cur = report[j];
      int next = report[j+1];
      int diff = next - cur;

      // Check for strictly increasing trend
      if(!(diff > 0 && diff <= 3)) {
        is_entirely_increasing = false;
      }

      // Check for strictly decreasing trend
      if(!(diff < 0 && diff >= -3)) {
        is_entirely_decreasing = false;
      }

      // Early termination if both trends are invalid
      if(!is_entirely_increasing && !is_entirely_decreasing) {
        break;
      }
    }

    // Determine the safety of the report based on trends
    if(is_entirely_increasing || is_entirely_decreasing) {
      std::cout << "Report " << i+1 << " is a safe report.\n";
      num_of_safe_reports += 1;
    }
    else {
      std::cout << "Report " << i+1 << " is not a safe report.\n";
    }
  }

  // Output the total number of safe reports
  std::cout << "Number of safe reports: " << num_of_safe_reports << "\n";

  return 0;
}



/*
  observations

  - i had trouble getting it to work with my original implementation.
    - in my approach I am setting incresaing and decreasing flags to false
    - any change in violation of the rules I set to true
    - my if statements are in corect
  - in the recommended approach they do the opposite, setting default to true
    -in their approach it works.
  - why?
    - i need to compare the differences.
  - what would be a more understandable approach?
    - i should first introduce a safe boolean
    - if they violate any rules i set it to false

  tasks to do
    - i need to compare the backup file (my approach) with this file and understand the difference.
    - maybe I should check for other people solutions.
*/
