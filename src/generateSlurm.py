SLDIR = "SLURM/"

numIter = 50
SPSize = [10]
wtList = [4]
SQmin = 25
SQmax = 1501
intervalSize = 25
ratioList = [25]
expType = 1
for SP in SPSize:
    for SQ in range(SQmin, SQmax, intervalSize):
        for wt in wtList:
            for r in ratioList:
                for i in range(numIter):
                    paramLine = " ".join([str(elem) for elem in [SP, SP, SQ, r, wt, expType, i]])
                    outputFile = paramLine.replace(" ", "_")+".sl"
                    
                    cmd = "#!/bin/bash\n"
                    cmd += "#SBATCH --job-name=C"+outputFile[:-3]+"\n"
                    cmd += "#SBATCH --account=commons\n"
                    cmd += "#SBATCH --partition=commons\n"
                    cmd += "#SBATCH --mem-per-cpu=8G\n"
                    cmd += "#SBATCH --mail-user=\n"
                    cmd += "#SBATCH --mail-type=ALL\n"
                    cmd += "#SBATCH --time=00:20:00\n"
                    cmd += "#SBATCH --ntasks=1\n"
                    cmd += "#SBATCH --nodes=1 --exclusive\n"
                    cmd += "#SBATCH --ntasks-per-node=1\n"
                    cmd += "#SBATCH --cpus-per-task=1\n"
                    cmd += "cd ..\n"
                    cmd += "python main.py " + paramLine +"\n"
                    cmd += "echo \"I Ran on:\"\n"
                    cmd += "cat $SLURM_JOB_NODELIST\n"
                    cmd += "cd $SLURM_SUBMIT_DIR\n"
                    slFile = open(SLDIR+outputFile, "w")
                    slFile.write(cmd)
                    slFile.close()
                    

