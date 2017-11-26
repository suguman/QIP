
import random
import time
import sys
import os
from math import ceil

INPUTDIR = "INPUTS/"
OUTPUTDIR = "OUTPUTS/"
BENCHMARKDIR = "Benchmark/"

beginState = 5
endState = 501
intervalState = 5

exeFile = "./quip"
df = 2

intervalRatio = 5
beginRatio = 10
endRatio = 41



def generateRandom(stateNum, transNum, wt, autNo, rootname):
    #alpha = ["a", "b", "c", "d","e", "f", "g", "h", "i", "j"]
    alpha  = ["a", "b"]
    filenameAut = INPUTDIR+rootname+"_" + str(autNo) + ".txt"
    #print filenameAut
    f = open(filenameAut, 'w')
    start = "0\n\n"
    transitions = ""
    for i in range(transNum):
        src = random.randint(0, stateNum-1)
        dest = random.randint(0, stateNum-1)
        alphaInt = random.randint(0, 1)
        w = random.randint(0, wt-1)
        trans = alpha[alphaInt]+"," + str(src)+"->" + str(dest) +"," + str(w) + "\n"
        transitions += trans
    f.write(start)
    f.write(transitions)
    f.close()
    return filenameAut

def functionRun(fixS, fixT, wt, fixedQuant, expType,  iterNo):
    rootname = str(fixS)+"_" + str(fixT)+"_"+str(wt)+"_"+str(fixedQuant)+"_"+str(expType)+"_"+str(iterNo)
    #ouputFile = rootname+".txt"
    

    if expType == 1:
        #This is when ratio of T/S is fixed, number of states of varAut is varied
        # fixedQuant refers to ratio here, ratio is given as *10
        
        for varS in range(beginState, endState, intervalState):
            fratio = float(fixedQuant)/10
            varT = int(ceil(varS*fratio))
            fixFile = generateRandom(fixS, fixT, wt, 1, rootname)
            varFile = generateRandom(varS, varT, wt, 2, rootname)
            #print fixFile, varFile
            #return 
            
                
            runCommand = " ".join([exeFile, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommand
            os.system(runCommand)              
               

    elif expType == 2:
        #This is when num of states is fixed, density of varAut is varied
        # fixedQuant is number of states in the variable autoamta  here
        varS = fixedQuant
        for ratio in range(beginRatio, endRatio, intervalRatio):
        
            fratio = float(ratio)/10
            #print ratio, fratio
            
            varT = int(ceil(varS * fratio))
            fixFile = generateRandom(fixS, fixT, wt, 1, rootname)
            varFile = generateRandom(varS, varT, wt, 2, rootname)

            runCommand = " ".join([exeFile, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommand
            os.system(runCommand)      
            
    else:
        #expType = 3    
        # This is when num of states grows in both inputs
        for i in range(beginState, endState, intervalState):

            fratio = float(fixedQuant)/10
            
            transNo = int(ceil(i*fratio))
            #print i, transNo
            fixFile = generateRandom(i, transNo, wt, 1, rootname)
            varFile = generateRandom(i, transNo, wt, 2, rootname)

            runCommand = " ".join([exeFile, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommand
            os.system(runCommand) 
            
    
line  = [(sys.argv[1]), (sys.argv[2]), (sys.argv[3]), (sys.argv[4]), (sys.argv[5]),(sys.argv[6])]
inputLine = [int(argString.replace(" ", "")) for argString in line]
stateFix, transFix, wtInput, ratio, expType, iterNo = inputLine[0], inputLine[1], inputLine[2],  inputLine[3], inputLine[4], inputLine[5]
functionRun(stateFix, transFix, wtInput, ratio, expType,  iterNo)
