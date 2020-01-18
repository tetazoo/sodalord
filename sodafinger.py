#!/usr/bin/python

import sys
import pg

input = sys.stdin.readline().strip()
if input == '':
    print "Try fingering a sodalord username.\n"
    sys.exit(3)
if not input.isalnum():
    print "Use alphanumerics only!\n"
    sys.exit(1)

db = pg.connect('soda')

if input == 'total':
    sum = db.query("SELECT SUM(balance) FROM sodauser WHERE username != 'tetazoo' AND username != 'testuser' AND username != 'testuser7' AND username != 'frosh'").getresult()[0][0]
    print "Total soda balance is $%.2f.\n" % sum
    db.close()
    sys.exit(0)

alias = db.query("SELECT user_id FROM alias WHERE aliasname = '%s'" % input).getresult()
if not alias.__len__() == 1:
    print "%s doesn't have a sodalord account\n" % input
    db.close()
    sys.exit(2)

userid = alias[0][0]
sodauser = db.query("SELECT * FROM sodauser WHERE id = %s" % userid).dictresult()[0]
user_stats = db.query("SELECT * FROM user_stats WHERE user_id = %s" % userid).dictresult()[0]

tally = 0
for a in range(10):
    tally += eval("user_stats['h0%s']" % a)
for a in range(10,24):
    tally += eval("user_stats['h%s']" % a)

print "%s has a soda tally of %s and a balance of $%.2f\n" % (sodauser['username'], tally, sodauser['balance'])
db.close()
sys.exit(0)

