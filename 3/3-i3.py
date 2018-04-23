# coding=utf-8
import copy
import sys
import math
import random

def circularStoneMerge(l):
    '''
    环形石堆合并问题
        环形摆放 len(l) 堆石子，第 i 堆有 l[i-1] 个石子。
        相邻石堆合并可得合并所得大石堆石头数目相等的分。
        求所有石头合并为一堆之后的可能最高得分和最低得分。
    '''
    
    n = len(l)
    accumulated = []
    sumOfL = 0
    for x in l:
        accumulated.append(sumOfL + x)
        sumOfL += x

    def clockwiseSum(i, j):
        '''
            Sum of [l[i], l[i+1], ... , l[n-1], l[0], l[1], ..., l[j-1]]
        '''
        if i > 0 and j >= i:
            return accumulated[j] - accumulated[i-1]
        if i == 0 and j >= i:
            return accumulated[j]
        if j < i:
            return accumulated[n-1] - accumulated[i-1] + accumulated[j]

    x = [[[math.inf,-math.inf] for k in range(0, n+1)] for i in range(0, n+1)]
    # x[i][j] = [minPoints, maxPoints]
    #   从第 i 个石子（从 0 开始）到下 j 个石子这个范围，可以获得的最小分和最大分。
    for i in range(0,n+1):
        x[i][0] = [0,0] #从本身到本身，无法合并，两个分都为 0

    for j in range(1, n):     # 外循环为步长，从 1 开始
        for i in range(0, n):   # 内循环为起始石子的编号
            for k in range(0, j+1):     # 遍历所有剖分方式
                x[i][j][0] = min(x[i][j][0], x[i][k][0] + x[(i+k+1)%n][j-k-1][0] + clockwiseSum(i, (i+j)%n))
                x[i][j][1] = max(x[i][j][1], x[i][k][1] + x[(i+k+1)%n][j-k-1][1] + clockwiseSum(i, (i+j)%n))

    minPoint = math.inf;
    maxPoint = -math.inf;

    for i in range(0, n):    # 遍历起始石子为 i，步长固定为 n-1（即绕一圈整合所有石子），得到分数的最小值和最大值
        minPoint = min(minPoint, x[i][n-1][0])
        maxPoint = max(maxPoint, x[i][n-1][1])

    return minPoint, maxPoint

    
            
def main():
    testTimeNo = 1000
    listMaxLength = 10
    maxStoneNo = 9

    correctNo = 0
    for k in range(testTimeNo):
        currLen = random.randint(0, listMaxLength) + 1

        stones = [random.randint(1, maxStoneNo) for i in range(currLen)]
        
        if (k == 0):
            stones = [4,4,5,9]

        minPoint, maxPoint = circularStoneMerge(stones)

        if(k == 0):
            print("第一次测试的题面：", "\nstones:", stones)
            print("我的答案 - 最小分、最大分：", minPoint, maxPoint)
        print("第 {} 次测试。".format(k+1), end='\r')
        
    print("\n运行完成。")

    
main()
        