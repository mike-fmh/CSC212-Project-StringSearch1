import tqdm
import time
from matplotlib import pyplot
from guppy import hpy

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


def search(text, query):
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
    mem = hpy().heap().size / 1000000
    return indices, mem


def getmem(txt, query, xrange, reps, intvl):
    mems = []
    [mems.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in (range(reps)):
        looptxt = txt
        for i in tqdm.tqdm(range(xrange - len(txt))):
            if i % intvl == 0:
                matches, mem = search(looptxt, query)
                mems[i] += mem
                looptxt += "a"

    for i in range(xrange - len(txt)):
        mems[i] /= reps  # compute the average runtimes

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
    xrange = 50000

    runtimes, textsizes = getmem(text, query, xrange, reps, itvl)
    createPlot(textsizes, runtimes, "Text Size", "Memory Usage (MB)", "Memory Usage of Boyer-Moore (Bad Char) Algorithm")
