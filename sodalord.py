#!/usr/bin/python

import signal
import sys
import os
import email.Utils
import threading
import Queue
import time
import re
import pg
import crypt
import random
import string
import base64
import md5

import mdb.cashless
import mdb.sniff


if __name__ == '__main__':
	# ignore ^C
	signal.signal(signal.SIGINT, signal.SIG_IGN)


logfile = open('/soda/logs/sodalord.log','a')
mdblogfile = open('/soda/logs/mdb.log','a')
sodalord_email = 'sodalord@mit.edu'
mail_command = '/usr/sbin/sendmail -t -f %s' % (sodalord_email)
soda_buy_window = 60
hardlimit = -1


last_cash_insertion = 0
last_mdb_activity = 0
last_mdb_inactivity = 0



def log(str):
	logfile.write('%s %s\n' % (get_date(), str))
	logfile.flush()


def mdblog(ex):
	return
	mdblogfile.write('%s %s\n' % (get_date(), ex))
	mdblogfile.flush()



def get_tickets():
	os.environ['KRB5CCNAME'] = '/tmp/krb5cc_soda'
	os.environ['KRBTKFILE'] = '/tmp/tkt_soda'
	os.system('/usr/athena/bin/kinit -k -t /etc/krb5.keytab')




def get_date():
	return email.Utils.formatdate(localtime=True)



def hex2dec(hex):
	dec = 0
	digits = {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, 'A':10, 'B':11, 'C':12, 'D':13, 'E':14, 'F':15}
	for i in range(len(hex)):
		dec = dec + digits[hex[i]]*16**(len(hex)-i-1)
	return dec





def process_mdb(ex):
	if ex == None: return None
	elif ex == (): return None

	mdblog(ex)
	if False: pass

	elif ex[0] == 'M: 08*': return mdb_0x08(ex)
	elif ex[0] == 'M: 09*': return mdb_0x09(ex)
	elif ex[0] == 'M: 0A*': return mdb_0x0A(ex)
	elif ex[0] == 'M: 0B*': return mdb_0x0B(ex)
	elif ex[0] == 'M: 0C*': return mdb_0x0C(ex)
	elif ex[0] == 'M: 0D*': return mdb_0x0D(ex)
	elif ex[0] == 'M: 0E*': return mdb_0x0E(ex)
	elif ex[0] == 'M: 0F*': return mdb_0x0F(ex)

	elif ex[0] == 'M: 10*': return mdb_0x10(ex)
	elif ex[0] == 'M: 11*': return mdb_0x11(ex)
	elif ex[0] == 'M: 12*': return mdb_0x12(ex)
	elif ex[0] == 'M: 13*': return mdb_0x13(ex)
	elif ex[0] == 'M: 14*': return mdb_0x14(ex)
	elif ex[0] == 'M: 15*': return mdb_0x15(ex)
	elif ex[0] == 'M: 16*': return mdb_0x16(ex)
	elif ex[0] == 'M: 17*': return mdb_0x17(ex)

	elif ex[0] == 'M: 30*': return mdb_0x30(ex)
	elif ex[0] == 'M: 31*': return mdb_0x31(ex)
	elif ex[0] == 'M: 32*': return mdb_0x32(ex)
	elif ex[0] == 'M: 33*': return mdb_0x33(ex)
	elif ex[0] == 'M: 34*': return mdb_0x34(ex)
	elif ex[0] == 'M: 35*': return mdb_0x35(ex)
	elif ex[0] == 'M: 36*': return mdb_0x36(ex)
	elif ex[0] == 'M: 37*': return mdb_0x37(ex)

	elif ex == 'timeout': return mdb_timeout(ex)

	else: return None



def mdb_0x08(ex): return None
def mdb_0x09(ex): return None
def mdb_0x0A(ex): return None

