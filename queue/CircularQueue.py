def solution(priorities, location):
    cnt = 0  # 작업 완료 횟수 카운트
    circularqueue = [0 for i in range(len(priorities))]
    prior_sort = sorted(priorities.copy(), reverse=True)  # 우선순위 오름차순 정렬
    circularqueue = priorities + circularqueue

    i = 0
    while cnt != len(priorities):
        print(circularqueue)
        print(prior_sort)
        print(cnt)
        if circularqueue[i] == prior_sort[cnt]:
            cnt = cnt + 1
            if location == i or location == i + len(priorities):
                return cnt

        tmp = circularqueue[i]
        circularqueue[i] = 0

        if circularqueue[i % len(priorities)] == 0:
            circularqueue[i % len(priorities)] = tmp
        else:
            circularqueue[i % len(priorities) + len(priorities)] = tmp
            print(circularqueue)
            print("인덱스")
            print(i % len(priorities) + len(priorities))

        i = i + 1
        if i == len(priorities) * 2:
            i = 0

    return cnt

p = [1, 1, 9, 1, 1, 1]
l = 0
print(solution(p, l))