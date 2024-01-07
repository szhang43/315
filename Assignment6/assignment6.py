import sys

def is_english_word(word, dictionary):
    return word in dictionary

def split_words(string, dictionary):
    n = len(string)
    dp = [False] * (n + 1)
    dp[n] = True
    split_points = [0] * (n + 1)

    for i in range(n - 1, -1, -1):
        for j in range(i + 1, n + 1):
            if is_english_word(string[i:j], dictionary) and dp[j]:
                dp[i] = True
                split_points[i] = j
                break

    if not dp[0]:
        return None

    result = []
    i = 0
    while i < n:
        j = split_points[i]
        result.append(string[i:j])
        i = j

    return result

# Read the dictionary file and store the words in a set
with open("diction10k.txt", "r") as f:
    dictionary = set(f.read().split())

# Read the input phrases from standard input
lines = sys.stdin.readlines()
C = int(lines[0])
phrases = [line.strip() for line in lines[1:]]

# Process each phrase
for i, phrase in enumerate(phrases):
    print("phrase", i + 1)
    print(phrase)
    print()

    words = split_words(phrase, dictionary)
    if words is not None:
        print("output", i + 1)
        print("YES, can split.")
        print(" ".join(words))
        print()
    else:
        print("output", i + 1)
        print("NO, cannot split.")