def mdb_0x0B(ex): # coin mech POLL
	global last_cash_insertion
	if len(ex) == 2:
		# no response
		return None
	elif len(ex) == 3 and ex[2] == 'S: 00*':
		# ACK
		return None
	else:
		skip_bytes = 0
		for i in range(2,len(ex)-2):
			if skip_bytes > 0:
				skip_bytes = skip_bytes - 1
				continue
			code = hex2dec(ex[i][3:5])
			if code >= 128:
				skip_bytes = 1
#				print """\
#coin mech: %d coins of type %d dispensed manually
#there are at least %d coins in that tube now""" % (code%16, (code/16)%8, hex2dec(ex[i+1][3:5]))
			elif code >= 64:
				skip_bytes = 1
				type = code%16
				routing = (code/16)%4
				if routing == 0:
					last_cash_insertion = time.time()
					#print "last_cash_insertion =",last_cash_insertion
					if type == 0:
						db.query("UPDATE current_cash SET cashbox_nickels = cashbox_nickels + 1")
					elif type == 1:
						db.query("UPDATE current_cash SET cashbox_dimes = cashbox_dimes + 1")
					elif type == 2:
						db.query("UPDATE current_cash SET cashbox_quarters = cashbox_quarters + 1")
					elif type == 3:
						db.query("UPDATE current_cash SET cashbox_dollars = cashbox_dollars + 1")
				elif routing == 1:
					last_cash_insertion = time.time()
					#print "last_cash_insertion =",last_cash_insertion
					if type == 0:
						db.query("UPDATE current_cash SET tube_nickels = tube_nickels + 1")
					elif type == 1:
						db.query("UPDATE current_cash SET tube_dimes = tube_dimes + 1")
					elif type == 2:
						db.query("UPDATE current_cash SET tube_quarters = tube_quarters + 1")

#				routing_dict = {0: 'routed to the cash box',
#						1: 'routed to the tubes',
#						3: 'rejected'}
#				print """\
#coin mech: 1 coin of type %d %s
#there are at least %d coins in that tube now""" % (code%16, routing_dict.get(routing, 'went somewhere'), hex2dec(ex[i+1][3:5]))
#			elif code in range(1,13+1):
#				coin_mech_status = {1: 'escrow request',
#						    2: 'changer payout busy',
#						    3: 'no credit',
#						    4: 'defective tube sensor',
#						    5: 'double arrival',
#						    6: 'acceptor jammed',
#						    7: 'tube jam',
#						    8: 'ROM checksum error',
#						    9: 'coin routing error',
#						   10: 'changer busy',
#						   11: 'changer was reset',
#						   12: 'coin jam',
#						   13: 'possible credited coin removal'}
#				print 'coin mech:', coin_mech_status.get(code)

		return None

def mdb_0x0C(ex): return None

def mdb_0x0D(ex): # coin mech DISPENSE
	code = hex2dec(ex[1][3:5])
	if len(ex) != 4:
		return None
	if ex[3] == 'S: 00*':
		num_coins = code/16
		type = code%16
		if type == 0:
			db.query("UPDATE current_cash SET tube_nickels = tube_nickels - %d" % num_coins)
		elif type == 1:
			db.query("UPDATE current_cash SET tube_dimes = tube_dimes - %d" % num_coins)
		elif type == 2:
			db.query("UPDATE current_cash SET tube_quarters = tube_quarters - %d" % num_coins)
#		print "coin mech: dispense %d coins of type %d" % (code/16, code%16)
	return None

def mdb_0x0E(ex): return None
def mdb_0x0F(ex): return None



def mdb_0x10(ex): return None
def mdb_0x11(ex): return None
def mdb_0x12(ex): return None
def mdb_0x13(ex): return None

