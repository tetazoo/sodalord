#!/usr/bin/python

import sys
import getopt
import pg
import time
import re
import string

def main(argv):
#	print argv

	if len(argv) == 0:
		return force_help()

	primary = argv[0]
	secondary = argv[1:]

	if cmddict.has_key(primary):
		return cmddict[primary](secondary)
	else:
		return "Command not found\n" + force_help()

	sys.exit(0)














	try:
		opts, args = getopt.getopt(argv, 'hs:cpr:u', ['help', 
'selection=', 'cash', 'product', 'run=', 'unpaid', 'pay=', 'stocking', 'removal', 'add-run'])
		print
	except getopt.GetoptError:
		usage()
		sys.exit(2)

	db = pg.connect('soda')

	if opts == []:
		usage()
		sys.exit()

	for opt, arg in opts:
		if opt in ('--help','-h'):
			usage()
			sys.exit()



		elif opt in ('--selection','-s'):
			if arg.lower() == 'all':
				result = db.query("""\
SELECT selection.selection_num, flavor.name AS flavor_name
FROM selection
JOIN product ON selection.product_id = product.id
JOIN flavor ON product.flavor_id = flavor.id
ORDER BY selection.selection_num""")
				print result
				sys.exit()
			elif eval(arg) in range(1,10):
				selection = int(arg)
				result = db.query("""\
SELECT selection.selection_num, selection.columns, selection.actual_price, 
selection.current_level_upper_bound, selection.current_level_lower_bound, 
package.name AS package_name, package.column_capacity,
flavor.name AS flavor_name, flavor.nickname
FROM selection
JOIN product on selection.product_id = product.id
JOIN flavor ON product.flavor_id = flavor.id
JOIN package ON product.package_id = package.id
WHERE selection.selection_num = %d""" % selection)
				if result.ntuples() == 0:
					print "No information for selection %d" % selection
				else:
					resdict = result.dictresult()[0]
					flavor_name = resdict.get('flavor_name')
					nickname = resdict.get('nickname')
					columns = resdict.get('columns')
					package = resdict.get('package_name')
					capacity = columns * resdict.get('column_capacity')
					price = resdict.get('actual_price')
					lower = resdict.get('current_level_lower_bound')
					upper = resdict.get('current_level_upper_bound')
					print """\
Selection %d currently contains %s (%s)
  Columns: %d
  Package: %s
  Capacity: %d
  Price: $%.2f
  Current level: %d-%d
""" % (selection, flavor_name, nickname, columns, package, capacity, price, lower, upper)



		elif opt in ('--add-run',):
			line = None
			while line == None:
				print "What date? (YYYY-MM-DD) [today]"
				line = raw_input()
				if line == '':
					line = time.strftime('%Y-%m-%d')
					print "Using %s" % line
				elif not re.match('^[0-9]{4}-[0-9]{2}-[0-9]{2}$',line):
					line = None
			run_date = line

			line = None
			while line == None:
				print "What supplied the soda?"
				line = raw_input()
				if line == '':
					line = None
				elif not re.match('^[-_ a-zA-Z0-9]+$',line):
					line = None
					print "Alphanumerics only"
			supplier = sanitize(line)

			line = None
			while line == None:
				print "Are you sure? (yes/no)"
				line = raw_input()
				if line != 'yes' and line != 'no':
					line = None
			really = line

			if really != 'yes':
				sys.exit()
			else:
				result = db.query("""\
INSERT INTO run
(run_date, supplier)
VALUES ('%s', '%s')""" % (run_date, supplier))
				result = db.query("""\
SELECT id FROM run
WHERE run_date = '%s' AND supplier = '%s'""" % (run_date, supplier))
				for row in result.dictresult():
					print "Run id: %d" % row.get('id')
				sys.exit()



		elif opt in ('--add-stock',): print "not yet written"





		elif opt in ('--product',):
			result = db.query("""\
SELECT product.id AS product_id, package.name AS package_name, flavor.name AS flavor_name
FROM product
JOIN flavor ON product.flavor_id = flavor.id
JOIN package ON product.package_id = package.id""")
			print "product id	package		flavor"
			for product in result.dictresult():
				print "%(product_id)d		%(package_name)s	%(flavor_name)s" % product
			print






		elif opt in ('--run','-r'):
			if arg == 'all':
				result = db.query("""\
SELECT * FROM run""")
				resdict = result.dictresult()
				if len(resdict) == 0:
					print "No runs found"
				else:
					print "\
id	date		supplier"
				for row in resdict:
					print "\
%(id)d	%(run_date)s	%(supplier)s" % row
			elif re.search('^[0-9]+$',arg):
				result = db.query("""\
SELECT * FROM run WHERE run.id = %s""" % arg)
				if result.ntuples() == 0:
					print "No run with that run id found"
				else:
					print "%(run_date)s	%(supplier)s" % result.dictresult()[0]
					print
					result = db.query("""\
SELECT run_item.wholesale_price AS price,
run_item.deposit AS deposit,
run_item.tax AS tax,
run_item.quantity_included AS quantity,
flavor.name AS flavor,
package.name AS package,
sodauser.username AS payer
FROM run_item
JOIN product ON product.id = run_item.product_id
JOIN flavor ON product.flavor_id = flavor.id
JOIN package ON product.package_id = package.id
JOIN sodauser ON run_item.payer_userid = sodauser.id
WHERE run_item.run_id = %s""" % arg)
					print "\
payer	price	dep.	tax	#items	package		flavor"
					for item in result.dictresult():
						print "\
%(payer)s	$%(price).2f	$%(deposit).2f	$%(tax).2f	%(quantity)d	%(package)s	%(flavor)s" % item
					print
					result = db.query("""\
SELECT run_extra_cost.amount,run_extra_cost.description,sodauser.username
FROM run_extra_cost
JOIN sodauser ON run_extra_cost.payer_userid=sodauser.id
WHERE run_extra_cost.run_id = %s""" % arg)
					if result.ntuples() == 0:
						print "No extra costs found"
					else:
						print "payer	amount	description"
						for item in result.dictresult():
							print "%(username)s	$%(amount).2f	%(description)s" % item
			print






		elif opt in ('--pay',):
			debt_id = sanitize(arg)
			result = db.query("""\
SELECT *,deposit.oid FROM deposit
JOIN sodauser ON deposit.user_id = sodauser.id
WHERE deposit.oid = '%s'""" % (debt_id))
			if result.ntuples() == 0:
				print "No debt with that debt id found"
			elif result.ntuples() != 1:
				print "There seem to be multiple debts with that debt id..."
				print "something's horribly wrong! here, have some data:"
				print result
			else:
				print_debt(result.dictresult()[0])
				print
				print "Is this the correct debt? (yes/no)"
				line = raw_input().strip()
				amount = result.dictresult()[0]['amount']
				if line == 'yes':
					print "What's your username (who's getting the money)?"
					alias = sanitize(raw_input().strip())
					result = db.query("""\
SELECT user_id FROM alias WHERE aliasname = '%s'""" % alias)
					if result.ntuples() != 1:
						print "Bad username"
					else:
						user_id = result.getresult()[0][0]
						print "Admin comment (where's the money)?"
						line = raw_input().strip()
						if line == '':
							print "You have to enter an admin comment"
						else:
							comment = sanitize(line)
							print "Are you keeping the money (yes) or is it going _into sodalord_ (no)"
							line = raw_input().strip().lower()
							if not line in ('yes','no'):
								print "I asked a yes or no question, how hard can it be??"
							else:
								db.query("""\
UPDATE deposit SET admin_comment = '%s', recipient_userid = %s
WHERE oid = %s""" % (comment,user_id,debt_id))
								if line == 'yes':
									db.query("""\
INSERT INTO money_removal (removal_time, amount, recipient_userid)
VALUES (now(), %s, %s)""" % (amount, user_id))




























