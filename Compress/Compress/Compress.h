#pragma once  

#include <stdlib.h>
#include <string>
#include "HuffmanTree.h"

typedef unsigned long LongType;

struct CharInfo
{
	unsigned char	_ch;
	LongType		_count;
	string			_code;

	CharInfo(const LongType& count = 0 )
		: _count(count)
	{ }

	bool operator <(const CharInfo& ch) const 
	{
		return _count < ch._count;
	}

	CharInfo operator + (const CharInfo& ch)
	{
		return CharInfo(_count + ch._count);
	}

	bool operator != (const CharInfo& ch) const
	{
		return _count != ch._count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;

public:

	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
				_info[i]._count = 0;
		}
	}

	void GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root, string code)
	{
		if (NULL == root)
			return;

		if (root->_left == NULL && root->_right == NULL)
		{
			_info[root->_weight._ch]._code = code;
			return;
		}

		GenerateHuffmanCode(root->_left, code + '0');
		GenerateHuffmanCode(root->_right, code + '1');
	}

	void Compress(const char* filename)
	{
		//打开的方式很重要
		FILE * fp = fopen(filename, "rb");
		if (NULL == fp)
		{
			assert(false);
		}

		//统计文件中字符的个数
		unsigned char ch = fgetc(fp);
		while (!feof(fp))
		{
			_info[(unsigned char) ch]._count++;  //会出现中文解析不了
			_info[(unsigned char) ch]._ch = ch;
			ch = fgetc(fp);
		}

		CharInfo invalid;	
		HuffmanTree<CharInfo> huf(_info, 256, invalid);

		Node* root = huf.GetRoot();
		string code;
		GenerateHuffmanCode(root, code);

		fseek(fp, 0, SEEK_SET); //重新定位读指针在文件头

		string CompressFileName = filename;
		CompressFileName += ".compress";
		FILE * fIn = fopen(CompressFileName.c_str(), "wb");
		if (NULL == fIn)
		{
			fclose(fp);
			assert(false);
		}

		int value = 0;
		int size = 0;

		ch = fgetc(fp);
		while (!feof(fp))
		{
			string& code = _info[(unsigned char) ch]._code;
			size_t N = code.size();

			for (size_t i = 0; i < N; ++i)
			{
				value <<= 1;
				if (code[i] & 1)
				{
					value |= 1;
				}

				++size;

				if (size == 8)
				{
					fputc(value, fIn);
					size = 0;
					value = 0;
				}
			}

			ch = fgetc(fp);
		}

		if (size)
		{
			value <<= (8 - size);
			fputc(value, fIn);
		}

		string ConfigFileName = filename;
		ConfigFileName += ".config";
		FILE * fInconfig = fopen(ConfigFileName.c_str(), "wb");
		if (NULL == fInconfig)
		{
			fclose(fp);
			fclose(fIn);
			assert(false);
		}

		string line;
		char buf[256];

		for (size_t i = 0; i < 256; ++i)
		{
			if (_info[i]._count > 0)
			{
				line += i;
				line += ',';
				line += _itoa(_info[i]._count,buf,10);
				line += '\n';

				//处理字符为'\0'情况
				if (line[0] == '\0')
				{
					fputc('\0', fInconfig);
					fputc(',', fInconfig);
					fputs(_itoa(_info[i]._count, buf, 10), fInconfig);
					fputc('\n', fInconfig);
					line.clear();
					continue;
				}

				fputs(line.c_str(), fInconfig);
				line.clear();
			}
		}

		fclose(fInconfig);
		fclose(fIn);
		fclose(fp);
	}

	bool ReadLine(FILE* fp ,string& code)
	{
		char ch = fgetc(fp);
		if (feof(fp))
		{
			return false;
		}

		while (!feof(fp) && ch != '\n')
		{
			code += ch;
			ch = fgetc(fp);
		}

		return true;
	}

	void Uncompress(const char* filename)
	{
		string CompressFileName = filename;
		CompressFileName += ".compress";
		FILE * fOut = fopen(CompressFileName.c_str(), "rb");
		if (NULL == fOut)
		{
			assert(false);
		}

		string UncompressFileName = filename;
		UncompressFileName += ".uncompress";
		FILE * fIn = fopen(UncompressFileName.c_str(), "wb");
		if (NULL == fIn)
		{
			fclose(fOut);
			assert(false);
		}

		string ConfigFileName = filename;
		ConfigFileName += ".config";
		FILE * fInconfig = fopen(ConfigFileName.c_str(), "rb");
		if (NULL == fInconfig)
		{
			fclose(fOut);
			fclose(fIn);
			assert(false);
		}

		string code;
		while (ReadLine(fInconfig, code))
		{
			//处理换行符
			if (code.size() ==  0 )
			{
				code += '\n';
				char ch = fgetc(fInconfig);
				while (!feof(fInconfig) && ch != '\n')
				{
					code += ch;
					ch = fgetc(fInconfig);
				}
			}

			_info[(unsigned char)code[0]]._ch = code[0];
			_info[(unsigned char)code[0]]._count = atoi(code.substr(2).c_str());
			code.clear();
		}

		fclose(fInconfig);

		CharInfo invalid;
		HuffmanTree<CharInfo> huf(_info, 256, invalid);

		Node* root = huf.GetRoot();
		Node* cur = root;

		int CharCout = root->_weight._count; //文件中字符的总个数

		unsigned char ch = fgetc(fOut); //文件只解析了一半就结束了
		int pos = 7;

		while (!feof(fOut))       //解析照片时，发现 ch != EOF 有问题 （-1）
		{
			if (ch & (1 << pos))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			--pos;

			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fIn);
				--CharCout;
				cur = root;
			}

			if (CharCout == 0)
			{
				break;
			}

			if (pos < 0)
			{
				ch = fgetc(fOut);
				pos = 7;
			}
		}

		fclose(fIn);
		fclose(fOut);
	}

private:

	CharInfo _info[256];
};

#include <Windows.h>

void CompressTest()
{
	FileCompress file;

	int start = GetTickCount();

	file.Compress("Input.BIG");

	int end = GetTickCount();
	cout << "Compress :" << end - start<< endl;

	start = GetTickCount();

	file.Uncompress("Input.BIG");

	end = GetTickCount();
	cout << "UnCompress :" << end - start << endl;

	getchar();
}

//void GenerateHuffmanCode(HuffmanTreeNode<CharInfo>*& root, string& code,Node*& prev)
//{
//	if (NULL == root)
//		return;

//	if (root->_left == NULL && root->_right == NULL)
//	{
//		cout << root->_weight._ch << " : ";
//		for (size_t i = 0; i, i < code.size(); ++i)
//		{
//			cout << code[i];
//		}
//		cout << " " << endl;

//		for (size_t i = 0; i < code.size(); ++i)
//		{
//			root->_weight._code.push_back(code[i]);
//			_info[root->_weight._ch]._code.push_back(code[i]);
//		}

//		return;
//	}

//	prev = root;

//	if (NULL != root->_left)
//	{
//		code.push_back('0');
//		GenerateHuffmanCode(root->_left, code, prev);
//	}

//	if (NULL != root->_right)
//	{
//		if (prev != root)
//		{
//			//当prevNode与curNode不同,将code置空
//			while (!code.empty())
//			{
//				code.pop_back();
//			}
//		}
//		else
//		{
//			code.pop_back();
//		}
//		code.push_back('1');

//		GenerateHuffmanCode(root->_right, code, prev);
//	}
//}