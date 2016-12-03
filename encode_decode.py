import os
import sys
import base64

CUR_DIR = os.path.dirname(os.path.abspath(__file__))

def encode(estr):
	return base64.encodestring(estr)

def decode(dstr):
	return base64.decodestring(dstr)

def createEncodeFolder(estr):
	folder_name = encode(estr)
	full_path = os.path.join(CUR_DIR, folder_name)

	if not os.path.exists(full_path):
		os.makedirs(full_path)

if __name__ == '__main__':
	# print encode('zillow')
	# print encode('pocket gems')
	createEncodeFolder('pocket gems')