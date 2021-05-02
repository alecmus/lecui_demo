#include <liblec/lecui/controls.h>
#include <liblec/lecui/appearance.h>
#include <liblec/lecui/containers/page.h>
#include <liblec/lecui/widgets/label.h>
#include <liblec/lecui/widgets/text_field.h>
#include <liblec/lecui/widgets/password_field.h>
#include <liblec/lecui/widgets/button.h>
#include <liblec/lecui/widgets/image_view.h>
using namespace liblec;

class login : public lecui::form {
	const float margin_ = 10.f;
	lecui::page_management page_man_{ *this };
	lecui::controls ctrls_{ *this };
	lecui::appearance apprnc_{ *this };
	lecui::dimensions dim_{ *this };
	bool& logged_in_;
	const std::string username_ = "User";
	const std::string password_ = "password";

public:
	login(const std::string& caption, bool& logged_in) :
		lecui::form(caption),
		logged_in_(logged_in) {}

	bool on_layout(std::string& error) override {
		ctrls_.minimize(false);
		ctrls_.resize(false);
		apprnc_.theme(lecui::themes::light);
		dim_.size({ 350, 400 });

		auto& page = page_man_.add("home");

		lecui::widgets::image_view avatar(page, "avatar");
		avatar().rect.place({ margin_, page.size().width - margin_,
			margin_, margin_ + (dim_.size().height / 2.f) },
			50.f, 0.f);
		avatar().file = "images\\avatar.png";

		lecui::widgets::text_field username(page, "username");
		username().rect.snap_to(avatar().rect,
			lecui::rect::snap_type::bottom, 3.f * margin_);
		username().events().action = [&]() { on_login(); };

		lecui::widgets::password_field password(page, "password");
		password().rect.snap_to(username().rect,
			lecui::rect::snap_type::bottom, margin_);
		password().events().action = [&]() { on_login(); };

		lecui::widgets::button do_login(page);
		do_login().rect.snap_to(password().rect,
			lecui::rect::snap_type::bottom, 1.5f * margin_);
		do_login().text = "Login";
		do_login().events().click = [this]() { on_login(); };

		page_man_.show("home");
		return true;
	}

	void on_login() {
		try {
			auto& username = lecui::widgets::text_field::specs(*this, "home/username").text;
			auto& password = lecui::widgets::text_field::specs(*this, "home/password").text;

			if (username.empty() || password.empty())
				return;

			if (username == username_ && password == password_) {
				logged_in_ = true;
				close();
			}
			else
				message("Wrong username or password");
		}
		catch (const std::exception& e) { message("Error: " + std::string(e.what())); }
	}
};

int main() {
	bool logged_in = false;
	login login_("Login", logged_in);
	std::string error;
	if (login_.show(error)) {
		if (logged_in)
			login_.message("Login successful!");
	}
	else
		login_.message("Error: " + error);
	return 0;
}