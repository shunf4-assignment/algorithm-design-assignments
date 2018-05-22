
import copy
import random

INFINITY = 9999999

class PlayerPartnership(object):
    def __init__(self, P, Q):
        assert(len(P) > 0)
        self.n = len(P)     # 运动员总数
        for x in P:
            assert(isinstance(x, list))
            assert(len(x) == self.n)

        self.P = P          # P[i-1][j-1] 表示第 i 个男运动员和第 j 个女运动员配合后男方优势

        assert(len(Q) == self.n)
        for x in Q:
            assert(isinstance(x, list))
            assert(len(x) == self.n)
        self.Q = Q          # Q[i-1][j-1] 表示第 i 个女运动员和第 j 个男运动员配合后女方优势

        self.Pmax = [max(x) for x in self.P]    # Pmax[i-1] 表示第 i 个男运动员的最大优势


    def startBacktrack(self):
        # 回溯时使用的数组，select[i - 1] == j - 1 表示第 i 个男运动员和第 j 个女运动员配合
        # 初始化时必须是有序的
        self.arrange = list(range(self.n))
        self.currCompetitiveness = 0
        self.bestCompetitiveness = 0
        self.result = None

        self._backtrack(0)

        if self.result == None:
            raise ValueError("Can not find solution.")

        return self.result

    def swap(arrange, i, j):
        temp = arrange[i]
        arrange[i] = arrange[j]
        arrange[j] = temp

    def _backtrack(self, depth):
        if depth >= self.n:
            if self.currCompetitiveness > self.bestCompetitiveness:
                self.bestCompetitiveness = self.currCompetitiveness
                arrangePlusOne = [x + 1 for x in self.arrange]
                self.result = (self.bestCompetitiveness, arrangePlusOne)
        else:
            # 扩展该节点，第 depth + 1 个男运动员的配合可以从 arrange[depth] 到 arrange[n - 1] 对应的女运动员进行逐个交换，然后搜索下一层
            for j in range(depth, self.n):
                PlayerPartnership.swap(self.arrange, depth, j)
                self.currCompetitiveness += self.P[depth][self.arrange[depth]] * self.Q[self.arrange[depth]][depth]
                if self.currCompetitiveness + sum(self.Pmax[depth + 1:]) < self.bestCompetitiveness:        # 即使后面的男运动员都发挥出最大优势，仍达不到已有的最优解
                    pass
                else:
                    self._backtrack(depth + 1)
                self.currCompetitiveness -= self.P[depth][self.arrange[depth]] * self.Q[self.arrange[depth]][depth]
                PlayerPartnership.swap(self.arrange, depth, j)

def main():
    testTimeNo = 1
    listMaxLength = 10
    maxCompetitiveness = 20
    correctNo = 0
    for k in range(testTimeNo):
        if(k == 0):
            n = 3
            P = [[10,2,3],[2,3,4],[3,4,5]]
            Q = [[2,2,2],[3,5,3],[4,5,1]]
        else:
            n = random.randint(0, listMaxLength) + 1
            P = [[random.randint(1, maxCompetitiveness) for j in range(n)] for i in range(n)]
            Q = [[random.randint(1, maxCompetitiveness) for j in range(n)] for i in range(n)]

        bestCompetitiveness, arrange = PlayerPartnership(P, Q).startBacktrack()

        if(k == 0):
            print("第一次测试题面：", "\nP:", P, "\nQ:", Q)
            print("答案的配合总体优势：", bestCompetitiveness)
            print("答案的配合方式：")
            for i in range(n):
                print("第 %d 个男运动员和第 %d 个女运动员配合" % (i + 1, arrange[i]))

        print("第 {} 次测试。".format(k+1), end='\r')
        
    print("\n运行完成。")

    
main()