def sanitize(dangerous):
	allowed = string.ascii_letters + string.digits + ' -+_,.$@&'
	safe = ''
	for i in range(len(dangerous)):
		if dangerous[i] in allowed:
			safe = safe + dangerous[i]
		else:
			safe = safe + '-'
	return safe





###########################
###			###
###	HELP		###
###			###
###########################

def force_help():
	return cmd_help([])

def cmd_help(args):
	output = ''

	if len(args) == 0:
		topic = 'general'
	else:
		topic = args[0]

	if topic == 'general':
		output += """
The sodalord admin interface supports several subcommands. For more help 
on any one of them, try "help TOPIC" (TOPIC being what you're interested 
in).

  help				print this help
  cash				tell how much cash is in the machine
  unpaid			list all unverified credits
  pay				verify a credit
  selection			display what the database thinks each 
				selection contains.

(more to come later)
"""

	elif topic == 'cash':
		output += """
If given no arguments, cash will display the current cash levels in 
human-readable form.

  --machine			display in machine readable form instead. 
				this is cashbox_nickels,cashbox_dimes,
				cashbox_quarters,cashbox_dollars,
				tube_nickels,tube_dimes,tube_quarters,
				bill_dollars as a comma separated list.
"""

	elif topic == 'unpaid':
		output += """
This command takes no arguments and returns a human-readable list of all 
credits to sodalord accounts that are currently unpaid
"""

	elif topic == 'selection':
		output += """
If given no arguments, selection will display what's in each selection. If 
a selection is specified, it will give more detailed information about it 
(product levels).

  [1-9]				display detailed information about the 
				selection.
"""

	else:
		output += "No help available on that topic"

	return output
	sys.exit(0)



