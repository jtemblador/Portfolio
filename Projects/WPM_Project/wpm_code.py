import curses 
import time
import random
from curses import wrapper

def start_screen(stdscr):
	stdscr.clear()
	stdscr.addstr("This is a Speed Typing Test!")
	stdscr.addstr("\nPress any key to begin!")
	stdscr.refresh()
	stdscr.getkey()

def display_text(stdscr, target, current, wpm=0):
	stdscr.addstr(target)
	stdscr.addstr(1, 0, f"WPM: {wpm}")

	for i, char in enumerate(current):
		correct_char = target[i]	#comparing current char to correct char
		color = curses.color_pair(1)#assigns green to the correct char
		if char !=correct_char:		#if not correct assigns color red
			color = curses.color_pair(2)
		if char == " ":
			char = '_'
		stdscr.addstr(0, i, char, color)

def load_text():
	with open('text.txt', 'r') as f:
		lines = f.readlines()
		return random.choice(lines).strip()	#randomizes lines and strips /n at end of file


def wpm_test(stdscr):
	target_text = load_text()
	current_text = []	#keeps track off all keys pressed
	wpm = 0
	start_time = time.time()
	stdscr.nodelay(True)

	while True:
		#if a value is less than 1, than 1 is returned instead)
		time_elapsed = max(time.time() - start_time, 1)
		
		#time_elapsed / 60 converts seconds to minutes
		#current_text / (time_elapsed / 60) returns words per minute
		wpm = round((len(current_text) / (time_elapsed / 60)) / 5)

		stdscr.clear()
		display_text(stdscr, target_text, current_text, wpm)
		stdscr.refresh()

		if "".join(current_text) == target_text:
			stdscr.nodelay(False)
			break

		
		try:
			key = stdscr.getkey()
		except:
			continue

		if ord(key) == 27:
			break

		if key in ("KEY_BACKSPACE", '\b', '\x7f'):
			if len(current_text) > 0:
				current_text.pop()	#pops off the last letter in current_text
		elif len(current_text) < len(target_text): 
			current_text.append(key)


def main(stdscr):
	curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_WHITE, curses.COLOR_BLACK)

	start_screen(stdscr)
	while(True):
		wpm_test(stdscr)
		stdscr.addstr(2, 0, "You completed the test! Press any key to continue or ESC to quit...")
		key = stdscr.getkey()

		if ord(key) == 27:
			break


wrapper (main)
