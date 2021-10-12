#coding:utf-8
import sys
from Crypto.Cipher import AES
from os import urandom
import hashlib

KEY = urandom(16) # 128

def pad(s):
	p = AES.block_size-len(s)%AES.block_size # 填充字符数
	ps = s+p*chr(p) # 其实除了使用chr(p)填充,也可以用任何其他字符
	return ps

def aes_encrypy(s,key):
	k = hashlib.sha256(KEY).digest()
	iv = 16 * '\x00'
	s = pad(s)
	cipher = AES.new(k,AES.MODE_CBC,iv)
	# a = cipher.encrypt(bytes(s))
	# print(a)
	# b = cipher.decrypt(a)
	# print(b)
	return cipher.encrypt(bytes(s))

def to16(data):
	return ('{ 0x'+', 0x'.join(hex(ord(x))[2:] for x in data)+' };')

def main():
	if len(sys.argv)>1:
		fn = sys.argv[1]
	else:
		fn = 'p.bin'
	print('---\nRead the file: {}\n---'.format(fn))
	with open(fn,'r') as f:
		data = f.read()
		print('aeskey[] = '+to16(KEY))
		print('payload[] = '+to16(aes_encrypy(data,KEY)))

if __name__ == '__main__':
	main()
