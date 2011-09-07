#!/usr/bin/env python


import watchio

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
			
		
	
	
class Person:

	# times array for this person
	times = []
	
	# details, PersonDetail object
	details = PersonDetail()
	
	
	
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
	
	
class Tournament:
	# providing a handling class for tournaments and the persons involved
	
	# the persons array
	persons = []
	
	# the ruleset to be applied, a function that takes two persons 
	# and outputs -1, 0 or 1 respectively
	rankfun = default_rankfun
	
	def __init__(self):
		pass
	
	def ranksort(self):
	# apply sorting by ruleset saved in rankfun
		return [item + 1 for item in range(len(self.persons))] #tbd
		
	def sortby(self,mode):
	# sort the persons by a specific detail
		pass #tbd
		
		
	def __str__(self):
		ranks = self.ranksort()
		sl = ["%d\t%s\n" % (ranks[n], self.persons[n].details.name) for n in range(len(self.persons))]
		sl.insert(0,"Rank\tName\n")
		
		return "".join(sl)
		
	
	
	
	
