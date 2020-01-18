#!/usr/bin/python

#import popen2
import threading
import sys
import re
import os
import Queue
import shlex
import admin


TZC = '/afs/sipb.mit.edu/project/outland/arch/i386_rhel4/bin/tzc'
TZCEXTRAS = '-o -s'
LISTEN_CLASS = 'sodalord-admin'
LISTEN_INSTANCE = ''
ZSIG = 'I am your humble servant.'
ZSUBS = '/soda/.zephyr.subs.tzc'


#sexp_rexp = re.compile('\(([\w\-]*) \. ("(?:\\.|[^\\\"])*"|[\w\-]*|\((?:"(?:\\.|[^\\\"])*"\s*)*\)|\([0-9 ]*\))\)')

sexp_rexp = re.compile('\(([\w\-]*) \. ("(?:\\.|[^\\\"])*"|[\w\-]*|\((?:"(?:\\.|[^\\\"]|(?:\\\"))*"\s*)*\)|\([0-9 ]*\))\)')

msg_rexp = re.compile('"((?:\\.|[^\\\"])*)"\s*"((?:\\.|[^\\\"])*)"')


def get_tickets():
        os.environ['KRB5CCNAME'] = '/tmp/krb5cc_sodabot'
        os.environ['KRBTKFILE'] = '/tmp/tkt_sodabot'
        os.system('/usr/athena/bin/kinit -k -t /etc/krb5.keytab')
	os.system('/usr/athena/bin/zctl load %s' % ZSUBS)
#	print "got tickets"
#	os.system('/usr/athena/bin/klist')


def send_zephyr(message, zrecipient='', zclass='message', zinstance='personal'):
	if zrecipient=='' and zclass=='message' and zinstance=='personal':
		# no destination specified!
		return
	get_tickets()
	if zrecipient == '':
		zephyr = os.popen('/usr/athena/bin/zwrite -s "%s" -c %s -i %s' % (ZSIG, zclass, zinstance),'w')
	else:
		zephyr = os.popen('/usr/athena/bin/zwrite -s "%s" %s' % (ZSIG,zrecipient),'w')
	zephyr.write(message)
	zephyr.close()


class WorkerThread(threading.Thread):
	in_pipe = None
	q = Queue.Queue(10)
	def __init__(self, pipe):
		self.in_pipe = pipe
		super(WorkerThread,self).__init__()
	def run(self):
		while True:
			sexp = ''
			while sexp[-2:-1] != '\x00':
				line = self.in_pipe.readline()
#				print line,
				if line == '':
#					print "reached EOF"
					break
				elif sexp == '' and line[0:1] == ';':
					pass
#					print "skipping comment"
				elif sexp == '' and line.strip() == '':
					pass
#					print "skiping empty line"
				else:
#					print "adding line to sexp"
					sexp += line
			if sexp == '':
				break
			self.q.put(self.parse_sexp(sexp))

	def parse_sexp(self,sexp):
		sexp = sexp.strip()
		sexp = sexp.replace('\x00','').replace('\x01','')
#		print 'sexp:',sexp
		sexp_dict = {}
		for match in re.findall(sexp_rexp,sexp[1:-1]):
#			print match
			sexp_dict[match[0]] = match[1]
#		print sexp_dict
		return sexp_dict


tzcin=None
#tzcout=None
worker=None


def __init__():
#	print "running __init__"
	global tzcin
#	global tzcout
	global worker

	get_tickets()

#	tzcin,tzcout=popen2.popen2(TZC+' '+TZCEXTRAS)
	tzcin=os.popen(TZC+' '+TZCEXTRAS)
	worker = WorkerThread(tzcin)
	worker.start()


if __name__ == '__main__':
#	tzcin,tzcout=popen2.popen2(TZC+' '+TZCEXTRAS)
#	tzcin=os.popen(TZC+' '+TZCEXTRAS)
#	worker = WorkerThread(tzcin)
#	worker.start()

	__init__()

	while True:
		tzc_dict = None
		try:
			tzc_dict = worker.q.get_nowait()
		except Queue.Empty:
			continue
		if tzc_dict == None:
			continue

#		print "got message",tzc_dict

		get_tickets()

		if tzc_dict.get('tzcspew','') != 'message':
			continue
		elif tzc_dict.get('class','') != LISTEN_CLASS:
			continue
		elif tzc_dict.get('instance','') != LISTEN_INSTANCE and LISTEN_INSTANCE != '':
			continue
		elif tzc_dict.get('auth','') != 'yes':
			continue
		else:
			sender = tzc_dict.get('sender','').replace('"','')
			if sender not in ('rhysh','mitchb','scottnla'):
				continue

#		print "got ok message",tzc_dict

#		sender = tzc_dict.get('sender','').replace('"','')

		message = tzc_dict.get('message','')[1:-1].strip()

#		print repr(message)

		msg_matches = re.findall(msg_rexp,message)

		if len(msg_matches) == 0:
			continue
		elif len(msg_matches) == 1:
			if len(msg_matches[0]) == 1:
				sig = ''
				msg = msg_matches[0][0]
			elif len(msg_matches[0]) == 2:
				sig = msg_matches[0][0]
				msg = msg_matches[0][1]
			else:
				continue

		print '''got ok message... zsig "%s", body "%s"''' % (sig,msg)

		tokens = [token for token in shlex.shlex(msg)]

#		print tokens

		if len(tokens) == 0:
			continue
		elif len(tokens) >= 6:
#			print tokens[0:6]
#			print tokens[6:]
			if tokens[0:6] == ['/','soda','/','admin','.','py']:
				send_zephyr(message="allowing %s to run %s" % (sender,msg), zclass=LISTEN_CLASS)
				result = admin.main(tokens[6:])
				send_zephyr(message="%s" % result, zrecipient=sender)

