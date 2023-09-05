import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()

    db = []
    with open(sys.argv[1], "r") as f:
        r = csv.reader(f)
        for row in r:
            db.append(row)

    dna = ""
    with open(sys.argv[2], "r") as f:
        r = csv.reader(f)
        for row in r:
            dna = row[0]

    runs = []
    for subsequence in db[0][1:]:
        runs.append(longest_match(dna, subsequence))

    for row in db[1:]:
        seqs = row[1:]
        match = 0
        for i, run in enumerate(runs):
            if run == int(seqs[i]):
                match += 1
        if match == len(runs):
            print(row[0])
            sys.exit()

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
