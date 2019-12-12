# -*- coding: utf-8 -*-
"""
Created on Mon Sep 19 11:45:20 2016
Edited  on Wednseday 12.12.2019
original @author: johnguttag
edition  @author: tallgeeze
"""

import random, pylab, numpy

#set line width
pylab.rcParams['lines.linewidth'] = 4
#set font size for titles 
pylab.rcParams['axes.titlesize'] = 20
#set font size for labels on axes
pylab.rcParams['axes.labelsize'] = 20
#set size of numbers on x-axis
pylab.rcParams['xtick.labelsize'] = 16
#set size of numbers on y-axis
pylab.rcParams['ytick.labelsize'] = 16
#set size of ticks on x-axis
pylab.rcParams['xtick.major.size'] = 7
#set size of ticks on y-axis
pylab.rcParams['ytick.major.size'] = 7
#set size of markers
pylab.rcParams['lines.markersize'] = 10
#set number of examples shown in legends
pylab.rcParams['legend.numpoints'] = 1


def rSquared(observed, predicted):
    error = ((predicted - observed)**2).sum()
    meanError = error/len(observed)
    return 1 - (meanError/numpy.var(observed))

class JBC(object):
    def __init__(self, s):
        info = s.split(',')
        self.v1 = float(info[0])
        self.v2 = float(info[1])
        self.v3 = float(info[2])
        
    def getValue(request):
        if request == 1:
            return self.v1
        if request == 2:
            return self.v2
        if request == 3:
            return self.v3

v1_list = []
v2_list = []
v3_list = []
xVals = range(0,90)   

def getV(data):
    
    for d in data:
        try:
            v1_list.append(d.v1)
            #print("v1 loaded")
        except:
            print("failed")
            pass
            
    for d in data:
        try:
            v2_list.append(d.v2)
            #print("v2 loaded")
        except:
            print("failed")
            pass
            
    for d in data:
        try:
            v3_list.append(d.v3)
            #print("v3 loaded")
        except:
            print("failed")
            pass
        
def getData():
    inFile = open('database_90.csv')
    data = []
    for l in inFile:
        data.append(JBC(l))
    return data

    
data = getData()
getV(data)
    

def splitData(xVals, yVals):
    toTrain = random.sample(range(len(xVals)),
                            len(xVals)//2)
    trainX, trainY, testX, testY = [],[],[],[]
    for i in range(len(xVals)):
        if i in toTrain:
            trainX.append(xVals[i])
            trainY.append(yVals[i])
        else:
            testX.append(xVals[i])
            testY.append(yVals[i])
    return trainX, trainY, testX, testY

def Run(file_num):
    numSubsets = 91
    dimensions = (1, 2, 3, 4, 5, 6, 7, 8)
    if file_num == 1:
        yVals = v1_list
    if file_num == 2:
        yVals = v2_list
    if file_num == 3:
        yVals = v3_list

    rSquares = {}
    for d in dimensions:
        rSquares[d] = []
        
    for f in range(numSubsets):
        trainX, trainY, testX, testY = splitData(xVals, yVals)
        for d in dimensions:
            model = pylab.polyfit(trainX, trainY, d)
            estYVals = pylab.polyval(model, trainX)
            estYVals = pylab.polyval(model, testX)
            rSquares[d].append(rSquared(testY, estYVals))
##            print("following d & model:")
##            print(d)
##            print(model,'\n')
    print('Mean R-squares for data for datasets:\n')
    print(file_num)
    for d in dimensions:
        mean = round(sum(rSquares[d])/len(rSquares[d]), 4)
        sd = round(numpy.std(rSquares[d]), 4)
        print('For dimensionality', d, 'mean =', mean,
              'Std =', sd)
    #print(rSquares[3])
    
##    pylab.plot(xVals, yVals)
##    pylab.xlabel('Angles')
##    pylab.ylabel('Values')
##    pylab.title('Values to Angles')


Run(1)
Run(2)
Run(3)

def plot_at(file_num, dim,ch):
    model_list = []
    rSquares = []
    if file_num == 1:
        yVals = v1_list
    if file_num == 2:
        yVals = v2_list
    if file_num == 3:
        yVals = v3_list
    for f in range(91):
        trainX, trainY, testX, testY = splitData(xVals, yVals)
        model = pylab.polyfit(trainX, trainY, dim)
        model_list.append(model)
        estYVals = pylab.polyval(model, trainX)
        estYVals = pylab.polyval(model, testX)
        rSquares.append(rSquared(testY, estYVals))

    if ch == 'best':
        temp = rSquares 
        for elements in temp:
            max_wert = max(temp)
            index = temp.index(max_wert)
            best_model = model_list[index]
        x = []
        for i in range(0,90):
            x.append(i)
        for i in x:
            x[i] = float(x[i])
		
        y = pylab.polyval(best_model, x)

        pylab.plot(x, y)
        pylab.xlabel('Angles')
        pylab.ylabel('Values')
        pylab.title('Best Fits ')

    if ch == 'worst':
        temp = rSquares
        for elements in temp:
            min_wert = min(temp)
            index = temp.index(min_wert)
        best_model = model_list[index]
        x = []
        for i in range(0,90):
            x.append(i)
        for i in x:
            x[i] = float(x[i])
		
        y = pylab.polyval(best_model, x)
        pylab.plot(x, y)
        pylab.xlabel('Angles')
        pylab.ylabel('Values')
        pylab.title('Worst Fits ')
        
##plot_at(1,3,'best')
##plot_at(2,3,'best')
##plot_at(3,4,'best')
##pylab.show()
##
##plot_at(1,3,'worst')
##plot_at(2,3,'worst')
##plot_at(3,4,'worst')
##pylab.show()

#if more precise
plot_at(1,5,'best')
plot_at(2,5,'best')
plot_at(3,4,'best')
pylab.show()

plot_at(1,5,'worst')
plot_at(2,5,'worst')
plot_at(3,4,'worst')
pylab.show()
