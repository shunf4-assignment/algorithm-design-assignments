# coding=utf-8
import copy
import sys
import math
import random

def schedule(timesA, timesB):
    '''独立任务最优调度问题
        处理机 A 和 B 独立完成作业 i 的时间为 timesA[i-1] 和 timesB[i-1]，它们不能操作同一个作业，但可并行工作直至处理完 n 个作业
        求最短时间处理完作业的调度方案
        返回 : [0,1,0,0,1,...]
        表示 : 第 1 个作业给 A，第 2 个作业给 B ……'''
    
    n = len(timesA)
    assert(n == len(timesB))

    aTotal = sum(timesA)
    bTotal = sum(timesB)

    x = [[[[False, -1, -1, -1, -2, -3] for k in range(n + 1)] for j in range(bTotal + 1)] for i in range(aTotal + 1)]
    # x[i][j][k] = [can, prevI, prevJ, prevK, addK, addKTo]
    # can : 处理机能不能在对 A 限时 i，对 B 限时 j 的情况下，完成作业 1...k
    # 若可以的话，其调度等于 x[prevI][prevJ][prevK] 对应的调度，加上将作业 addK 分配给 addKTo(0 表示给 A，1 表示给 B)
    for i in range(0, aTotal+1):
        for j in range(0, bTotal+1):
            x[i][j][0] = [True, -1, -1, -1, -2, -3]

    for i in range(0, aTotal+1):
        for j in range(0, bTotal+1):
            for k in range(1, n+1):
                if i >= timesA[k-1] and x[i - timesA[k-1]][j][k - 1][0]:
                    # 可将作业 k 放在 A 上
                    x[i][j][k] = [True, i - timesA[k-1], j, k - 1, k, 0]
                elif j >= timesB[k-1] and x[i][j - timesB[k-1]][k - 1][0]:
                    # 可将作业 k 放在 B 上
                    x[i][j][k] = [True, i, j - timesB[k-1], k - 1, k, 1]
                else:
                    # 不可能做
                    x[i][j][k] = [False, -1, -1, -1, -2, -3]

    # 目标 : x[.][.][n] 的 can 为 True 的约束之下，前两个下标的大者最小
    minMaxIndexes = math.inf
    indexI = -1
    indexJ = -1
    for i in range(0, aTotal+1):
        for j in range(0, bTotal+1):
            if x[i][j][n][0] == False:
                continue;
            currMaxIndexes = max(i, j)
            if currMaxIndexes < minMaxIndexes:
                minMaxIndexes = currMaxIndexes
                indexI = i
                indexJ = j

    if indexI == -1 or indexJ == -1:
        raise ValueError("Impossible.")
    
    # 根据每次记录的前一下标不断追溯，直到形成完整的调度表
    scheduleResult = [-1] * n
    currI = indexI
    currJ = indexJ
    currK = n
    while(currI >= 0 and currJ >= 0 and currK >= 0):
        currX = x[currI][currJ][currK]
        if (currX[4] > 0 and currX[5] >= 0):
            scheduleResult[currX[4] - 1] = currX[5]
        currI = currX[1]
        currJ = currX[2]
        currK = currX[3]

    # 根据调度表统计 A 和 B 所用时间，看看是否和算出来的最小最大下标一致
    ATime = 0
    BTime = 0
    for i, e in enumerate(scheduleResult):
        if e == 0:
            ATime += timesA[i]
        elif e == 1:
            BTime += timesB[i]
        else:
            raise ValueError("Unexpected scheduleResult")

    assert(max(ATime, BTime) == minMaxIndexes)
    return (minMaxIndexes, scheduleResult)
            
def main():
    testTimeNo = 1000
    listMaxLength = 10
    maxTime = 10

    correctNo = 0
    for k in range(testTimeNo):
        currLen = random.randint(0, listMaxLength) + 1

        timesA = [random.randint(1, maxTime) for i in range(currLen)]
        timesB = [random.randint(1, maxTime) for i in range(currLen)]
        
        if (False):
            timesA = [2,5,7,10,5,2]
            timesB = [3,8,4,11,3,4]

        timeAll, scheduleResult = schedule(timesA, timesB)

        jobsA = [i for i in range(len(scheduleResult)) if scheduleResult[i] == 0]
        jobsB = [i for i in range(len(scheduleResult)) if scheduleResult[i] == 1]

        if(k == 0):
            print("第一次测试的题面：", "\ntimesA:", timesA, "\ntimesB:", timesB)
            print("我的答案的调度 - 处理机 A：", jobsA)
            print("我的答案的调度 - 处理机 B：", jobsB)
            print("我的答案的调度 - 总时间：", timeAll)
        print("第 {} 次测试。".format(k+1), end='\r')
        
    print("\n运行完成。")

    
main()
        