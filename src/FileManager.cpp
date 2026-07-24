#include "FileManager.hpp"
#include "SubjectManager.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void FileManager::load_subject_file(const std::string &path,
                                    SubjectManager &sm) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + path);
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      std::cerr << "Line is empty.\n";
      continue;
    }

    std::stringstream ss(line);
    std::string code, title, units_str;

    if (!std::getline(ss, code, ','))
      continue;
    if (!std::getline(ss, title, ','))
      continue;
    if (!std::getline(ss, units_str))
      continue;

    try {
      int units = std::stoi(units_str);
      sm.m_subjects.emplace_back(code, title);
      sm.m_subjects.back().set_units(units);
    } catch (const std::exception &) {
      continue;
    }
  }
}

void FileManager::write_subject_file(const std::string &path,
                                     Subject &subject) {
  std::ofstream file(path, std::ios::app);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open the file for appending: " + path);
  }

  file << subject.code() << "," << subject.title() << "," << subject.units()
       << "\n";

  file.close();

  std::cout << "Subject saved succesfully.\n";
}

void FileManager::update_subject_file(const std::string &orig_path,
                                      Subject &subject) {
  std::string temp_file_name = "data/temp_subjects.txt";

  std::ifstream in_file(orig_path);
  std::ofstream out_file(temp_file_name);

  if (!in_file.is_open() || !out_file.is_open()) {
    throw std::runtime_error("Error: Could not open files for updating.\n");
  }

  std::string line;
  std::string target_subject_code = subject.code();
  bool is_updated = false;

  while (std::getline(in_file, line)) {
    if (line.find(target_subject_code) == 0) {
      out_file << subject.code() << "," << subject.title() << ","
               << subject.units() << "\n";
      is_updated = true;
    } else {
      out_file << line << "\n";
    }
  }

  in_file.close();
  out_file.close();

  if (is_updated) {
    std::remove(orig_path.c_str());
    std::rename(temp_file_name.c_str(), orig_path.c_str());
    std::cout << "Record updated successfully!\n";
  } else {
    std::remove(temp_file_name.c_str());
    std::cout << "Cannot update file.\n";
  }
}

void FileManager::delete_subject_file(const std::string &orig_path,
                                      Subject &subject) {
  std::string temp_file_name = "data/temp_subjects.txt";

  std::ifstream in_file(orig_path);
  std::ofstream out_file(temp_file_name);

  if (!in_file.is_open() || !out_file.is_open()) {
    throw std::runtime_error("Error: Could not open files for deletion.\n");
  }

  std::string line;
  std::string target_subject_code = subject.code();
  bool is_updated = false;

  while (std::getline(in_file, line)) {
    if (line.find(target_subject_code) == 0) {
      is_updated = true;
    } else {
      out_file << line << "\n";
    }
  }

  in_file.close();
  out_file.close();

  if (is_updated) {
    std::remove(orig_path.c_str());
    std::rename(temp_file_name.c_str(), orig_path.c_str());
    std::cout << "Record deleted successfully!\n";
  } else {
    std::remove(temp_file_name.c_str());
    std::cout << "Cannot delete file.\n";
  }
}
