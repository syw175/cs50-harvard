# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []

    # Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        # Open the file as a dictionary
        filereader = csv.DictReader(file)

        # Iterate through the file
        for row in filereader: 
            # Append team and rating as a dictionary to the list teams
            teams.append({"team": row["team"], "rating": int(row["rating"])})
    
    # Intitialize a dictionary to track the number of wins for each team
    counts = {}


    # Simulate N tournaments and keep track of win counts
    for tournament in range(N):
        # Simulate a tournament and get the winning team
        winningTeam = simulate_tournament(teams)

        # If the winning team is in the dictionary, increment the count
        try: 
            counts[winningTeam] += 1
        
        # Otherwise, add the team to the dictionary and set the count to 1
        except KeyError: 
            counts[winningTeam] = 1


    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) > 1: 
        teams = simulate_round(teams)

    # Return the winning team
    return teams[0]["team"]


if __name__ == "__main__":
    main()
