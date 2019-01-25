""" 
Author: John Nemeth
Sources: Class material, lab4 notes, python documentation
         https://stackoverflow.com/questions/826493/python-mixing-files-and-loops
         https://stackoverflow.com/questions/14997799/most-pythonic-way-to-print-at-most-some-number-of-decimal-places
         https://www.youtube.com/watch?v=VmogG01IjYc
Description: main file for problem2
"""
import heapq
import sys

#called from __main__
def findConsecMedian(fileName):
    with open(fileName, 'r') as f:
        numLines = int(f.readline())
        #lowerhalf is maxheap, upper is minheap. did not implement 
        #a priorityqueue class like was done for problem1
        lowerHalf = []
        upperHalf = []
        """
        0-For each integer in file ( O(n) at end)
        1-We will insert by lowerhalf root (max value of lower half of int list)
          ( O(log n/2) at end as only half of input n is present in each heap)
        2-The length of lists can only differ by a max of 1 because the median 
          is found in the center of the an ordered list of ints.
        3-Therefore, we can find the integer by either selecting the root 
          of the bigger list (because this will be the middle value), 
          or by performing the calculation on the roots of each ordered list.
        4-Every lowerHalf value must be input as negative value to be a
          max list and must be negated again once pulled out. 
        5-Because this structure splits the work up between two heaps and
          many of the conditionals only occur and affect a portion of the
          list at a time, it has runtime complexity of O(n * log n)
        """
        for integer in f:
            integer = int(integer)

            if len(lowerHalf) == 0 or integer < - lowerHalf[0]:
                heapq.heappush(lowerHalf, - integer)
            else:
                heapq.heappush(upperHalf, integer) 

            if len(lowerHalf) - len(upperHalf) > 1:
                heapq.heappush(upperHalf, - heapq.heappop(lowerHalf))
            elif len(upperHalf) - len(lowerHalf) > 1:
                heapq.heappush(lowerHalf, -heapq.heappop(upperHalf))

            if len(upperHalf) == len(lowerHalf):
                median =  float(- lowerHalf[0] + upperHalf[0]) / 2.0
            else:
                if len(upperHalf) > len(lowerHalf):
                    median = upperHalf[0]
                else:
                    median = - lowerHalf[0]

            print formatted(median)

#from stack overflow, to format output to 1 decimal place if required
def formatted(median):
    return format(median, '.2f').rstrip('0').rstrip('.')

if __name__ == '__main__':
    findConsecMedian(sys.argv[1])
