from csv import reader, DictReader

from sys import argv

name = []
STR = []
STRlist = []

data = {}
counts = {}

if len(argv) != 3:
    print("Usage: python dna.py file.csv file.txt")
    exit(1)

# count the number of rows
f = open(argv[1], "r")
temp1 = reader(f)
N = len(list(temp1))
f.close()

# count the number of columns
f = open(argv[1], "r")
temp2 = reader(f)
M = len(next(temp2))
f.close()

# load the STRs
f = open(argv[1], "r")
temp3 = reader(f)
i = 0
for row in next(temp3):
    if row != "name":
        STRlist.append(row)
        i += 1
f.close()


# load csv datas into list
f = open(argv[1], "r")

reader = reader(f)

STR = [[] for x in range(N)]

i = 0
for row in reader:
    if row[0] != "name":
        name.append(row[0])
        STRnested = STR[i]
        i += 1
        for j in range(M):
            if j > 0:
                STRnested.append(int(row[j]))

f.close()

# load the csv data into dictionary
for j in range(len(name)):
    data[name[j]] = STR[j]


# check
f = open(argv[2], "r")

DNA = f.readline().rstrip("\n")
for i in (range(len(DNA))):
    for x in range(len(STRlist)):
        j = i + (len(STRlist[x]))
        if DNA[i:j] == STRlist[x]:
            if DNA[i:j] in counts:
                oldcounts = counts[DNA[i:j]]
            else:
                oldcounts = 0
            counts[DNA[i:j]] = 1
            k = i + (len(STRlist[x]))
            l = j + (len(STRlist[x]))
            while k < len(DNA):
                if DNA[k:l] == DNA[i:j]:
                    counts[DNA[i:j]] += 1
                    k += (len(STRlist[x]))
                    l += (len(STRlist[x]))
                else:
                    k = len(DNA)
            if oldcounts > counts[DNA[i:j]]:
                counts[DNA[i:j]] = oldcounts
        elif STRlist[x] not in counts:
            counts[STRlist[x]] = 0

f.close()


# calculate
counts_total = [0 for x in range(len(STRlist))]

for x in range(len(STRlist)):
    counts_total[x] = counts[STRlist[x]]

# compare
for i in range(len(name)):
    if counts_total == data[name[i]]:
        print(name[i])
        exit(0)

print("No match")