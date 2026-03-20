#include <tuple>

#include <RmlSolLua_private.h>
#include <RmlUi/Core.h>
#include SOLHPP

namespace Rml::SolLua
{

	using ColourbTuple = std::tuple<Rml::byte, Rml::byte, Rml::byte, Rml::byte>;
	using ColourfTuple = std::tuple<float, float, float, float>;

	template <typename T, int Alpha, bool PremultipliedAlpha>
	std::tuple<T, T, T, T> getRGBA(Rml::Colour<T, Alpha, PremultipliedAlpha>& self)
	{
		return std::tuple<T, T, T, T>(self.red, self.green, self.blue, self.alpha);
	}

	template <typename T, int Alpha, bool PremultipliedAlpha>
	void setRGBA(Rml::Colour<T, Alpha, PremultipliedAlpha>& self, std::tuple<T, T, T, T> color)
	{
		sol::tie(self.red, self.green, self.blue, self.alpha) = color;
	}

	void bind_color(sol::state_view& lua)
	{
		// clang-format off
		lua.new_usertype<Rml::Colourb>("Colourb", sol::constructors<Rml::Colourb(), Rml::Colourb(Rml::byte, Rml::byte, Rml::byte), Rml::Colourb(Rml::byte, Rml::byte, Rml::byte, Rml::byte)>(),
			// O
			sol::meta_function::addition, &Rml::Colourb::operator+,
			sol::meta_function::subtraction, &Rml::Colourb::operator-,
			sol::meta_function::multiplication, &Rml::Colourb::operator*,
			sol::meta_function::division, &Rml::Colourb::operator/,
			sol::meta_function::equal_to, &Rml::Colourb::operator==,

			// G+S
			"red", sol::property([](Rml::Colourb& self) { return self.red; }, [](Rml::Colourb& self, Rml::byte v) { self.red = v; }),
			"green", sol::property([](Rml::Colourb& self) { return self.green; }, [](Rml::Colourb& self, Rml::byte v) { self.green = v; }),
			"blue", sol::property([](Rml::Colourb& self) { return self.blue; }, [](Rml::Colourb& self, Rml::byte v) { self.blue = v; }),
			"alpha", sol::property([](Rml::Colourb& self) { return self.alpha; }, [](Rml::Colourb& self, Rml::byte v) { self.alpha = v; }),
			"rgba", sol::property(static_cast<ColourbTuple(*)(Rml::Colourb&)>(&getRGBA), static_cast<void(*)(Rml::Colourb&, ColourbTuple)>(&setRGBA))
		);

		lua.new_usertype<Rml::Colourf>("Colourf", sol::constructors<Rml::Colourf(), Rml::Colourf(float, float, float), Rml::Colourf(float, float, float, float)>(),
			// O
			sol::meta_function::addition, &Rml::Colourf::operator+,
			sol::meta_function::subtraction, &Rml::Colourf::operator-,
			sol::meta_function::multiplication, &Rml::Colourf::operator*,
			sol::meta_function::division, &Rml::Colourf::operator/,
			sol::meta_function::equal_to, &Rml::Colourf::operator==,

			// G+S
			"red", sol::property([](Rml::Colourf& self) { return self.red; }, [](Rml::Colourf& self, float v) { self.red = v; }),
			"green", sol::property([](Rml::Colourf& self) { return self.green; }, [](Rml::Colourf& self, float v) { self.green = v; }),
			"blue", sol::property([](Rml::Colourf& self) { return self.blue; }, [](Rml::Colourf& self, float v) { self.blue = v; }),
			"alpha", sol::property([](Rml::Colourf& self) { return self.alpha; }, [](Rml::Colourf& self, float v) { self.alpha = v; }),
			"rgba", sol::property(static_cast<ColourfTuple(*)(Rml::Colourf&)>(&getRGBA), static_cast<void(*)(Rml::Colourf&, ColourfTuple)>(&setRGBA))
		);
		// clang-format on
	}

} // end namespace Rml::SolLua
