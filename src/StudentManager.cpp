#include "StudentManager.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>

// Helpers

void StudentManager::clear()
{
    for (StudentNode *&bucket : students)
    {
        StudentNode *curr = bucket;
        while (curr)
        {
            StudentNode *next = curr->next;
            delete curr;
            curr = next;
        }
        bucket = nullptr;
    }
}

int StudentManager::size()
{
    return student_count;
}

int StudentManager::hash(int key)
{
    return key % students.size();
}

// Constructors

StudentManager::~StudentManager()
{
    clear();
}

StudentManager::StudentManager(const StudentManager &other)
    : students(1000, nullptr)
{
    for (size_t i = 0; i < other.students.size(); ++i)
    {
        StudentNode *curr = other.students[i];
        StudentNode *tail = nullptr;

        while (curr)
        {
            StudentNode *copy = new StudentNode(curr->student);
            copy->key = curr->key;
            copy->next = nullptr;

            if (tail)
            {
                tail->next = copy;
            }
            else
            {
                students[i] = copy;
            }

            tail = copy;
            student_count++;
            curr = curr->next;
        }
    }
}

StudentManager &StudentManager::operator=(const StudentManager &other)
{
    if (this != &other)
    {
        StudentManager temp(other);
        std::swap(students, temp.students);
        std::swap(student_count, temp.student_count);
    }

    return *this;
}

StudentManager::StudentManager(StudentManager &&other) noexcept
    : students(std::move(other.students))
{
    other.students.assign(1000, nullptr);
    other.student_count = 0;
}

StudentManager &StudentManager::operator=(StudentManager &&other) noexcept
{
    if (this != &other)
    {
        clear();
        students = std::move(other.students);
        other.students.assign(1000, nullptr);
        other.student_count = 0;
    }

    return *this;
}

// Methods

void StudentManager::put(
    const Student &student,
    const int key)
{
    int hkey = hash(key);
    StudentNode *curr = students[hkey];

    while (curr)
    {
        if (curr->key == key)
        {
            curr->student = student;
            return;
        }
        curr = curr->next;
    }

    StudentNode *new_student_node = new StudentNode(student);
    new_student_node->key = key;
    new_student_node->next = students[hkey];
    students[hkey] = new_student_node;
    student_count++;
}

void StudentManager::remove(int key)
{
    int hkey = hash(key);

    StudentNode *prev = nullptr, *curr = students[hkey];

    while (curr)
    {
        if (curr->key == key)
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                students[hkey] = curr->next;
            }

            delete curr;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
    student_count--;
}

Student StudentManager::get(int key)
{
    int hkey = hash(key);

    StudentNode *curr = students[hkey];

    while (curr)
    {
        if (curr->key == key)
        {
            return curr->student;
        }

        curr = curr->next;
    }

    throw std::runtime_error("Student not found");
}

void StudentManager::print()
{
    // Set headers with a fixed 12-character width
    std::cout << std::left
              << std::setw(40) << "ID"
              << std::setw(20) << "First Name"
              << "Last Name" << std::endl;

    for (size_t i = 0; i < students.size(); i++)
    {
        StudentNode *curr = students[i];

        while (curr)
        {
            std::string id = curr->student.get_id();
            std::string fname = curr->student.get_first_name();
            std::string lname = curr->student.get_last_name();

            // Print in neat, aligned columns
            std::cout << std::left
                      << std::setw(40) << id
                      << std::setw(20) << fname
                      << lname << std::endl;

            curr = curr->next;
        }
    }
}
