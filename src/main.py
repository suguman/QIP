
import random
import time
import sys
import os
from math import ceil

INPUTDIR = "INPUTS/"
OUTPUTDIR = "OUTPUTS/"
BENCHMARKDIR = "Benchmark/"

beginState = 5
endState = 1501
intervalState = 5

exeFile = "./quip"
exeFileDet = "./detlp"
df = 4

intervalRatio = 5
beginRatio = 10
endRatio = 41

def generateCompleteRandom(stateNum, ratio, wt, autNo, rootname):
    #alpha = ["a", "b", "c", "d","e", "f", "g", "h", "i", "j"]
    alpha  = ["a", "b"]
    filenameAut = INPUTDIR+rootname+"_" + str(autNo) + ".txt"
    return filenameAut
"""
    #print filenameAut
    f = open(filenameAut, 'w')
    start = "0\n\n"
    transitions = ""

    #make a transition on all alphabet from each state first
    for i in range(stateNum):
        for a in alpha:
            dest = random.randint(0, stateNum-1)
            w = random.randint(0, wt-1)
            trans = a + "," + str(i) + "->" + str(dest) + "," + str(w) + "\n"
            transitions += trans

    transNum = int(ceil(stateNum*ratio)) - stateNum*2
    
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
"""

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
            
    elif expType == 3:
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

    elif expType == 4:
        # expType = 4
        # Comparing detLP with QuIP
        # fixedQuant refers to ratio
        # size of first automata is fixed
        fratio = float(fixedQuant)/10
        for i in range(beginState, endState, intervalState):
            fixFile = generateCompleteRandom(fixS, fratio, wt, 1, rootname)
            varFile = generateCompleteRandom(i, fratio, wt, 2, rootname)
            runCommandQIP = " ".join([exeFile, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommandQIP
            os.system(runCommandQIP)
            runCommandDet = " ".join([exeFileDet, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommandDet
            os.system(runCommandDet)



    else:
        # expType = 
        # Comparing detLP with QuIP
        # fixedQuant refers to ratio
        # size of both automata is varying
        fratio = float(fixedQuant)/10
        for i in range(beginState, endState, intervalState):
            fixFile = generateCompleteRandom(i, fratio, wt, 1, rootname)
            varFile = generateCompleteRandom(i, fratio, wt, 2, rootname)
            runCommandQIP = " ".join([exeFile, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommandQIP
            os.system(runCommandQIP)
            runCommandDet = " ".join([exeFileDet, str(df), fixFile, varFile, OUTPUTDIR+rootname])
            print runCommandDet
            os.system(runCommandDet)            
#generateCompleteRandom(5, 3, 4, 1, "test")


def functionRunNew(SP, TP, SQ, ratio, wt, expType,  iterNo):
    rootname = str(SP)+"_" + str(TP)+"_"+str(SQ)+"_"+str(ratio)+"_"+str(wt)+"_"+str(expType)+"_"+str(iterNo)
    #ouputFile = rootname+".txt"                                                                                                                                 


    if expType == 1:
        #Scaling DetLP
        #Compare QiIP
        #ration is given as r*10
                
        fratio = float(ratio)/10
        TQ = int(ceil(SQ*fratio))
        fileP = generateCompleteRandom(SP, fratio, wt, 1, rootname)
        fileQ = generateCompleteRandom(SQ, fratio, wt, 2, rootname)
            #print fixFile, varFile                                                                                                                              
            #return                                                                                                                                              

        
        runCommandQuip = " ".join([exeFile, str(df), fileP, fileQ, OUTPUTDIR+rootname])
        print runCommandQuip
        os.system(runCommandQuip)

        #runCommandDet = " ".join([exeFileDet, str(df), fileP, fileQ, OUTPUTDIR+rootname])
        #print runCommandDet
        #os.system(runCommandDet)
        
        #runCommandQuip = " ".join([exeFile, str(df), fileP, fileQ, OUTPUTDIR+rootname])
        #print runCommandQuip
        #os.system(runCommandQuip)

        
    elif expType == 2:
        #Scaling QuIP on Complete automata, ratio is given as r*10
        fratio = float(ratio)/10
        TQ = int(ceil(SQ*fratio))
        fileP = generateCompleteRandom(SP, fratio, wt, 1, rootname)
        fileQ = generateCompleteRandom(SQ, fratio, wt, 2, rootname)
        runCommand = " ".join([exeFile, str(df), fileP, fileQ, OUTPUTDIR+rootname])
        print runCommand
        os.system(runCommand)

    else:
        expType = 3
        #Scaling QuIP on inComplete automata                                                                                                                                  
        #ration is given as r*10                                                                                                   

        fratio = float(ratio)/10
        TQ = int(ceil(SQ*fratio))
        fileP = generateRandom(SP, fratio, wt, 1, rootname)
        fileQ = generateRandom(SQ, fratio, wt, 2, rootname)
        runCommand = " ".join([exeFile, str(df), fileP, fileQ, OUTPUTDIR+rootname])
        print runCommand
        os.system(runCommand)

line  = [(sys.argv[1]), (sys.argv[2]), (sys.argv[3]), (sys.argv[4]), (sys.argv[5]),(sys.argv[6]), (sys.argv[7])]
inputLine = [int(argString.replace(" ", "")) for argString in line]
SP, TP, SQ, ratio, wt, expType, iterNo = inputLine[0], inputLine[1], inputLine[2],  inputLine[3], inputLine[4], inputLine[5], inputLine[6]
functionRunNew(SP, TP, SQ, ratio, wt, expType,  iterNo)


#line  = [(sys.argv[1]), (sys.argv[2]), (sys.argv[3]), (sys.argv[4]), (sys.argv[5]),(sys.argv[6])]
#inputLine = [int(argString.replace(" ", "")) for argString in line]
#stateFix, transFix, wtInput, ratio, expType, iterNo = inputLine[0], inputLine[1], inputLine[2],  inputLine[3], inputLine[4], inputLine[5]
#functionRun(stateFix, transFix, wtInput, ratio, expType,  iterNo)



