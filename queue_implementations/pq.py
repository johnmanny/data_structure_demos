"""
Author: John Nemeth
Sources: 
Description: priority queue class file for assignment 2, problem 1

"""
from heapq import *

class priorityQueue:

    def __init__(self):
        self.q = []

    def isEmpty(self):
        return not bool(self.q)

    def insert(self, x):
        heappush(self.q, x)

    def removeMin(self):
        return heappop(self.q)

#accesses priorityqueue class and sorts requests 
def sortTraffic(unsortedList):
    tierARequests = priorityQueue()
    tierBRequests = priorityQueue()
    for estimate, count, tier, ip in unsortedList:
        curRequest = [estimate, count, tier, ip]
        #insert request into respective heap, count used as tie-breaker in heapq
        if tier == 'A':
            tierARequests.insert(curRequest)
        else:
            tierBRequests.insert(curRequest)
    sortedList = []
    #output into sortedlist in order of tier
    while not tierARequests.isEmpty():
        sortedList.append(tierARequests.removeMin())
    while not tierBRequests.isEmpty():
        sortedList.append(tierBRequests.removeMin())
    
    return sortedList
