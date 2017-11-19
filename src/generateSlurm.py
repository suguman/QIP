SLDIR = "SLURM/"

iterno = 100
fixSize = [(5,5),(5, 10), (5,15)]
wtList = [2,3,4,5]
ratioTS = [10, 15, 20, 25, 30]
stateSize = [100, 200, 300, 400, 500, 600, 700, 800, 1000]

#fixSize = [(5,6)]
#wtList = [1]
#ratioTS = [2]
#ratioS = [1]

#Exp1
expType = 1
for fixS, fixT in fixSize:
    for wt in wtList:
        for r in ratioTS:
            for fixAut in [1]:
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
                    cmd += "#SBATCH --nodes=1\n"
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
            cmd += "#SBATCH --nodes=1\n"
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
            cmd += "#SBATCH --nodes=1\n"
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
            


