fileData = open("data.txt", "w")
with open("priors.txt", "r") as data:
    for line in data.readlines():
        line = line.strip()[1:-2]
        for tmp in line.split(", "):
            fileData.write(tmp + "\n")
        

fileData.close()