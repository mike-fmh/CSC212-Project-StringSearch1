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


def time_rk(txt, query, return_matches=0):
    stime = time.time()
    m = rabinkarp(txt, query)
    etime = time.time()

    runtime = etime - stime
    if return_matches:
        return runtime, m
    else:
        return runtime


if __name__ == '__main__':
    inp = "a"
    q = "a"

    r = 0
    runtimes, textsizes = [], []
    for i in tqdm.tqdm(range(10000)):
        r, matches = time_rk(inp, q, 1)
        #print(r)
        runtimes.append(r)
        textsizes.append(len(inp))
        inp += "a"

    pl = pyplot.plot(textsizes, runtimes)
    pyplot.show()
