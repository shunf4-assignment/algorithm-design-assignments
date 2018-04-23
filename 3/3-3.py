# coding=utf-8
import copy
import sys
import math
import random

def knapSack(weights, values, b, zeroone):
    '''背包问题'''
    # weights[i-1] : 物品 i 的重量
    # values[i-1] : 物品 i 的价值
    # b : 限定重量
    # zeroone : 是否是一个 0-1 背包问题（否则为一般背包问题）
    n = len(weights)
    assert(n == len(values))

    x = [[copy.copy([0, -1, -1, 0, -1]) for j in range(b + 1)] for i in range(n + 1)]
    # x[i][j] == [val, prevI, prevJ, addItemNo, addItem]
    # 当限定只能用物品 1~i，限定重量不能超过 j 时，背包可最多装价值为 val 的物品，且物品组合等于 x[prevI][prevJ] 对应组合加上 addItemNo 件 addItem

    # 订正：addItemNo 非0即1，故下面计算时不做考虑
    for i in range(1, n+1):
        for j in range(1, b+1):
            # 当不选物品 i 时 vs 加选一件物品 i 时
            # 首先，当 j 的容量决定了无法加选物品 i 时，只能选前者
            if j < weights[i-1]:
                x[i][j] = x[i-1][j]
            # 否则，比较这两者，择优
            else:
                if(zeroone):
                    #若是 0-1 背包，应该从不加 i 的子问题出发；若是一般背包，可以从有 i 的子问题出发
                    ix = i - 1
                else:
                    ix = i
                if (x[i-1][j][0] > x[ix][j-weights[i-1]][0] + values[i-1]):
                    x[i][j] = x[i-1][j]
                else:
                    x[i][j] = [x[ix][j-weights[i-1]][0] + values[i-1], ix, j-weights[i-1], 1, i]

    # print(x)
    # 目标 x[n][b]
    knapSackItems = []
    currentI = n
    currentJ = b
    countValue = 0
    countWeight = 0
    while(currentI != -1 and currentJ != -1):
        if(x[currentI][currentJ][4] > 0):
            currentX = x[currentI][currentJ]
            knapSackItems.append(currentX[4])
            countValue += values[knapSackItems[-1]-1]
            countWeight += weights[knapSackItems[-1]-1]
            currentI = currentX[1]
            currentJ = currentX[2]
        else:
            break

    assert(countValue == x[n][b][0])
    assert(countWeight <= b)

    return (x[n][b][0], countWeight, knapSackItems)


def main():
    testTimeNo = 1000
    listMaxLength = 10
    maxWeight = 20
    maxValue = 40
    correctNo = 0
    for k in range(testTimeNo):
        currLen = random.randint(0, listMaxLength) + 1
        if(k == 0):
            currLen = 10
        weights = [random.randint(1, maxWeight) for i in range(currLen)]
        values = [random.randint(1, maxValue) for i in range(currLen)]
        b = random.randint(0, maxWeight * currLen)
        weights = [23,
                     31,
                     29,
                     44,
                     53,
                     38,
                     63,
                     85,
                     89,
                     82]
        values = [92,
                     57,
                     49,
                     68,
                     60,
                     43,
                     67,
                     84,
                     87,
                     72]
        b = 165

        knapSackValue, knapSackWeight, knapSackItems = knapSack(weights, values, b, False)

        if(k == 0):
            print("第一次测试题面：", "\nweights:", weights, "\nvalues:", values, "\nb:", b)
            print("我的答案的背包价值：", knapSackValue)
            print("我的答案的背包重量：", knapSackWeight)
            print("我的答案的背包内容：", knapSackItems)
        #    print("标准答案的长度：", standardMaxLength)
        #     print("标准答案的最长递增子序列：", standardSubsequence)
        #     print("{}".format(["错误", "正确"][myAnswerMaxLength == standardMaxLength]))
        # if(myAnswerSubsequence == standardSubsequence):
        #     correctNo = correctNo + 1
        # print("经过 {} 次测试后，有 {} 次为正确。".format(k+1, correctNo), end='\r')
        print("第 {} 次测试。".format(k+1), end='\r')
        
    print("\n运行完成。")

    
main()
        