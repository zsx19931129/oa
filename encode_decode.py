import os
import sys
import base64

def encode(estr):
	return base64.encodestring(estr)

def decode(dstr):
	return base64.decodestring(dstr)

def encode_dir(estr):
	dname = base64.encodestring(estr)
	fpath = os.path.dirname(os.path.abspath(__file__))

	full_path = os.path.join(fpath, dname)
	if not os.path.exists(full_path):
		os.makedirs(full_path)

if __name__ == '__main__':
	print encode('zillow')