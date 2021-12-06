import tqdm
from matplotlib import pyplot
import time

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

def search(text, query):
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



def gettime(txt, query, xrange, reps, intvl):
    times = []
    [times.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in tqdm.tqdm(range(reps)):
        looptxt = txt
        for i in (range(xrange - len(txt))):
            if i % intvl == 0:
                starttime = time.time()
                m = search(looptxt, query)
                endtime = time.time()
                times[i] += endtime - starttime
                looptxt += "a"

    for i in range(xrange-len(txt)):
        times[i] /= reps  # compute the average runtimes
    return times, sizes


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

    reps = 10
    itvl = 10
    xrange = 50000

    runtimes, textsizes = gettime(text, query, xrange, reps, itvl)
    createPlot(textsizes, runtimes, "Text Size", "Runtime (secs)", "Graph of runtimes for Boyer-Moore (Good Suffix) String Search")