def mdb_0x14(ex):
	global last_cash_insertion
	global last_mdb_inactivity
	#print "got 0x14 on mdb"
	if len(ex) <= 2:
		return
	elif ex[1] == 'M: 01 ':
		now = time.time()
		#print "now =",now
		#print "now - last_mdb_inactivity =",(now-last_mdb_inactivity)
		#print "now - last_cash_insertion =",(now-last_cash_insertion)
		if last_mdb_inactivity == 0:
			return
		if last_cash_insertion == 0:
			return
		if ((now - last_mdb_inactivity) < 1) and ((now - last_cash_insertion) < 600):
			last_mdb_inactivity = 0
			last_cash_insertion = 0
			#print "soda purchased with cash"
			send_zephyr('cash', 'Someone bought a soda!')
			db.query("""\
UPDATE selection SET current_level_lower_bound = current_level_lower_bound - 1""")

def mdb_0x15(ex): return None
def mdb_0x16(ex): return None
def mdb_0x17(ex): return None



def mdb_0x30(ex): return None
def mdb_0x31(ex): return None
def mdb_0x32(ex): return None

def mdb_0x33(ex): # validator POLL
	global last_cash_insertion
	if len(ex) == 2:
		# no response
		return None
	elif len(ex) == 3 and ex[2] == 'S: 00*':
		# ACK
		return None
	else:
		for i in range(2,len(ex)-2):
			code = hex2dec(ex[i][3:5])
			if code >= 128:
#				positon_dict = {0: 'stacked',
#						1: 'in escrow',
#						2: 'returned',
#						4: 'rejected (disabled)'}
				position = (code/16)%8
				if code == 128:
					last_cash_insertion = time.time()
					#print "last_cash_insertion =",last_cash_insertion
					db.query("UPDATE current_cash SET bill_dollars = bill_dollars + 1")
#				print """\
#validator: bill type %d %s""" % (code%16, position_dict.get(position, "code " + str(positon)))
#			elif code >= 64 and code <= 95:
#				print """\
#validator: %d attempts to insert a bill while unit disabled""" % (code%32)
#			elif code in range(1,12+1):
#				validator_status = {1: 'defective motor',
#						    2: 'sensor problem',
#						    3: 'validator busy',
#						    4: 'ROM checksum error',
#						    5: 'validator jammed',
#						    6: 'validator was reset',
#						    7: 'bill removed',
#						    8: 'cash box out of position',
#						    9: 'unit disabled',
#						   10: 'invalid escrow request',
#						   11: 'bill rejected',
#						   12: 'possible credited bill removal'}
#				print "validator: %s" % validator_status.get(code)
			elif code == 1: pass
			elif code == 2: pass
			elif code == 3: pass
			elif code == 4: pass
			elif code == 5: pass
			elif code == 6: pass
			elif code == 7: pass
			elif code == 8: pass
			elif code == 9: pass
			elif code == 10: pass
			elif code == 11: pass
			elif code == 12: pass
		return None

def mdb_0x34(ex): return None
def mdb_0x35(ex): return None

def mdb_0x36(ex): # validator STACKER
#	code = hex2dec(ex[2][3:5])*256 + hex2dec(ex[3][3:5])
#	if code >= 32768:
#		print "validator: stacker full"
#	print "validator: stacker has %d bills in it" % (code%32768)
	return None

def mdb_0x37(ex): return None



def mdb_timeout(ex):
	global last_mdb_inactivity
	last_mdb_inactivity = time.time()
	#print "last_mdb_inacivity =",last_mdb_inactivity








def add_to_mailing_list(email):
	if re.search('@mit.edu$', email):
		email = email[:-8]
	get_tickets()
	os.system('/usr/athena/bin/blanche sodalord-users -a %s' % email)



def send_zephyr(instance, message):
	get_tickets()
	zephyr = os.popen('/usr/athena/bin/zwrite -s "I am your god." -c sodalord -i %s' % instance,'w')
	zephyr.write(message)
	zephyr.close()





def in_keys(name):
	"""Ask the database for the username associated with an alias"""

#	result = db.query("""\
#SELECT username FROM sodauser WHERE username = '%s'""" % (name))
#
#	if result.ntuples() != 0:
#		return result.getresult()[0][0]

	result = db.query("""\
SELECT username FROM sodauser JOIN alias ON sodauser.id = alias.user_id WHERE alias.aliasname = '%s'""" % (name))

	if result.ntuples() != 0:
		return result.getresult()[0][0]











