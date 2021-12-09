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
    n = 0;
    for j in query:
        v = ord(j)
        badList[v] = n
        n = n + 1
    return badList


def BM(text, query):
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


def RK(text, query) -> list:
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
    return matches


def gettime(txt, query, xrange, reps, intvl):
    RKtimes = []
    [RKtimes.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    BMtimes = []
    [BMtimes.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in tqdm.tqdm(range(reps)):
        looptxt = txt
        for i in (range(xrange - len(txt))):
            if i % intvl == 0:
                starttime = time.time()
                m = BM(looptxt, query)
                endtime = time.time()
                BMtimes[i] += (endtime - starttime) * 1000

                starttime = time.time()
                m = RK(looptxt, query)
                endtime = time.time()
                RKtimes[i] += (endtime - starttime) * 1000

            looptxt += "a"

    RKlast = RKtimes[0]
    BMlast = BMtimes[0]
    for i in range(xrange - len(txt)):
        RKtimes[i] /= reps
        BMtimes[i] /= reps  # compute the average runtimes

        if BMtimes[i] != 0:
            BMlast = BMtimes[i]
        else:
            BMtimes[i] = BMlast

        if RKtimes[i] != 0:
            RKlast = RKtimes[i]
        else:
            RKtimes[i] = RKlast

    return RKtimes, BMtimes, sizes


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

    reps = 1000
    itvl = 20
    xrange = 5000
    rktimes, bmtimes, textsizes = gettime(text, query, xrange, reps, itvl)
    createPlot(textsizes, rktimes, bmtimes, "Text Size", "Runtime (ms)", "intervals of {}, average of {} samples".format(itvl, reps))
