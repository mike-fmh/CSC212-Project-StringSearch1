from matplotlib import pyplot
import time
import tqdm


def rabinkarp(text, query) -> list:
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


def time_rk(txt, query, batches=10):
    """Gets the runtime of the algorithm. Runs in batches and gets the average to account for inconsistencies"""
    runtime = 0
    for _ in range(batches):
        starttime = time.time()
        m = rabinkarp(txt, query)
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
    for i in tqdm.tqdm(range(10000)):
        r = time_rk(inp, q, b)
        #print(r)
        runtimes.append(1000*r)  # convert milliseconds to seconds
        textsizes.append(len(inp))
        inp += "a"

    createPlot(textsizes, runtimes, "text size", "runtime (ms)", "runtimes vs text sizes, query size=10, batches="+str(b))
