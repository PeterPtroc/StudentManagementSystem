from faker import Faker
import random

fake = Faker('zh_CN')

data_size = 500
generated_nums = set()

def generate_student_data():
    # 学号
    while True:
        num = '2024' + str(random.randint(1000, 9999))
        if num not in generated_nums:
            generated_nums.add(num)
            break
    
    # 姓名
    name = fake.name()
    
    # 班级
    class_num = '24' + str(random.randint(1, 15)).zfill(2)
    
    # 成绩&绩点
    scores_credits = []
    for _ in range(10):
        score = random.choices(
            population=[random.randint(61, 100), random.randint(0, 60)],
            weights=[0.9, 0.1]
        )[0]
        credit = round(random.uniform(0.5, 5.0), 1)
        scores_credits.append(f"{score} {credit}")
    
    # 拼接
    student_data = f"{num} {name} {class_num} " + " ".join(scores_credits)
    return student_data

# 导出
with open('export.ini', 'w') as file:
    for _ in range(data_size):
        file.write(generate_student_data() + '\n')