salt_chars = './' + string.ascii_letters + string.digits

def crypt_password(password):
	password = password.replace('\n','')
	salt = salt_chars[random.randrange(64)] + salt_chars[random.randrange(64)]
	return crypt.crypt(password, salt)

def check_password(crypted_password, password):
	password = password.replace('\n','')
	salt = crypted_password[:2]
	return crypt.crypt(password, salt) == crypted_password





def sanitize(dangerous):
	allowed = string.ascii_letters + string.digits + ' -+_,.$@&'
	safe = ''
	for i in range(len(dangerous)):
		if dangerous[i] in allowed:
			safe = safe + dangerous[i]
		else:
			safe = safe + '-'
	return safe








def cmd_quit(args):
#	print "Command executer quitting"
	logfile.close()
	input_buffer.out_q.put(False)
	sys.exit(0)
cmd_exit = cmd_quit



def cmd_buy(args, skippass=False, method=''):
	global last_cash_insertion

	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: buy username"
	elif in_keys(args[0]):
		alias = args[0]
		username = in_keys(alias)

		result = db.query("""\
SELECT * FROM sodauser WHERE username = '%s'""" % (username))

		# we know we got a result because in_keys(alias) gave us a username
		resultdict = result.dictresult()[0]
		passcrypt = resultdict.get('passwd')
		balance = int(resultdict.get('balance') * 100)

		if not username:
			print "You don't have an account. Make one first"
		else:
			if skippass:
				pass0 = ''
			else:
				os.system('/bin/stty -echo')
				sys.stdout.write('Password: ')
				pass0 = sys.stdin.readline()
				sys.stdout.write('\n')
				os.system('/bin/stty echo')

			if not skippass and not check_password(passcrypt,pass0):
				print "Wrong password!"
			elif balance <= hardlimit:
				print "You have reached the hard credit limit! Please add more credit to your account."
			else:
				print "balance = %.2f" % (balance / 100.0)

				if balance > 0:
					fake_balance = balance
				else:
					fake_balance = 2

				mdb.cashless.trigger(fake_balance)

				print "Make your selection..."

				# wait for $soda_buy_window seconds for them to make their selection
				start_time = time.time()

				while True:
					if time.time() - start_time > soda_buy_window:
						print "vend timed out"
						mdb.cashless.cancel()
						break
					ex = mdb.sniff.get_ex()
					if ex == ('M: 0B*', 'M: 0B ', 'S: 01 ', 'S: 01*', 'M: 00 '):
						print "Coin return requested - vend cancelled"
						mdb.cashless.cancel()
						process_mdb(ex)
						break
					elif ex[0] == 'M: 13*' and ex[1] == 'M: 00 ':
						selection = hex2dec(ex[4][3:5])*256 + hex2dec(ex[5][3:5])
						sodacost = (hex2dec(ex[2][3:5])*256 + hex2dec(ex[3][3:5])) / 100.0
						# TODO decide if this person can have a soda
						if (balance - sodacost < hardlimit):
							print "That would take you over the hard credit limit."
							print "Please put more money on your account."
							mdb.cashless.deny()
							process_mdb(ex)
						else:
							last_cash_insertion = 0

							result = db.query("""\
SELECT flavor.name FROM flavor JOIN product ON flavor.id = product.flavor_id JOIN selection ON product.id = selection.product_id
WHERE selection.selection_num = '%d'""" % (selection))

							if len(result.getresult()) != 0:
								print "%s, a wise selection. Enjoy!" % result.getresult()[0][0]
							else:
								print "Mmm, soda!"
							mdb.cashless.approve()
							process_mdb(ex)
							start_time = time.time()
							while True:
								if time.time() - start_time > 20:
									# is the vending machine turned on??
									# sold out??
									mdb.cashless.cancel()
									break
								ex = mdb.sniff.get_ex()
								if ex[0] == 'M: 13*' and ex[1] == 'M: 02 ':
									selection = hex2dec(ex[2][3:5])*256 + hex2dec(ex[3][3:5])
									result = db.query("""\
SELECT flavor.name, selection.actual_price, selection.product_id, flavor.nickname
FROM flavor
JOIN product ON flavor.id = product.flavor_id
JOIN selection ON product.id = selection.product_id
WHERE selection.selection_num = %d""" % (selection))
									if len(result.getresult()) != 0:
										name = result.getresult()[0][0]
										price = result.getresult()[0][1]
										product_id = result.getresult()[0][2]
										nickname = result.getresult()[0][3]
										db.query("""\
UPDATE sodauser
SET balance = balance - %.2f
WHERE username = '%s'""" % (price, username))
										db.query("""\
UPDATE selection
SET current_level_upper_bound = current_level_upper_bound - 1,
current_level_lower_bound = current_level_lower_bound - 1
WHERE selection_num = %d""" % (selection))
										hour = time.strftime('%H')
										day = time.strftime('%a').lower()
										db.query("""\
UPDATE user_stats
SET h%(hour)s = h%(hour)s + 1, %(day)s = %(day)s + 1
WHERE user_id IN
(SELECT id
FROM sodauser
WHERE username = '%(username)s')""" % ({'hour':hour, 'day':day, 'username':username}))
										db.query("""\
INSERT INTO purchase (purchase_time, user_id, product_id, price)
VALUES ('%s', (SELECT sodauser.id FROM sodauser WHERE sodauser.username = '%s'),
%d, %.2f)""" % (time.strftime('%Y-%m-%d %H:%M:%S'), username, product_id, price))
										log("""\
%s bought a soda - selection %d, $%.2f, probably %s""" % (username, selection, price, name))
										process_mdb(ex)
										send_zephyr(alias, "%s bought a %s%s!" % (alias, nickname, method))
										break
									else:
										print "You can't buy that on credit"
										mdb.cashless.deny()
										break
								elif ex[0] == 'M: 13*' and ex[1] == 'M: 03':
									mdb.cashless.cancel()
									process_mdb(ex)
									break
						break
					else:
						process_mdb(ex)
	else:
		print "buy: %s doesn't have an account" % (args[0])



