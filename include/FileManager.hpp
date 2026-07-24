#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>

class SubjectManager;
class Subject;

class FileManager {
public:
  void load_subject_file(const std::string &path, SubjectManager &sm);

  void write_subject_file(const std::string &path, Subject &subject);

  void update_subject_file(const std::string &orig_path, Subject &subject);

  void delete_subject_file(const std::string &orig_path, Subject &subject);
};

#endif
