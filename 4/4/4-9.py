# coding=utf-8
import copy
import sys
import math
import random
def refuel(fullDistance, distanceList):
    i = 0;
    refuelTime = 0
    fuel = fullDistance
    while(True):
        if(i == len(distanceList)):
            break
        if fullDistance < distanceList[i]:
            print("不可能完成任务。")
            return
        if fuel < distanceList[i]:
            print("从节点", i, "到节点", i+1, "需要汽油", distanceList[i], "，当前有", fuel, "，需要第", refuelTime+1, "次加油")
            fuel = fullDistance
            refuelTime += 1
        else:
            fuel -= distanceList[i]
            print("成功从节点", i, "到达节点", i+1, "剩余油量", fuel, "。")
            i += 1
    print("加油次数：", refuelTime)

def main():
    fullDistance = 7
    distanceList = [1,2,3,4,5,1,6,6]
    refuel(fullDistance, distanceList)

main()
