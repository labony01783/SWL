#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

// Base class
class Employee {
public:
    virtual void showDetails() = 0;
};

// Leaf classes
class Developer : public Employee {
    string name;
public:
    Developer(string n) {
        name = n;
    }

    void showDetails() override {
        cout << "Developer: " << name << endl;
    }
};

class Designer : public Employee {
    string name;
public:
    Designer(string n) {
        name = n;
    }

    void showDetails() override {
        cout << "Designer: " << name << endl;
    }
};

// Composite class
class Manager : public Employee {
    string name;
    vector<Employee*> team;
public:
    Manager(string n) {
        name = n;
    }

    void add(Employee* e) {
        team.push_back(e);
    }

    void showDetails() override {
        cout << "Manager: " << name << endl;
        for (int i = 0; i < team.size(); i++) {
            team[i]->showDetails();
        }
    }
};

// ------------------ Google Test Cases ------------------

TEST(CompositePatternTest, SingleLeafTest) {
    Developer dev("Alice");
    Designer des("Bob");

    testing::internal::CaptureStdout();
    dev.showDetails();
    des.showDetails();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Developer: Alice\nDesigner: Bob\n");
}

TEST(CompositePatternTest, ManagerWithTeam) {
    Developer* dev = new Developer("Alice");
    Designer* des = new Designer("Bob");
    Manager mgr("Carol");

    mgr.add(dev);
    mgr.add(des);

    testing::internal::CaptureStdout();
    mgr.showDetails();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Manager: Carol\nDeveloper: Alice\nDesigner: Bob\n");

    delete dev;
    delete des;
}

// Main function to run tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
