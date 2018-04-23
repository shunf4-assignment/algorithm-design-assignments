import copy
import sys
import math
import random

def standardSolution_LIS(a):
    """
    别人的算法，用来检验正确性
    """
    L = []
    for (k,v) in enumerate(a):
        L.append(max([L[i] for (i,n) in enumerate(a[:k]) if n<v] or [[]], key=len) + [v])
    return max(L, key=len)

def longestIncrementalSubsequence(l):
    '''找出l的最长单调递增子序列'''
    n = len(l)  #l的长度
    x = [copy.copy([0,-1]) for i in range(n)]  #x[i]=[a, b]表示以l[i]结尾的最长单调递增子序列，长度为a，倒数第二个元素为l[b]

    x[0] = [1, -2]  #以l[0]结尾的子序列长度只能为1，没有倒数第二个元素

    for i in range(1, n):
        maxLength = -math.inf
        lastIndexOfSubsequenceThatHasMaxLength = -1
        for j in range(0, i):
            if x[j][0] > maxLength and l[j] < l[i]:
                maxLength = x[j][0]
                lastIndexOfSubsequenceThatHasMaxLength = j  #找到了一个l[i]可以加到后面去的子序列
        if lastIndexOfSubsequenceThatHasMaxLength == -1:
            #没有找到可以让l[i]加到后面的子序列，故l[i]自成一序列
            x[i] = [1, -2]
        else:
            x[i] = [x[lastIndexOfSubsequenceThatHasMaxLength][0] + 1, lastIndexOfSubsequenceThatHasMaxLength]

    maxLength = -math.inf
    lastIndexOfSubsequenceThatHasMaxLength = -1
    for i in range(0, n):
        if x[i][0] > maxLength:
            maxLength = x[i][0]
            lastIndexOfSubsequenceThatHasMaxLength = i


    assert(lastIndexOfSubsequenceThatHasMaxLength != -1)

    resultSubsequence = []
    currentIndex = lastIndexOfSubsequenceThatHasMaxLength

    while(currentIndex != -2):
        resultSubsequence[0:0] = [l[currentIndex]]
        currentIndex = x[currentIndex][1]

    return (maxLength, resultSubsequence)
    
def binaryReplace(l, LISLeastEndIndex, start, end, i):
    currStart = start
    currEnd = end
    if currStart == currEnd:
        LISLeastEndIndex[currStart] = i
        return currStart
    if l[i] > l[LISLeastEndIndex[end]]:
        return -1
    while(True):
        if currStart == currEnd:
            LISLeastEndIndex[currStart] = i
            return currStart
        pivot = (currStart + currEnd) // 2
        if l[i] == l[LISLeastEndIndex[pivot]]:
            return pivot
        if l[i] < l[LISLeastEndIndex[pivot]]:
            currEnd = pivot
        if l[i] > l[LISLeastEndIndex[pivot]]:
            currStart = pivot + 1

def longestIncrementalSubsequence_NlgN(l):
    '''找出l的最长单调递增子序列，NlgN 时间复杂度'''
    LISLeastEndIndex = [-1] * len(l)
    LISPrevIndex = [-1] * len(l)
    LISPointer = 0
    for i in range(len(l)):
        if (i == 0):
            LISLeastEndIndex[LISPointer] = 0
            LISPointer = LISPointer + 1
        elif (l[i] > l[LISLeastEndIndex[LISPointer - 1]]):
            LISLeastEndIndex[LISPointer] = i
            LISPrevIndex[i] = LISLeastEndIndex[LISPointer - 1]
            LISPointer = LISPointer + 1
        else:
            replacedIndex = binaryReplace(l, LISLeastEndIndex, 0, LISPointer - 1, i)
            if replacedIndex >= 0:
                LISPrevIndex[i] = LISLeastEndIndex[replacedIndex - 1]
            else:
                LISPrevIndex[i] = -1

    subseqLastI = LISLeastEndIndex[LISPointer - 1]
    currI = subseqLastI
    subseq = []
    while(currI >= 0):
        subseq[0:0] = [l[currI]]
        currI = LISPrevIndex[currI]

    return (LISPointer, subseq)

def main():
    testTimeNo = 1000
    listMaxLength = 100
    correctNo = 0
    for k in range(testTimeNo):
        currLen = random.randint(0, listMaxLength) + 1
        if(k == 0):
            currLen = 10
        l = [random.randint(-listMaxLength, listMaxLength) for i in range(currLen)]

        myAnswerMaxLength, myAnswerSubsequence = longestIncrementalSubsequence_NlgN(l)
        standardSubsequence = (standardSolution_LIS(l))
        standardMaxLength = len(standardSubsequence)
        if(k == 0):
            print("第一次测试题面：", l)
            print("我的答案的长度：", myAnswerMaxLength)
            print("我的答案的最长递增子序列：", myAnswerSubsequence)
            print("标准答案的长度：", standardMaxLength)
            print("标准答案的最长递增子序列：", standardSubsequence)
            print("{}".format(["错误", "正确"][myAnswerMaxLength == standardMaxLength]))
        #if(myAnswerSubsequence == standardSubsequence):
        if(myAnswerMaxLength == standardMaxLength):
            correctNo = correctNo + 1
        print("经过 {} 次测试后，有 {} 次为正确。".format(k+1, correctNo), end='\r')
        
    print("\n运行完成。")

    
main()
        