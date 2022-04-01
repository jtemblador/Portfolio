import tkinter as tk
import requests
import time

BASE_URL = "https://api.openweathermap.org/data/2.5/weather?q=" #Base URL to retrieve weather data
API      = "&appid=5dfb8c30721fe23e31098b60a2e483f7"			#API id

def getWeather(canvas):
	city      = textfield.get()
	api       = BASE_URL + city + API
	json_data = requests.get(api).json()        #Requests and stores json_data
	condition = json_data['weather'][0]['main'] #Tells us condition of weather
	temp      = int((json_data['main']['temp'] - 273.15) * 1.8 + 32)     #Converting Kelvin to F
	min_temp  = int((json_data['main']['temp_min'] - 273.15) * 1.8 + 32) #Converting Kelvin to F
	max_temp  = int((json_data['main']['temp_max'] - 273.15) * 1.8 + 32) #Converting Kelvin to F
	pressure  = json_data['main']['pressure'] #retreiving pressure data
	humidity  = json_data['main']['humidity'] #retreiving humidity data
	wind      = json_data['wind']['speed']    #retreiving wind data
	sunrise   = time.strftime("%I:%M:%S", time.gmtime(json_data['sys']['sunrise'] - 21600)) #converting to HRS/MIN/Sec
	sunset    = time.strftime("%I:%M:%S", time.gmtime(json_data['sys']['sunset'] - 21600))  #converting to HRS/MIN/Sec

	#Fomatting data for ouput
	final_info = condition + "\n" + str(temp) + "°F" 
	final_data = "\n" + "Max Temp: " + str(max_temp) + "\n" + "Min Temp: " + str(min_temp) + "\n" + "Pressure: " + str(pressure) + "\n" + "Humidity: " + str(humidity) + "\n" + "Wind speed: " + str(wind) + "\n" + "Sunrise: " + str(sunrise) + "\n" + "Sunset: " + str(sunset) + "\n"
	label1.config(text = final_info)
	label2.config(text = final_data)


canvas = tk.Tk()
canvas.geometry("600x500")	#dimensions of window
canvas.title("Weather App")	#Title

f = ("poppins", 15, "bold") #setting text size
t = ("poppins", 25, "bold") #setting text size

textfield = tk.Entry(canvas, font = t)
textfield.pack(pady = 20)
textfield.focus()
textfield.bind('<Return>', getWeather) #Fetches data whenever return key is pressed

label1 = tk.Label(canvas, font = t)
label1.pack()
label2 = tk.Label(canvas, font = f)
label2.pack()

canvas.mainloop()


