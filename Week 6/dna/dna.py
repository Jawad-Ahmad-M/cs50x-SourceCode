import csv
import sys


def main():

    # First of all we have to check that are there any additional or less no of
    # command-line arguments provided by the user, the len(sys.argv) gives the number
    # of arguments which come after python command in terminal one if filename,
    # second one is database.csv and thirs one is sequesnce which we have to check.
    if (len(sys.argv) != 3):
        print("Error. Usage: python dna.py dabases.csv sequence.txt")
        # It returns the main function with the specific message like we have added 1 in it.
        sys.exit(1)

    # We have to open our database.csv file into a variable database , we read it using
    # reader from csv library and then we convert it into list and make a variable table by it.
    with open(sys.argv[1], "r") as database:
        reader = csv.reader(database)
        table = list(reader)

    # Convert the table into a dictionary
    # Format: {'name': [STR1_count, STR2_count, ...]}
    # Skip the first row (header), and convert all STR counts to integers
    dic = {}
    for i in range(1, len(table)):
        name = table[i][0]  # Name of Person
        # The list of STR counts : [Str1_count , Str2_count, ...]
        value = list(map(int, table[i][1::]))
        dic[name] = value  # Adding the pair in dictionary

        # The above three lines can we reduced to this single line also,
        # I did above for just decreasing the complexity
        # dic[f"{table[i][0]}"] = list(map(int, table[i][1::]))

    # We will open our dna sequence file as dna file and then read
    # all of the file into sequence variable
    with open(sys.argv[2], "r") as dna:
        sequence = dna.read().strip()

    # Again opening the database file and then add only the first row and
    # then add the values in format like [name, STR1, STR2, STR3, ...]
    with open(sys.argv[1], "r") as file:
        a = file.readline().strip()
        firstRow = a.split(",")

    strList = []
    for x in range(1, len(firstRow)):
        # Adds the longest match integer in new list named strList which
        strList.append(longest_match(sequence, firstRow[x]))
        # will then be used to compare with values in dic so as a result
        # the name of that person can be accessed as a result.

    # Make the result as No match as initial point
    result = "No match"
    for key, value in dic.items():
        if value == strList:
            result = key  # If any list matches then make result equal to key of
            # dic which is the name of person which have that STR sequence.

    print(result)  # Prints the result
    return


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

# ---------------------Runnable Code--------------------- #


main()  # Runs the main function defined above
