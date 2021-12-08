import tqdm
import time
from matplotlib import pyplot
from guppy import hpy

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


def search(text, query, mainmem):
    i = 0
    temp = 0
    badList, heurmem = badProcess(query, mainmem)
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

    #print(hpy().heap())
    mem = (hpy().heap().size / 1000000) - mainmem + heurmem
    return indices, mem


def getmem(txt, query, xrange, reps, intvl, mainmem):
    mems = []
    sizes = []

    for i in tqdm.tqdm(range(xrange - len(txt))):
        if i % intvl == 0:
            matches, mem = search(txt, query, mainmem)
            mems.append(mem)
            sizes.append(len(txt))
            txt += "a"

    return mems, sizes


def createPlot(x, y, xlabel="", ylabel="", graph_label=""):
    figure, axes = pyplot.subplots()
    axes.plot(x, y)
    axes.set_ylabel(ylabel)
    axes.set_xlabel(xlabel)
    axes.set_title(graph_label)
    pyplot.show()


if __name__ == '__main__':
    text = "a"
    query = "a"

    reps = 1
    itvl = 1
    xrange = 5000
    mem = hpy().heap().size / 1000000
    runtimes, textsizes = getmem(text, query, xrange, reps, itvl, mem)
    createPlot(textsizes, runtimes, "Text Size", "Memory Usage (MB)", "Memory Usage of Boyer-Moore (Bad Char) Algorithm")
