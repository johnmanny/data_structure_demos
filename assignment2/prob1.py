""" 
Author: John Nemeth
Sources: Class material, lab4 notes, python documentation
Description: main file for sorting HTTP requests from input
             file in order of: tier, estimated time, and
             order of input (in that order) using a heap
             implementation of priority queue
"""
import pq
import sys

#function called in __main__ to sort entries of requests from cmdline argument(filename)
def sortEntries(fileName):
    with open(fileName, 'r') as f:
        numLines = int(f.readline())
        requests = []
        #make list of all requests and insert count (which comes from enumerate)
        for count, line in enumerate(f):
            ip, tier, estimate = line.split()
            estimate = int(estimate)
            request = (estimate, count, tier, ip)
            requests.append(request)
        #send to pq.py to sort list
        sortedLists = pq.sortTraffic(requests)
        for request in sortedLists:
            print request[3]

if __name__ == '__main__':
    sortEntries(sys.argv[1])
