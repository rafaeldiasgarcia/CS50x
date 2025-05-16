import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    database_path = sys.argv[1]
    sequence_path = sys.argv[2]

    database = []
    try:
        with open(database_path, 'r') as csvfile:
            reader = csv.DictReader(csvfile)
            strs_to_check = reader.fieldnames[1:]  # Get STR names (skip 'name')
            for row in reader:
                database.append(row)
    except FileNotFoundError:
        print(f"Error: Could not open database file {database_path}")
        sys.exit(1)

    sequence = ""
    try:
        with open(sequence_path, 'r') as txtfile:
            sequence = txtfile.read()
    except FileNotFoundError:
        print(f"Error: Could not open sequence file {sequence_path}")
        sys.exit(1)

    sequence_str_counts = {}
    for str_name in strs_to_check:
        sequence_str_counts[str_name] = longest_match(sequence, str_name)

    match_found = False
    matched_name = ""
    for person_data in database:
        is_current_person_match = True
        for str_name in strs_to_check:
            if int(person_data[str_name]) != sequence_str_counts[str_name]:
                is_current_person_match = False
                break
        if is_current_person_match:
            match_found = True
            matched_name = person_data['name']
            break

    if match_found:
        print(matched_name)
    else:
        print("No match")

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

        # Check for a subsequence match starting at `i`
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

        # Update longest run found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
