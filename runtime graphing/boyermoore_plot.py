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


def bmsearch(text, query):
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


def time_bm(txt, query, batches=10):
    """Gets the runtime of the algorithm. Runs in batches and gets the average to account for inconsistencies"""
    runtime = 0
    for _ in range(batches):
        starttime = time.time()
        m = bmsearch(txt, query)
        endtime = time.time()
        runtime += (endtime - starttime)
    runtime /= batches
    return runtime


def createPlot(x, y, xlabel="", ylabel="", graph_label=""):
    figure, axes = pyplot.subplots()
    axes.plot(x, y)
    axes.set_ylabel(ylabel)
    axes.set_xlabel(xlabel)
    axes.set_title(graph_label)
    pyplot.show()


if __name__ == '__main__':
    inp = "aaaaaaaaaa"
    q = "aaaaaaaaaa"

    r = 0
    b = 1000
    runtimes, textsizes = [], []
    for i in tqdm.tqdm(range(1000)):
        r = time_bm(inp, q, b)
        #print(r)
        runtimes.append(1000*r)  # convert milliseconds to seconds
        textsizes.append(len(inp))
        inp += "a"

    createPlot(textsizes, runtimes, "text size", "runtime (ms)", "runtimes vs text sizes, query size=10, batches="+str(b))