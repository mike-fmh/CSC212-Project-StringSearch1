import tqdm
import time
from guppy import hpy
from matplotlib import pyplot


def badProcess(query, mainmem):
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
    mem = (hpy().heap().size / 1000000) - mainmem
    return badList, mem


def goodProcess(query, mainmem):
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
    mem = (hpy().heap().size / 1000000) - mainmem
    return goodList, mem


def shifter(goodList, badList, j, ch, mainmem):
    bad = j - badList[ord(ch)]
    good = goodList[j + 1]
    mem = (hpy().heap().size / 1000000) - mainmem
    if(good > bad):
        return good, mem
    else:
        return bad, mem


def BMbad(text, query, mainmem):
    i = 0
    temp = 0
    badList, bmem = badProcess(query, mainmem)
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
    mem = (hpy().heap().size / 1000000) - mainmem + bmem
    return indices, mem


def BMgood(text, query, mainmem):
    i = 0
    temp = 0
    goodList, gmem = goodProcess(query, mainmem)
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
    mem = (hpy().heap().size / 1000000) - mainmem + gmem
    return indices, mem


def BMdual(text, query, mainmem):
    i = 0
    temp = 0
    smem = 0
    goodList, gmem = goodProcess(query, mainmem)
    badList, bmem = badProcess(query, mainmem)
    indices = []
    complete = True
    j = len(query) - 1
    while i <= len(text) - len(query):
        complete = True
        j = len(query) - 1
        while j >= 0:
            if text[i + j] != query[j]:
                temp, smem = shifter(goodList, badList, j, text[i + j], mainmem)
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
    mem = ((hpy().heap().size / 1000000) - mainmem) + smem + bmem + gmem
    return indices, mem


def gettime(txt, query, xrange, reps, intvl, mainmem):
    badTimes = []
    goodTimes = []
    dualTimes = []
    sizes = []

    for i in tqdm.tqdm(range(xrange - len(txt))):
        if i % intvl == 0:
            matches, bmem = BMbad(txt, query, mainmem)
            badTimes.append(bmem)
            matches, gmem = BMgood(txt, query, mainmem)
            goodTimes.append(gmem)
            matches, dmem = BMdual(txt, query, mainmem)
            dualTimes.append(dmem)
            sizes.append(len(txt))

        txt += "a"

    mem = (hpy().heap().size / 1000000) - mainmem + dmem + bmem + gmem
    return badTimes, goodTimes, dualTimes, sizes, mem


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
    reps = 1
    itvl = 10
    xrange = 500
    mainmem = hpy().heap().size / 1000000
    bTimes, gTimes, dTimes, textsizes, mem = gettime(text, query, xrange, reps, itvl, mainmem)
    createPlot(textsizes, bTimes, gTimes, dTimes, "Text Size", "Memory (MB)", "Memory measured on intervals of {} text sizes".format(itvl))
