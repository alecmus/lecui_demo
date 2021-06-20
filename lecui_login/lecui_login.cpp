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
	const float margin_ = 10.f;
	page_management page_man_{ *this };
	controls ctrls_{ *this };
	appearance apprnc_{ *this };
	dimensions dim_{ *this };
	bool& logged_in_;
	const string username_ = "User";
	const string password_ = "password";

	bool on_initialize(std::string& error) {
		ctrls_.allow_minimize(false);
		ctrls_.allow_resize(false);
		apprnc_.theme(themes::light);
		dim_.set_size({ 280, 320 });
		return true;
	}

	bool on_layout(string& error) override {
		auto& page = page_man_.add("home");

		widgets::image_view avatar(page, "avatar");
		avatar().rect.size(130, 130);
		avatar().rect.place({ margin_, page.size().width - margin_,
			margin_, margin_ + (dim_.get_size().height / 2.f) },
			50.f, 0.f);
		avatar().quality = image_quality::high;
		avatar().file = "images\\avatar.png";

		widgets::text_field username(page, "username");
		username().rect.snap_to(avatar().rect,
			rect::snap_type::bottom, 3.f * margin_);
		username().events().action = [&]() { on_login(); };

		widgets::password_field password(page, "password");
		password().rect.snap_to(username().rect,
			rect::snap_type::bottom, margin_);
		password().events().action = [&]() { on_login(); };

		widgets::button do_login(page);
		do_login().rect.snap_to(password().rect,
			rect::snap_type::bottom, 1.5f * margin_);
		do_login().text = "Login";
		do_login().events().action = [this]() { on_login(); };

		page_man_.show("home");
		return true;
	}

	void on_login() {
		try {
			auto& username = widgets::text_field::specs(*this, "home/username").text;
			auto& password = widgets::text_field::specs(*this, "home/password").text;

			if (username.empty() || password.empty())
				return;

			if (username == username_ && password == password_) {
				logged_in_ = true;
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
		logged_in_(logged_in) {}
};

int main() {
	bool logged_in = false;
	login login_("Login", logged_in);
	string error;
	if (login_.show(error)) {
		if (logged_in)
			login_.message("Login successful!");
	}
	else
		login_.message("Error: " + error);
	return 0;
}