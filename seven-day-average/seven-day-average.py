import csv
import requests
from collections import defaultdict


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ").strip().lower().capitalize()
        if state == "":
            break
        if state in new_cases:
            states.append(state)

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    last_15_d_idx = -15
    states = 56
    start_idx = last_15_d_idx * states
    last_14_d_data = list(reader)[start_idx:-1]
    new_cases = defaultdict(list)
    prev_cases = defaultdict(list)

    for row in last_14_d_data:
        state = row["state"]
        cases = int(row["cases"])
        prev_cases[state].append(cases)

        if len(prev_cases[state]) > 1:
            new_cases[state].append(cases - prev_cases[state][-2])

    return new_cases


def comparative_averages(new_cases, states):
    if len(states) < 1:
        print("No correct state name was provided, sorry, bey.")
        return

    print(f"\nSeven-Day Averages")

    for state in states:
        cases = new_cases[state]
        last_week = cases[-7:]
        prev_week = cases[:7]

        last_avg = round(sum(last_week) / 7)
        prev_avg = round(sum(prev_week) / 7)
        change_perc = round((last_avg - prev_avg) / prev_avg * 100)

        print(f"{state} had a 7-day average of {last_avg} and {'an increase' if change_perc > 0 else 'a decrease'} of {change_perc}%.")


main()
