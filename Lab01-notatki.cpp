#include <iostream>
// <---- Notatki z laborek --->
class String {
	size_t size;
	char* data;
public:
	String(): size(0), data(new char[1])
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

	String(const size_t size, const char c) : size(size), data(new char[size+1])
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


	size_t Size() const noexcept 
	{
		return size;
	}

	const char* c_str() const noexcept
	{
		return data;
	}
};
/*
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
}
*/