from requests import get         	#module to make requests 
from pprint import PrettyPrinter	#print module to print json data

BASE_URL = "http://data.nba.net"	#URL where data is requested from
ALL_JSON = "/prod/v1/today.json"	#json data extension
printer = PrettyPrinter()


def get_links():
	data = get(BASE_URL + ALL_JSON).json()  #retrieves json data
	links = data['links']					#retrieves 'links' list from json data
	return links

def get_scoreboard():
	scoreboard = get_links()['currentScoreboard'] 		#retrieves scoreboard json data
	games = get(BASE_URL + scoreboard).json()['games']  #retrieves games json data
	
	#Organizing data into their own elements
	for game in games:
		home  = game['hTeam']								
		away  = game['vTeam']
		start = game['startTimeEastern']
		clock = game['clock'] if game['clock'] else "00:00"

		#If game is live, stores time left on clock
		home_score = home['score'] if home['score'] else 0 
		away_score = away['score'] if away['score'] else 0

		#Stores what period current game is in
		period = game['period']['current']

		#Displays Data
		print(f"{home['triCode']} vs {away['triCode']}")
		print(f"{home_score} - {away_score}")
		print(f"Starts at: {start} | Period: {period} | Clock: {clock}")
		print("-------------------------------------------------")
	print() #prints new line


def get_stats():
	#Retrieving json data
	stats = get_links()['leagueTeamStatsLeaders']

	#Retrieving data for each team
	teams = get(BASE_URL + stats).json()['league']['standard']['regularSeason']['teams']

	teams = list(filter(lambda x: x['name'] != "Team", teams))	#filters out empty data
	teams.sort(key = lambda x: int(x['ppg']['rank']))			#sorts teams based by rank

	#Displays data 
	for i, team in enumerate(teams):
		name = team['name']
		nickname = team['nickname']
		ppg = team['ppg']['avg']
		print(f"{i+1}. {name} - {nickname} - {ppg}")


print("List of most recent NBA games including scores:")
get_scoreboard()
print("List of NBA Teams ordered by average points per game:")
get_stats()


