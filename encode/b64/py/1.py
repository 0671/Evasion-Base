#coding: utf-8

# 转换表
cvt_table = 'IBC#JOc@e456f0123PQvwghAEFG+HKLMN)rs!ujklmno78(/pqUVWXYZ-bxyzTRS'

def b64encode(s):
	es = ''
	pn = 0 if not len(s)%3 else (3-len(s)%3)
	s += pn*chr(0)
	slen = len(s)
	edn = 0
	for edn in range(0,slen,3):
		# 取3*8切成4*6,再填充为4*8
		# 将8位按转换表转换为对应下标的b64字符,末尾2个8位,若为0则转为=
		_n1 = bin(ord(s[edn+0]))[2:].rjust(8,'0')
		_n2 = bin(ord(s[edn+1]))[2:].rjust(8,'0')
		_n3 = bin(ord(s[edn+2]))[2:].rjust(8,'0')
		_n = _n1 + _n2 + _n3

		_i1 = int(_n[ 0: 6].rjust(8,'0'),2)
		_i2 = int(_n[ 6:12].rjust(8,'0'),2)
		_i3 = int(_n[12:18].rjust(8,'0'),2)
		_i4 = int(_n[18:24].rjust(8,'0'),2)
		# print('%d,%d,%d,%d'%(_i1,_i2,_i3,_i4))

		_c1 = cvt_table[_i1]
		_c2 = cvt_table[_i2]
		_c3 = cvt_table[_i3]
		_c4 = cvt_table[_i4]

		if edn == (slen-3):
			if _i3 == 0:
				_c3 = '='
			if _i4 == 0:
				_c4 = '='

		es += _c1+_c2+_c3+_c4
	# print('-d-')
	return es


def b64decode(s):
	ds = ''
	slen = len(s)
	edn = 0
	for edn in range(0,slen,4):
		# 取4*8,将8位转换为对应b64字符的下标
		# 取下标后6位,得4*6 切成3*8,8位转换为对应的ascii字符
		_n1 = cvt_table.find(s[edn+0])
		_n2 = cvt_table.find(s[edn+1])
		_n3 = cvt_table.find(s[edn+2])
		_n4 = cvt_table.find(s[edn+3])

		_n3 = 0 if _n3 == -1 else _n3
		_n4 = 0 if _n4 == -1 else _n4

		_n1 = bin(_n1&0x3f)[2:].rjust(6,'0')
		_n2 = bin(_n2&0x3f)[2:].rjust(6,'0')
		_n3 = bin(_n3&0x3f)[2:].rjust(6,'0')
		_n4 = bin(_n4&0x3f)[2:].rjust(6,'0')
		_n = _n1 + _n2 + _n3 + _n4

		_i1 = int(_n[ 0: 8],2)
		_i2 = int(_n[ 8:16],2)
		_i3 = int(_n[16:24],2)
		# print('%d,%d,%d'%(_i1,_i2,_i3))

		_c1 = chr(_i1)
		_c2 = chr(_i2)
		_c3 = chr(_i3)

		if edn == (slen-4):
			if _i2 == 0:
				_c2 = ''
			if _i3 == 0:
				_c3 = ''
		ds += _c1+_c2+_c3
	# print('-e-')
	return ds

def main():
	a='<'
	b='123i1op<'
	c='E44444av<>444DF133'
	print(a)
	print(b)
	print(c)
	print('*'*10)
	b64_a=b64encode(a)
	b64_b=b64encode(b)
	b64_c=b64encode(c)
	print(b64_a)
	print(b64_b)
	print(b64_c)
	print('*'*10)
	b64d_a=b64decode(b64_a)
	b64d_b=b64decode(b64_b)
	b64d_c=b64decode(b64_c)
	print(b64d_a)
	print(b64d_b)
	print(b64d_c)
	print('*'*10)

if __name__ == '__main__':
	main()