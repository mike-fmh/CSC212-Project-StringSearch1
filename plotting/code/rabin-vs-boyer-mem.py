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


def BM(text, query, mainmem):
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
    mem = (hpy().heap().size / 1000000) - mainmem + heurmem
    return indices, mem


def RK(text, query, mainmem):
    h, prime, alphabet = 1, 101, 256
    for i in range(len(query) - 1):
        h = (h * alphabet) % prime
    matches = []
    phash, whash = 0, 0
    for i in range(len(query)):
        phash = (alphabet * phash + ord(query[i])) % prime
        whash = (alphabet * whash + ord(text[i])) % prime

    for i in range(len(text) - len(query) + 1):
        if phash == whash:
            j = 0
            for j in range(len(query)):
                if text[j + i] != query[j]:
                    break
            if j + 1 == len(query):
                matches.append(i)

        if i < len(text) - len(query):
            whash = (alphabet * (whash - ord(text[i]) * h) + ord(text[i + len(query)])) % prime
            if whash < 0:
                whash += prime
    mem = (hpy().heap().size / 1000000) - mainmem
    return matches, mem


def getmem(txt, query, xrange, reps, intvl, mainmem):
    RKmems = []
    [RKmems.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    BMmems = []
    [BMmems.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in (range(reps)):
        looptxt = txt
        for i in tqdm.tqdm(range(xrange - len(txt))):
            if i % intvl == 0:
                matches, mem = RK(looptxt, query, mainmem)
                RKmems[i] += mem

                matches, mem = BM(looptxt, query, mainmem)
                BMmems[i] += mem

            looptxt += "a"

    RKlast = RKmems[0]
    BMlast = BMmems[0]
    for i in range(xrange - len(txt)):
        RKmems[i] /= reps  # compute the average runtimes
        BMmems[i] /= reps

        if RKmems[i] != 0:  # remove any 0s (only needed when intv > 1)
            RKlast = RKmems[i]
        else:
            RKmems[i] = RKlast

        if BMmems[i] != 0:
            BMlast = BMmems[i]
        else:
            BMmems[i] = BMlast

    return RKmems, BMmems, sizes


def createPlot(x, rky, bmy, xlabel="", ylabel="", graph_label=""):
    figure, axes = pyplot.subplots()
    axes.plot(x, rky, label="Rabin-Karp")
    axes.plot(x, bmy, label="Boyer-Moore (Bad Char)")
    axes.set_ylabel(ylabel)
    axes.set_xlabel(xlabel)
    axes.set_title(graph_label)
    pyplot.legend()
    pyplot.show()


if __name__ == '__main__':
    text = "a"
    query = "a"
    mem = hpy().heap().size / 1000000
    reps = 1
    itvl = 20
    xrange = 5000
    rktimes, bmtimes, textsizes = getmem(text, query, xrange, reps, itvl, mem)
    createPlot(textsizes, rktimes, bmtimes, "Text Size", "Memory Usage (MB)", "Memory measured on intervals of {} text sizes".format(itvl))
