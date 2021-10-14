#coding:utf-8
import sys

# 这就是xor密钥
key = 'ad780*^%21'

def xor(data, key):
	if isinstance(data,str):
		data= bytes(data.encode()) # py3
	key = bytes(key.encode()) # py3
	# key = str(key) # py2
	klen = len(key)
	xordata = ''
	for i in range(len(data)):
		nowchar = data[i]
		now_key = key[i%klen]
		xordata += chr(nowchar^now_key) # py3
		# xordata += chr(ord(nowchar)^ord(now_key)) # py2
	return xordata

def printCarray(data):
	print('[*] c_array = { 0x'+', 0x'.join(hex(ord(x))[2:] for x in data)+'};')
# def print_(data): # py2
# 	print('[*] ascii show: {}'.format(data))

def main():
	print('xor密钥为: {}'.format(key))

	data = 'VirtualProtect'
	print(data)
	data2 = xor(data,key)
	printCarray(data2)

	if len(sys.argv)>1:
		fn = sys,argv[1]
	else:
		fn = 'p.bin'
	print('---\nRead the file: {}'.format(fn))
	with open(fn,'rb') as f:
		data = f.read()
		# print16(data)
		# print_(data)
		print('加密结果如下:')
		data2 = xor(data,key)
		printCarray(data2)

if __name__ == '__main__':
	main()