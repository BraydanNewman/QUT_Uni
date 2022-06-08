from tkinter import *
from urllib.request import urlopen, Request
from re import findall, finditer
from sqlite3 import *

import json


root = Tk()

#STUDENT NAME = NA

#STUDENT NUMBER = NA

root.title("Hiram's Live entertainment")

root.configure(background="White")
#frames!
root.geometry("550x350")
venue = LabelFrame(root,text="Venue")
venue.grid(row=3,column=3)
options = LabelFrame(root, text="Options")
options.grid(row=0, column=3)
chosen_event = LabelFrame(root, text="Chosen Event")
chosen_event.grid(row=3, column=0)

# load image
img = PhotoImage(file='hiram.png')

# add image
img_label = Label(root, image=img).grid(row=0, column=0)


def get_data(location):
    # Add the different urls for the different radio buttons here
    venue_ref = {
        1: "url 1",
        2: "url 2",
        3: "url 3"
    }

    # just for the json test data but might be usefully
    venue_name_ref = {
        1: "The Zoo",
        2: "brisbane SHit",
        3: "idk"
    }

    # TODO: this is just a test thing to grab fake data, need to scrape the data from the website
    # Use 'RegEx' on the stringify website to get the data
    website_data = urlopen(venue_ref[location])

    # This is the where it grabs the fake data
    with open("test_data.json", "r") as f:
        temp = json.load(f)
    return temp[venue_name_ref[location]]


def create_ticket(event_info):
    # This function id=s don't pass in a dictionary with the parameters name,
    # description and so forth, and it will create the ticket
    ticket_template = f"""
<h1>Event Ticket</h1>
<h3>{event_info['name']}</h3>
<h3>{event_info['description']}</h3>
<h3>{event_info['date']}</h3>
<img src="{event_info['image_url']}" >
    """
    with open("ticket.html", 'w+') as f:
        f.write(ticket_template)


def display_event_data(data):
    # This function is not done but make the data parameter displayed in the events list
    events = ""
    for i in range(len(data)):
        events += f"fuck"
    event_text.set(events)


def save_data(event):
    # this function is done and will input the booked event into the
    # database just pass in a dictionary with correct parameters
    conn = connect('bookings.db')
    conn.execute(f"INSERT INTO tickets_bought (event, date_or_dates, venue, website) \
      VALUES ({event['name']}, {event['date']}, {event['venue']}, {event['website']})")
    conn.commit()
    conn.close()


def set_venue():
    # this function is beingused as a basic main function atm but needs to be changes to do what the function name says
    radio_index = ven.get()
    venue_data = get_data(radio_index)
    # Just creating a ticket for the first piece of fake data
    create_ticket(venue_data["Events"][0])



    display_event_data(venue_data["Events"])


# Creating a Option widget
ven = IntVar()
ttt = Radiobutton(venue, variable=ven, command=set_venue, value=1, text="The Tivoli Theatre").pack()
bc = Radiobutton(venue, variable=ven, command=set_venue, value=2, text="Brisbane City").pack()
sc = Radiobutton(venue, variable=ven, command=set_venue, value=3, text="Suncorp Staitum").pack()

# Creating Venue widget

opt = IntVar()
showEvent = Button(options,text ="Show Event").pack()
displayDetails = Button(options,text ="Display details").pack()
printTicket = Button(options,text = "Print Ticket").pack()
saveBooking = Button(options,text ="Save Booking").pack()


# Creating use for radio button event chosen
event_text = StringVar()
chosen_event = Label(chosen_event, text=event_text)
event_text.set("Event name will appear here, Event date will appear here")


chosen_event.grid(row=2, column=2)

root.mainloop()
