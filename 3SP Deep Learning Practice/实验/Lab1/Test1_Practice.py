#本文件仅用于python新手课前练习，不作为本次实验课程提交要求。


# 1. 给定一个字符串，将字符串的英文字母全变为大写
input_str = "This is ustc"
expected_str = "THIS IS USTC"

import string
input_str = input('Please input a string:\n')
expected_str = ''  ## how to do
print(input_str, expected_str)

# 2. 反向输出一个列表的元素的值
input_str = [1, 2, 3, 5.6]
#expected_output： 5.6, 3, 2, 1


# 3.写一个函数，将输出一个列表重复的元素去除，返回去重的列表和重复的元素列表
input_list = [1, 1, 12, 2, 1, 'a', 'a', 'a', 'b', 'b', 'b', 'c']

#expected_return: （[1, 12, 2, 'a', 'b', 'c'],[1,'a','b'])


def remove_duplicates(input_list):
    unique_list = []
    duplicates = []
    for item in input_list:
        if item not in unique_list:
            unique_list.append(item)
        else:
            if item not in duplicates:
                duplicates.append(item)
    return unique_list, duplicates

input_list = [1, 1, 12, 2, 1, 'a', 'a', 'a', 'b', 'b', 'b', 'c']
print(remove_duplicates(input_list))
([1, 12, 2, 'a', 'b', 'c'], [1, 'a', 'b'])

# 4. 输入一行字符，分别打印出其中字母，空格，数字和其他字符的个数
input_str = input("Please input a string:\n")

input_str = input("Please input a string:\n")
letters = 0
spaces = 0
digits = 0
others = 0

for char in input_str:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        spaces += 1
    elif char.isdigit():
        digits += 1
    else:
        others += 1

print(f"Letters: {letters}, Spaces: {spaces}, Digits: {digits}, Others: {others}")

# 5. 求1！+2！+3！+... + 的和， 直到这个和超过20亿，输出这个和
import math

sum_ = 0
i = 1
while sum_ <= 2000000000:
    sum_ += math.factorial(i)
    i += 1

print(sum_)

# 6. 输出100-200之间(含两端）所有的合数之和

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

composite_sum = 0
for num in range(100, 201):
    if not is_prime(num):
        composite_sum += num

print(composite_sum)

# 7. 每一秒钟都输出现在的时间（年月日时分秒）
import datetime

# 8. Longest common suffix
# Write a function that returns the lonest common suffix

#input: ["look", "book", "hook"]

#output: "ook"

#input: ["dogcar", "racercar", "car"]

#output: "car"


