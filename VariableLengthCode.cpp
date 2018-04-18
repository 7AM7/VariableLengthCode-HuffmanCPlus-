#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
#include <algorithm>
#include<string>
using namespace std;

map<char, string> m_Code;
map<char, int> m_VlcFreq;
vector<pair<char, int>>LF;
struct VlcNode{
	char data;
	string code;
	int frequency;
	VlcNode*left, *right,*root;
	VlcNode(char data, int frequency) 
	{
		code = "";
		left = right= root = NULL;
		this->data = data;
		this->frequency = frequency;
	}
};

struct comp {
	bool operator()(VlcNode*left, VlcNode*right) 
	{
		return (left->frequency > right->frequency);
	}
}compp;

struct VLC {
	
	vector<VlcNode*>v_Vlc;
	void CreateVlcCode()
	{
		VlcNode*left, *right, *root;

		// with Queue

		/*
		priority_queue<VlcNode*, vector<VlcNode*>, comp>queueV;	
		for (map<char, int>::iterator i = m_Vlc.begin(); i != m_Vlc.end(); i++) {
			queueV.push(new VlcNode(i->first, i->second));
		}
		priority_queue<VlcNode*, vector<VlcNode*>, comp>tempq;
		tempq = queueV;
		int s = tempq.size();
		while ( s>0)
		{
			VlcNode*temp = tempq.top();
			cout << temp->data << " " << temp->frequency << endl;
			tempq.pop();
			s--;
		}
		*/
		//start from tree leaf
		while (v_Vlc.size()>1)
		{
			left = v_Vlc[v_Vlc.size()-1];
			v_Vlc.pop_back();

			right = v_Vlc[v_Vlc.size() - 1];
			v_Vlc.pop_back();

			root = new VlcNode('*', right->frequency+left->frequency);
			if (left->frequency> right->frequency)
			{
				root->left = left;
				root->right = right;
			}
			else
			{
				root->left = right;
				root->right = left;
			}
			v_Vlc.push_back(root);
			sort(v_Vlc.begin(), v_Vlc.end(), compp);
		}
		addCode("", v_Vlc[v_Vlc.size() - 1]);
	}
	VlcNode* TreeHead() {
		return v_Vlc[0];
	}
	string DecodeVlc(string text, VlcNode*root)
	{
		string res = "";
		VlcNode*temp = root;
		for (int i = 0; i < text.length(); i++)
		{
			text[i] == '0' ? temp = temp->left : temp = temp->right;
			if (temp->left == NULL && temp->right == NULL) {
				res += temp->data;
				temp = root;
			}
		}
		return res;
	}

	void addCode(string code, VlcNode*root)
	{
		
		if (root == NULL)return;
		// too print the tree leaf data
		if (root->data != '*') {
			m_Code[root->data] = code;
			cout << root->data << "  " << code << endl;
		}
		// to print the root data
		//cout << root->frequency << endl;

		addCode(code + "0", root->left);
		addCode(code + "1", root->right);
	}

	void ClucFrequencyWithSort(string text)
	{
		v_Vlc.clear();
		m_VlcFreq.clear();
		for (int i = 0; i < text.length(); i++) 
		{
			m_VlcFreq[text[i]]++;//map count charcter repated 
		}

		for (auto i : m_VlcFreq)	 //push map to vector
		{
			v_Vlc.push_back(new VlcNode(i.first, i.second));
		}
		sort(v_Vlc.begin(), v_Vlc.end(), compp);
		//v_Vlc.erase(unique(v_Vlc.begin(), v_Vlc.end()), v_Vlc.end());
	}
	void PrintCharAndFreq() 
	{
		for (int i = 0; i < v_Vlc.size(); i++)
		{
			cout << v_Vlc[i]->data << " " << v_Vlc[i]->frequency << endl;
		}
	}
	void Raito(int textlen)
	{
		
		map<char, string > temp1 = m_Code;
		map<char, int>temp2 = m_VlcFreq;
		map<char, string>::iterator it1 = temp1.begin();
		map<char, int>::iterator it2 = temp2.begin();

		for (; it1 != temp1.end(), it2 != temp2.end(); it1++, it2++)
		{
			if (it1->first == it2->first) {
				int lenCode = strlen(it1->second.c_str());
				int freq = it2->second;
				LF.push_back(make_pair(it1->first, lenCode*freq));
			}
		}
		int after = 0;
		for (auto i : LF)
		{
			after += i.second;
		}
		//before -after/before *100
		double before = (textlen * 8);
		double raito = ((before - after) / before) * 100;
		cout << "Raito: " << raito << endl;
	}
	void Entropy(int textlen)
	{
		map<char, int>temp2 = m_VlcFreq;
		map<char, int>::iterator it2 = temp2.begin();
		long double entropy = 0;
		for (; it2 != temp2.end();  it2++)
		{
			long double frq = (double)((double)it2->second/ (double)textlen);

			// Sum(Pi*log2 Pi)
			entropy += ((double)frq*log2((double)frq));
		}

		cout << "Entropy: " << entropy << endl;
	}
	void Efficiency()
	{
		double efficiency = 0;
		for (auto i : LF)
		{
			// Sum(L*F*log2 L*F) 
			//L*F is  Length * Frequency
			efficiency+= (i.second*log2(i.second));
		}
		cout << "Efficiency: " << efficiency << endl;
	}
}Vlc;


int main()
{
	//with simple text
	/*
	string test = "hello world";
	Vlc.ClucFrequencyWithSort(test);
	Vlc.PrintCharAndFreq();
	cout <<"Charcter & Code: " <<endl;
	Vlc.CreateVlcCode();
	*/


	//with file

	const string filename = "test.am7";
	const string Tempfilename = "testTemp.am7";
	fstream file;
	file.open(filename, ios::out);
	file << "Hello anllo pello";
	file.close();
	string code;
	string line;
	file.open(filename, ios::in,ios::binary);
	while (getline(file,line))
	{
	}
	file.close();

	// convert string to lowercase
	transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);

	cout << "Charcter & Frequency: " << endl;
	Vlc.ClucFrequencyWithSort(line);
	Vlc.PrintCharAndFreq();
	cout << "Charcter & Code: " << endl;
	Vlc.CreateVlcCode();
	if (!m_Code.empty()) 
	{
		for (auto i : line)
		{
			code += m_Code[i];
		}
	}
	cout << "After Enecode: " << code << endl;
	Vlc.Raito(strlen(line.c_str()));
	Vlc.Entropy(strlen(line.c_str()));
	Vlc.Efficiency();
	//Decode
	
	
	string Decode = Vlc.DecodeVlc(code, Vlc.TreeHead());
	cout <<"After Decode: "<<Decode << endl;
	file.open(Tempfilename, ios::out);
	file << Decode;
	file.close();
	system("pause");
	return 0;
}