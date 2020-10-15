#include <iostream>
// <---- Notatki z laborek --->
class String {
	size_t size;
	char* data;
public:
	String() : size(0), data(new char[1])
	{
		data[0] = 0;
	}

	String(const char* const text)
	{
		if (text == nullptr)
		{
			size = 0;
			data = new char[1];
			data[0] = 0;
		}
		else
		{
			size = strlen(text);
			data = new char[size + 1];
			strcpy_s(data, size + 1, text);
		}
	}

	String(const size_t size, const char c) : size(size), data(new char[size + 1])
	{
		for (int i = 0; i < size; i++) data[i] = c;
		data[size] = 0;
	}

	String(const String& string) : size(string.size), data(new char[size + 1])
	{
		strcpy_s(data, size + 1, string.data);

	}

	String(String&& string) : size(string.size), data(string.data)
	{
		string.size = 0;
		string.data = new char[1];
		string.data[0] = 0;
	}

	~String() { // nie moze zglaszzac wyjatkow
		std::cout << "~String()" << std::endl;
		delete[] data;
	}

	String& operator = (const String &string) noexcept
	{
		if (this != &string)
		{
			delete[] data;
			size = string.size;
			data = new char[size + 1];
			strcpy_s(data, size + 1, string.data);
		}
		return *this;
	}

	String& operator = (const char* const text) noexcept
	{
		if (data != text)
		{
			delete[] data;
			size = text == nullptr ? 0 : strlen(text);
			data = new char[size + 1];
			strcpy_s(data, size + 1, text);
			data[size] = 0;
		}
		return *this;
	}

	String& operator ++() noexcept
	{
		for (int i = 0; i < size; i++) ++data[i];
		return *this;
	}

	String& operator --() noexcept
	{
		for (int i = 0; i < size; i++) --data[i];
		return *this;
	}

	String operator ++(int) noexcept //post przyjmuje int [konwencja]
	{
		String s(*this);
		for (int i = 0; i < size; i++) ++data[i];
		return s;
	}

	String operator --(int) noexcept //post przyjmuje int [konwencja]
	{
		String s(*this);
		for (int i = 0; i < size; i++) --data[i];
		return s;
	}

	bool operator ==(const String& string) const noexcept
	{
		if (this == &string) return true;
		if (size != string.size) return false;
		return strcmp(data, string.data) == 0;
	}

	bool operator ==(const char * const text) const noexcept
	{
		if (data == text) return true;
		return strcmp(data, text) == 0;
	}

	bool operator !=(const String& string) const noexcept
	{
		if (this == &string) return false;
		if (size != string.size) return true;
		return strcmp(data, string.data) != 0;
	}

	bool operator <(const String& string) const noexcept
	{
		if (this == &string) return false;
		return strcmp(data, string.data) < 0;
	}

	size_t Size() const noexcept
	{
		return size;
	}

	const char* c_str() const noexcept
	{
		return data;
	}

	char operator[] (const size_t index) 
	{
		if (index >= size) throw std::exception("niewlasciwy indeks");
		return data[index];
	}

	char& operator[] (const size_t index) const
	{
		if (index >= size) throw std::exception("niewlasciwy indeks");
		return data[index];
	}



	//Nieintuicyjne, lepiej robiæ to jawnie

	//operator const char* ()
	//{
	//	return data;
	//}
};
bool operator == (const char* const text, const String& string)
{
	if (text == string.c_str()) return true;
	return strcmp(text, string.c_str()) == 0;
}

int main()
{
	String s(20, '%');
	std::cout << s.c_str() << std::endl << "Size " << s.Size() << std::endl;
	String s2(s);
	std::cout << s2.c_str() << std::endl << "Size " << s2.Size() << std::endl;
	String s3(std::move(s));
	std::cout << "<------------------------------------------>\n";
	std::cout << s3.c_str() << std::endl <<"Size " << s3.Size() << std::endl;
	std::cout << s.c_str() << std::endl << "Size " << s.Size() << std::endl;

	std::cout << "<---------------------------------------------------------------------->\n";
	String s4 = s2;//konstruktor kopiuj¹cy
	std::cout << s4.c_str() << std::endl << "Size " << s4.Size() << std::endl;

	s4 = s2;// operator przeniesienia
	std::cout << s4.c_str() << std::endl << "Size " << s4.Size() << std::endl;

	s4 = "bcd";
	s4--;
	std::cout << s4.c_str() << std::endl << "Size " << s4.Size() << std::endl;

	if (s4 == "abc") std::cout << "s4 == abc\n";
	else std::cout << "s4 != abc\n";

	if (s4 < s3) std::cout << "s4 < s3\n";
	else std::cout << "s4 >= s3\n";


}
