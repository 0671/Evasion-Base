#coding:utf-8
import sys

# 这就是xor密钥
key = 'ad780*^%21'

def xor(data, key):
	key = bytes(key.encode()) # py3
	# key = str(key) # py2
	klen = len(key)
	# xordata = '' # py2
	xordata = bytearray() # py3
	for i in range(len(data)):
		nowchar = data[i]
		now_key = key[i%klen]
		xordata.append(nowchar^now_key) # py3
		# xordata += chr(ord(nowchar)^ord(now_key)) # py2
	return bytes(xordata) #py3
	# return bytes(xordata) #py2

def print16(data):
	print('[*] hex show: { 0x'+', 0x'.join(hex(x)[2:] for x in data)+'};') #py3
	# print('[*] hex show: { 0x'+', 0x'.join(hex(ord(x))[2:] for x in data)+'};') #py2

def main():

	if len(sys.argv)>1:
		fn = sys,argv[1]
	else:
		fn = 'p.bin'
	print('---\nRead the file: {}\n---'.format(fn))
	with open(fn,'rb') as f:
		data = f.read()
		print("payload:")
		print16(data)
		print("-"*15)
		print('xor密钥为: {}\n加密结果如下:'.format(key))
		data2 = xor(data,key)
		print16(data2)



if __name__ == '__main__':
	main()