# Ends here
"""
#Exp1
expType = 1
for fixS, fixT in fixSize:
    for wt in wtList:
        for r in ratioTS:
            for fixAut in [1]:
                for i in range(6, 10):
                    #python main fixS fixT wt r expType fixAutNo i
                    paramLine = str(fixS)+" "+str(fixT)+" "+str(wt)+" "+str(r)+" "+str(expType)+" "+str(i)
                    outputFile = paramLine.replace(" ", "_")+".sl"
                    
                    cmd = "#!/bin/bash\n"
                    cmd += "#SBATCH --job-name="+outputFile[:-3]+"\n"
                    cmd += "#SBATCH --account=commons\n"
                    cmd += "#SBATCH --partition=commons\n"
                    cmd += "#SBATCH --mem-per-cpu=4G\n"
                    cmd += "#SBATCH --mail-user=\n"
                    cmd += "#SBATCH --mail-type=ALL\n"
                    cmd += "#SBATCH --time=07:00:00\n"
                    cmd += "#SBATCH --ntasks=1\n"
                    cmd += "#SBATCH --nodes=1 --exclusive\n"
                    cmd += "#SBATCH --ntasks-per-node=1\n"
                    cmd += "#SBATCH --cpus-per-task=1\n"
                    cmd += "cd ..\n"
                    cmd += "python main.py " + paramLine +"\n"
                    cmd += "echo \"I Ran on:\"\n"
                    cmd += "cat $SLURM_JOB_NODELIST\n"
                    cmd += "cd $SLURM_SUBMIT_DIR\n"
                    slFile = open(SLDIR+outputFile, "w")
                    slFile.write(cmd)
                    slFile.close()


#Exp2
expType = 2
fixS = 5
fixT = 10
for wt in wtList:
    for r in stateSize:
        fixAut = 1
        for i in range(iterno):
            #python main fixS fixT wt r expType fixAutNo i
            paramLine = str(fixS)+" "+str(fixT)+" "+str(wt)+" "+str(r)+" "+str(expType)+" "+str(i)
            outputFile = paramLine.replace(" ", "_")+".sl"
            cmd = "#!/bin/bash\n"
            cmd += "#SBATCH --job-name=quantIP"+outputFile[:-3]+"\n"
            cmd += "#SBATCH --account=commons\n"
            cmd += "#SBATCH --partition=commons\n"
            cmd += "#SBATCH --mem-per-cpu=4G\n"
            cmd += "#SBATCH --mail-user=\n"
            cmd += "#SBATCH --mail-type=ALL\n"
            cmd += "#SBATCH --time=07:00:00\n"
            cmd += "#SBATCH --ntasks=1\n"
            cmd += "#SBATCH --nodes=1  --exclusive\n"
            cmd += "#SBATCH --ntasks-per-node=1\n"
            cmd += "#SBATCH --cpus-per-task=1\n"
            cmd += "cd ..\n"
            cmd += "python main.py " + paramLine +"\n"
            cmd += "echo \"I Ran on:\"\n"
            cmd += "cat $SLURM_JOB_NODELIST\n"
            cmd += "cd $SLURM_SUBMIT_DIR\n"
            slFile = open(SLDIR+outputFile, "w")
            slFile.write(cmd)
            slFile.close()
                   

#Exp3
expType=3
fixS, fixT = 5, 10
fixAut = 1
for wt in wtList:
    for r in ratioTS:
        for i in range(iterno):
            paramLine = str(fixS)+" "+str(fixT)+" "+str(wt)+" "+str(r)+" "+str(expType)+" "+str(i)
            outputFile = paramLine.replace(" ", "_")+".sl"
            cmd = "#!/bin/bash\n"
            cmd += "#SBATCH --job-name=quantIP"+outputFile[:-3]+"\n"
            cmd += "#SBATCH --account=commons\n"
            cmd += "#SBATCH --partition=commons\n"
            cmd += "#SBATCH --mem-per-cpu=4G\n"
            cmd += "#SBATCH --mail-user=\n"
            cmd += "#SBATCH --mail-type=ALL\n"
            cmd += "#SBATCH --time=07:00:00\n"
            cmd += "#SBATCH --ntasks=1\n"
            cmd += "#SBATCH --nodes=1 --exclusive\n"
            cmd += "#SBATCH --ntasks-per-node=1\n"
            cmd += "#SBATCH --cpus-per-task=1\n"
            cmd += "cd ..\n"
            cmd += "python main.py " + paramLine +"\n"
            cmd += "echo \"I Ran on:\"\n"
            cmd += "cat $SLURM_JOB_NODELIST\n"
            cmd += "cd $SLURM_SUBMIT_DIR\n"
            slFile = open(SLDIR+outputFile, "w")
            slFile.write(cmd)
            slFile.close()


wtList = [4,5]
#Exp4
expType=4
#fixS, fixT = 5, 10
fixAut = 1
for fixS, fixT in [(10, 20)]:
    for wt in wtList:
        for r in ratioComplete:
            for i in range(iterno):
                paramLine = str(fixS)+" "+str(fixT)+" "+str(wt)+" "+str(r)+" "+str(expType)+" "+str(i)
                outputFile = paramLine.replace(" ", "_")+".sl"
                cmd = "#!/bin/bash\n"
                cmd += "#SBATCH --job-name=quantIP"+outputFile[:-3]+"\n"
                cmd += "#SBATCH --account=commons\n"
                cmd += "#SBATCH --partition=commons\n"
                cmd += "#SBATCH --mem-per-cpu=4G\n"
                cmd += "#SBATCH --mail-user=\n"
                cmd += "#SBATCH --mail-type=ALL\n"
                cmd += "#SBATCH --time=07:00:00\n"
                cmd += "#SBATCH --ntasks=1\n"
                cmd += "#SBATCH --nodes=1  --exclusive\n"
                cmd += "#SBATCH --ntasks-per-node=1\n"
                cmd += "#SBATCH --cpus-per-task=1\n"
                cmd += "cd ..\n"
                cmd += "python main.py " + paramLine +"\n"
                cmd += "echo \"I Ran on:\"\n"
                cmd += "cat $SLURM_JOB_NODELIST\n"
                cmd += "cd $SLURM_SUBMIT_DIR\n"
                slFile = open(SLDIR+outputFile, "w")
                slFile.write(cmd)
                slFile.close()
            


"""
