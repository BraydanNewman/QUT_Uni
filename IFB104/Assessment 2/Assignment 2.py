import tkinter as tk

# STUDENT NAME = Seraphina Conroy Kryger
# STUDENT NUMBER = n11077476


class MainApplication(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent

        self.parent.title("Hiram's Live entertainment")

        self.parent.configure(background="White")
        # # frames!
        self.parent.geometry("550x350")

        self.parent.columnconfigure(0, weight=1)
        self.parent.columnconfigure(1, weight=3)

        self.venue = tk.LabelFrame(self.parent, text="Venue")
        self.venue.grid(row=3, column=3)
        self.options = tk.LabelFrame(self.parent, text="Options")
        self.options.grid(row=0, column=1)
        self.chosen_event = tk.LabelFrame(self.parent, text="Chosen Event")
        self.chosen_event.grid(row=3, column=0)

        # load image
        self.img = tk.PhotoImage(file='hiram.png')

        # add image
        img_label = tk.Label(self.parent, image=self.img)
        img_label.grid(row=0, column=0)
        #
        # # Creating a Option widget
        ven = tk.IntVar()
        tk.Radiobutton(self.venue, variable=ven, value=1, text="The Tivoli Theatre").pack()
        tk.Radiobutton(self.venue, variable=ven, value=2, text="Brisbane City").pack()
        tk.Radiobutton(self.venue, variable=ven, value=3, text="Suncorp Staitum").pack()
        #
        # # Creating Venue widget
        #
        opt = tk.IntVar()
        tk.Button(self.options, text="Show Event").pack()
        tk.Button(self.options, text="Display details").pack()
        tk.Button(self.options, text="Print Ticket").pack()
        tk.Button(self.options, text="Save Booking").pack()
        #
        # Creating use for radio button event chosen
        chosen_event = tk.Label(self.chosen_event, text="Event name will appear here, Event date will appear here")

        chosen_event.grid(row=2, column=2)


if __name__ == "__main__":
    root = tk.Tk()
    MainApplication(root)
    root.mainloop()
