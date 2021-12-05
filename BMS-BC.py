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


def main():
    text = input()
    query = input()
    if len(text) < len(query):
        print("Query Not Found!")
    else:
        print("Query found at the following indices: ")
        print(search(text, query))
main()
