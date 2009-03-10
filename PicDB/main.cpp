#include "pic_db.h"


using namespace std;

int main(int argc, char *argv[])
{
	Pic_db pdb(".");
	pdb.fill_db();

	system("pause");
	return 0;
}

