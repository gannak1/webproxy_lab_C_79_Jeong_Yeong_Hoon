def solution(sequence, k):
    min_start = 999999999999999999
    answer_array = [-1,9999999999999999999]
    for i in range(len(sequence)):
        this_sum = sequence[i]
        start = i
        end = -1
        is_answer = False
        for j in range(i,len(sequence)):
            if i == j:
                pass
            else:
                this_sum += sequence[j]
            if k == this_sum:
                end = j
                is_answer = True
                break
            elif k < this_sum:
                break
        if is_answer:
            if min_start > start and ((answer_array[1] - answer_array[0]) > end - start):
                min_start = start
                answer_array[1] = end
                answer_array[0] = start
    
    answer = answer_array
    return answer



print(solution([1, 2, 3, 4, 5], 7))