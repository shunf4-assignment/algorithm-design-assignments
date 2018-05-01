# coding=utf-8
import copy
import sys
import math
import random

def partition(l, begI, endI, func):
    pivot = l[begI]
    leftI = begI
    rightI = endI
    while(leftI < rightI):
        while(True):
            if(leftI >= rightI):
                break
            if(func(l[rightI]) < func(pivot)):
                l[leftI] = l[rightI]
                break
            rightI -=1
        while(True):
            if(leftI >= rightI):
                break
            if(func(l[leftI]) > func(pivot)):
                l[rightI] = l[leftI]
                break
            leftI += 1
    l[leftI] = pivot
    return leftI

def quickSort_do(l, begI, endI, func):
    if begI >= endI:
        return

    pivotI = partition(l, begI, endI, func)
    quickSort_do(l, begI, pivotI - 1, func)
    quickSort_do(l, pivotI + 1, endI, func)

def quickSort(l, func):
    quickSort_do(l, 0, len(l) - 1, func)

def servicePriority(customers):
    customersE = list(enumerate(customers))
    quickSort(customersE, lambda x:x[1])

    totalWaitingTime = 0
    n = len(customers)

    for x in customersE:
        totalWaitingTime += n * x[1]
        n -= 1

    return (totalWaitingTime / len(customers), customersE)

def main():
    customers = [56,12,1,99,1000,234,33,55,99,812]
    avgWaitTime, cusArr = servicePriority(customers)
    n = len(customers)
    totalWaitingTime = 0

    for i, e in enumerate(cusArr):
        print(i, ": 第", e[0], "位顾客")
    print("平均等待时间: ", avgWaitTime)
    
main()