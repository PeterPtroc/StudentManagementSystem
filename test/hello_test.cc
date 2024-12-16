#include <gtest/gtest.h>
#include <sstream>
#include "gpa.h"
#include "input.h"

// 重定向 stdin
void redirectStdin(const std::string &input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());
}

class GPA_Test : public ::testing::Test {
protected:
    // 创建测试用的学生数据
    void SetUp() override {
        student1 = {1, "Alice", "Class A",
                    {85, 90, 76, 88, 92, 81, 79, 87, 93, 84},
                    {3.0, 3.0, 2.0, 2.5, 3.5, 2.0, 3.0, 2.0, 2.0, 1.5},
                    0.0};

        student2 = {2, "Bob", "Class B",
                    {55, 60, 70, 80, 90, 100, 65, 75, 85, 95},
                    {2.0, 2.5, 2.0, 3.0, 3.5, 4.0, 3.0, 2.5, 3.0, 2.0},
                    0.0};

        students[0] = student1;
        students[1] = student2;
    }

    Student student1;
    Student student2;
    Student students[2];
};

// 测试 calculateGPA 函数
TEST_F(GPA_Test, CalculateGPA) {
    calculateGPA(&student1);

    // 手动计算 Alice 的 GPA
    float expectedGPA = ((85 - 50) / 10.0 * 3.0 +
                         (90 - 50) / 10.0 * 3.0 +
                         (76 - 50) / 10.0 * 2.0 +
                         (88 - 50) / 10.0 * 2.5 +
                         (92 - 50) / 10.0 * 3.5 +
                         (81 - 50) / 10.0 * 2.0 +
                         (79 - 50) / 10.0 * 3.0 +
                         (87 - 50) / 10.0 * 2.0 +
                         (93 - 50) / 10.0 * 2.0 +
                         (84 - 50) / 10.0 * 1.5) /
                        (3.0 + 3.0 + 2.0 + 2.5 + 3.5 + 2.0 + 3.0 + 2.0 + 2.0 + 1.5);

    EXPECT_FLOAT_EQ(student1.gpa, expectedGPA);
}


// 测试 findAndPrintGPA 函数
TEST(GPA_Test, FindAndPrintGPAWithMockInput) {
    // 准备测试数据
    Student students[1] = {
        {20245363, "Alice", "Class A",
         {85, 90, 76, 88, 92, 81, 79, 87, 93, 84},
         {3.0, 3.0, 2.0, 2.5, 3.5, 2.0, 3.0, 2.0, 2.0, 1.5},
         0.0}};

    // 模拟输入学号为 1
    redirectStdin("20245363\n");

    // 捕获标准输出
    testing::internal::CaptureStdout();
    findAndPrintGPA(students, 1);
    std::string output = testing::internal::GetCapturedStdout();

    // 验证输出
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("GPA 为"), std::string::npos);
}

