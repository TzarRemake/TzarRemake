/*
* TzarRemake
* Copyright (C) 2018
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceManager::load - Failed to load "
		+ filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second); // assert if insertion didn't happen (for example if id is already in ResourceMpa)
}

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::add(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second); // assert if insertion didn't happen (for example if id is already in ResourceMpa)
}

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceManager::load - Failed to load "
		+ filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second); // assert if insertion didn't happen (for example if id is already in ResourceMpa)
}

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end()); // assert if resource id is not found in ResourceMpa
	return *found->second;
}

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end()); // assert if resource id is not found in ResourceMpa
	return *found->second;
}

//--------------------------------------------------------------------------

template <typename Resource, typename Identifier>
Resource * ResourceManager<Resource, Identifier>::getPtr(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end()); // assert if resource id is not found in ResourceMpa
	return found->second.get();
}