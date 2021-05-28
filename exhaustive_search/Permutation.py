import itertools


def solution(numbers):
    answer = 0
    arr = list(numbers)
    num_list = []
    for i in range(1, len(arr) + 1):
        tmp = list(map(''.join, itertools.permutations(arr, i)))
        num_list = num_list + tmp

    num_list = list(set(list(map(int, num_list))))
    print(num_list)
    for i in num_list:
        if isPrime(i) == True:
            answer = answer + 1
    return answer


def isPrime(a):
    if (a < 2):
        return False
    for i in range(2, a):
        if (a % i == 0):
            return False
    return True

solution("011")