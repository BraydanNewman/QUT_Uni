from tkinter import *

root = Tk()

#STUDENT NAME = Seraphina Conroy Kryger

#STUDENT NUMBER = n11077476

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



#load image
img=PhotoImage(file='hiram.png')

#add image 
img_label = Label(root, image=img).grid(row=0, column=0)





#Creating a Option widget
ven= IntVar()
ttt = Radiobutton(venue, variable = ven,value =1, text="The Tivoli Theatre").pack()
bc = Radiobutton(venue,variable = ven,value =2, text="Brisbane City").pack()
sc = Radiobutton(venue,variable = ven,value =3, text ="Suncorp Staitum").pack()

#Creating Venue widget

opt= IntVar()
showEvent = Button(options,text ="Show Event").pack()
displayDetails = Button(options,text ="Display details").pack()
printTicket = Button(options,text = "Print Ticket").pack()
saveBooking = Button(options,text ="Save Booking").pack()





#Creating use for radio button event chosen
chosen_event = Label(chosen_event, text="Event name will appear here, Event date will appear here")


chosen_event.grid(row=2, column=2)

 


root.mainloop()
