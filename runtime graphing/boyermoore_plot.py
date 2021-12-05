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


def gettime(txt, query, xrange, reps=10):
    """Gets the runtime of the algorithm. Runs the for loop an amount of times == 'reps' and gets the averages to account for software inconsistencies"""
    # software inconsistencies = sometimes the cpu will proiritize other tasks which creates random spikes in runtimes
    times = []
    [times.append(0) for i in range(xrange - len(txt))]  # prefill the list with 0s
    sizes = []
    [sizes.append(i) for i in range(xrange - len(txt))]  # prefill with len(txt)-->1000

    for s in tqdm.tqdm(range(reps)):
        looptxt = txt
        for i in (range(xrange - len(txt))):
            if i % 100 == 1:
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
    """Takes a very long time to run - it runs the alorithm a lot in order to get average runtimes for each textsize"""
    text = "a"
    query = "a"

    repetitions = 10
    xrange = 5000000
    runtimes, textsizes = gettime(text, query, xrange, repetitions)
    createPlot(textsizes, runtimes, "text size", "runtime (secs)", "Graph of runtimes for Boyer-Moore String Search")
