"""
$Id$
"""

import gtk
import gtk.glade
import os
import socket
import binascii, re
""" Definition """
UDP_IP="169.254.1.1"
UDP_PORT=9761
""" Definition des commandes"""
STOP     		= '\x00'
FORWARD  		= '\x01'
BACKWARD 		= '\x02'
SPEED_UP_ON 	= '\x01'
SPEED_UP_OFF	= '\x00'
SPEED_DOWN_ON 	= '\x01'
SPEED_DOWN_OFF	= '\x00'
DIR_UP_ON 		= '\x01'
DIR_UP_OFF    	= '\x00'
DIR_DOWN_ON 	= '\x01'
DIR_DOWN_OFF    = '\x00'

commande={}
commande['FB']=STOP
commande['SPEED_UP']=SPEED_UP_OFF
commande['SPEED_DOWN']=SPEED_DOWN_OFF
commande['DIR_UP']=DIR_UP_OFF
commande['DIR_DOWN']=DIR_DOWN_OFF



def bytestohex(byteStr):
	return ''.join(["%02X "%ord(x) for x in byteStr]).strip()

class mywindowGUI:
	def __init__(self, *args):
		self.create_instances()
		xml = gtk.glade.XML( "Interface.glade")
		self.topMyWindow = xml.get_widget("window1")
		self.btnFor = xml.get_widget("button_forward")
		self.btnBack = xml.get_widget("button_backward")
		self.btnLeft = xml.get_widget("button_left")
		self.btnRight = xml.get_widget("button_right")
		self.btnStop = xml.get_widget("button_stop")
		self.btnUp = xml.get_widget("button_up")
		self.btnDown = xml.get_widget("button_down")
		self.text    = xml.get_widget("UDP_text")

		self.btnFor.connect("clicked", self.on_button_forward_clicked)
		self.btnBack.connect("clicked", self.on_button_backward_clicked)
		self.btnLeft.connect("clicked", self.on_button_left_clicked)
		self.btnRight.connect("clicked", self.on_button_right_clicked)
		self.btnStop.connect("clicked", self.on_button_stop_clicked)
		self.btnUp.connect("clicked", self.on_button_up_clicked)
		self.btnDown.connect("clicked", self.on_button_down_clicked)		

		self.btnFor.connect("released", self.on_button_release)
		self.btnBack.connect("released", self.on_button_release)
		self.btnLeft.connect("released", self.on_button_release)
		self.btnRight.connect("released", self.on_button_release)
		self.btnStop.connect("released", self.on_button_release)
		self.btnUp.connect("released", self.on_button_release)
		self.btnDown.connect("released", self.on_button_release)
		pass
		      
	def create_instances(self, *args):
		pass
		
	def on_button_backward_clicked(self,*args):
		global commande
		commande['FB']=BACKWARD
		pass
		
	def on_button_forward_clicked(self,*args):
		global commande
		commande['FB']=FORWARD
		pass
		
	def on_button_left_clicked(self,*args):
		global commande
		commande['DIR_UP']=DIR_UP_ON
		commande['DIR_DOWN']=DIR_DOWN_OFF
		pass
		
	def on_button_right_clicked(self,*args):
		global commande
		commande['DIR_UP']=DIR_UP_OFF
		commande['DIR_DOWN']=DIR_DOWN_ON
		pass
		
		
	def on_button_stop_clicked(self,*args):
		global commande
		commande['FB'] = STOP
		commande['SPEED_UP']=SPEED_UP_OFF
		commande['SPEED_DOWN']=SPEED_DOWN_OFF
		commande['DIR_UP']=DIR_UP_OFF
		commande['DIR_DOWN']=DIR_DOWN_OFF
		pass
		

	def on_button_down_clicked(self,*args):
		global commande
		commande['SPEED_UP']=SPEED_UP_OFF
		commande['SPEED_DOWN']=SPEED_DOWN_ON
		pass
		
	def on_button_up_clicked(self,*args):
		global commande
		commande['SPEED_UP']=SPEED_UP_ON
		commande['SPEED_DOWN']=SPEED_DOWN_OFF
		pass

	def show_window(self, *args):
		self.initialise()
		self.topMyWindow.show_all()
		self.bln_hide = False
		pass	
		
	def initialise(self, *args):
		pass
	def on_button_release(self,*args):
		MESSAGE=commande['FB']+commande['SPEED_UP']+commande['SPEED_DOWN']+commande['DIR_UP']+commande['DIR_DOWN']
		print "UDP target IP : ", UDP_IP
		print "UDP target PORT : ", UDP_PORT
		print "UDP target Message : ", bytestohex(MESSAGE)
		sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		sock.sendto(MESSAGE,(UDP_IP,UDP_PORT))
		

		
if __name__ == '__main__':
    m = mywindowGUI()
    gtk.main()
