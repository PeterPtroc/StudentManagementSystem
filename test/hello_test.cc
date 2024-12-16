#include <gtest/gtest.h>
#include "calculate/gpa.h"
#include "calculate/student.h"

TEST(GPA, BasicTest)
{
    Student stu;
    stu.num = 123456;
    strcpy(stu.name, "John Doe");
    for (int i = 0; i < COURSE_NUM; i++)
    {
        stu.score[i] = 75; // 假设每门课的分数是75
        stu.credit[i] = 3; // 假设每门课的学分是3
    }

    // 计算 GPA
    calculateGPA(&stu);

    // 检查 GPA 是否符合预期
    EXPECT_FLOAT_EQ(stu.gpa, 2.5); // 假设 GPA 为 2.5
}

TEST(GPA, ZeroCredits)
{
    Student stu;
    stu.num = 123456;
    strcpy(stu.name, "Jane Doe");
    for (int i = 0; i < COURSE_NUM; i++)
    {
        stu.score[i] = 75;
        stu.credit[i] = 0; // 所有课程的学分为0
    }

    // 计算 GPA（应处理学分为0的情况）
    calculateGPA(&stu);

    // 期望 GPA 为 0 或者其他特定值，取决于你的业务逻辑
    EXPECT_FLOAT_EQ(stu.gpa, 0.0);
}
