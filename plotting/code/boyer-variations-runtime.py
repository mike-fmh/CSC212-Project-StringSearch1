import tqdm
import time
from matplotlib import pyplot


def badProcess(query):
    badList = []
    i = 0
    while(i < 256):
        badList.append(-1)
        i = i + 1
    j = 0
    n = 0
    for j in query:
        v = ord(j)
        badList[v] = n
        n = n + 1
    return badList


def goodProcess(query):
    goodList = []
    border = []
    f = 0
    while f <= len(query):
        goodList.append(0)
        border.append(0)
        f += 1
    i = len(query)
    j = len(query) + 1
    border[i] = j
    while i > 0:
        while j <= len(query) and query[j - 1] != query[i - 1]:
            if goodList[j] == 0:
                goodList[j] = j - i
            j = border[j]
        i -= 1
        j -= 1
        border[i] = j
    b = border[0]
    a = 0
    while a <= len(query):
        if goodList[a] == 0:
            goodList[a] = b
        if a == b:
            b = border[b]
        a += 1
    return goodList


def shifter(goodList, badList, j, ch):
    bad = j - badList[ord(ch)]
    good = goodList[j + 1]
    if(good > bad):
        return good
    else:
        return bad


def BMbad(text, query):
    i = 0
    temp = 0
    badList = badProcess(query)
    indices = []
    complete = True
    j = len(query) - 1
    while i <= len(text) - len(query):
        complete = True
        j = len(query) - 1
        while j >= 0:
            if text[i + j] != query[j]:
                temp = j - badList[ord(query[j])]
                if temp > 0:
                    i += temp
                else:
                    i += 1
                complete = False
                break
            j -= 1
        if complete:
            indices.append(i)
            i += 1
    return indices


def BMgood(text, query):
    i = 0
    temp = 0
    goodList = goodProcess(query)
    indices = []
    complete = True
    j = len(query) - 1
    while i <= len(text) - len(query):
        complete = True
        j = len(query) - 1
        while j >= 0:
            if text[i + j] != query[j]:
                temp = goodList[j + 1]
                if temp > 0:
                    i += temp
                else:
                    i += 1
                complete = False
                break
            j -= 1
        if complete:
            indices.append(i)
            i += 1
    return indices


def BMdual(text, query):
    i = 0
    temp = 0
    goodList = goodProcess(query)
    badList = badProcess(query)
    indices = []
    complete = True
    j = len(query) - 1
    while i <= len(text) - len(query):
        complete = True
        j = len(query) - 1
        while j >= 0:
            if text[i + j] != query[j]:
                temp = shifter(goodList, badList, j, text[i + j])
                if temp > 0:
                    i += temp
                else:
                    i += 1
                complete = False
                break
            j -= 1
        if complete:
            indices.append(i)
            i += 1
    return indices


def gettime(txt, query, xrange, reps, intvl):
    badTimes = []
    [badTimes.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    goodTimes = []
    [goodTimes.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    dualTimes = []
    [dualTimes.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in tqdm.tqdm(range(reps)):
        looptxt = txt
        for i in (range(xrange - len(txt))):
            if i % intvl == 0:
                starttime = time.time()
                m = BMbad(looptxt, query)
                endtime = time.time()
                badTimes[i] += (endtime - starttime) * 1000

                starttime = time.time()
                m = BMgood(looptxt, query)
                endtime = time.time()
                goodTimes[i] += (endtime - starttime) * 1000

                starttime = time.time()
                m = BMdual(looptxt, query)
                endtime = time.time()
                dualTimes[i] += (endtime - starttime) * 1000
                for _ in range(itvl):
                    looptxt += "a"

    blast = badTimes[0]
    glast = goodTimes[0]
    dlast = dualTimes[0]
    for i in range(xrange-len(txt)):
        badTimes[i] /= reps  # compute the average runtimes
        goodTimes[i] /= reps
        dualTimes[i] /= reps

        if badTimes[i] != 0:  # set 0s to last available datapoint (only needed if interval > 1)
            blast = badTimes[i]
        else:
            badTimes[i] = blast
        if goodTimes[i] != 0:
            glast = goodTimes[i]
        else:
            goodTimes[i] = glast
        if dualTimes[i] != 0:
            dlast = dualTimes[i]
        else:
            dualTimes[i] = dlast

    return badTimes, goodTimes, dualTimes, sizes


def createPlot(x, gx, bx, dx, xlabel="", ylabel="", graph_label=""):
    figure, axes = pyplot.subplots()
    axes.plot(x, gx, label="Good Suffix")
    axes.plot(x, bx, label="Bad Char")
    axes.plot(x, dx, label="Dual")
    axes.set_ylabel(ylabel)
    axes.set_xlabel(xlabel)
    axes.set_title(graph_label)
    pyplot.legend()
    pyplot.show()


if __name__ == '__main__':
    """Compares Boyer-Moore Good Suffix vs Bad vs Dual"""
    text = "a"
    query = "a"

    reps = 1000
    itvl = 20
    xrange = 5000
    bTimes, gTimes, dTimes, textsizes = gettime(text, query, xrange, reps, itvl)
    createPlot(textsizes, bTimes, gTimes, dTimes, "Text Size", "Runtime (ms)", "intervals of {}, average of {} samples".format(itvl, reps))