def cmd_adduser(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: adduser username"
	elif not re.search('^[a-z]*$', args[0]):
		print "Use alphabetic characters only"
	elif cmddict.has_key(args[0]):
		print "That username is reserved. Please choose another."
	elif in_keys(args[0]):
		print "That username is taken. Please choose another."
	else:
		username = args[0]
		pass0 = ''
		pass1 = ''
		email = ''

		sys.stdout.write('\nFull email address: ')
		email = sys.stdin.readline().strip()
		email = sanitize(email)

		if not re.search('@',email):
			email = email + '@mit.edu'

		os.system('/bin/stty -echo')
		sys.stdout.write('Soda password: ')
		pass0 = sys.stdin.readline()
		sys.stdout.write('\nConfirm soda password: ')
		pass1 = sys.stdin.readline()
		sys.stdout.write('\n')
		os.system('/bin/stty echo')

		if pass0 != pass1:
			print "Passwords do not match!"
		else:
			passwd = crypt_password(pass0)

			date_str = time.strftime('%Y-%m-%d')

			db.query("""\
INSERT INTO sodauser
(username, email, create_date, balance, passwd) VALUES
('%s', '%s', '%s', '%.2f', '%s')""" % (username, email, date_str, 0, passwd))

			result = db.query("""\
SELECT id FROM sodauser WHERE username = '%s'""" % (username))

			user_id = result.getresult()[0][0]

			db.query("""\
INSERT INTO alias (user_id, aliasname) VALUES (%s, '%s')""" % (user_id, username))

			db.query("""\
INSERT INTO user_stats
(user_id, h00, h01, h02, h03, h04, h05, h06, h07, h08, h09, h10, h11,
h12, h13, h14, h15, h16, h17, h18, h19, h20, h21, h22, h23,
sun, mon, tue, wed, thu, fri, sat)
VALUES (%s, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0)""" % (user_id))

			log('added user %s with email %s\n' % (username, email))

			add_to_mailing_list(email)

			fromstring = '%s <%s>' % (username, email)
			newmail = os.popen(mail_command,'w')
			newmail.write("""\
From: %(fromstring)s
To: %(sodalord_email)s
Subject: [Sodalord] new user %(fromstring)s

User %(fromstring)s created a new sodalord account.
""" % {'fromstring':fromstring,'sodalord_email':sodalord_email})
			newmail.close()



def cmd_addcard(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: addcard username"
	elif in_keys(args[0]):
		username = in_keys(args[0])

		result = db.query("""\
SELECT * FROM sodauser WHERE username = '%s'""" % (username))

		# we know we got a result because in_keys(alias) gave us a username
		resultdict = result.dictresult()[0]
		passcrypt = resultdict.get('passwd')

		if not username:
			print "You don't have an account. Make one first"
		else:
			os.system('/bin/stty -echo')
			sys.stdout.write('Password: ')
			pass0 = sys.stdin.readline()
			sys.stdout.write('\n')
			os.system('/bin/stty echo')

			if not check_password(passcrypt,pass0):
				print "Wrong password!"
			else:
				os.system('/bin/stty -echo')
				sys.stdout.write('\n\nPlease swipe your card now!\n\n')
				card = sys.stdin.readline().strip()
				sys.stdout.write('\n')
				os.system('/bin/stty echo')

				digest = base64.encodestring(md5.new(card).digest())[0:22]

				result = db.query("""\
SELECT * FROM card WHERE cardhash = '%s'""" % digest)

				if result.ntuples() != 0:
					print "That card is already in the database"
				else:
					db.query("""\
INSERT INTO card (user_id, cardhash)
VALUES ((SELECT id FROM sodauser WHERE username = '%s'),'%s')""" % (username,digest))
					print "Card added - have a nice day!"




def cmd_buycard(args):
	if len(args) != 1:
		return
	elif not re.search('^[0123456789:;<=>?]*$', args[0]):
		return
	else:
		card = args[0]
		digest = base64.encodestring(md5.new(card).digest())[0:22]

		result = db.query("""\
SELECT sodauser.username FROM sodauser
JOIN card ON sodauser.id = card.user_id
WHERE card.cardhash = '%s'""" % digest)
		if result.ntuples() != 1:
			print "Unknown card - add a card with the addcard command"
			return
		else:
			username = result.getresult()[0][0]
			cmd_buy([username], skippass=True, method=' on the card')
			return



def cmd_addalias(args):
	args = [arg.lower() for arg in args]
	if len(args) != 2:
		print "Syntax: addalias alias username"
	elif in_keys(args[0]):
		print "That alias is taken."
	elif cmddict.has_key(args[0]):
		print "That alias is reserved. Please choose another."
	elif not re.search('^[a-z]*$', args[0]):
		print "Use alphabetic characters only"
	elif not in_keys(args[1]):
		print "User %s not found in database" % (args[1])
	else:
		username = in_keys(args[1])

		result = db.query("""\
SELECT * FROM sodauser WHERE username = '%s'""" % (username))

		resultdict = result.dictresult()[0]
		passcrypt = resultdict.get('passwd')

		os.system('/bin/stty -echo')
		sys.stdout.write('Password: ')
		pass0 = sys.stdin.readline()
		sys.stdout.write('\n')
		os.system('/bin/stty echo')

		if not check_password(passcrypt,pass0):
			print "Wrong password!"
		else:
			db.query("""\
INSERT INTO alias (user_id, aliasname)
VALUES ((SELECT id FROM sodauser WHERE username = '%s'), '%s')""" % (username, args[0]))
			log('Added alias %s to %s' % (args[0], username))






def cmd_passwd(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: passwd username"
	else:
		username = in_keys(args[0])

		if not username:
			print "User %s not found in database" % (args[0])
		else:
			os.system('/bin/stty -echo')
			sys.stdout.write('Soda password: ')
			pass0 = sys.stdin.readline()
			sys.stdout.write('\n')
			os.system('/bin/stty echo')

			result = db.query("""\
SELECT passwd FROM sodauser WHERE username = '%s'""" % (username))

			oldcrypt = result.getresult()[0][0]

			if not check_password(oldcrypt,pass0):
				print "Wrong password!"
			else:
				os.system('/bin/stty -echo')
				sys.stdout.write('New soda password: ')
				pass1 = sys.stdin.readline()
				sys.stdout.write('\nConfirm soda password: ')
				pass2 = sys.stdin.readline()
				sys.stdout.write('\n')
				os.system('/bin/stty echo')

				if pass1 != pass2:
					print "Passwords do not match!"
				else:
					newcrypt = crypt_password(pass1)
					db.query("""\
UPDATE sodauser SET passwd = '%s' WHERE username = '%s'""" % (newcrypt, username))
					log("User %s updated his/her password" % (username))





def cmd_listalias(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: listalias username"
	else:
		username = in_keys(args[0])
		if not username:
			print "User %s not found in database" % args[0]
		else:
			result = db.query("""\
SELECT aliasname FROM alias WHERE user_id = (SELECT id FROM sodauser WHERE username = '%s')""" % (username))
			print "Username:", username
			print reduce(lambda a,b: a+'\n'+b, [alias[0] for alias in result.getresult()])



def cmd_list(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: list username"
	else:
		username = in_keys(args[0])
		if not username:
			print "User %s not found in database" % args[0]
		else:
			result = db.query("""\
SELECT balance FROM sodauser WHERE username = '%s'""" % (username))
			print "User %s has a balance of $%.2f" % (username, result.getresult()[0][0])



#def cmd_debit(args):
#	# TODO?
#	pass



def cmd_credit(args):
	args = [arg.lower() for arg in args]
	if len(args) != 1:
		print "Syntax: credit username"
	else:
		username = in_keys(args[0])
		if not username:
			print "No such user!"
		else:
			os.system('/bin/stty -echo')
			sys.stdout.write('Soda password: ')
			pass0 = sys.stdin.readline()
			sys.stdout.write('\n')
			os.system('/bin/stty echo')

			result = db.query("""\
SELECT passwd FROM sodauser WHERE username = '%s'""" % (username))

			oldcrypt = result.getresult()[0][0]

			if not check_password(oldcrypt,pass0):
				print "Wrong password!"
			else:
				reason = ''
				credit = 0
				sys.stdout.write('Credit how much? (dollars) ')
				line = sys.stdin.readline().strip()

				if not (re.search('^\d+\.?\d*$',line) or re.search('^\.\d+$',line) or re.search('^\-\d+\.?\d*$',line) or re.search('^\-\.\d+$',line)):
					print "Use a numeric value only."
				else:
					credit = eval(line)
					if credit < 0:
						print "The amount credited must be greater than $0.00"
					else:
						line = ''
						while line.strip() == '':
							sys.stdout.write('Reason for credit (location of money):\n')
							line = sys.stdin.readline().strip()
							line = sanitize(line)
						reason = line

						result = db.query("""\
SELECT email, balance FROM sodauser WHERE username = '%s'""" % (username))
						email = result.getresult()[0][0]
						balance = result.getresult()[0][1]
						credit = int(credit*100)/100.0
						credit_str = '$%.2f' % credit
						fromstring = '%s <%s>' % (username, email)

						get_tickets()

						newmail = os.popen(mail_command,'w')
						newmail.write("""\
From: %(fromstring)s
To: %(sodalord_email)s
Subject: [Sodalord] Credit of %(credit_str)s

*** Note: This is an automated e-mail ***

User %(username)s with email address %(email)s credited
%(credit_str)s dollars to his/her account.
%(username)s said %(reason)s was a good enough reason.
""" % {'fromstring':fromstring,'sodalord_email':sodalord_email,'credit_str':credit_str,'username':username,'email':email,'reason':reason})
						newmail.close()

						print "Credited %s dollars to %s." % (credit_str, username)
						log('Credited %s dollars to %s.' % (credit_str, username))
						db.query("""\
INSERT INTO deposit (user_id, deposit_time, amount, user_comment, admin_comment, recipient_userid)
VALUES ((SELECT id FROM sodauser WHERE username = '%s'),
'%s', %.2f, '%s', NULL, NULL)""" % (username, time.strftime('%Y-%m-%d %H:%M:%S'), credit, reason))
						db.query("""\
UPDATE sodauser SET balance = balance + %.2f WHERE username = '%s'""" % (credit, username))
						print "New balance is: $%.2f" % (balance + credit)



def cmd_help(args):
	print """\
I know the following:

adduser		buy		addalias	list
listalias	passwd		credit		addcard

"""







def cmd_which(args): print "It's mine. That's all you need to know"

def cmd_whoami(args): print "I am SODALORD!"

def cmd_man(args): print "No man page available."

def cmd_ls(args): print "elite\thaxxors\t0wned\tthis\tb0x"

def cmd_rm(args): print "I'm sorry, Dave, I just can't do that..."

def cmd_more(args): print "You can't have more unless you pay for it!"

def cmd_cat(args): print "The cats are Ratchet and The Fluffernutter."

def cmd_head(args): print "The head is down the hall on the East side."

def cmd_sh(args): print "Sh! Be vewy vewy quiet..."





cmddict = {}

for obj in dir():
	if re.search('^cmd_.*$',obj):
		cmddict[obj[4:]] = eval(obj)





class TextInputBuffer(threading.Thread):
	in_q = Queue.Queue(1)
	out_q = Queue.Queue(1)
	def __init__(self):
		threading.Thread.__init__(self)
	def run(self):
		alphanumspace = re.compile('^[a-zA-Z0-9 ]*$')
		cardchars = re.compile('^[0123456789:;<=>?]+$')

		while True:
			# we need sys.stdout.write() here instead of print because
			# the latter doesn't play very well with sys.stdin.readline()
			sys.stdout.write('sodalord% ')

			# we have to use sys.stdin.readline() instead of raw_input()
			# because the latter catches SIGINT itself and quits
			line = sys.stdin.readline()


			if re.search(cardchars,line):
				sys.stdout.write('[Asodalord% (censored)                                                          \n')
				line = 'buycard ' + line
			elif not re.search(alphanumspace, line):
				print "Use alphanumerics only."
				continue

			self.in_q.put(line)

#			print "Added %s to the queue" % line.strip()

			while True:
				try:
					keep_going = self.out_q.get()
				except Queue.Empty:
					continue
				if keep_going:
					break
				else:
#					print "Text input buffer quitting"
					sys.exit(0)



if __name__ == '__main__':
	input_buffer = TextInputBuffer()
	input_buffer.start()
	#print "Input buffer started"

	db = pg.connect('soda',user='soda')

	while True:

		ex = mdb.sniff.get_ex()

		process_mdb(ex)


		line = ''
		try:
			line = input_buffer.in_q.get_nowait()
		except Queue.Empty:
			continue

		splitline = line.strip().split(' ')
		cmd = splitline[0]
		args = splitline[1:]


		if cmd == '':
			pass
		elif cmddict.has_key(cmd):
			cmddict[cmd](args)
		elif args == [] and in_keys(cmd):
			cmd_buy([cmd])
		else:
			print '%s: Command not found.' % cmd

		input_buffer.out_q.put(True)

