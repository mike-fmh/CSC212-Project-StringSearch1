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
    itvl = 10
    xrange = 500000
    runtimes, textsizes = gettime(text, query, xrange, reps, itvl)
    createPlot(textsizes, runtimes, "text size", "runtime (secs)", "Graph of runtimes for Rabin-Karp String Search")
