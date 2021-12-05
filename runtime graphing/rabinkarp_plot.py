from matplotlib import pyplot
import time
import tqdm


def search(text, query) -> list:
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


def print_matches(inp, q):
    out = ""
    for i in range(len(inp)):
        for n in range(len(matches)):
            if i == matches[n]:
                out += "["
            if i == matches[n] + len(q):
                out += "]"
        out += inp[i]
    if matches[-1] + len(q) == len(inp):
        out += "]"
    print(out)


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
    createPlot(textsizes, runtimes, "text size", "runtime (secs)", "Graph of runtimes for Rabin-Karp String Search")
