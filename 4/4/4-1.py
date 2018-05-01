# coding=utf-8
import copy
import sys
import math
import random

def partition(l, begI, endI):
    ix = begI
    iy = endI
    pivot = l[begI]
    while iy > ix:
        while(True):
            if iy <= ix:
                break
            if(l[iy] < pivot):
                l[ix] = l[iy]
                break
            iy = iy - 1
        while(True):
            if iy <= ix:
                break
            if l[ix] > pivot:
                l[iy] = l[ix]
                break
            ix = ix + 1
    assert(iy == ix)
    l[iy] = pivot
    return iy
    

def quickSort_do(l, begI, endI):
    if begI >= endI:
        return
    if begI == endI - 1:
        if l[begI] > l[endI]:
            tmp = l[begI]
            l[begI] = l[endI]
            l[endI] = tmp
        return

    pivotI = partition(l, begI, endI)
    quickSort_do(l, begI, pivotI - 1)
    quickSort_do(l, pivotI + 1, endI)

def quickSort(l):
    '''
        以 l[i][0] 为主键，将 l 从小到大排序。
    '''
    quickSort_do(l, 0, len(l) - 1)
    
def biSearch_do(rooms, time, begI, endI, prevBegI, prevEndI):
    if begI == endI:
        if time < rooms[begI][0]:
            return (prevBegI, begI)
        if time == rooms[begI][0]:
            return (begI, begI)
        if time > rooms[begI][0]:
            return (begI, prevEndI)
    if begI > endI:
        return (prevBegI, begI)

    midI = (begI + endI) // 2
    if time == rooms[midI][0]:
        return (midI, midI)
    elif time < rooms[midI][0]:
        return biSearch_do(rooms, time, begI, midI - 1, prevBegI, midI)
    elif time > rooms[midI][0]:
        return biSearch_do(rooms, time, midI+1, endI, midI, prevEndI)

def biSearch(rooms, time):
    return biSearch_do(rooms, time, 0, len(rooms)-1, -1, len(rooms))

def activityRoomScheduling(startTime, endTime, debug):
    '''
        会场安排问题，贪心算法
            startTime[i] 是活动 i 的开始时间
            endTime[i] 是活动 i 的结束时间
            会场有无限多个，但要求最少
            求使得安排活动会场数最少的活动调度
        
        返回：会场数，最晚结束时间，具体安排
    '''
    n = len(startTime)
    assert(n == len(endTime))

    rooms = []  # 当前所用会场
    #rooms = [(latestEndTime, [activity1, activity3, activity6]), (...)]
    # rooms is ordered of latestEndTime

    if debug:
        print("原开始时间：", startTime)
        print("原结束时间：", endTime)

    # 首先将活动按照 endTime 排序
    zippedTime = list(zip(endTime, startTime))
    quickSort(zippedTime)
    startTime = [x[1] for x in zippedTime]
    endTime = [x[0] for x in zippedTime]

    if debug:
        print("排序后开始时间：", startTime)
        print("排序后结束时间：", endTime)

    # 接着开始安排
    for i in range(n):
        print("考虑活动", i, "其开始时间", startTime[i], "结束时间", endTime[i])
        leftI, rightI = biSearch(rooms, startTime[i])   # 搜索所有的 room，找适合插入的位置
        if leftI == -1:     # 所有的 room 的最晚结束时间比该起始时间要晚，要用一个新房间
            if(debug):
                print("使用了新会场")
            newRoom = (endTime[i], [i])
            newLeftI, newRightI = biSearch(rooms, endTime[i])   # 理论上endTime[i]肯定要比所有room的都晚，所以此处可不查找，直接插到room末尾
            assert(newRightI == len(rooms))
            rooms[newRightI:newRightI] = [newRoom]
        else:
            if(debug):
                print("使用了会场", leftI)
            updatedRoom = (rooms[leftI])
            rooms[leftI:leftI+1] = []
            updatedRoom = (endTime[i], updatedRoom[1] + [i])
            newLeftI, newRightI = biSearch(rooms, endTime[i])
            rooms[newRightI:newRightI] = [updatedRoom]  # 重新插入该房间
        if(debug):
            print("更新后的会场", rooms)

    if debug:
        for i,r in enumerate(rooms):
            print("会场 {} : 结束时间 {}, 安排活动 {}".format(i, r[0], r[1]))

    roomsNo = len(rooms)
    return (roomsNo, rooms[roomsNo-1][0], [r[1] for r in rooms])
    
    
        

def main():
    testTimeNo = 1000
    listMaxLength = 10000
    maxValue = 40000
    
    startTime = [1,12,25,27,36]
    endTime = [23,28,35,80,50]

    roomsNo, latestEndTime, rooms = activityRoomScheduling(startTime, endTime, True)

    print("结果：", roomsNo)

    print("\n运行完成。")

main()