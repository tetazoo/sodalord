import serial
import time

_ser = serial.Serial('/dev/ttyS0',115200,timeout=0.2)

_ser.setRTS(0)

def trigger(balance, balance_unknown = False):
	_ser.setRTS(1)

	for i in range(100):
		if _ser.getCTS():
			break
		time.sleep(0.01)

	if _ser.getCTS():
		_ser.write('b')
		time.sleep(0.01)
		if balance_unknown:
			_ser.write('\xff')
			time.sleep(0.01)
			_ser.write('\xff')
		elif balance < 0:
			_ser.write('\xff')
			time.sleep(0.01)
			_ser.write('\xff')
		elif balance > 65534:
			_ser.write('\xff')
			time.sleep(0.01)
			_ser.write('\xfe')
		else:
			_ser.write(chr(balance / 256))
			time.sleep(0.01)
			_ser.write(chr(balance % 256))
		_ser.setRTS(0)
		return 0
	else:
		_ser.setRTS(0)
		return 1



def approve():
	_ser.setRTS(1)

	for i in range(100):
		if _ser.getCTS():
			break
		time.sleep(0.01)

	if _ser.getCTS():
		_ser.write('a')
		_ser.setRTS(0)
		return 0
	else:
		_ser.setRTS(0)
		return 1



def deny():
	_ser.setRTS(1)

	for i in range(100):
		if _ser.getCTS():
			break
		time.sleep(0.01)

	if _ser.getCTS():
		_ser.write('d')
		_ser.setRTS(0)
		return 0
	else:
		_ser.setRTS(0)
		return 1



def cancel():
	_ser.setRTS(1)

	for i in range(100):
		if _ser.getCTS():
			break
		time.sleep(0.01)

	if _ser.getCTS():
		_ser.write('c')
		_ser.setRTS(0)
		return 0
	else:
		_ser.setRTS(0)
		return 1
