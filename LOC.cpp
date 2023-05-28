
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> getFiles()
{
  std::vector<std::string> files;
  fs::path currentDirectory = fs::current_path();

  for (const auto &entry : fs::directory_iterator(currentDirectory))
  {
    if (entry.is_regular_file())
    {
      files.push_back(entry.path().filename().string());
    }
  }
  return files;
}

void printfFiles(std::vector<std::string> files)
{
  for (const auto &file : files)
  {
    std::cout << file << std::endl;
  }
}

void checkForType(std::vector<std::string> file_types, std::vector<std::string> &files)
{
  files.erase(std::remove_if(files.begin(), files.end(), [&](const std::string &file)
                             {
                               for (const auto &file_ending : file_types)
                               {
                                 if (file.size() >= file_ending.size() && file.substr(file.size() - file_ending.size()) == file_ending)
                                 {
                                   return false; // valid file type, keep
                                 }
                               }
                               return true; // File does not end with any valid file type, remove
                             }),
              files.end());
}

int countLinesOfCode(const std::string &fileName)
{
  std::ifstream file(fileName);
  std::string line;
  int lineCount = 0;

  while (std::getline(file, line))
  {
    lineCount++;
  }

  return lineCount;
}

int main()
{
  std::vector<std::string> files = getFiles();
  std::string file_type;
  std::vector<std::string> file_types_vec;
  std::cout << std::endl;
  std::cout << "### LINES OF CODE counter ###" << std::endl;
  std::cout << "----------------------------" << std::endl;
  std::cout << "Enter file types to count (type 'end' to end type declaration): " << std::endl;
  while (file_type != "end")
  {
    std::cout << "----------------------------" << std::endl;
    std::cout << "Enter file type (.cpp, .py, .txt, etc.): ";
    std::cin >> file_type;
    if (file_type[0] == '.')
      file_types_vec.push_back(file_type);
    else if (file_type != "end")
      std::cout << "Invalid file type. File type must start with a dot (.)" << std::endl;
  }

  checkForType(file_types_vec, files);
  printfFiles(files);
  std::cout << "----------------------------" << std::endl;
  std::cout << "Display lines of code for each file or only total count ? (y/n): ";
  char choice;
  while (choice != 'y' && choice != 'n')
  {
    std::cin >> choice;
  }

  std::cout << "----------------------------" << std::endl;

  bool display_all = false;
  if (choice == 'y')
  {
    display_all = true;
  }

  int total_lines = 0;
  std::cout << std::endl;
  for (const auto &file : files)
  {
    int linesOfCode = countLinesOfCode(file);
    total_lines += linesOfCode;
    if (display_all)
      std::cout << file << ": " << linesOfCode << " lines of code." << std::endl << std::endl;
  }

  std::cout << "Total lines of code: " << total_lines << std::endl;
  std::cout << "----------------------------" << std::endl;

  return 0;
}
