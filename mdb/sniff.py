import serial
import sys

_ser = serial.Serial('/dev/ttyS0',115200,timeout=0.2)

_ser.setRTS(0)





def _interpret_exchange(exchange):
	if len(exchange) == 0:
		return None

	ex = []

	for byte in exchange:
		if len(byte) != 10:
			return None

		str = _int2hex(_rbin2int(byte[1:9]),2)

		if byte[9] == '1':
			str = str + '*'
		else:
			str = str + ' '

		if byte[0] == 'M':
			str = 'M: ' + str
		elif byte[0] == 'S':
			str = 'S: ' + str
		else:
			return None

		ex.append(str)

	if len(ex) == 0:
		return None

#	if ex[0] == 'M: 0A*': addr_0x0A(ex)

	return tuple(ex)





def _rbin2int(str):
	myint = 0
	for i in range(len(str)):
		if str[i] == '1':
			myint = myint + 2**i
	return myint




def _int2hex(myint, minlen=0):
	hex = ''

	digits = {0:'0', 1:'1', 2:'2', 3:'3', 4:'4', 5:'5', 6:'6', 7:'7', 8:'8', 9:'9', 10:'A', 11:'B', 12:'C', 13:'D', 14:'E', 15:'F'}

	while myint != 0:
		hex = digits[myint%16] + hex
		myint = myint / 16

	while len(hex) < minlen:
		hex = '0' + hex

	return hex





_exchange = []

def get_ex():
	for i in range(100):
		char = ''
		line = ''

		for j in range(10):
			char = _ser.read()
			if char == 'M' or char == 'S':
				line = char + _ser.read(9)
				break
			elif char == '':
				return ('timeout')
			else:
				continue

		if len(line) != 10:
			continue

		if line[0] == 'M' and line[9] == '1':
			ex = _interpret_exchange(_exchange)
			while len(_exchange) > 0:
				_exchange.pop()
			_exchange.append(line)
			return ex

		_exchange.append(line)
