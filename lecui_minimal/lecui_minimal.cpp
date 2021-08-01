/* The smallest possible lecui app
*/
#include <liblec/lecui/form.h>
using namespace liblec::lecui;

int main() {
	form("Form").message("Hello world!");
	return 0;
}