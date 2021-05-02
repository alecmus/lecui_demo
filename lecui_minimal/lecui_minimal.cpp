/* The smallest possible lecui app
*/
#include <liblec/lecui/form.h>

int main() {
	liblec::lecui::form("Form").message("Hello world!");
	return 0;
}