#include "requests.h"

int main(int argc, const char *argv[])
{
	struct host *h;

	h = Requests.init(argv[1]);
	Requests.get(h);
	Requests.destroy(h);

	return 0;
}