###########################
###			###
###	CASH		###
###			###
###########################

def cmd_cash(args):
	output = ''

	db = pg.connect('soda',user='soda')

	result = db.query("""\
SELECT * FROM current_cash""")
	resdict = result.dictresult()[0]

	if args == ['--machine']:
		output += """\
%(cashbox_nickels)d,%(cashbox_dimes)d,%(cashbox_quarters)d,%(cashbox_dollars)d,\
%(tube_nickels)d,%(tube_dimes)d,%(tube_quarters)d,\
%(bill_dollars)d""" % resdict

	else:
		resdict['cashbox_total'] = resdict.get('cashbox_nickels')*0.05 + resdict.get('cashbox_dimes')*0.10 + resdict.get('cashbox_quarters')*0.25 + resdict.get('cashbox_dollars')*1.00
		resdict['tube_total'] = resdict.get('tube_nickels')*0.05 + resdict.get('tube_dimes')*0.10 + resdict.get('tube_quarters')*0.25
		resdict['bill_total'] = resdict.get('bill_dollars')*1.00
		resdict['total'] = resdict.get('cashbox_total') + resdict.get('tube_total') + resdict.get('bill_total')
		output += """\
The machine currently contains $%(total).2f total.
  The cashbox contains $%(cashbox_total).2f
    %(cashbox_nickels)d nickels
    %(cashbox_dimes)d dimes
    %(cashbox_quarters)d quarters
    %(cashbox_dollars)d dollar coins
  The coin tubes contains $%(tube_total).2f
    %(tube_nickels)d nickels
    %(tube_dimes)d dimes
    %(tube_quarters)d quarters
  The bill stacker contains $%(bill_total).2f
    %(bill_dollars)d dollar bills
""" % resdict

	db.close()

	return output
	sys.exit(0)



###########################
###			###
###	UNPAID		###
###			###
###########################

def cmd_unpaid(args):
	output = ''

	db = pg.connect('soda',user='soda')

	result = db.query("""\
SELECT *,deposit.oid FROM deposit
JOIN sodauser ON deposit.user_id = sodauser.id
WHERE recipient_userid IS NULL
ORDER BY deposit.deposit_time""")
	resdict = result.dictresult()
	for dict in resdict:
		output += return_debt(dict)
#	output += '\n'

	db.close()
	return output
	sys.exit(0)



def return_debt(dict):
	output = ''

	if dict['admin_comment'] == None:
		dict['admin_comment'] = '(no comment)'
	output += """
%(deposit_time)s: (debt id %(oid)d) User %(username)s <%(email)s>
  credited $%(amount).2f (current balance is $%(balance).2f)
  User comment:  %(user_comment)s
  Admin comment: %(admin_comment)s
""" % dict

	return output



###########################
###			###
###	PAY		###
###			###
###########################

def cmd_pay(args):
	return "not quite yet"


			debt_id = sanitize(arg)
			result = db.query("""\
SELECT *,deposit.oid FROM deposit
JOIN sodauser ON deposit.user_id = sodauser.id
WHERE deposit.oid = '%s'""" % (debt_id))











###########################
###			###
###	SELECTION	###
###			###
###########################

def cmd_selection(args):
	return "not quite yet"


















	try:
		opts, args = getopt.getopt(argv, 'hs:cpr:u', ['help', 
'selection=', 'cash', 'product', 'run=', 'unpaid', 'pay=', 'stocking', 'removal', 'add-run'])
		print
	except getopt.GetoptError:
		cmd_help('selection')
		sys.exit(2)



def usage():
	print """\
  -h, --help			print help
  -s, --selection=SELECTION	display what's currently in a selection 
				(or "all")
  -c, --cash			how much cash is in the machine
  --product			display all the products we have stocked
  --add-run			add a soda run
  --run=RUN			display a soda run (or "all")
  --stocking			display all the stockings we've done
  --removal			display all money removals
  -u, --unpaid			display unconfirmed account credits
  --pay=DEBT_ID			record receipt of cash from a user
"""











cmddict = {}
for obj in dir():
	if obj.startswith('cmd_'):
		cmddict[obj[4:]] = eval(obj)



if __name__ == "__main__":
	print main(sys.argv[1:])
