f = open("input/input.txt", 'r')
data = f.readlines()
liste = []

testlist = ["a:", "b:", "c:"]
for i in testlist:
    sline = i.strip(":")
    testlist.append(sline)

print(testlist)

inc = 0

s = data[inc]
s.split("-")
s.split()