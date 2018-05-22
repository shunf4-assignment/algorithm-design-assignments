
import copy
import random

INFINITY = 9999999

class MGame(object):
    def __init__(self, numbers, m):
        self.numbers = numbers
        self.m = m
        self.n = len(self.numbers)

    def startBacktrack(self):
        # 回溯时使用的数组，arrange[i - 1] == j - 1 表示现在第 i 个数字是原来的第 j 个数字
        # 初始化时必须是有序的
        self.arrange = list(range(self.n))
        self.operators = [None] * (self.n - 1)  # 操作符数组
        self.partAnswer = None
        self.result = []

        self._backtrack(0)

        return self.result

    def swap(arrange, i, j):
        temp = arrange[i]
        arrange[i] = arrange[j]
        arrange[j] = temp

    def _backtrack(self, depth):
        if depth >= self.n:
            if self.partAnswer == self.m:
                resultStr = ""
                partAnswer = self.numbers[self.arrange[0]]
                for i in range(self.n - 1):
                    resultStr += str(int(partAnswer))
                    partAnswer = partAnswer.__getattribute__(["__add__", "__sub__", "__mul__", "__truediv__"][self.operators[i]])(self.numbers[self.arrange[i+1]])
                    resultStr += "+-*/"[self.operators[i]] + str(self.numbers[self.arrange[i+1]]) + "=" + str(int(partAnswer)) + "; "
                self.result.append(resultStr)
        else:
            for j in range(depth, self.n):
                MGame.swap(self.arrange, depth, j)
                if depth == 0:
                    self.partAnswer = self.numbers[self.arrange[depth]]
                    self._backtrack(depth + 1)
                else:
                    for opCode in range(4):     # 对于每种运算符
                        op = ["__add__", "__sub__", "__mul__", "__truediv__"][opCode]
                        partAnswerBackup = self.partAnswer
                        self.operators[depth - 1] = opCode
                        self.partAnswer = self.partAnswer.__getattribute__(op)(self.numbers[self.arrange[depth]])
                        self._backtrack(depth + 1)
                        self.partAnswer = partAnswerBackup
                MGame.swap(self.arrange, depth, j)

def main():
    result = MGame([7,2,2,12,3], 125).startBacktrack()
    for line in result:
        print(line)

    
main()

