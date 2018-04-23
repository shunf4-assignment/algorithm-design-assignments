# coding=utf-8
import copy
import sys
import math
import random

def knapSack(weights, volumes, values, c, d, zeroone):
    '''背包问题'''
    # weights[i-1] : 物品 i 的重量
    # valumes[i-1] : 物品 i 的体积
    # values[i-1] : 物品 i 的价值
    # c : 限定重量
    # d : 限定体积
    # zeroone : 是否是一个 0-1 背包问题（否则为一般背包问题）
    n = len(weights)
    assert(n == len(values))
    assert(n == len(volumes))

    x = [[[copy.copy([0, -1, -1, -1, 0, -1]) for k in range(d + 1)] for j in range(c + 1)] for i in range(n + 1)]
    # x[i][j] == [val, prevI, prevJ, prevK, addItemNo, addItem]
    # 当限定只能用物品 1~i，限定重量不能超过 j，限定容量不能超过 k 时，背包可最多装价值为 val 的物品，且物品组合等于 x[prevI][prevJ][prevK] 对应组合加上 addItemNo 件 addItem

    # 订正：addItemNo 非0即1，故下面计算时不做考虑
    for i in range(1, n+1):
        for j in range(1, c+1):
            for k in range(1, d+1):
                # 当不选物品 i 时 VS 加选一件物品 i 时
                # 首先，当 j 的重量或 k 的体积决定了无法加选物品 i 时，只能选前者
                if j < weights[i-1] or k < volumes[i-1]:
                    x[i][j][k] = x[i-1][j][k]
                # 否则，比较这两者，择优
                else:
                    if(zeroone):
                        #若是 0-1 背包，应该从不加 i 的子问题出发；若是一般背包，可以从有 i 的子问题出发
                        ix = i - 1
                    else:
                        ix = i

                    
                    if (x[i-1][j][k][0] > x[ix][j-weights[i-1]][k-volumes[i-1]][0] + values[i-1]):
                        x[i][j][k] = x[i-1][j][k]
                    else:
                        x[i][j][k] = [x[ix][j-weights[i-1]][k-volumes[i-1]][0] + values[i-1], ix, j-weights[i-1], k-volumes[i-1], 1, i]

    # print(x)
    # 目标 x[n][c][d]
    knapSackItems = []
    currentI = n
    currentJ = c
    currentK = d
    countValue = 0
    countWeight = 0
    countVolume = 0
    while(currentI != -1 and currentJ != -1 and currentK != -1):
        if(x[currentI][currentJ][currentK][5] > 0):
            currentX = x[currentI][currentJ][currentK]
            knapSackItems.append(currentX[5])
            countValue += values[knapSackItems[-1]-1]
            countWeight += weights[knapSackItems[-1]-1]
            countVolume += volumes[knapSackItems[-1]-1]
            currentI = currentX[1]
            currentJ = currentX[2]
            currentK = currentX[3]
        else:
            break

    assert(countValue == x[n][c][d][0])
    assert(countWeight <= c)
    assert(countVolume <= d)

    return (x[n][c][d][0], countWeight, countVolume, knapSackItems)


def main():
    testTimeNo = 1000
    listMaxLength = 10
    maxWeight = 20
    maxVolume = 15
    maxValue = 40
    correctNo = 0
    for k in range(testTimeNo):
        currLen = random.randint(0, listMaxLength) + 1
        if(k == 0):
            currLen = 10
        weights = [random.randint(1, maxWeight) for i in range(currLen)]
        volumes = [random.randint(1, maxVolume) for i in range(currLen)]
        values = [random.randint(1, maxValue) for i in range(currLen)]
        c = random.randint(0, maxWeight * currLen)
        d = random.randint(0, maxVolume * currLen)

        knapSackValue, knapSackWeight, knapSackVolume, knapSackItems = knapSack(weights, volumes, values, c, d, True)

        if(k == 0):
            print("题面：", "\nweights:", weights, "\nvolumes:", volumes, "\nvalues:", values, "\nc:", c, "\nd:", d)
            print("我的答案的背包价值：", knapSackValue)
            print("我的答案的背包重量：", knapSackWeight)
            print("我的答案的背包体积：", knapSackVolume)
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
        