#ifndef COURSE_H
#define COURSE_H

typedef enum
{
    CHINESE = 1,
    MATH,
    ENGLISH,
    PHYSICS,
    CHEMISTRY,
    BIOLOGY,
    POLITICAL_EDUCATION,
    HEALTH,
    PROGRAMMING,
    HISTORY
} CourseNumber;

static const char *courseNames[] = {
    "语文", "chinese", "chi",
    "数学", "math", "mat",
    "英语", "english", "eng",
    "物理", "physics", "phy",
    "化学", "chemistry", "che",
    "生物", "biology", "bio",
    "政治", "political_education", "pol",
    "健康", "health", "hea",
    "编程", "programming", "pro",
    "历史", "history", "his"};

#endif