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

#pragma once

//--------------------------------------------------------------------------

#include <map>
#include <memory>

//--------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------

namespace tls
{
	/*!
	* \brief ID of texture
	*/
	enum class TextureID
	{
		MAIN_MENU_BACK,	///< background of main menu
		MAIN_MENU_BTN,  ///< buttons of main menu
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief ID of font
	*/
	enum FontID
	{
		FONT_NULL,
		FONT_TAHOMA,
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief ID of shader
	*/
	enum ShaderID
	{
		SHADER_NULL,
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief Resource manager class
	*/
	template <typename Resource, typename Identifier>
	class ResourceManager
	{
	public:
		size_t size(){ return mResourceMap.size(); } ///< Return amount of maped resources in resource holder

		/*
		* \brief Load resource to resource map
		*/
		void load(Identifier id, const std::string& filename);

		/*
		* \brief Add resource to resource map
		*/
		void add(Identifier id, std::unique_ptr<Resource> resource);

		/*
		* \brief Load resource with additional parameter
		*/
		template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& secondParam);

		/*
		* \brief Return reference to resource indicated by id
		*/
		Resource& get(Identifier id);

		/*
		* \brief Return const reference to resource indicated by id
		*/
		const Resource& get(Identifier id) const;

		/*
		* \brief Return pointer to resource indicated by id
		*/
		Resource * getPtr(Identifier id);

	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;	///< this container hold all avalaible resources

	};
	#include "ResourceManager.inl"

}

//--------------------------------------------------------------------------

typedef tls::ResourceManager<sf::Texture, tls::TextureID> TextureHolder;
typedef tls::ResourceManager<sf::Font, tls::FontID> FontHolder;
typedef tls::ResourceManager<sf::Shader, tls::ShaderID> ShaderHolder;
