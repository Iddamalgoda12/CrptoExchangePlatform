#include <iostream>
#include <vector>
#include <string>




std::vector<std::string> tokenise(std::string csvLine, char seperator)
{
	std::vector<std::string> tokens;
	std::string token;
	signed int start, end;
	start = csvLine.find_first_not_of(seperator, 0);
	do
	{
		end = csvLine.find_first_of(seperator, start);

		if (start == csvLine.length() || start == end) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);

		tokens.push_back(token);
		start = end + 1;

	} 
	while (end>0);

	return tokens;
}




int main()
{
	std::vector<std::string> tokenizedTokens;
	std::string s = "i am,piyuma,21 years old,learning oop";
	tokenizedTokens = tokenise(s, ',');

	for (const std::string& s : tokenizedTokens)
	{
		std::cout << s << std::endl;
	}

	return 0;
}