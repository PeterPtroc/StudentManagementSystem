# 学生信息管理系统

## 使用方式

在 cmakelists 文件里增加了编译选项

option(USE_MINGW "Use x86_64-w64-mingw32-g++ compiler" OFF)

默认为 OFF，即使用 gcc 编译器编译 linux 下文件

如果改为 ON，则使用 x86_64-w64-mingw32-gcc 编译器编译 win 下文件（当然编译器可以自己改）

请先确认目标平台再执行以下步骤

```bash
mkdir build

cd build

cmake ..

make

./StudentManagementSystem
```

## 提供了 datagen 来生成假数据

安装依赖，执行即可，生成文件需放到可执行文件夹的/data 子目录下
当然，我已经提供了预生成的 export.ini 文件以供使用，在项目根目录的/data 子目录下
提供数据生成的规则（也是存储数据的格式）：

```
数据格式："num name class [score credit]*10"
数据解释：学号、姓名、班级、课程成绩及绩点（一共十个课程），所有项之间由一个空格隔开
数据范围：
学号一共八位，前四位固定为2024，后四位随机整数
姓名由faker库随机生成
班级一共四位，前两位为24；后两位在01~15之间的随机整数
成绩范围为0~100的整数，90%的可能性score为大于60的随机数，10%可能性下score才低于60
学分是范围在0.5~5之间的随机浮点数，以0.1为刻度
```
