#include <string>
namespace json {

	// declaring here so we can define later 
	bool isNumber(std::string input);

	// the json object which can be loaded from string and turned into string
	class JsonObj
	{
	public:
		std::string *key;
		std::string *value;
		// json shouldn't be used as database, but we'll allow going up to ~9billion elements
		long long int size = 0;

		// this string should be cleared very often as possible and never be used for anything
		// this string is only used as stuff that we can't route anywhere else, like if an index is out of range but we don't want to crash the program
		std::string voided;

		// set size to n_size and change accordingly
		int setSize(long long int n_size)
		{
			delete[] key;
			delete[] value;
			size = n_size;
			key = new std::string[n_size];
			value = new std::string[n_size];
			return 0;
		}

		// turn object into string
		std::string toString()
		{
			std::string returnData;
			returnData += '{';
			for (long long int i = 0; i < size; i++)
			{
				// {"key":'h'}
				returnData += '"';
				returnData += key[i];
				returnData += "\":";

				if (isNumber(value[i]))
				{
					// how we gonna do the values??
					returnData += value[i];
				}
				else
				{
					returnData += '"';
					returnData += value[i];
					returnData += '"';
				}
				returnData += ',';
			}
			returnData[returnData.size() - 1] = '}';

			return returnData;
		}

		// load from string
		int fromString(std::string input)
		{
			// this won't be easy
			int currentIndex = 0;
			int jsonIndex = 0;
			for (long long int i = 0; i < input.size(); i++)
			{
				// check for contents of object
				// i'm trying to make this function non recursive, and have plans
				
				// start of string, this is probably the index
				if (input[i] == '"'){
					i++;
					while (input[i] != '"' || input[i-1] == '\\'){
						key[currentIndex] += input[i];
						i++;
					}
					// we got first part now the hard stuff
					// skip the : character
					i+=2;
					// we need to check if integer, string, or object
					if (input[i] == '"'){
						// is string
						i++;
						while (input[i] != '"' || input[i - 1] == '\\')
						{
							value[currentIndex] += input[i];
							i++;
						}
					}

					// is json
					else if (input[i] == '{')
					{
						i++;
						jsonIndex++;
						while (jsonIndex > 0){
							if (input[i] == '{')
								jsonIndex++;
							else if (input[i] == '}')
								jsonIndex--;
							value[currentIndex] += input[i];
							i++;
						}
						value[currentIndex][value[currentIndex].size() - 1] = ' ';
					}

					// is num
					else {
						
						while (input[i] != ',' && input[i] != '}')
						{
							value[currentIndex] += input[i];
							i++;
						}
					}
					currentIndex++;
				}
			}

			return 0;
		}

		// custom constructors
		JsonObj()
		{

			// ALWAYS use new when initializing, never initialize without new
			// we use new so we can always use delete[] later
			key = new std::string[5];
			value = new std::string[5];
			size = 5;
		}

		// custom operators

		// acces opperator Jsonobj['h']; etcetera
		// access value with string
		std::string &operator[](std::string &n_key)
		{
			for (int i = 0; i < size; i++)
			{
				if (key[i] == n_key)
				{
					return value[i];
				}
			}

			// when 0 gets returned, program is kinda failed, \0
			return voided;
		}
		std::string &operator[](char *n_key)
		{
			for (int i = 0; i < size; i++)
			{
				if (key[i] == n_key)
				{
					return value[i];
				}
			}

			// when 0 gets returned, program is kinda failed, \0
			return voided;
		}
		std::string &operator[](int n_keyID)
		{
			// if size > keyid return value[keyID], else return 0 because we don't want segfaults
			return size > n_keyID ? value[n_keyID] : voided;
		}
	};

	bool isNumber(std::string input)
	{
		for (int i = 0; i < input.size(); i++)
		{
			// if not a decimal cipher
			if (!(input[i] >= '0' && input[i] <= '9'))
			{
				return false;
			}
		}
		// else return true
		return true;
	}
}

