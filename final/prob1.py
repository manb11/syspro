import operator

count = {}
countList = []


def Frequency_analytic(s):
    for s in msg:
        if'A' <= s and s <="z":
            if s in count:
                count[s] +=1
            else:
                count[s] = 1

    countList = sorted(
        count.items(), key=operator.itemgetter(1), reverse=True)
    
    for i in range(0, len(countList)):
        print(countList[i][0], '\t', countList[i][1])


if __name__=="__main__":
    msg = input("input your message : ")
    Frequency_analytic(msg)
