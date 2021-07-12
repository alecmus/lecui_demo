/* Simple login form
*/
#include <liblec/lecui/controls.h>
#include <liblec/lecui/appearance.h>
#include <liblec/lecui/containers/page.h>
#include <liblec/lecui/widgets/label.h>
#include <liblec/lecui/widgets/text_field.h>
#include <liblec/lecui/widgets/password_field.h>
#include <liblec/lecui/widgets/button.h>
#include <liblec/lecui/widgets/image_view.h>
using namespace liblec::lecui;
using std::string;

class login : public form {
	const float _margin = 10.f;
	page_manager _page_man{ *this };
	controls _ctrls{ *this };
	appearance _apprnc{ *this };
	dimensions _dim{ *this };
	bool& _logged_in;
	const string _username = "User";
	const string _password = "password";

	bool on_initialize(std::string& error) override {
		_ctrls
			.allow_minimize(false)
			.allow_resize(false);
		_apprnc.theme(themes::light);
		_dim.set_size({ 280, 320 });
		return true;
	}

	bool on_layout(string& error) override {
		auto& page = _page_man.add("home");

		widgets::image_view_builder avatar(page, "avatar");
		avatar()
			.file("images\\avatar.png").quality(image_quality::high)
			.rect()
				.size(130, 130)
				.place({ _margin, page.size().width - _margin,
					_margin, _margin + (_dim.get_size().height / 2.f) },
					50.f, 0.f);

		widgets::text_field_builder username(page, "username");
		username().rect().snap_to(avatar().rect(), rect::snap_type::bottom, 3.f * _margin);
		username().events().action = [&]() { on_login(); };

		widgets::password_field_builder password(page, "password");
		password().rect().snap_to(username().rect(), rect::snap_type::bottom, _margin);
		password().events().action = [&]() { on_login(); };

		widgets::button_builder do_login(page);
		do_login().text("Login")
			.rect().snap_to(password().rect(), rect::snap_type::bottom, 1.5f * _margin);
		do_login().events().action = [this]() { on_login(); };

		_page_man.show("home");
		return true;
	}

	void on_login() {
		try {
			auto& username = widgets::text_field_builder::specs(*this, "home/username").text();
			auto& password = widgets::text_field_builder::specs(*this, "home/password").text();

			if (username.empty() || password.empty())
				return;

			if (username == _username && password == _password) {
				_logged_in = true;
				close();
			}
			else
				message("Wrong username or password");
		}
		catch (const std::exception& e) { message("Error: " + string(e.what())); }
	}

public:
	login(const string& caption, bool& logged_in) :
		form(caption),
		_logged_in(logged_in) {}
};

int main() {
	bool logged_in = false;
	login _login("Login", logged_in);
	string error;
	if (_login.show(error)) {
		if (logged_in)
			_login.message("Login successful!");
	}
	else
		_login.message("Error: " + error);
	return 0;
}