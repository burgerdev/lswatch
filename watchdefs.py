#!/usr/bin/env python


import watchio
import threading




class CurrentRoundInterface:
	_currentround = None
	
	def setcurrentround(self,n):
	# set current round to n
	# remember: n is a positive integer, i.e. greater than zero
	
		if not CurrentRoundInterface.checknumber(n, "%s.setcurrentround" % type(self)):
			return
				
		if isinstance(self,Person) and len(self._times)<=n:
			self._times += [dict() for i in range(n-len(self._times))]
			
		self._currentround = n-1
		return
	
	def getcurrentround(self):
		if self._currentround is None:
			return None
		else:
			return self._currentround +1
			
			
	def checknumber(n,s='<CurrentRoundInterface>.checknumber'):
		if not isinstance(n,int):
			try: # TODO this is bogus! replace by better call
				n=int(n)
			except ValueError:
				watchio.error("Argument to %s must be convertible to an integer." % s)
				return False
				
		
		
		if n<1:
			watchio.error("Argument to %s must be a positive integer." % s)
			return False
			
		return True
	
	
class Lockable:
	datalock = threading.RLock()
	
	def lock(self):
		watchio.debug("attempting to lock %s" % type(self))
		self.datalock.acquire()
		watchio.debug("%s locked" % type(self))
		
	def unlock(self):
		watchio.debug("attempting to unlock %s" % type(self))
		self.datalock.release()
		watchio.debug("%s unlocked" % type(self))
		
		
		
		

class PersonDetail:
	
	# name of the person (one string, use "surname, name" for sorting purposes)
	name = "<name>"
	
	# address, also one string
	address = "<address>"
	
	# phone number
	phone = "<phone>"
	
	# ....
	
	def __init__(self):
		pass
		
	def __str__(self):
		return "Name:\t%s\nAddr.:\t%s\nPhone:\t%s" % (self.name, self.address, self.phone)
		
	def update(self, name=None, address=None, phone=None):
		if name:
			self.name = name
		if name:
			self.address = address
		if name:
			self.phone = phone
			
		
	
	
class Person(CurrentRoundInterface,Lockable):

	# times array for this person
	# this is a list of dictionaries
	# - the list items correspond to rounds
	# - the dict entries are of the form {<device_number>: <time>}
	
	
	
	# details, PersonDetail object
	
	def __init__(self, name=None, address=None, phone=None):
		self._times = []
		self.details = PersonDetail()
		self.details.update(name,address,phone)
		self.setcurrentround(1)
	
	
			
	def updatetimes(self,data):
	# set the times of the current round to the ones provided by data
	# data is a list of 2-tuples: (<number of device>, <time>)
		
		if self._currentround is None:
			self.setcurrentround(1)
		
		for n,t in data:
			self._times[self._currentround][n] = t
			
		return
	
	def __str__(self):
		s = "%s: %s" % (self.details.name,repr(self._times[self._currentround]))
		return s
	
	
	
class League:
	pass #tbd
	
def default_rankfun(person1, person2):
	# sorts the persons by their best (i.e. shortest) time
	
	better = 1
	equal = 0
	worse = -1
	
	if len(person1.times)==0:
		if len(person2.times)==0:
			return equal
		else:
			return worse
	else:
		m1=min(person1.times)
		if len(person2.times)==0:
			return better
		else:
			m2=min(person2.times)
			
	
	if m1<m2:
		return better
	if m1>m2:
		return worse
	if m1 is m2:
		return equal
	
	# this should not be reached
	watchio.warning("This should not be reached (default comparison function). Returning 0.")
	return equal
	
	
class Tournament(CurrentRoundInterface, Lockable):
	# providing a handling class for tournaments and the persons involved
	# TODO replace all calls to _times[number-1] by a method
	
	# the persons array
	persons = []
	
	# the index of the current person
	_currentperson = None
	

	
	
	# the ruleset to be applied, a function that takes two persons 
	# and outputs -1, 0 or 1 respectively
	rankfun = default_rankfun
	
	def __init__(self):
		self.setcurrentround(1)
		#self.setcurrentperson(1)
		
	def setcurrentperson(self,n):
		if not CurrentRoundInterface.checknumber(n,"%s.setcurrentperson" % type(self)):
			return
		
		#while len(self.persons)<=n:
		#	self.persons.append(Person())
		
		if len(self.persons)<=n:
			self.persons += [Person() for i in range(n-len(self.persons))]
			
		self._currentperson = n-1
		return
	
	def getcurrentperson(self):
		if self._currentperson is None:
			return None
		else:
			return self._currentperson +1
		


	def setcurrentround(self,n, sub=True):
	# sets the current round in this object and in all available person objects if sub is True
		super().setcurrentround(n)
		
		if sub:
			for person in self.persons:
				person.setcurrentround(n)
		
		return
		
	def lock(self,sub=False):
	# if sub is set to true you promise not to add stuff to the Tournament!
		super().lock()
		
		if sub:
			for person in self.persons:
				person.lock()
				
	def unlock(self,sub=False):
	# if sub is set to true you promise that you locked ALL persons in the Tournament before!
		super().unlock()
		
		if sub:
			for person in self.persons:
				person.unlock()
		
	
	def ranksort(self):
	# apply sorting by ruleset saved in rankfun
		return [item + 1 for item in range(len(self.persons))] #tbd
		
	def sortby(self,mode):
	# sort the persons by a specific detail
		pass #tbd
		
		
	def __str__(self):
		#ranks = self.ranksort()
		sl = ["%s\t%s\n" % (person.details.name, repr(person._times[person.getcurrentround()-1])) for person in self.persons]
		sl.insert(0,"Name\t Times\n")
		
		return "".join(sl)
		
	

	
	
	
