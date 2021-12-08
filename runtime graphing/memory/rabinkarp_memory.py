from matplotlib import pyplot
import time
import tqdm
from guppy import hpy


def search(text, query):
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

  #  print(hpy().heap())
    mem = hpy().heap().size/1000000  # gives memory, divide by 1000000 to convert bytes to MB
    return matches, mem


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


def getmem(txt, query, xrange, reps, intvl):
    mems = []
    sizes = []

    for i in tqdm.tqdm(range(xrange - len(txt))):
        if i % intvl == 0:
            matches, mem = search(txt, query)
            mems.append(mem)
            sizes.append(len(txt))
            txt += "a"

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

    mems, textsizes = getmem(text, query, xrange, reps, itvl)
    createPlot(textsizes, mems, "Text Size", "Memory Usage (MB)", "Memory Usage of Rabin-Karp Algorithm")
