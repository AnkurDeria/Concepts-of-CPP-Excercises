#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <map>

// TODO create implementation here!

bool add(contact_list::storage& contacts, std::string_view name, contact_list::number_t number)
{
	if (name.empty())
		return false;
	if (number < 0)
		return false;
	if (std::find(contacts.names.begin(), contacts.names.end(), static_cast<std::string>(name)) != contacts.names.end())
		return false;
	contacts.names.push_back(static_cast<std::string>(name));
	contacts.numbers.push_back(number);
	return true;
}

contact_list::number_t get_number_by_name(contact_list::storage& contacts, std::string_view name)
{
	const auto ret = std::find(
		contacts.names.begin(), contacts.names.end(), static_cast<std::string>(name));
	if (ret != contacts.names.end())
		return contacts.numbers[ret - contacts.names.begin()];
	return -1;
}

std::string to_string(const contact_list::storage& contacts)
{
	std::string result;
	for (int i = 0; i < contacts.names.size(); i++)
	{
		result += contacts.names[i] + "-" + std::to_string(contacts.numbers[i]) + "\n";
	}
	return result;
}

bool remove(contact_list::storage& contacts, std::string_view name)
{
	if (name.empty())
		return false;

	for(int i = 0; i < contacts.names.size(); i++)
	{
		if(name.compare(contacts.names[i]) == 0)
		{
			contacts.names.erase(contacts.names.begin() + i);
			contacts.numbers.erase(contacts.numbers.begin() + i);
			return true;
		}
	}
	return false;
}

void sort(contact_list::storage& contacts)
{
	std::map<std::string, int> dict_contacts;
	for(int i = 0; i < contacts.names.size(); i++)
	{
		dict_contacts.try_emplace(contacts.names[i], contacts.numbers[i]);
	}
	contacts.names.clear();
	contacts.numbers.clear();
	for (const auto& [name, number]:dict_contacts)
	{
		contacts.names.push_back(name);
		contacts.numbers.push_back(number);
	}
}

std::string get_name_by_number(contact_list::storage& contacts, contact_list::number_t number)
{
	if (const auto ret = std::find(contacts.numbers.begin(), contacts.numbers.end(), number); ret != contacts.numbers.end())
		return contacts.names[ret - contacts.numbers.begin()];
	return "";
}

size_t size(const contact_list::storage& contacts)
{
	return contacts.names.size();
}
