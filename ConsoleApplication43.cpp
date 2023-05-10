#include <iostream>
#include "trie.h"
using namespace std;

int main()
{

	Trie* trie = new Trie;

	trie->insertKey("pow");
	trie->insertKey("power");
	trie->insertKey("powerbank");
	trie->insertKey("grace");
	trie->insertKey("graphics");
	trie->insertKey("grapfruit");

	string userIn;
	bool run = true;
	while (run)
	{
		cout << "Enter word or \"exit\": ";
		cin >> userIn;
		if (userIn.compare("exit") == 0)
		{
			run = false;
			break;
		}
		if (trie->searchKey(userIn, true) == false)
		{
			cout << "No variants" << endl;;
		}
		cout << endl;
	}
	delete trie;

	return 0;
}