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
    return indices


def gettime(txt, query, xrange, reps, intvl):
    times = []
    [times.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in tqdm.tqdm(range(reps)):
        looptxt = txt
        for i in (range(xrange - len(txt))):
            if i % intvl == 1:
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
    # HOW IT WORKS
    #
    # with textsize starting at n=1, this script runs the search algo on a textsize of n up until (n==xrange) on intervals of (itvl).
    # then, it repeats the above (reps) times to compute the average runtimes
    # finally it plots a graph with the data
    #
    # it takes a long time to run because I chose a very large xrange to minimize software inconsistencies
    # taking the average is supposed to do that but I thought a large xrange might help also
    # (software inconsistencies = sometimes the runtimes are 'off' due to random fluxuations in how the computer prioritizes python)

    text = "a"
    query = "a"

    reps = 10
    itvl = 100
    xrange = 5000000
    runtimes, textsizes = gettime(text, query, xrange, reps, itvl)
    createPlot(textsizes, runtimes, "text size", "runtime (secs)", "Graph of runtimes for Boyer-Moore String Search")
