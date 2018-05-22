import copy
import random

INFINITY = 9999999

class MinWeightMachine(object):
    def __init__(self, costs, weights, costsLimit):
        assert(len(costs) > 0)
        self.componentsNum = len(costs)      # 部件总数
        assert(isinstance(costs[0], list))
        assert(len(costs[0]) > 0)
        for x in costs:
            assert(len(x) == len(costs[0]))
        self.providersNum = len(costs[0])   # 供应商总数
        self.costs = costs                  # costs[c - 1][p - 1] 表示第 c 个部件从第 p 个供应商处获得所付出的价格
        self.costsWhenSelectedCheapest = [min(x) for x in self.costs]   # 每一个部件的最小价格

        assert(len(weights) == self.componentsNum)
        for x in weights:
            assert(len(x) == self.providersNum)
        self.weights = weights
        self.weightsWhenSelectedLightest = [min(x) for x in self.weights]   # 每一个部件的最轻重量

        self.costsLimit = costsLimit

    def startBacktrack(self):
        # 回溯时使用的数组，select[c - 1] == p - 1 表示对于第 c 件部件，选择第 p 个供应商
        self.select = [0] * self.componentsNum
        self.currWeight = 0
        self.currCosts = 0
        self.currMinWeight = INFINITY
        self.result = None

        self._backtrack(0)

        if self.result == None:
            raise ValueError("Can not find solution.")

        return self.result

    def _backtrack(self, depth):
        
        if depth >= self.componentsNum:
            if self.currMinWeight > self.currWeight:
                self.currMinWeight = self.currWeight
                selectPlusOne = [x + 1 for x in self.select]
                self.result = (self.currWeight, self.currCosts, selectPlusOne)
        else:
            # 扩展该节点，第 depth - 1 个部件可以从 providersNum 个供应商中选择
            for p in range(self.providersNum):
                self.select[depth] = p
                self.currWeight += self.weights[depth][p]
                self.currCosts += self.costs[depth][p]

                # 如果此后的部件全选最便宜的，还是没法在限制之内

                if self.currCosts + sum(self.costsWhenSelectedCheapest[depth + 1:]) > self.costsLimit:
                    pass
                # 如果此后的部件全选最轻的，还是没法和当前的最小值比
                elif self.currWeight + sum(self.weightsWhenSelectedLightest[depth + 1:]) > self.currMinWeight:
                    pass
                else:
                    # 否则，可以开始这个子树的扩展
                    self._backtrack(depth + 1)

                self.currWeight -= self.weights[depth][p]
                self.currCosts -= self.costs[depth][p]

def main():
    testTimeNo = 1000
    listMaxLength = 10
    maxWeight = 20
    maxCost = 40
    correctNo = 0
    for k in range(testTimeNo):
        if(k == 0):
            currLen = 10
            costs = [[1,2,3],[3,2,1],[2,2,2]]
            weights = [[1,2,3],[3,2,1],[2,2,2]]
            costsLimit = 4
        else:
            currLen = random.randint(0, listMaxLength) + 1
            currProvider = random.randint(0, listMaxLength) + 1
        
            weights = [[random.randint(1, maxWeight) for j in range(currProvider)] for i in range(currLen)]
            costs = [[random.randint(1, maxCost) for j in range(currProvider)] for i in range(currLen)]
            costsLimit = random.randint(max([min(x) for x in costs]) * currLen, maxCost * currLen)

        resultWeight, resultCosts, resultSelect = MinWeightMachine(costs, weights, costsLimit).startBacktrack()
        costsSum = 0
        for i, p in enumerate(resultSelect):
            costsSum += costs[i][p-1]

        assert(costsSum <= costsLimit)

        if(k == 0):
            print("第一次测试题面：", "\nweights:", weights, "\ncosts:", costs, "\ncostsLimit:", costsLimit)
            print("答案的总重量：", resultWeight)
            print("答案的总花费：", resultCosts)
            print("答案的供应商选择：", resultSelect)

        print("第 {} 次测试。".format(k+1), end='\r')
        
    print("\n运行完成。")

    
main()