def goodProcess(query):
    goodList = []
    border = []
    f = 0;
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


def main():
    text = input()
    query = input()
    if len(text) < len(query):
        print("Query Not Found!")
    else:
        print("Query found at the following indices: ")
        print(search(text, query))
main()