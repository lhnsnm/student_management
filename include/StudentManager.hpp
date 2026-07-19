#ifndef STUDENT_MANAGER_HPP
#define STUDENT_MANAGER_HPP

#include <vector>
#include <utility>
#include "Student.hpp"

class StudentNode
{
public:
    int key;
    Student student;
    StudentNode *next{nullptr};

    StudentNode(Student s)
        : student{std::move(s)}, next{nullptr} {}
};

class StudentManager
{
private:
    std::vector<StudentNode *> students{1000, nullptr};

    int student_count{0};

    int hash(int key);

    void clear();

public:
    StudentManager() = default;
    ~StudentManager();

    StudentManager(const StudentManager &other);
    StudentManager &operator=(const StudentManager &other);
    StudentManager(StudentManager &&other) noexcept;
    StudentManager &operator=(StudentManager &&other) noexcept;

    void put(const Student &student, const int key);
    void remove(int key);
    Student get(int key);
    void print();
    int size();
};

#endif