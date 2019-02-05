import sys
f1=sys.argv[1]
f2=sys.argv[2]

data1={}
data2={}

firstline1=""
firstline2=""

for l in file(f1):
  if firstline1=="":
    firstline1=l
    continue
  data=l.split(",")
  data1[data[0].strip()]=[ e.strip() for e in data[1:] ]

for l in file(f2):
  if firstline2=="":
    firstline2=l
    continue
  data=l.split(",")
  data2[data[0].strip()]=[ e.strip() for e in data[1:] ]

datanew={}
datachange={}
for elem in data1:
  datanew[elem]=data1[elem]
  
for elem in data2:
  if elem in datanew:
    datachange[elem]=datanew[elem]
    datanew[elem]=data2[elem]
    print elem,
    for i in xrange(min(len(datachange[elem]),len(datanew[elem]))):
      try:
        e1= float(datachange[elem][i])
        e2= float( datanew[elem][i])
      except:
        e1=  datachange[elem][i]
        e2=  datanew[elem][i]
      if e1 != e2:
        print datachange[elem][i], datanew[elem][i],
      print
    print datachange[elem]
    print datanew[elem]
  datanew[elem]=data2[elem]
 
keys=datanew.keys()
keys.sort()
for e in keys:
  s=",".join([e]+datanew[e])
  print s
